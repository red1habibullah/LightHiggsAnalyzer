// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      JetFakeTauEfficiency
// 
/**\class JetFakeTauEfficiency JetFakeTauEfficiency.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/JetFakeTauEfficiency.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Wed, 06 Nov 2019 13:28:35 GMT
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
#include "TEfficiency.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class JetFakeTauEfficiency : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit JetFakeTauEfficiency(const edm::ParameterSet&);
      ~JetFakeTauEfficiency();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;
  edm::EDGetTokenT<reco::PFJetCollection> jetSrc_;
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;

  TEfficiency* JetTauFake;
  //double dRTauJet=99999;
  double dR_JetGenLepton=999999;
  double dR_min=999999;

  int NumCount=0;
  int DenomCount=0;

  //int EleCount=0;
  //int MuCount=0;
  //int TauCount=0;
  //int ZCount=0;
  
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
JetFakeTauEfficiency::JetFakeTauEfficiency(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  jetSrc_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("jetSrc"))),
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned")))

{
  //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;

   const int  nbins =5;
   double edges[nbins+1]={10,15,20,30,50,100};
   JetTauFake = f->make<TEfficiency>("JetTauFake","Jet Fake Tau Probability ;Pt(GeV);#epsilon",nbins,edges);

}


JetFakeTauEfficiency::~JetFakeTauEfficiency()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
JetFakeTauEfficiency::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;

  vector< const Candidate*> Fix;
  //int ZCount=0;
  //int ZDaughter=0;
  
  Handle<pat::TauCollection> Taus;
  
  iEvent.getByToken(TauSrc_,Taus);

  edm::Handle<reco::PFJetCollection> pfJets;
  iEvent.getByToken(jetSrc_, pfJets);

  Handle<edm::View<reco::GenParticle> > pruned;
  iEvent.getByToken(prunedGenToken_, pruned);



  for(size_t i=0; i<(pruned.product())->size() ;i++)
    {
      if(fabs((*pruned)[i].pdgId())==23)
	{
	  //++ZCount;
	  //cout<< "Start"<<endl;
	
	  const Candidate *Z = &(*pruned)[i];
	  
	  unsigned  n=Z->numberOfDaughters(); 

	  for ( size_t j =0; j < n ; j++)
	    {
	      const Candidate * Daughter=Z->daughter(j);
	      
	      if((fabs(Daughter->pdgId())==11) || (fabs(Daughter->pdgId())==13) || (fabs(Daughter->pdgId())==15))
		{
		
		  Fix.push_back(Daughter);
		}
	      // if ((fabs(Daughter->pdgId())==11))
	      // 	{
	      // 	  //++EleCount;
		  
	      // 	  break;

		
	      // 	}
	      // if ((fabs(Daughter->pdgId())==13))
              //   {
              //     //++MuCount;

              //     break;


              //   }
	      // if ((fabs(Daughter->pdgId())==15))
              //   {
              //     //++TauCount;

              //     break;


              //   }

	      // if ((fabs(Daughter->pdgId())==23))
              //   {
              //     //++ZDaughter;

              //     break;


              //   }
	      // std::vector<pat::PackedGenParticle*>::iterator check;
	    //   check=std::find(Packed.begin(),Packed.end(),const_cast<pat::PackedGenParticle*>((*packed).ptrAt(j).get()));
	    //   if(check==Packed.end())
	    // 	{
	    // 	  Packed.push_back(const_cast<pat::PackedGenParticle*>((*packed).ptrAt(j).get()));
	    // 	  invariant_v4_Tau_had +=TLorentzVector((*packed)[j].p4().X(),(*packed)[j].p4().Y(),(*packed)[j].p4().Z(),(*packed)[j].p4().T());


	    //   if ((fabs(Daughter->pdgId())==13))  
	    // 	{
		
	    // 	}

	      
	    
	    // }
	  
	  // const Candidate *PseudoTau = &(*pruned)[i];
	  // unsigned  n=PseudoTau->numberOfDaughters();

	  // for ( size_t j =0; j < n ; j++)
	  //   {
	  //     const Candidate * Daughter=PseudoTau->daughter(j);
	  //     if ((fabs(Daughter->pdgId())==11))
	  // 	{
	  // 	  EleFound=true;

	  // 	  EleEta=(double)(Daughter->eta());
	  // 	  ElePhi=(double)(Daughter->phi());


		



	    }

	}
  //cout<< " e lepton:  "<< EleCount <<endl;
  //cout<< " mu lepton: "<< MuCount <<endl;
  //cout<< " tau lepton: "<< TauCount <<endl;
  //cout<< " Z Count  "<< ZCount<<endl;
  //cout<< " Z Daughter Count  "<< ZDaughter<<endl;


    }







  // for(unsigned int i=0;i<Fix.size();i++)
  //   {
  //     cout<< "pdgId:" << (Fix[i])->pdgId() << "Eta:   "<< (Fix[i])->eta()<<endl;
  //   }





for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet)
    {
      
      
      for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
	
	{
	  bool JetKinematicCut= false;
	  bool TauKinematicCut = false;
	  bool dRMatch= false;
	  
	  JetKinematicCut= ((iJet->pt() > 10) && (fabs(iJet->eta()) <2.3));
	  TauKinematicCut=((itau->pt() > 10) && (fabs(itau->eta()) <2.3));
	  
	  //dRTauJet=reco::deltaR(*iJet,*itau);
	  //dRMatch=(dRTauJet < 0.1);
	  for(unsigned i=0;i<Fix.size();i++)
	    {

	      //Pt_event=(((PtElectrons[i]).p4()+(PtTaus[i]).p4()).pt());                                                                                                                                                                                                              
	      dR_JetGenLepton=reco::deltaR((Fix[i])->eta(),(Fix[i])->phi(),iJet->eta(),iJet->phi());
	      if(dR_JetGenLepton < dR_min)
		{

		  dR_min=dR_JetGenLepton;

		  //dR_ele=i;
		  //dR_tau=i;
		}


	    }
	  




	  dRMatch=(dR_min>0.4);


	  if(JetKinematicCut && TauKinematicCut && dRMatch)
	    {
	      bool PassMVA= false;
	      ++DenomCount;
	      PassMVA=((itau->tauID("byIsolationMVArun2v1DBoldDMwLTraw") >-0.5) && (itau->tauID("byMediumIsolationMVArun2v1DBoldDMwLT")));
	      
	      if(PassMVA)
		{
		 
		  ++NumCount;
		    }
	      JetTauFake->Fill(PassMVA,itau->pt());

	    }
	  
	  
	  
	}
      
      
    }


 cout<<" Numerator: " << NumCount<<endl;
 cout<<" Denominator: " << DenomCount<<endl;


}



// ------------ method called once each job just before starting event loop  ------------
void 
JetFakeTauEfficiency::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetFakeTauEfficiency::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetFakeTauEfficiency::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetFakeTauEfficiency);
