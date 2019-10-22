// -*- C++ -*-
//
// Package:    GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer
// Class:      PrimaryMuonAnalyzer
// 
/**\class PrimaryMuonAnalyzer PrimaryMuonAnalyzer.cc GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer/plugins/PrimaryMuonAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Thu, 11 Apr 2019 04:40:39 GMT
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
#include "DataFormats/PatCandidates/interface/PATObject.h"

#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1.h"
#include "TH2.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "TLatex.h"


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class PrimaryMuonAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit PrimaryMuonAnalyzer(const edm::ParameterSet&);
      ~PrimaryMuonAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<pat::MuonCollection> muonSrc_;



  TH1D *HighPtPreIdIso;
  TH1D *SemiHighPtPreIdIso;
  TH1D *HighPtPostIdPreIso;
  TH1D *SemiHighPtPostIdPreIso;
  TH1D *HighPtPostIdIso;
  TH1D *SemiHighPtPostIdIso;

  


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
PrimaryMuonAnalyzer::PrimaryMuonAnalyzer(const edm::ParameterSet& iConfig):
  muonSrc_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonSrc")))


{
   //now do what ever initialization is needed
  usesResource("TFileService");
  edm::Service<TFileService> fl;
  HighPtPreIdIso = fl->make<TH1D>("HighPtPreIdIso" , "Pt of Highest Pt Muon before Loose ID and Isolation" , 150 , -0.5,149.5 );
  SemiHighPtPreIdIso = fl->make<TH1D>("SemiHighPtPreIdIso" , "Pt of Second Highest Pt Muon before Loose ID and Isolation" , 150 , -0.5,149.5 );
  HighPtPostIdPreIso = fl->make<TH1D>("HighPtPostIdPreIso" , "Pt of Highest Pt Muon after Loose ID and before Isolation" , 150 , -0.5,149.5 );
  SemiHighPtPostIdPreIso = fl->make<TH1D>("SemiHighPtPostIdPreIso" , "Pt of Highest Pt Muon after Loose ID and before Isolation" , 150 , -0.5,149.5 );
  HighPtPostIdIso= fl->make<TH1D>("HighPtPostIdIso" , "Pt of Highest Pt Muon after Loose ID and Isolation" , 150 , -0.5,149.5 );
  SemiHighPtPostIdIso=  fl->make<TH1D>("SemiHighPtPostIdIso" , "Pt of Second Highest Pt Muon after Loose ID and Isolation" , 150 , -0.5,149.5 );



}


PrimaryMuonAnalyzer::~PrimaryMuonAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
PrimaryMuonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace pat;
   using namespace reco;
   using namespace std;
  
   
   Handle<pat::MuonCollection> Muons;
   iEvent.getByToken(muonSrc_,Muons);
   
   int iMuon_Id=0;
   double max_pt_Muon=0;
   
   double MaxPt=99999;
   double SecondPt=99999;
   
   pat::Muon MaxMuon;
   pat::Muon SecondMuon;
   
   double LooseMaxPt=99999;
   double LooseSecondPt=99999;
   
   
   double sub_pt_Muon=0;
   bool Loose=0;
    
   for(pat::MuonCollection::const_iterator iMuon = Muons->begin() ; iMuon !=Muons->end();++iMuon,++iMuon_Id)
     {
       //cout<< "  Muon: " <<  iMuon_Id  << " pt: " << iMuon->pt() << "  eta: " << iMuon->eta()<< endl; 
       //reco::MuonPFIsolation iso = iMuon->pfIsolationR04();
       //reliso = (iso.sumChargedHadronPt+TMath::Max(0.,iso.sumNeutralHadronEt+iso.sumPhotonEt-0.5*iso.sumPUPt))/iMuon->pt();
       //Loose=muon::isLooseMuon(*iMuon);

       

       

       if(iMuon->pt() > max_pt_Muon)
	 {
	   max_pt_Muon=iMuon->pt();
	   MaxMuon=(*iMuon);
	   
	 }
       //cout<< " MaxPt: " << MaxMuon.pt() <<endl;
       
       
       if((iMuon->pt() < MaxMuon.pt()) && (iMuon->pt() > sub_pt_Muon))
	 {
	   sub_pt_Muon=iMuon->pt();
	   SecondMuon=(*iMuon);

	 }
       //cout<< "SecondMaxPt: "<<SecondMuon.pt() <<endl;
       
       
       if(iMuon->pt() > max_pt_Muon)
         {
           max_pt_Muon=iMuon->pt();
           MaxMuon=(*iMuon);

         }
       
     }
   MaxPt=MaxMuon.pt();
   HighPtPreIdIso->Fill(MaxPt);
   SecondPt=SecondMuon.pt();
   SemiHighPtPreIdIso->Fill(SecondPt);
   
   pat::Muon LooseMaxMuon;
   pat::Muon LooseSecondMuon;
   double Loose_max_pt_Muon=0;
   double Loose_sub_pt_Muon=0;
   for(pat::MuonCollection::const_iterator iMuon = Muons->begin() ; iMuon !=Muons->end();++iMuon,++iMuon_Id)
     {

       Loose=muon::isLooseMuon(*iMuon);   
       if(Loose)
	 {
       if(iMuon->pt() > Loose_max_pt_Muon)
         {
           Loose_max_pt_Muon=iMuon->pt();
           LooseMaxMuon=(*iMuon);

         }
       if((iMuon->pt() < LooseMaxMuon.pt()) && (iMuon->pt() > Loose_sub_pt_Muon))
         {
           Loose_sub_pt_Muon=iMuon->pt();
           LooseSecondMuon=(*iMuon);
	   
         }
       
       
	 }
       
     }
   LooseMaxPt=LooseMaxMuon.pt();
   HighPtPostIdPreIso->Fill(LooseMaxPt);
   LooseSecondPt=LooseSecondMuon.pt();
   SemiHighPtPostIdPreIso->Fill(LooseSecondPt);
   
   pat::Muon IsoHighMuon;
   pat::Muon IsoSecondMuon;
   double Iso_max_pt_Muon=0;
   double Iso_sub_pt_Muon=0;
   double reliso=0;

   for(pat::MuonCollection::const_iterator iMuon = Muons->begin() ; iMuon !=Muons->end();++iMuon,++iMuon_Id)
     {

       Loose=muon::isLooseMuon(*iMuon);
       reco::MuonPFIsolation iso = iMuon->pfIsolationR04();                                                                                                                                                                                                                  
       reliso = (iso.sumChargedHadronPt+TMath::Max(0.,iso.sumNeutralHadronEt+iso.sumPhotonEt-0.5*iso.sumPUPt))/iMuon->pt();
       if(Loose && (reliso <0.25))
         {
	   if(iMuon->pt() > Iso_max_pt_Muon)
	     {
	       Iso_max_pt_Muon=iMuon->pt();
	       IsoHighMuon=(*iMuon);

	     }
	   if((iMuon->pt() < IsoHighMuon.pt()) && (iMuon->pt() > Iso_sub_pt_Muon))
	     {
	       Iso_sub_pt_Muon=iMuon->pt();
	       IsoSecondMuon=(*iMuon);

	     }


         }

     }
   HighPtPostIdIso->Fill(IsoHighMuon.pt());
   SemiHighPtPostIdIso->Fill(IsoSecondMuon.pt());
			 


 

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
PrimaryMuonAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PrimaryMuonAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PrimaryMuonAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PrimaryMuonAnalyzer);
