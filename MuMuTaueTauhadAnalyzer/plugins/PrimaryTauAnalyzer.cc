// -*- C++ -*-
//
// Package:    GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer
// Class:      PrimaryTauAnalyzer
// 
/**\class PrimaryTauAnalyzer PrimaryTauAnalyzer.cc GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer/plugins/PrimaryTauAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Thu, 11 Apr 2019 10:37:20 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1.h"
#include "TH2.h"

#include"DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PATObject.h"

typedef math::XYZPoint Point;

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class PrimaryTauAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit PrimaryTauAnalyzer(const edm::ParameterSet&);
      ~PrimaryTauAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;
  edm::EDGetTokenT<reco::VertexCollection> vtx_;
  TH1D *PtNoIso;
  TH1D *PtFullNoIso;
  TH1D *PtIso;
  TH1D *PtFullIso;
  TH1D *Pt;
  TH1D *PtNot;
  TH1D *PtCut;
  TH1D *PtFullCut;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
PrimaryTauAnalyzer::PrimaryTauAnalyzer(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  vtx_ (consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertex")))
  
  
{
   //now do what ever initialization is needed
   //usesResource("TFileService");
   usesResource("TFileService");
   edm::Service<TFileService> fl;
   PtNoIso = fl->make<TH1D>("PtNoIso" , "Pt of Highest Pt Tau before Medium Isolation" , 150 ,0 ,150 );
   PtFullNoIso = fl->make<TH1D>("PtFullNoIso" , "Pt of Taus before Meduim Isolation but with DecayMode and Impact paramenter cuts" , 150 ,0 ,150 );
   PtIso =fl->make<TH1D>("PtIso" , "Pt of Highest Pt Tau after Medium Isolation" , 150 ,0 , 150 );
   PtFullIso = fl->make<TH1D>("PtFullIso" , "Pt of Taus after Medium Isolation" , 150 ,0 ,150 );
   Pt=fl->make<TH1D>("Pt" , "Pt of Taus in every event" , 150 ,0 , 150 );
   PtNot=fl->make<TH1D>("PtNot" , "Pt of Taus Highest pt in every event" , 150 ,0 , 150 );
   PtCut=fl->make<TH1D>("PtCut" , "Pt of Taus Highest pt after Medium Isolation and pt eta Cut" , 150 ,0 , 150 );
   PtFullCut=fl->make<TH1D>("PtFullCut" , "Pt of Taus after Medium Isolation and pt eta Cut" , 150 ,0 , 150 );

   
}


PrimaryTauAnalyzer::~PrimaryTauAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
PrimaryTauAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   Handle<pat::TauCollection> Taus;
   iEvent.getByToken(TauSrc_,Taus);
   
   Handle<reco::VertexCollection> Vertex;
   iEvent.getByToken(vtx_,Vertex);
   //cout<<"Bloop"<<endl; 
   const reco::Vertex& pv=*Vertex->begin();
   Point p;
   //math::XYZPointF p2;
   //math::XYZPointF p3;
   p=pv.position();
   // cout<<"Bleep"<<endl;
                                                                                                                                                                                                                                                                               
   double dz_tau;
   double dxy_tau;

   
   vector<pat::Tau>SelectedTaus;
   vector<pat::Tau>SelectedIsoTaus;
   vector<pat::Tau>SelectedCutTaus;
   double No_Iso_Pt=99999;
   double Iso_Pt=99999;
   double Cut_Pt=99999;
   bool NonEmpty=false;
   //int Highcount=0; 
   //bool Pass=false;
   NonEmpty=((Taus->size()) > 0);
   pat::Tau MaxTauNoIso;
   double Max_Tau_Pt=0;

   
   if(NonEmpty)
     {
   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)

     {
       //cout<<"0"<<endl;
       pat::PackedCandidate const* packedLeadTauCand = dynamic_cast<pat::PackedCandidate const*>(itau->leadChargedHadrCand().get());
       //pat::PackedCandidate packedLeadTauCand = itau->leadChargedHadrCand().get();
       //cout<<"Ref"<<endl;
       //cout<<"Ref_PrimatyTau.cc_: "<<itau->leadChargedHadrCand().get();
       //p2= itau->primaryVertexPos();
       //cout<<"1"<<endl;
       dz_tau=packedLeadTauCand->dz(p);
       dxy_tau=packedLeadTauCand->dxy(p);
       //-----------------------------Workaround for now------------------//
       //dz_tau=abs(p.z()-p2.z());
       //dxy_tau=itau->dxy();
       //cout<<"d_xy__PrimarTauAnalyzer__: "<< dxy_tau <<endl;
       //cout<<"d_z__PrimaryTauAnalyzer__: "<<dz_tau<<endl;
       //cout<<"2"<<endl;
       Pt->Fill(itau->pt());
       if( (itau->tauID("decayModeFinding")) && (dxy_tau<0.2) && (dz_tau < 0.5) )

	 {
	   /*if(itau->pt() > Max_Tau_Pt)
	     {
	       cout<<" happened" <<endl;
	       Max_Tau_Pt=itau->pt();
	       MaxTauNoIso=(*itau);
	     }*/
	   SelectedTaus.push_back(*itau);
	   PtFullNoIso->Fill(itau->pt());
	 }
     }
   //cout<<" Pt of Tau No Iso: " <<MaxTauNoIso.pt()<<endl;;
   //No_Iso_Pt=MaxTauNoIso.pt();
   //PtNoIso->Fill(No_Iso_Pt);
   
   //}
   
   for(unsigned i=0;i<SelectedTaus.size();i++)
     
     {
       
       if(SelectedTaus[i].pt() > Max_Tau_Pt)
	 
	 {
	   //++Highcount;
	   
	   Max_Tau_Pt=SelectedTaus[i].pt();
	   MaxTauNoIso=SelectedTaus[i];
	 }
       
     }
   No_Iso_Pt=MaxTauNoIso.pt();                                                                                                                                                                                                                                            
   if(SelectedTaus.size() > 0)
     {
       PtNoIso->Fill(No_Iso_Pt);  
     }
   
     }
   
   pat::Tau MaxTauIso;
   double Max_Tau_Pt_Iso=0;
   pat::Tau MaxCutTau;
   double Max_Tau_Cut=0;
       if(NonEmpty)
	 {
       for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)

	 {
	   pat::PackedCandidate const* packedLeadTauCand = dynamic_cast<pat::PackedCandidate const*>(itau->leadChargedHadrCand().get());
	   dz_tau=packedLeadTauCand->dz(p);
	   dxy_tau=packedLeadTauCand->dxy(p);
	   //-----Workaround for now--------------//
	   //p3= itau->primaryVertexPos();

	   //dxy_tau=itau->dxy();
	   //dz_tau=abs(p.z()-p3.z());

	   if( (itau->tauID("decayModeFinding")) && (itau->tauID("byIsolationMVArun2v1DBoldDMwLTraw") >-0.5) && (itau->tauID("byMediumIsolationMVArun2v1DBoldDMwLT"))  && (dxy_tau<0.2) && (dz_tau < 0.5) )
	     
	     {
	       /*if(itau->pt() > Max_Tau_Pt_Iso)
		 {
		 Max_Tau_Pt_Iso=itau->pt();
		 MaxTauIso=(*itau);
		 }*/
	       
	       SelectedIsoTaus.push_back(*itau);
	       PtFullIso->Fill(itau->pt());
	       if((itau->pt() > 10) && (abs(itau->eta()) < 2.3) )
		 {
		   SelectedCutTaus.push_back(*itau);
		   PtFullCut->Fill(itau->pt());
		 }

	     
	     }
	   
	 }
       //Iso_Pt=MaxTauIso.pt();
       //PtIso->Fill(Iso_Pt);
       
       for(unsigned i=0;i<SelectedIsoTaus.size();i++)
	 
	 {
	   
	   if(SelectedIsoTaus[i].pt() > Max_Tau_Pt_Iso)
	     
	     {
	       //++Highcount;                                                                                                                                                                                                                                                      
	       
	       Max_Tau_Pt_Iso=SelectedIsoTaus[i].pt();
	       MaxTauIso=SelectedIsoTaus[i];
	     }
	 }
       Iso_Pt=MaxTauIso.pt();
       if(SelectedIsoTaus.size() > 0)
	 {
	   PtIso->Fill(Iso_Pt); 
	 }
       
       for(unsigned i=0;i<SelectedCutTaus.size();i++)

         {
	   if(SelectedCutTaus[i].pt() > Max_Tau_Cut)
	     {
	       Max_Tau_Cut=SelectedCutTaus[i].pt();
               MaxCutTau=SelectedCutTaus[i];
	     }
	 }
       Cut_Pt=MaxCutTau.pt();
       if(SelectedCutTaus.size()> 0)
       
	 {
	   PtCut->Fill(Cut_Pt);
	 }
	 }
       
       
       
       



       
       pat::Tau MaxTau;
       double Max_Pt=0;
       
       if(NonEmpty)
         {
	   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)

	     {
	       if(itau->pt() > Max_Pt)
                 {
                   Max_Pt=itau->pt();
                   MaxTau=(*itau);
                 }


	     }
	   PtNot->Fill(MaxTau.pt());
	 }
   /*/#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif*/
}

// ------------ method called once each job just before starting event loop  ------------
void 
PrimaryTauAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PrimaryTauAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PrimaryTauAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PrimaryTauAnalyzer);
