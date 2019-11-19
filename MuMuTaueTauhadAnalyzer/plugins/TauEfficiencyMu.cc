// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      TauEfficiencyMu
// 
/**\class TauEfficiencyMu TauEfficiencyMu.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/TauEfficiencyMu.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Thu, 24 Oct 2019 13:58:05 GMT
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

class TauEfficiencyMu : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TauEfficiencyMu(const edm::ParameterSet&);
      ~TauEfficiencyMu();
  bool isSpecificDaughter(const reco::Candidate * particle,int Id);
  double RefToDaughterPhi(const reco::Candidate * particle,int Id);
  double RefToDaughterEta(const reco::Candidate * particle,int Id);


  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
      // ----------member data ---------------------------
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;

  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;

  edm::EDGetTokenT<pat::MuonCollection> muonSrc_;

  TEfficiency* TauEff;
  TEfficiency* TauEffDMode;
  TEfficiency* TauEffDModes;
  
  double dRTauGenTau=99999;
  double dRTauGenDecay=99999;

  double dRMuGenMu=99999;
  double dRMuGenDecay=99999;


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
TauEfficiencyMu::TauEfficiencyMu(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  muonSrc_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonSrc")))

  
{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;
   const int  nbins =5;
   double edges[nbins+1]={10,15,20,30,50,100};
   TauEff = f->make<TEfficiency>("TauEff","Tau Reconstruction  Efficiency;Pt(GeV);#epsilon",nbins,edges);
   TauEffDMode = f->make<TEfficiency>("TauEffDMode","Tau DecayMode  Efficiency;Pt(GeV);#epsilon",nbins,edges);
   TauEffDModes = f->make<TEfficiency>("TauEffDModes","Tau DecayMode  Efficiency;DecayModes;#epsilon",12,-0.5,11.5);





}


TauEfficiencyMu::~TauEfficiencyMu()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}




bool TauEfficiencyMu::isSpecificDaughter(const reco::Candidate * particle,int Id)
{
  if ((fabs(particle->pdgId())==Id))
    return true;
  for(size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(isSpecificDaughter(particle->daughter(i),Id)) return true;

    }
  return false;
}

double TauEfficiencyMu::RefToDaughterPhi(const reco::Candidate * particle,int Id)
{

  double Phi=0;
  if ((fabs(particle->pdgId())==Id))
    return particle->phi();
  for( size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(RefToDaughterPhi(particle->daughter(i),Id))
        Phi=particle->daughter(i)->phi();

    }
  return Phi;
}



double TauEfficiencyMu::RefToDaughterEta(const reco::Candidate * particle,int Id)
{

  double Eta=0;
  if ((fabs(particle->pdgId())==Id))
    return particle->eta();
  for( size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(RefToDaughterEta(particle->daughter(i),Id))
        Eta=particle->daughter(i)->eta();

    }
  return Eta;
}




//
// member functions
//

// ------------ method called for each event  ------------
void
TauEfficiencyMu::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;
   
   Handle<pat::TauCollection> Taus;
   iEvent.getByToken(TauSrc_,Taus);

   Handle<edm::View<reco::GenParticle> > pruned;
   iEvent.getByToken(prunedGenToken_, pruned);

   Handle<pat::MuonCollection> Muon;
   iEvent.getByToken(muonSrc_,Muon);


   
   double PseudoTauPhi=99999;
   double PseudoTauEta=99999;

   double DecayTauPhi=99999;
   double DecayTauEta=99999;
   
   double MuPhi=99999;
   double MuEta=99999;

   double MuDecayEta=99999;
   double MuDecayPhi=99999;
   
   
   bool TauFound=false;
   bool TauDecay=false;

   bool MuFound=false;
   bool MuDecay=false;


   for(size_t i=0; i<(pruned.product())->size() ;i++)
     {
       if(fabs((*pruned)[i].pdgId())==15)
         {
           const Candidate * Tau = &(*pruned)[i];
           if (fabs(Tau->mother()->pdgId())==36)
             {
               const Candidate *PseudoTau = &(*pruned)[i];
               unsigned  n=PseudoTau->numberOfDaughters();

               for ( size_t j =0; j < n ; j++)
                 {
                   const Candidate * Daughter=PseudoTau->daughter(j);
                   if ((fabs(Daughter->pdgId())==13))
                     {   

                       MuFound=true;

                       MuEta=(double)(Daughter->eta());
		       MuPhi=(double)(Daughter->phi());


                     }

		   
		   
		   
		   
		   if( (!TauFound) && (fabs(Daughter->pdgId())!=13) &&  (fabs(Daughter->pdgId())!=14) && (fabs(Daughter->pdgId())!=15) && (fabs(Daughter->pdgId())!=22) && (fabs(Daughter->pdgId())!=16)  )
                     {
                                                                                                                                       
                       TauFound=true;
                                                                                          
                       PseudoTauPhi=(double)(PseudoTau->phi());
                       PseudoTauEta=(double)(PseudoTau->eta());
                     }
		   bool isHad= false;
		   bool isMuon=false;
                   if(fabs(Daughter->pdgId())==15)
                     {
                       isHad=!isSpecificDaughter(Daughter,13) && !isSpecificDaughter(Daughter,14);
		       if(isHad)
			 {
			                                                                  
			   TauDecay=true;
			                                                               
			   DecayTauPhi=PseudoTau->phi();
			   DecayTauEta=PseudoTau->eta();


			 }
		       if(isMuon)
                         {
                             
                           MuDecay=true;
                           MuDecayEta=RefToDaughterEta(Daughter,13);
                           MuDecayPhi=RefToDaughterPhi(Daughter,13);
                         }


                     }

                 }


             }


         }



     }


  




   for(pat::MuonCollection::const_iterator iMuon = Muon->begin() ; iMuon !=Muon->end() ; ++iMuon)
     {




   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)

     {
       bool PassDecayMode= false;
       bool AnalysisCuts= false;
       bool GenMatched =false;

       if(TauFound)
	 {
	   dRTauGenTau=reco::deltaR(PseudoTauEta,PseudoTauPhi,itau->eta(),itau->phi());
                                                                                                                                      
	 }

       if(TauDecay)
	 {
	   dRTauGenDecay=reco::deltaR(DecayTauEta,DecayTauPhi,itau->eta(),itau->phi());

	 }
       if(MuFound)
	 {
	   dRMuGenMu=reco::deltaR(MuEta,MuPhi,iMuon->eta(),iMuon->phi());
       
	 }
       if(MuDecay)
	 {
	   dRMuGenDecay=reco::deltaR(MuDecayEta,MuDecayPhi,iMuon->eta(),iMuon->phi());

	 }

       GenMatched=((TauFound && (dRTauGenTau < 0.1)) || (TauDecay && (dRTauGenDecay<0.1))) && ((MuFound && (dRMuGenMu < 0.1)) || (MuDecay && (dRMuGenDecay<0.1)));
       AnalysisCuts= ((itau->pt()) > 10 && (abs(itau->eta()) <2.3));


       if(GenMatched && AnalysisCuts)
	 {
           PassDecayMode=itau->tauID("decayModeFinding");
           TauEffDMode->Fill(PassDecayMode,itau->pt());
           TauEffDModes->Fill(PassDecayMode,itau->decayMode());


	 }



     }


     }




















   

   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)

     {

       bool PassDecayMode= false;
       bool GenMatched =false;
       bool PassMVA= false;
       bool AnalysisCuts =false;

       //if(itau->tauID("decayModeFinding"))
       //if(itau->tauID("byIsolationMVArun2v1DBoldDMwLTraw") > -0.5)

       if(TauFound)
	 {
	   dRTauGenTau=reco::deltaR(PseudoTauEta,PseudoTauPhi,itau->eta(),itau->phi());
	   //dRTauCleanedGenTau=reco::deltaR(PseudoTauEta,PseudoTauPhi,itau_cl->eta(),itau_cl->phi());
	 }

       if(TauDecay)
	 {
	   dRTauGenDecay=reco::deltaR(DecayTauEta,DecayTauPhi,itau->eta(),itau->phi());
	   //dRTauCleanedGenDecay=reco::deltaR(DecayTauEta,DecayTauPhi,itau_cl->eta(),itau_cl->phi());
	 }
       
       PassDecayMode=itau->tauID("decayModeFinding");
       //PassMVA=itau->tauID("byIsolationMVArun2v1DBoldDMwLTraw");
       
       

       GenMatched=((TauFound && (dRTauGenTau < 0.1)) || (TauDecay && (dRTauGenDecay<0.1)));   
       AnalysisCuts= ((itau->pt()) > 10 && (abs(itau->eta()) <2.3));
       if ( PassDecayMode && GenMatched && AnalysisCuts)
	 {
	   PassMVA=((itau->tauID("byIsolationMVArun2v1DBoldDMwLTraw") >-0.5) && (itau->tauID("byMediumIsolationMVArun2v1DBoldDMwLT")));
	   
	   TauEff->Fill(PassMVA,itau->pt());
	 }
       



     }









}


// ------------ method called once each job just before starting event loop  ------------
void 
TauEfficiencyMu::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauEfficiencyMu::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TauEfficiencyMu::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TauEfficiencyMu);