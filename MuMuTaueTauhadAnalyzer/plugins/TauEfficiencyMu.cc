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
  
  edm::EDGetTokenT<reco::PFJetCollection> jetSrc_;

  TEfficiency* TauEff;
  
  
  
  TH1F* NumDMode;
  TH1F* DenomDMode;
  TEfficiency* TauEffDMode;
  
  TEfficiency* TauEffDModes;
  
  TH1F* NumDMode0;
  TEfficiency* TauEffDMode0;
  
  TH1F* NumDMode1;
  TEfficiency* TauEffDMode1;
  
  TH1F* NumDMode5;
  TEfficiency* TauEffDMode5;
  
  TH1F* NumDMode6;
  TEfficiency* TauEffDMode6;
  
  TH1F* NumDMode10;
  TEfficiency* TauEffDMode10;
  
  TH1D* TauPt;
  TH1D* JetPt;
  
  
  double dRTauGenTau=99999;
  double dRTauGenDecay=99999;
  
  double dRJetGenTau=99999;
  double dRJetGenDecay=99999;

  double dRMuGenMu=99999;
  double dRMuGenDecay=99999;
  
  double dRTauJet=99999;
  
  int NumCount=0;
  int DenomCount=0;
  

  int NumCountIso=0;
  int DenomCountIso=0;

  int NumCount0=0;
  int DenomCount0=0;

  int Counter=0;

};

//
// constants, enums and type//
// static data member definitions
//

