// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      TauRerunTester
// 
/**\class TauRerunTester TauRerunTester.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/TauRerunTester.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Tue, 15 Oct 2019 20:39:49 GMT
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
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/PATTauDiscriminator.h"


#include "RecoTauTag/RecoTau/interface/PFRecoTauClusterVariables.h"
#include "DataFormats/PatCandidates/interface/Muon.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
#include "TH2D.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/TauPFSpecific.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"



//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TauRerunTester : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TauRerunTester(const edm::ParameterSet&);
      ~TauRerunTester();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------

//
// constants, enums and typedefs
//

edm::EDGetTokenT<pat::TauCollection> TauSrc_;
edm::EDGetTokenT<pat::TauCollection> TauUnCleanedSrc_;




  TH1D* Pt;
  TH1D* Pt_u;
  
  TH2D* Pt2D;
  TH2D* Pt2D_o;
  
  TH2D* Eta2D;
  TH2D* Eta2D_o;
  
  TH2D* Phi2D;
  TH2D* Phi2D_o;
  
  TH2D* chargedIsoPtSum;
  TH2D* chargedIsoPtSum_o;

};


//
// static data member definitions
//

//
// constructors and destructor
//
TauRerunTester::TauRerunTester(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  TauUnCleanedSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("TausUnCleaned")))
  

{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;
   
   Pt= f->make<TH1D>("Pt",";Pt_{Tau}(GeV);#entries",50,0,50);
   Pt_u= f->make<TH1D>("Pt_UnCleaned",";Pt_{Tau UnCleaned}(GeV);#entries",50,0,50);




   Pt2D = f->make<TH2D>("Pt2D",";Pt_{Tau UnCleaned}(GeV);Pt_{Tau}(GeV)",50,0,50,50,0,50);
   Pt2D_o = f->make<TH2D>("Pt2D Same Collection",";Pt_{Tau}(GeV);Pt_{Tau}(GeV)",50,0,50,50,0,50);

   Eta2D = f->make<TH2D>("Eta2D",";#eta_{Tau UnCleaned};#eta_{Tau}",100,-5,5,100,-5,5);
   Eta2D_o = f->make<TH2D>("Eta2D Same Collection",";#eta_{Tau};#eta_{Tau}",100,-5,5,100,-5,5);

   
   Phi2D = f->make<TH2D>("Phi2D",";#phi_{Tau UnCleaned};#phi_{Tau}",100,-5,5,100,-5,5);
   Phi2D_o = f->make<TH2D>("Phi2D Same Collection",";#phi_{Tau}(GeV);#phi_{Tau}",100,-5,5,100,-5,5);

   chargedIsoPtSum = f->make<TH2D>("chargedIsoPtSum",";ChargedIsoPtSum_{Tau UnCleaned}(GeV);ChargedIsoPtSum_{Tau}(GeV)",50,0,50,50,0,50);
   chargedIsoPtSum_o = f->make<TH2D>("chargedIsoPtSum Same Collection",";ChargedIsoPtSum_{Tau}(GeV);ChargedIsoPtSum_{Tau}(GeV)",50,0,50,50,0,50);

}


TauRerunTester::~TauRerunTester()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TauRerunTester::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  
  Handle<pat::TauCollection> Taus;
  iEvent.getByToken(TauSrc_,Taus);
  
  Handle<pat::TauCollection> TausUnCleaned;
  iEvent.getByToken(TauUnCleanedSrc_,TausUnCleaned);
  
  int idx=0;
  int idx2=0;
  
  vector<pat::Tau>TausSlimmed;
  vector<pat::Tau>TausSlimmedUnCleaned;
  
   
  
  for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau,++idx)
    {                                                                                                                                                                                                                                                                         
      TausSlimmed.push_back(*itau);
      Pt->Fill(itau->pt());
    }
  
  for(pat::TauCollection::const_iterator itau_u = TausUnCleaned->begin() ; itau_u !=TausUnCleaned->end() ; ++itau_u,++idx2)                                                                                                                                                       
    {  
      
      TausSlimmedUnCleaned.push_back(*itau_u);
      Pt_u->Fill(itau_u->pt());
      
    }
  
   
  for(unsigned i=0;i< /*TausSlimmedUnCleaned.size()*/ TausSlimmed.size() ;i++)

    {
    // Pt2D->Fill(itau_u->pt(),itau->pt());                                                                                               
   // //Pt2D->Fill(Taus[idx].pt(),TausUnCleaned[idx].pt());                                                                                                                                
      Pt2D->Fill(TausSlimmedUnCleaned[i].pt(),TausSlimmed[i].pt());  
      Pt2D->SetOption("COLZ");
   
   // Eta2D->Fill(itau_u->eta(),itau->eta());
      Eta2D->Fill(TausSlimmedUnCleaned[i].eta(),TausSlimmed[i].eta()); 
      Eta2D->SetOption("COLZ");
   
      // Phi2D->Fill(itau_u->phi(),itau->phi());
      Phi2D->Fill(TausSlimmedUnCleaned[i].phi(),TausSlimmed[i].phi());
      Phi2D->SetOption("COLZ");                                                                                                                                                                                                                                                   
      chargedIsoPtSum->Fill(TausSlimmedUnCleaned[i].tauID("chargedIsoPtSum"),TausSlimmed[i].tauID("chargedIsoPtSum"));
      chargedIsoPtSum->SetOption("COLZ");


    }

  
  //for(unsigned i=0;i<TausSlimmedUnCleaned.size() ;i++)

    //{
    
  for(unsigned i=0;i<TausSlimmed.size() && i<TausSlimmed.size() ;i++)
  	{
 	 
  	  // Pt2D_o->Fill(itau_o->pt(),itau->pt());
          
  	  Pt2D_o->Fill(TausSlimmed[i].pt(),TausSlimmed[i].pt()); 
  	  Pt2D_o->SetOption("COLZ");
	   
  	  // Eta2D_o->Fill(itau_o->eta(),itau->eta())
  	  Eta2D_o->Fill(TausSlimmed[i].eta(),TausSlimmed[i].eta());
  	  Eta2D_o->SetOption("COLZ");

  	  // Phi2D_o->Fill(itau_o->phi(),itau->phi());
  	  Phi2D_o->Fill(TausSlimmed[i].phi(),TausSlimmed[i].phi());
  	  Phi2D_o->SetOption("COLZ");   
  	
	  chargedIsoPtSum_o->Fill(TausSlimmed[i].tauID("chargedIsoPtSum"),TausSlimmed[i].tauID("chargedIsoPtSum"));
	  chargedIsoPtSum_o->SetOption("COLZ");

	}
      //}
                                                                   

   /*#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
   */
    }


// ------------ method called once each job just before starting event loop  ------------
void 
TauRerunTester::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauRerunTester::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TauRerunTester::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TauRerunTester);
