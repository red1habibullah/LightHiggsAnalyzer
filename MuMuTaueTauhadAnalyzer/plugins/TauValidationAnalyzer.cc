// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      TauValidationAnalyzer
// 
/**\class TauValidationAnalyzer TauValidationAnalyzer.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/TauValidationAnalyzer.cc

 Description: [one line class summary]
Plot of the Cluster variabels in order to compare between the cleaned and the unlceaned collection
 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Thu, 15 Aug 2019 23:51:20 GMT
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
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/PATTauDiscriminator.h"


#include "RecoTauTag/RecoTau/interface/PFRecoTauClusterVariables.h"
#include "DataFormats/PatCandidates/interface/Muon.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
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

class TauValidationAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TauValidationAnalyzer(const edm::ParameterSet&);
      ~TauValidationAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  TauIdMVAAuxiliaries clusterVariables_;
  
  // Get the Necessary Tokens
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;
  edm::EDGetTokenT<pat::MuonCollection> MuonL_;
  edm::EDGetTokenT<pat::MuonCollection> MuonT_;


  //Initialize Histograms

  TH1D* decayMode;
  TH1D* chargedIsoPtSum;
  TH1D* neutralIsoPtSum;
  TH1D* puCorrPtSum;
  TH1D* photonPtSumOutsideSignalCone;
  TH1D* footprintCorrection;

  TH1D* decayDistMag;
  TH1D* dxy;
  TH1D* dxySig;
  TH1D* ip3d;
  TH1D* ip3dSig;

  //cut variables
  double Mu1TaudRCut_;
  double dRMu1Tau=99999;

  double Mu2TaudRCut_;
  double dRMu2Tau=99999;








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
TauValidationAnalyzer::TauValidationAnalyzer(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  MuonL_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("Muons1"))),
  MuonT_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("Muons2"))),
  Mu1TaudRCut_(iConfig.getParameter<double>("Mu1TaudRCut")),
  Mu2TaudRCut_(iConfig.getParameter<double>("Mu2TaudRCut"))
{
  //now do what ever initialization is needed
  usesResource("TFileService");
  edm::Service<TFileService> f;
  
  decayMode = f->make<TH1D>("decayMode",";decayMode;Taus",12,-0.5,11.5);
  chargedIsoPtSum = f->make<TH1D>("chargedIsoPtSum",";ChargedIsoPtSum(GeV);Taus",500,0,50);
  neutralIsoPtSum = f->make<TH1D>("neutralIsoPtSum",";neutralIsoPtSum(GeV);Taus",500,0,50);
  puCorrPtSum = f->make<TH1D>("puCorrPtSum",";puCorrPtSum(GeV);Taus",500,0,50);
  photonPtSumOutsideSignalCone = f->make<TH1D>("photonPtSumOutsideSignalCone",";photonPtSumOutsideSignalCone(GeV);Taus",500,0,50);
  footprintCorrection = f->make<TH1D>("footprintCorrection",";footprintCorrection;Taus",500,0,50);
  
  decayDistMag = f->make<TH1D>("decayDistMag",";decayDistMag(cm);Taus",100,0,10);
  dxy = f->make<TH1D>("dxy",";d_{xy}(cm);Taus",100,0,0.1);
  dxySig = f->make<TH1D>("dxySig",";d_{xy} significance;Taus",10,-0.5,9.5);
  ip3d = f->make<TH1D>("ip3d",";ip3d(cm);Taus",100,0,10);
  ip3dSig = f->make<TH1D>("ip3dSig",";ip3d significance;Taus",10,-0.5,9.5);
  
}


TauValidationAnalyzer::~TauValidationAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TauValidationAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  
  
  Handle<pat::TauCollection> Taus;
  iEvent.getByToken(TauSrc_,Taus);

  Handle<pat::MuonCollection> Muons1;
  iEvent.getByToken(MuonL_,Muons1);

  Handle<pat::MuonCollection> Muons2;
  iEvent.getByToken(MuonT_,Muons2);

  for(pat::MuonCollection::const_iterator iMu = Muons1->begin() ; iMu !=Muons1->end() ; ++iMu)
    {   
      for(pat::MuonCollection::const_iterator imu = Muons2->begin() ; imu !=Muons2->end() ; ++imu)
	{
	  for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
	    
	    {
	      bool dRMatch=false;
	      dRMu1Tau=reco::deltaR(*iMu,*itau);
	      dRMu2Tau=reco::deltaR(*imu,*itau);

	      dRMatch=((dRMu1Tau > Mu1TaudRCut_) && (dRMu2Tau  >  Mu2TaudRCut_) && (itau->tauID("decayModeFinding")) );
	      
	      if(dRMatch)
		{
	      decayMode->Fill(itau->decayMode());
	      
	      
	      
	      chargedIsoPtSum->Fill(itau->tauID("chargedIsoPtSum"));
	      
	      
	      
	      neutralIsoPtSum->Fill(itau->tauID("neutralIsoPtSum"));
	      
	      
	      puCorrPtSum->Fill(itau->tauID("puCorrPtSum"));
	      
	      
	      photonPtSumOutsideSignalCone->Fill(itau->tauID("photonPtSumOutsideSignalCone"));
	  
	  
	      footprintCorrection->Fill(itau->tauID("footprintCorrection"));
	  
	  
	  
	  
	  
	  
	      float decayDistX = itau->flightLength().x();
	      float decayDistY = itau->flightLength().Y();
	      float decayDistZ = itau->flightLength().z();
	      float decayDistMagVal = sqrt(decayDistX*decayDistX +decayDistY*decayDistY+decayDistX*decayDistZ);
	      
	      decayDistMag->Fill(decayDistMagVal);
	      
	      dxy->Fill(itau->dxy());
	      
	      dxySig->Fill(itau->dxy_Sig());
	      
	      ip3d->Fill(itau->ip3d());
	  
	      ip3dSig->Fill(itau->ip3d_Sig());
	      
	  
	  
	  
		}
	      
	      
	    }
	}
    }
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
TauValidationAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauValidationAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TauValidationAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TauValidationAnalyzer);