//
// constructors and destructor
//
TauEfficiencyMu::TauEfficiencyMu(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  muonSrc_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonSrc"))),
  jetSrc_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("jetSrc")))

  
{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;
   const int  nbins =5;
   double edges[nbins+1]={10,15,20,30,50,100};
   TauEff = f->make<TEfficiency>("TauEff","Tau Reconstruction  Efficiency;Pt(GeV);#epsilon",nbins,edges);
   
   NumDMode = f->make<TH1F>("NumDMode","Numerator for Reconstruction Efficiency;Jet Pt(GeV);# of Events",nbins,edges);
   DenomDMode = f->make<TH1F>("DenomDMode","DEnominator for Reconstruction Efficiency;Jet Pt(GeV);# of Events",nbins,edges);
   
   TauEffDMode = f->make<TEfficiency>("TauEffDMode","Tau DecayMode  Efficiency;Jet Pt(GeV);#epsilon",nbins,edges);
   
   
   TauEffDModes = f->make<TEfficiency>("TauEffDModes","Tau DecayMode  Efficiency;DecayModes;#epsilon",12,-0.5,11.5);
   
   NumDMode0 = f->make<TH1F>("NumDMode0","Numerator for Reconstruction Efficiency for Decay Mode 0 -> 1 Prong ;Jet Pt(GeV);# of Events",nbins,edges);
   TauEffDMode0 = f->make<TEfficiency>("TauEffDMode0","Tau DecayMode  Efficiency for Decay Mode 0 -> 1 Prong ;Jet Pt(GeV);#epsilon",nbins,edges);
   
   
   NumDMode1 = f->make<TH1F>("NumDMode1","Numerator for Reconstruction Efficiency for Decay Mode 1 -> 1 Prong + 1 #pi 0  ;Jet Pt(GeV);# of Events",nbins,edges);
   TauEffDMode1 = f->make<TEfficiency>("TauEffDMode1","Tau DecayMode  Efficiency for Decay Mode 1 -> 1 Prong + 1 #pi 0 ;Jet Pt(GeV);#epsilon",nbins,edges);
   
   NumDMode5 = f->make<TH1F>("NumDMode5","Numerator for Reconstruction Efficiency for Decay Mode 5 -> 1 Prong + N #pi 0  ;Jet Pt(GeV);# of Events",nbins,edges);
   TauEffDMode5 = f->make<TEfficiency>("TauEffDMode5","Tau DecayMode  Efficiency for Decay Mode 5 -> 1 Prong + N #pi 0  ;Jet Pt(GeV);#epsilon",nbins,edges);
   
   
   NumDMode6 = f->make<TH1F>("NumDMode6","Numerator for Reconstruction Efficiency for Decay Mode 6 -> 2 Prong ;Jet Pt(GeV);# of Events",nbins,edges);
   TauEffDMode6= f->make<TEfficiency>("TauEffDMode6","Tau DecayMode  Efficiency for Decay Mode 6 -> 2 Prong ;Jet Pt(GeV);#epsilon",nbins,edges);
   
   NumDMode10 = f->make<TH1F>("NumDMode10","Numerator for Reconstruction Efficiency for Decay Mode 10 -> 3 Prong ;Jet Pt(GeV);# of Events",nbins,edges);
   TauEffDMode10 = f->make<TEfficiency>("TauEffDMode10","Tau DecayMode  Efficiency for Decay Mode 10 -> 3 Prong ;Jet Pt(GeV);#epsilon",nbins,edges);
   
   TauPt= f->make<TH1D>("TauPt","Tau Pt distribution;Pt(GeV);# of Events",100,0,100);
   JetPt= f->make<TH1D>("JetPt","Jet Pt distribution;Pt(GeV);# of Events",200,0,200);


   



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

   edm::Handle<reco::PFJetCollection> pfJets;
   iEvent.getByToken(jetSrc_, pfJets);


   
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

   bool TmuThad=false;
   
   for(size_t i=0; i<(pruned.product())->size() ;i++)
     {
       if(fabs((*pruned)[i].pdgId())==15)
         {
           const Candidate * Tau = &(*pruned)[i];
           if (fabs(Tau->mother()->pdgId())==36)
             {
	       cout << " Tau from PseudoScalar " <<endl;
	       
               const Candidate *PseudoTau = &(*pruned)[i];
               unsigned  n=PseudoTau->numberOfDaughters();
	       
               for ( size_t j =0; j < n ; j++)
                 {
                   
		   
		   const Candidate * Daughter=PseudoTau->daughter(j);
                   
		   cout<< " Daughter no:  "<< j << "  pdgId: " << Daughter->pdgId() <<endl;
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
		       isMuon=isSpecificDaughter(Daughter,13);

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

   
   TmuThad=((TauFound) || (TauDecay )) && ((MuFound) || (MuDecay));
   if(TmuThad)
     {
       ++Counter;
     }

   for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet)
     {
       
       
       
       for(pat::MuonCollection::const_iterator iMuon = Muon->begin() ; iMuon !=Muon->end() ; ++iMuon)
	 {
	   
	   
	   

	   //for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
	     
	   //{
	   //bool PassDecayMode= false;
	   bool AnalysisCuts= false;
	   bool GenMatched =false;
	       
	       if(TauFound)
		 {
		   
		   dRJetGenTau=reco::deltaR(PseudoTauEta,PseudoTauPhi,iJet->eta(),iJet->phi());

		 }
	       
	       if(TauDecay)
		 {
		  
		   dRJetGenDecay=reco::deltaR(DecayTauEta,DecayTauPhi,iJet->eta(),iJet->phi());
		   
		 }
	       if(MuFound)
		 {
		   dRMuGenMu=reco::deltaR(MuEta,MuPhi,iMuon->eta(),iMuon->phi());
	   
		 }
	       if(MuDecay)
		 {
		   dRMuGenDecay=reco::deltaR(MuDecayEta,MuDecayPhi,iMuon->eta(),iMuon->phi());
		   
		 }
	       
	       GenMatched= ((TauFound && (dRJetGenTau < 0.1)) || (TauDecay && (dRJetGenDecay<0.1))) && ((MuFound && (dRMuGenMu < 0.1)) || (MuDecay && (dRMuGenDecay<0.1)));
	       AnalysisCuts= /*((itau->pt()) > 10 && (abs(itau->eta()) <2.3)) &&*/ ((iJet->pt() > 10) && (fabs(iJet->eta()) <2.3));
	       
	       
	       if(GenMatched && AnalysisCuts)
		 {
		   ++DenomCount;
		   DenomDMode->Fill(iJet->pt());
		   
		   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau) 
		     {
		       bool PassDecayMode= false;
		       dRTauJet=reco::deltaR(*itau,*iJet);
		       
		       
		       PassDecayMode=(itau->tauID("decayModeFinding")) && (dRTauJet< 0.1);
		       
		       if(PassDecayMode)
			 {
			   ++NumCount;
			   NumDMode->Fill(iJet->pt());
			 }
		       
		       
		       
		       TauEffDMode->Fill(PassDecayMode,itau->pt());
		       TauEffDModes->Fill(PassDecayMode,itau->decayMode());
		       
		       
    

		       if((itau->decayMode())==0)
			 {
			   ++DenomCount0;
			   
			   TauEffDMode0->Fill(PassDecayMode,itau->pt());
			 }
		       if(((itau->decayMode())==0) && PassDecayMode)
			     {
			       NumDMode0->Fill(iJet->pt());
			       ++NumCount0;
			     }
			 
		       if(((itau->decayMode())==1) && PassDecayMode)
			 {
			   TauEffDMode1->Fill(PassDecayMode,itau->pt());
			   NumDMode1->Fill(iJet->pt());

			 }
		       if(((itau->decayMode())==5) && PassDecayMode)
			 {
			   TauEffDMode5->Fill(PassDecayMode,itau->pt());
			   NumDMode5->Fill(iJet->pt());

			 }
		       if(((itau->decayMode())==6) && PassDecayMode)
			 {
			   TauEffDMode6->Fill(PassDecayMode,itau->pt());
			   NumDMode6->Fill(iJet->pt());
			 }
		       if((itau->decayMode())==10 && PassDecayMode)
			 {
			   TauEffDMode10->Fill(PassDecayMode,itau->pt());
			   NumDMode10->Fill(iJet->pt());
			 }
		       
		       

		       
		     }
		   
		   
		   
		   
		 }
	       
	       //}
	       
	 }
       
     }
   
   //TauEffDMode->TEfficiency(NumDMode,DenomDMode);
   



















   

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
       
       

       GenMatched=((TauFound && (dRTauGenTau < 0.1)) || (TauDecay && (dRTauGenDecay<0.1))) && ((MuFound && (dRMuGenMu < 0.1)) || (MuDecay && (dRMuGenDecay<0.1)));   
       AnalysisCuts= ((itau->pt()) > 10 && (abs(itau->eta()) <2.3));
       if ( PassDecayMode && GenMatched && AnalysisCuts)
	 {
	   ++DenomCountIso;
	   PassMVA=((itau->tauID("byIsolationMVArun2v1DBoldDMwLTraw") >-0.5) && (itau->tauID("byMediumIsolationMVArun2v1DBoldDMwLT")));
	   
	   if(PassMVA)
	     {
	       ++NumCountIso;
	     }
	   TauEff->Fill(PassMVA,itau->pt());
	 }
       



     }
   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)

     {
       TauPt->Fill(itau->pt());
       
     
     }

   for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet)
     {

       JetPt->Fill(iJet->pt());
     }   




   std::cout<< " denominator DMode: " <<  DenomCount <<endl;
   std::cout<< " Numerator DMode: " <<  NumCount <<endl;
   std::cout<< "########################"<<std::endl;
   //std::cout<< " denominator Iso: " <<  DenomCountIso  <<endl;
   //std::cout<< " Numerator Iso: " <<  NumCountIso <<endl;

   std::cout<< " denominator DMode0: " <<  DenomCount<<std::endl;                                                                                                                                                                                                              std::cout<< " Numerator DMode0: " <<  NumCount0 <<std::endl;  
   std::cout<< "************************"<<std::endl;

   std::cout<< "TaumuTauhad: "<< Counter <<std::endl;
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
  //TauEffDMode->TauEffDMode(*DenomDMode,*NumDMode);
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
