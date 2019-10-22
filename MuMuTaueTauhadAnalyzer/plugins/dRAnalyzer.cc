// -*- C++ -*-
//
// Package:    GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer
// Class:      dRAnalyzer
// 
/**\class dRAnalyzer dRAnalyzer.cc GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer/plugins/dRAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Wed, 22 May 2019 20:03:12 GMT
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
#include "TH1.h"
#include "TH2.h"

#include "TLatex.h"
#include "TAttFill.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PATObject.h"

#include"DataFormats/PatCandidates/interface/Tau.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

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

class dRAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit dRAnalyzer(const edm::ParameterSet&);
      ~dRAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  // ----------member data ---------------------------
  edm::EDGetTokenT<pat::ElectronCollection> Cutelectron_;
  edm::EDGetTokenT<pat::TauCollection> CutTau_;
  
  TH1D *Mvisiblecut;
  TH1D *MvisiblecutPair;
  TH1I *Counter;
  TH1D *PtTau;
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
dRAnalyzer::dRAnalyzer(const edm::ParameterSet& iConfig):
  Cutelectron_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("Cutelectrons"))),
  CutTau_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("CutTaus")))

{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> fl;
   Mvisiblecut =fl->make<TH1D>("Mvisiblecut" , "Mass_{visible} after dR > 0.05 and < 0.8  cut" , 100 ,-0.5 , 99.5 );
   MvisiblecutPair =fl->make<TH1D>("Mvisiblecut" , "Mass_{visible} after dR > 0.05 and < 0.8  cut examined one pair at  time" , 100 ,-0.5 , 99.5 );
   Counter =fl->make<TH1I>("Counter", "Number of pairs in each event",10,0,10);
   PtTau =fl->make<TH1D>("PtTau" , "Tau Pt after passing dR(Tau,ele) > 0.05 and > 0.05" ,150,0,150 );

}


dRAnalyzer::~dRAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions

//

// ------------ method called for each event  ------------
void
dRAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;
   Handle<pat::ElectronCollection> electrons_c;
   iEvent.getByToken(Cutelectron_,electrons_c);
   Handle<pat::TauCollection> Taus_c;
   iEvent.getByToken(CutTau_,Taus_c);
   double VmassCut=99999;
   double VmassPair=99999;
   vector<pat::Electron> PairElectrons;
   vector<pat::Tau>PairTaus;
   int Count=0;
   
   for(pat::ElectronCollection::const_iterator iele = electrons_c->begin() ; iele !=electrons_c->end();++iele)
     {
       PairElectrons.push_back(*iele);
     }
   for(pat::TauCollection::const_iterator itau = Taus_c->begin() ; itau !=Taus_c->end() ; ++itau)

     {
       PairTaus.push_back(*itau);
     }


   for(pat::ElectronCollection::const_iterator iele = electrons_c->begin() ; iele !=electrons_c->end();++iele)
     {
       for(pat::TauCollection::const_iterator itau = Taus_c->begin() ; itau !=Taus_c->end() ; ++itau)

         {
           VmassCut=abs((iele->p4() + itau->p4()).mass());
           Mvisiblecut->Fill(VmassCut);
           Mvisiblecut->SetFillColor(kYellow);

           Mvisiblecut->GetXaxis()->SetTitle("M_{v} after cut ");
           Mvisiblecut->GetYaxis()->SetTitle("# of events");
	   //++Count;
	   PtTau->Fill(itau->pt());
         }
     }



   for(unsigned i=0;i<PairElectrons.size() && i<PairTaus.size();i++)                                                                                                                                                                                                   
     {                    
       VmassPair=abs(((PairElectrons[i]).p4() +(PairTaus[i]).p4()).mass());
       
       MvisiblecutPair->Fill(VmassPair);
       ++Count;
       
     }
   Counter->Fill(Count);
   /*
#ifdef THIS_IS_AN_EVENT_EXAMPLE
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
dRAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
dRAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
dRAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(dRAnalyzer);
