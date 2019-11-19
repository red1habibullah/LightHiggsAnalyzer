// -*- C++ -*-
//
// Package:    GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer
// Class:      DeltaRCut
// 
/**\class DeltaRCut DeltaRCut.cc GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer/plugins/DeltaRCut.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Fri, 17 May 2019 05:59:22 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "TLatex.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PATObject.h"

#include"DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "TAttFill.h"
#include "Math/VectorUtil.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "TLorentzVector.h"

#include "TMath.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronCore.h"

//
// class declaration
//

class DeltaRCut : public edm::stream::EDFilter<> {
   public:
      explicit DeltaRCut(const edm::ParameterSet&);
      ~DeltaRCut();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<pat::ElectronCollection> electronSrc_;
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;

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
DeltaRCut::DeltaRCut(const edm::ParameterSet& iConfig):
  electronSrc_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus")))


  
{
  
  produces<pat::ElectronCollection>("TestElectron");
  produces<pat::TauCollection>("TestTau");
//now do what ever initialization is needed

}


DeltaRCut::~DeltaRCut()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
DeltaRCut::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  Handle<pat::ElectronCollection> electrons;
  iEvent.getByToken(electronSrc_,electrons);
  unique_ptr<pat::ElectronCollection> DeltaElectrons(new pat::ElectronCollection);
  Handle<pat::TauCollection> Taus;
  iEvent.getByToken(TauSrc_,Taus);
  unique_ptr<pat::TauCollection> DeltaTaus(new pat::TauCollection);
  
  vector<pat::Electron>CountElectron;
  vector<pat::Tau>CountTau;
  vector<pat::Electron>PairElectron;
  vector<pat::Tau>PairTau;

  double dR=99999;


  /*for(pat::ElectronCollection::const_iterator iele = electrons->begin() ; iele !=electrons->end() ; ++iele)
    {      
      
      for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
	
	
	{  
	  dR = reco::deltaR(*iele, *itau);   
	  if( (dR <0.8) && (dR > 0.05))
	    {
	      DeltaElectrons->push_back(*iele);
	      DeltaTaus->push_back(*itau);
	      CountElectron.push_back(*iele);
	      CountTau.push_back(*itau);
	    }
	  
	  
	}

    }
  */

  for(pat::ElectronCollection::const_iterator iele = electrons->begin() ; iele !=electrons->end() ; ++iele)                                                                                                                                                                  
    { 
      PairElectron.push_back(*iele);
    }
  for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)                                                                                                                                                                               
    { 
      PairTau.push_back(*itau);
    }

  for(unsigned i=0; i< PairElectron.size() && i <PairTau.size(); i++)
    {
      dR=reco::deltaR((PairElectron[i]).eta(),(PairElectron[i]).phi(),(PairTau[i]).eta(),(PairTau[i]).phi());
      if (dR<0.8 && dR > 0.05)
	{
	  DeltaElectrons->push_back(PairElectron[i]);
	  DeltaTaus->push_back(PairTau[i]);
	  CountElectron.push_back(PairElectron[i]);                                                                                                                                                         
	  CountTau.push_back(PairTau[i]); 
	}

    

    } 




  
  iEvent.put(move(DeltaElectrons), "TestElectron");
  iEvent.put(move(DeltaTaus), "TestTau");
  bool Pass=false;
  Pass=(((CountElectron.size()) > 0) && ((CountTau.size()) >0));
  
    /*using namespace edm;
      #ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   Event.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  Handle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
  */
  if(Pass)
    return true;
  else
    return false;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
DeltaRCut::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
DeltaRCut::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
DeltaRCut::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
DeltaRCut::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
DeltaRCut::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
DeltaRCut::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DeltaRCut::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(DeltaRCut);
