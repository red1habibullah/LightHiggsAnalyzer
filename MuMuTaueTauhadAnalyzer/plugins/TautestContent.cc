// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      TautestContent
// 
/**\class TautestContent TautestContent.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/TautestContent.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Wed, 16 Oct 2019 13:43:04 GMT
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










//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TautestContent : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TautestContent(const edm::ParameterSet&);
      ~TautestContent();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;

  TH1D* Pt;




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
TautestContent::TautestContent(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus")))


{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;
   Pt = f->make<TH1D>("Pt",";Pt(GeV);#Taus",50,0,50);

}


TautestContent::~TautestContent()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TautestContent::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;


   Handle<pat::TauCollection> Taus;
   iEvent.getByToken(TauSrc_,Taus);
   
   int Idx=0;
   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau,++Idx)                                       

     {           
     
       cout<< " Tau no:  " << Idx << "  Tau Pt:  "    << itau->pt() << "  Tau eta:  " << itau->eta() << "  Tau phi:  " << itau->phi() <<endl; 
       
       const reco::CandidatePtrVector  signalCands = itau->signalCands();
       for (const auto& cands : signalCands)
	 {

	   std::cout <<" Signal Cand pdgId: " << cands->pdgId()<< " pt:  " << cands->pt() << " eta: " << cands->eta() << " phi: " << cands->phi()  <<std::endl;
	 }


     }






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
TautestContent::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TautestContent::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TautestContent::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TautestContent);
