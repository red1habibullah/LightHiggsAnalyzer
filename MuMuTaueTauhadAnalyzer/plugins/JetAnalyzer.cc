// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      JetAnalyzer
// 
/**\class JetAnalyzer JetAnalyzer.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/JetAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Tue, 03 Sep 2019 19:08:47 GMT
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
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/JetReco/interface/Jet.h"

#include "DataFormats/JetReco/interface/PFJet.h"
#include <iostream>

#include <cmath>
#include"TMath.h"

#include "TH1.h"
#include "TH2.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class JetAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit JetAnalyzer(const edm::ParameterSet&);
      ~JetAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<reco::PFJetCollection> jetSrc_;
  //Booking Histograms
  //TH1D* chargedIsoPtSum;
  TH1D* NHEF;
  TH1D* CHEF;
  TH1D* NHE;
  TH1D* CHE;
  TH1D* PE;
  TH1D* PEF;
  TH1D* JE;
  //TH1D* CEEF;
  //TH1D* NEEF;
  TH2D* PhivsEta;
  TH1I* nhMult ;
  TH1I*  chMult;
  
  TH1I* eMult;
  TH1I* muMult;
  
  TH1I* cMult;
  TH1I* nMult;
  TH1I* pMult;
  //TH1D* cEF;
  //TH1D* nEF;
  

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
JetAnalyzer::JetAnalyzer(const edm::ParameterSet& iConfig):
  jetSrc_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("jetSrc")))


{
   //now do what ever initialization is needed
   usesResource("TFileService");
   //File to put histogram in 
   edm::Service<TFileService> file;
   //Name and Bins for the histograms
   NHEF = file->make<TH1D>("neutralHadronEnergyFraction",";neutralHadronEnergyFraction;Jets",200,0,1);
   NHE = file->make<TH1D>("neutralHadronEnergy",";neutralHadronEnergy;Jets",500,0,500);
 
   CHEF = file->make<TH1D>("chargedHadronEnergyFraction",";chargedHadronEnergyFraction;Jets",200,0,1);
   CHE = file->make<TH1D>("chargedHadronEnergy",";chargedHadronEnergy;Jets",500,0,500);

   PE = file->make<TH1D>("photonEnergy",";photonEnergy;Jets",500,0,500);
   PEF = file->make<TH1D>("photonEnergyFraction",";photonEnergyFraction;Jets",200,0,1);
   JE = file->make<TH1D>("JetEnergy",";JetEnergy;Jets",1000,0,1000);

   //CEEF = file->make<TH1D>("chargedHadronEnergyFraction",";chargedHadronEnergyFraction;Jets",200,0,1);

   PhivsEta = file->make<TH2D>("#phi vs #eta ",";eta;phi",50,-5.0,5.0,50,-TMath::Pi(), TMath::Pi());
   nhMult = file->make<TH1I>("neutralHadronMultiplicity",";neutralHadronMultiplicity;Jets",12,0,12);
   chMult = file->make<TH1I>("chargedHadronMultiplicity",";chargedHadronMultiplicity;Jets",50,0,50);
   eMult = file->make<TH1I>("electronMultiplicity",";electronMultiplicity;Jets",5,0,5);
   muMult = file->make<TH1I>("muonMultiplicity",";muonMultiplicity;Jets",5,0,5);
   cMult = file->make<TH1I>("chargedMultiplicity",";chargedMultiplicity;Jets",50,0,50);
   nMult = file->make<TH1I>("neutralMultiplicity",";neutralMultiplicity;Jets",50,0,50);
   pMult = file->make<TH1I>("photonMultiplicity",";photonMultiplicity;Jets",50,0,50);

}


JetAnalyzer::~JetAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
JetAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;


  edm::Handle<reco::PFJetCollection> pfJets;
  iEvent.getByToken(jetSrc_, pfJets);

  for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet)
    {
      NHEF->Fill(iJet->neutralHadronEnergyFraction());
      NHE->Fill(iJet->neutralHadronEnergy());
 
      CHEF->Fill(iJet->chargedHadronEnergyFraction());
      CHE->Fill(iJet->chargedHadronEnergy());
      PE->Fill(iJet->photonEnergy());
      PEF->Fill(iJet->photonEnergyFraction());
      JE->Fill(iJet->energy());
      
      PhivsEta->Fill(iJet->eta(),iJet->phi());
      PhivsEta->SetOption("COLZ");
      
      nhMult->Fill(iJet->neutralHadronMultiplicity());
      chMult->Fill(iJet->chargedHadronMultiplicity());
      
      eMult->Fill(iJet->electronMultiplicity());
      muMult->Fill(iJet->muonMultiplicity());
      
      cMult->Fill(iJet->chargedMultiplicity());
      nMult->Fill(iJet->neutralMultiplicity());
      pMult->Fill(iJet->photonMultiplicity());

      /*cout<<"====================================================================="<<endl;
      cout<<" Neutral Hadron Multiplicity: " << iJet->neutralHadronMultiplicity() <<endl;
      cout<<" charged Hadron Multiplicity: " << iJet->chargedHadronMultiplicity() <<endl;
      cout<<"====================================================================="<<endl;
      */
      
      /*cout<<"-----------------------------------------------------------------------"<<endl;
	cout<<" charged Multiplcity: " << iJet->chargedMultiplicity() <<endl;
	cout<<" neutral Multiplcity: " << iJet->neutralMultiplicity() <<endl;
	cout<<"-----------------------------------------------------------------------"<<endl;
      */
      
      
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
JetAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetAnalyzer);
