// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      TauIDTester
// 
/**\class TauIDTester TauIDTester.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/TauIDTester.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Thu, 30 Jan 2020 19:29:39 GMT
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
#include "RecoTauTag/RecoTau/interface/PFRecoTauClusterVariables.h"
#include "DataFormats/PatCandidates/interface/Muon.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1F.h"
#include "TH1I.h"
#include "TH2D.h"

#include "TLatex.h"
#include "DataFormats/Math/interface/deltaR.h"


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TauIDTester : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TauIDTester(const edm::ParameterSet&);
      ~TauIDTester();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;
  edm::EDGetTokenT<std::vector<int> > ObjectPassing_;
  edm::EDGetTokenT<std::vector<int> > ObjectRemoved_;
  edm::EDGetTokenT<std::vector<int> > JetCleaned_;
  
  TH1I *NumObjectPassing;
  TH1I *NumObjectRemoved;
  TH1I *NumJetsCleaned;
  TH1I *NumTaus;
  






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
TauIDTester::TauIDTester(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  ObjectPassing_(consumes<std::vector<int> >(iConfig.getParameter<edm::InputTag>("ObjectID"))),
  ObjectRemoved_(consumes<std::vector<int> >(iConfig.getParameter<edm::InputTag>("ObjectRemoved"))),
  JetCleaned_(consumes<std::vector<int> >(iConfig.getParameter<edm::InputTag>("JetCleaned")))



{
   //now do what ever initialization is needed
  usesResource("TFileService");
  edm::Service<TFileService> f;

  NumObjectPassing= f->make<TH1I>("Objects Passing ID",";No of Muons/Electrons passing a certain ID;#entries",8,-0.5,7.5);
  NumObjectRemoved= f->make<TH1I>("Objects Removed",";No of Muons/Electrons removed from the Jet;#entries",8,-0.5,7.5);
  NumJetsCleaned= f->make<TH1I>("Objects Removed",";No of Jets with Muon/Electron Cleaned;#entries",8,-0.5,7.5);
  NumTaus= f->make<TH1I>("Taus",";No of Taus in Final collection;#entries",5,-0.5,4.5);

}


TauIDTester::~TauIDTester()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TauIDTester::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;
   int NumTau=0;

   
   Handle<pat::TauCollection> Taus;
   iEvent.getByToken(TauSrc_,Taus);
   
   Handle<std::vector<int> >ObjectPassing;
   iEvent.getByToken(ObjectPassing_,ObjectPassing);
   
   Handle<std::vector<int> >ObjectRemoved;
   iEvent.getByToken(ObjectRemoved_,ObjectRemoved);

   Handle<std::vector<int> >JetCleaned;
   iEvent.getByToken(JetCleaned_,JetCleaned);
   
   

   for( size_t i=0 ;i< ObjectPassing->size(); ++i)
     {
       NumObjectPassing->Fill((*ObjectPassing)[i]);
     }

   for( unsigned int i=0 ;i<ObjectRemoved->size(); ++i)
     {
       NumObjectRemoved->Fill((*ObjectRemoved)[i]);
     }
   
   for( unsigned int i=0 ;i< JetCleaned->size(); ++i)
     {
       NumJetsCleaned->Fill((*JetCleaned)[i]);
     }

   
   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
     { 
       ++NumTau;
     }
   NumTaus->Fill(NumTau);

// #ifdef THIS_IS_AN_EVENT_EXAMPLE
//    Handle<ExampleData> pIn;
//    iEvent.getByLabel("example",pIn);
// #endif
   
// #ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
//    ESHandle<SetupData> pSetup;
//    iSetup.get<SetupRecord>().get(pSetup);
// #endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
TauIDTester::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauIDTester::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TauIDTester::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TauIDTester);
