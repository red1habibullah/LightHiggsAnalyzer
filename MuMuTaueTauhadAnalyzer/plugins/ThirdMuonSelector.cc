// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      ThirdMuonSelector
// 
/**\class ThirdMuonSelector ThirdMuonSelector.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/ThirdMuonSelector.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Fri, 15 Nov 2019 01:07:10 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Math/interface/deltaR.h"


//
// class declaration
//

class ThirdMuonSelector : public edm::stream::EDProducer<> {
   public:
      explicit ThirdMuonSelector(const edm::ParameterSet&);
      ~ThirdMuonSelector();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<pat::MuonCollection> muonSrc_;
  edm::EDGetTokenT<pat::MuonCollection> MuonL_;
  edm::EDGetTokenT<pat::MuonCollection> MuonT_;

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
ThirdMuonSelector::ThirdMuonSelector(const edm::ParameterSet& iConfig):
  muonSrc_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonSrc"))),
  MuonL_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("Muons1"))),
  MuonT_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("Muons2")))
{
  produces<std::vector<pat::Muon>>("ThirdMuon");
 
  //register your products
/* Examples
   produces<ExampleData2>();

   //if do put with a label
   produces<ExampleData2>("label");
 
   //if you want to put into the Run
   produces<ExampleData2,InRun>();
*/
   //now do what ever other initialization is needed
  
}


ThirdMuonSelector::~ThirdMuonSelector()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
ThirdMuonSelector::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace reco;
   using namespace std;

   Handle<pat::MuonCollection> Muons;
   iEvent.getByToken(muonSrc_,Muons);


   Handle<pat::MuonCollection> Muons1;
   iEvent.getByToken(MuonL_,Muons1);

   Handle<pat::MuonCollection> Muons2;
   iEvent.getByToken(MuonT_,Muons2);
   
   unique_ptr <vector<pat::Muon>>Thirdmu(new vector<pat::Muon>);
   int iMuon_Id=0;

   
   for(pat::MuonCollection::const_iterator iMuon = Muons->begin() ; iMuon !=Muons->end();++iMuon,++iMuon_Id)
     {
       
       
       if(  (fabs(iMuon->eta())  < 2.4 )  && (iMuon->pt() > 3))
	 {
	   for(pat::MuonCollection::const_iterator iMu = Muons1->begin() ; iMu !=Muons1->end() ; ++iMu)
	     
	     {
	       for(pat::MuonCollection::const_iterator imu = Muons2->begin() ; imu !=Muons2->end() ; ++imu)
		 
		 {
		   bool Matchmu1=false;
		   bool Matchmu2=false;
		   
		   Matchmu1=(deltaR(*iMuon,*iMu) < 0.0001)  && (fabs(iMuon->pt()-iMu->pt()) < 0.0001);
		   Matchmu2=(deltaR(*iMuon,*imu) < 0.0001)  && (fabs(iMuon->pt()-imu->pt()) < 0.0001);
		   if(!(Matchmu1) && !(Matchmu2))
		   {
		     cout<< " Muon: " <<  iMuon_Id  << " Pt: " << iMuon->pt() << "  eta: " << iMuon->eta() << " phi: " << iMuon->phi() << " pdgId: " <<  iMuon->pdgId()  << endl; 
		     Thirdmu->push_back(*iMuon);
		     
		   }
		   
		 }
	       
	       
	     }
	   
	 }
     }
   
   
   
     
   iEvent.put(move(Thirdmu), "ThirdMuon");
}
   

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
ThirdMuonSelector::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
ThirdMuonSelector::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
ThirdMuonSelector::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
ThirdMuonSelector::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
ThirdMuonSelector::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
ThirdMuonSelector::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ThirdMuonSelector::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ThirdMuonSelector);
