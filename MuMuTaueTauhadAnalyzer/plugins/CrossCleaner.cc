// -*- C++ -*-
//
// Package:    GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer
// Class:      CrossCleaner
// 
/**\class CrossCleaner CrossCleaner.cc GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer/plugins/CrossCleaner.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Mon, 11 Mar 2019 03:54:43 GMT
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

#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "TLorentzVector.h"

#include "TMath.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronCore.h"



#include "DataFormats/Math/interface/deltaR.h"
#include "TLatex.h"

#include "DataFormats/PatCandidates/interface/PATObject.h"
#include"DataFormats/PatCandidates/interface/Tau.h"

//
// class declaration
//

class CrossCleaner : public edm::stream::EDFilter<> {
   public:
      explicit CrossCleaner(const edm::ParameterSet&);
      ~CrossCleaner();

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
  edm::EDGetTokenT<pat::MuonCollection> MuonL_;
  edm::EDGetTokenT<pat::MuonCollection> MuonT_;
  
  double Mu1TaudRCut_;
  double dRMu1Tau=99999;

  double Mu2TaudRCut_;
  double dRMu2Tau=99999;
  
  double Mu1EledRCut_;
  double dRMu1Ele=99999;

  double Mu2EledRCut_;
  double dRMu2Ele=99999;

  
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
CrossCleaner::CrossCleaner(const edm::ParameterSet& iConfig):
  electronSrc_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  MuonL_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("Muons1"))),
  MuonT_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("Muons2"))),
  Mu1TaudRCut_(iConfig.getParameter<double>("Mu1TaudRCut")),
  Mu2TaudRCut_(iConfig.getParameter<double>("Mu2TaudRCut")),
  Mu1EledRCut_(iConfig.getParameter<double>("Mu1EledRCut")),
  Mu2EledRCut_(iConfig.getParameter<double>("Mu2EledRCut"))


{
   //now do what ever initialization is needed
  produces<std::vector<pat::Electron>>("CrossCleanedHighMassElectron");
  produces<std::vector<pat::Tau>>("CrossCleanedHighMassTaus");
  produces<std::vector<pat::Muon>>("CrossCleanedLeadingMuon");
  produces<std::vector<pat::Muon>>("CrossCleanedTrailingMuon");
  produces<std::vector<pat::Electron>>("CrossCleanedHighPtElectron");
  produces<std::vector<pat::Tau>>("CrossCleanedHighPtTaus");
  produces<std::vector<pat::Electron>>("CrossCleaneddRElectron");
  produces<std::vector<pat::Tau>>("CrossCleaneddRTaus");

}


CrossCleaner::~CrossCleaner()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
CrossCleaner::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  using namespace std;
  using namespace reco;
  Handle<pat::ElectronCollection> electrons;
  iEvent.getByToken(electronSrc_,electrons);
  
  unique_ptr <vector<pat::Electron>>CrossEle(new vector<pat::Electron>);
  unique_ptr <vector<pat::Electron>>PtEle(new vector<pat::Electron>);
  unique_ptr <vector<pat::Electron>>dREle(new vector<pat::Electron>);
  
  Handle<pat::TauCollection> Taus;
  iEvent.getByToken(TauSrc_,Taus);
  
  unique_ptr <vector<pat::Tau>>CrossTau(new vector<pat::Tau>);
  unique_ptr <vector<pat::Tau>>PtTau(new vector<pat::Tau>);
  unique_ptr <vector<pat::Tau>>dRTau(new vector<pat::Tau>);
  
  Handle<pat::MuonCollection> Muons1;
  iEvent.getByToken(MuonL_,Muons1);
  
  Handle<pat::MuonCollection> Muons2;
  iEvent.getByToken(MuonT_,Muons2);
  
  unique_ptr <vector<pat::Muon>>CleanedLeadingmu(new vector<pat::Muon>);
  unique_ptr <vector<pat::Muon>>CleanedTrailingmu(new vector<pat::Muon>);
  //unique_ptr<pat::MuonRefVector> MaxMuonRef(new pat::MuonRefVector);

  vector<pat::Electron> CleanedElectrons;
  vector<pat::Tau>CleanedTaus;
  
  double Vmass=999999;
  double Vmax= 0;
  double Pt_event=999999;
  double Ptmax=0;
  double dR_m=999999;
  double dR_m_min=999999;

  unsigned int int_ele=0;
  unsigned int int_tau=0;
  
  unsigned int pt_ele=0;
  unsigned int pt_tau=0;
  
  unsigned int dR_ele=0;
  unsigned int dR_tau=0;

  bool CleanedEvent=false;
  
  int iMu_id=0;
  
  vector <unsigned int> MaxMuonCheck;


  for(pat::MuonCollection::const_iterator iMu = Muons1->begin() ; iMu !=Muons1->end() ; ++iMu,++iMu_id)
    
    {
      //pat::Muon outputMu(*Mu);
      pat::MuonRef MaxRef(Muons1,iMu_id);
      
      
      for(pat::MuonCollection::const_iterator imu = Muons2->begin() ; imu !=Muons2->end() ; ++imu)
	
	{
	  
	  for(pat::ElectronCollection::const_iterator iele = electrons->begin() ; iele !=electrons->end() ; ++iele)
	    {
	      for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
		{
		  bool CrossCleaned=false;
		  dRMu1Tau=reco::deltaR(*iMu,*itau);
		  dRMu2Tau=reco::deltaR(*imu,*itau);
		  dRMu1Ele=reco::deltaR(*iMu,*iele);
		  dRMu2Ele=reco::deltaR(*imu,*iele);
		  CrossCleaned= ((dRMu1Tau > Mu1TaudRCut_) && (dRMu2Tau  > Mu2TaudRCut_) && (dRMu1Ele > Mu1EledRCut_) && (dRMu2Ele > Mu2EledRCut_));
		    if (CrossCleaned)
		      {
			CleanedElectrons.push_back(*iele);
			CleanedTaus.push_back(*itau);
			
			//check=std::find(Packed.begin(),Packed.end(),const_cast<pat::PackedGenParticle*>((*packed).ptrAt(j).get()));
			vector<unsigned int>::iterator MaxCheck;
			MaxCheck=std::find(MaxMuonCheck.begin(),MaxMuonCheck.end(),MaxRef.key());
			if(MaxCheck==MaxMuonCheck.end())
			  
			  { // MaxMuonRef->push_back(MaxRef);
			    MaxMuonCheck.push_back(MaxRef.key());
			    CleanedLeadingmu->push_back(*iMu);
			    CleanedTrailingmu->push_back(*imu);
			
			  }
			//MaxMuonRef->push_back(MaxRef);
			
			
		      }
		}
	      
	      
	      
	    }
	}
      
    }
  
  

  for(unsigned i=0;i<CleanedElectrons.size() && i<CleanedTaus.size();i++)                                                                                                                                                                                                     

    { 
      Vmass=abs(((CleanedElectrons[i]).p4() +(CleanedTaus[i]).p4()).mass());
      if ((Vmass > Vmax))
	{
	  Vmax=Vmass;
	 
	  int_ele=i;
	  int_tau=i;
	  
	}
      
      
    }
  if((CleanedElectrons.size()>0) && (CleanedTaus.size()>0))

  {
    CrossEle->push_back(CleanedElectrons[int_ele]);
    CrossTau->push_back(CleanedTaus[int_tau]);
  }
  

  for(unsigned i=0;i<CleanedElectrons.size() && i<CleanedTaus.size();i++)

    {
      //Vmass=abs(((CleanedElectrons[i]).p4() +(CleanedTaus[i]).p4()).mass());
      Pt_event=(((CleanedElectrons[i]).p4()+(CleanedTaus[i]).p4()).pt());

      if (Ptmax<Pt_event)
        {
	  Ptmax=Pt_event;

          pt_ele=i;
	  pt_tau=i;

        }


    }
  if((CleanedElectrons.size()>0) && (CleanedTaus.size()>0))

    {
      PtEle->push_back(CleanedElectrons[pt_ele]);
      PtTau->push_back(CleanedTaus[pt_tau]);
    }

  for(unsigned i=0;i<CleanedElectrons.size() && CleanedTaus.size();i++)
    {
     
      //Pt_event=(((PtElectrons[i]).p4()+(PtTaus[i]).p4()).pt());
      dR_m=reco::deltaR((CleanedElectrons[i]).eta(),(CleanedElectrons[i]).phi(),(CleanedTaus[i]).eta(),(CleanedTaus[i]).phi());
      if(dR_m < dR_m_min)
	{
	 
	  dR_m_min=dR_m;
	  
	  dR_ele=i;
	  dR_tau=i;
	}
      
      
    }

  if((CleanedElectrons.size()>0) && (CleanedTaus.size()>0))
    {
      dREle->push_back(CleanedElectrons[dR_ele]);
      dRTau->push_back(CleanedTaus[dR_tau]);
    }








  CleanedEvent= ((dREle->size() > 0) && (dRTau->size() >0) && (CleanedLeadingmu->size() > 0) && (CleanedTrailingmu->size() > 0));
   
  
  iEvent.put(move(CrossEle), "CrossCleanedHighMassElectron");
  iEvent.put(move(CrossTau), "CrossCleanedHighMassTaus");
  iEvent.put(move(dREle), "CrossCleaneddRElectron");
  iEvent.put(move(dRTau), "CrossCleaneddRTaus");
  iEvent.put(move(PtEle), "CrossCleanedHighPtElectron");
  iEvent.put(move(PtTau), "CrossCleanedHighPtTaus");
  iEvent.put(move(CleanedLeadingmu),"CrossCleanedLeadingMuon");
  iEvent.put(move(CleanedTrailingmu),"CrossCleanedTrailingMuon");
  
  /* using namespace edm;
#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
  */
  if (CleanedEvent)
   return true;
  else
    return false;
}


// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
CrossCleaner::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
CrossCleaner::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
CrossCleaner::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
CrossCleaner::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
CrossCleaner::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
CrossCleaner::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
CrossCleaner::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(CrossCleaner);
