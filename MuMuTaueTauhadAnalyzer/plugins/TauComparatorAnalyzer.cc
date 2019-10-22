// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      TauComparatorAnalyzer
// 
/**\class TauComparatorAnalyzer TauComparatorAnalyzer.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/TauComparatorAnalyzer.cc

 Description: [one line class summary]
1;5202;0c
 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Wed, 28 Aug 2019 16:43:21 GMT
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

class TauComparatorAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TauComparatorAnalyzer(const edm::ParameterSet&);
      ~TauComparatorAnalyzer();
  bool isSpecificDaughter(const reco::Candidate * particle,int Id);
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  
  // Get the Necessary Tokens
  //The Tau and the Muon collections    
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;
  edm::EDGetTokenT<pat::TauCollection> TauCleanedSrc_;

  edm::EDGetTokenT<pat::MuonCollection> MuonL_;
  edm::EDGetTokenT<pat::MuonCollection> MuonT_;

  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
 
  edm::EDGetTokenT<reco::PFJetCollection> jetSrc_;
  edm::EDGetTokenT<reco::PFJetCollection> jetSrcCl_;

	  
  TH1D* dRTaus;
  
  TH1I* DiffsignalGammaCands;
  TH1I* DiffsignalNeutrHadrCands;
  TH1I* DiffsignalChargedHadrCands;
  
  
  TH1I* DiffisolationGammaCands;
  TH1I* DiffisolationNeutrHadrCands;
  TH1I* DiffisolationChargedHadrCands;

  TH2I* IsoGammaCleanedVsUnCleaned;
  TH2I* IsoChargedCleanedVsUnCleaned;
  TH2I* IsoNeutCleanedVsUnCleaned;
  
  TH2I* DMF;

  TH1D* NHE1;
  TH1D* NHE2;
  TH2D* NHE2D;
  
  TH1D* CHE1;
  TH1D* CHE2;
  TH2D* CHE2D;
  TH2D* CE2D;

  TH1I* nMult1;
  TH1I* nMult2;
  TH2I* nMult2D;

  TH1D* PE1;
  TH1D* PE2;
  TH2D* PE2D;
  
  TH1I*  chMult1;
  TH1I*  chMult2;
  TH2I* chMult2D;
  
  TH2I* cMult2D;
  TH2I* mMult2D;
  TH2I* eMult2D;
  
  TH1I* pMult1;
  TH1I* pMult2;
  TH2I* pMult2D;

  TH1I* nhMult1 ;
  TH1I* nhMult2 ;
  TH2I* nhMult2D;
  
  TH2I* JE2D;
  
  TH2D* chargedIsoPtSum;
  TH2D* neutralIsoPtSum;

  TH2D* Pt2D;

  //the cut variables
  double Mu1TaudRCut_;
  double dRMu1Tau=99999;
  
  double Mu2TaudRCut_;
  double dRMu2Tau=99999;
  
  double Mu1TauCleaneddRCut_;
  double dRMu1TauCleaned=99999;

  double Mu2TauCleaneddRCut_;
  double dRMu2TauCleaned=99999;

  double TauTauCleaneddRCut_;
  double dRTauTauCleaned=99999;

  double dRTauGenTau=99999;
  double dRTauGenDecay=99999;
  
  double dRTauCleanedGenTau=99999;
  double dRTauCleanedGenDecay=99999;
  int GenMatchTau=0;
  int GenMatchTauCleaned=0;

  
  //double dRTauJet=99999;
  //double dRTauJet_min=99999;
  
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
TauComparatorAnalyzer::TauComparatorAnalyzer(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  TauCleanedSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("TausCleaned"))),
  MuonL_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("Muons1"))),
  MuonT_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("Muons2"))),
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  jetSrc_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("jetSrc"))),
  jetSrcCl_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("jetSrcCl"))),
  Mu1TaudRCut_(iConfig.getParameter<double>("Mu1TaudRCut")),
  Mu2TaudRCut_(iConfig.getParameter<double>("Mu2TaudRCut")),
  Mu1TauCleaneddRCut_(iConfig.getParameter<double>("Mu1TauCleaneddRCut")),
  Mu2TauCleaneddRCut_(iConfig.getParameter<double>("Mu2TauCleaneddRCut")),
  TauTauCleaneddRCut_(iConfig.getParameter<double>("TauTauCleaneddRCut"))
  

  
  
  
{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;
   

   dRTaus = f->make<TH1D>("dR(Tau,TauCleaned)",";dR_{Tau,TauCleaned};#entries",100,0,1);
   
   DiffsignalGammaCands = f->make<TH1I>("DiffsignalGammaCands",";SignalGammaCands_{TauCleaned} - SignalGammaCands_{Tau};#entries",9,-4.5,4.5);
   DiffsignalNeutrHadrCands = f->make<TH1I>("DiffsignalNeutrHadrCands",";signalNeutrHadrCands_{TauCleaned} - signalNeutrHadrCands_{Tau};#entries",9,-4.5,4.5);
   DiffsignalChargedHadrCands = f->make<TH1I>("DiffsignalChargedHadrCands",";signalChargedHadrCands_{TauCleaned} - signalChargedHadrCands_{Tau};#entries",9,-4.5,4.5);
   
   DiffisolationChargedHadrCands = f->make<TH1I>("DiffisolationChargedHadrCands",";isolationChargedHadrCands_{TauCleaned} - isolationChargedHadrCands_{Tau};#entries",9,-4.5,4.5);
   DiffisolationNeutrHadrCands = f->make<TH1I>("DiffisolationNeutrHadrCands",";isolationNeutrHadrCands_{TauCleaned} - isolationNeutrHadrCands_{Tau};#entries",9,-4.5,4.5);
   DiffisolationGammaCands = f->make<TH1I>("DiffisolationGammaCands",";isolationGammaCands_{TauCleaned} - isolationGammaCands_{Tau};#entries",9,-4.5,4.5);
   
   IsoGammaCleanedVsUnCleaned = f->make<TH2I>("IsoGammaCleanedVsUnCleaned",";isolationGammaCands_{Tau};isolationGammaCands_{TauCleaned}",15,0,15,15,0,15);
   IsoChargedCleanedVsUnCleaned = f->make<TH2I>("IsoChargedCleanedVsUnCleaned",";isolationChargedHadrCands_{Tau};isolationChargedHadrCands_{TauCleaned}",15,0,15,15,0,15);
   IsoNeutCleanedVsUnCleaned = f->make<TH2I>("IsoNeutCleanedVsUnCleaned",";isolationNeutrHadrCands_{Tau};isolationNeutrHadrCands_{TauCleaned}",5,0,5,5,0,5);
   
   DMF= f->make<TH2I>("decayModeCleanedVsUnCleaned",";decayMode_{Tau};decayMode_{Tau_Cleaned}",12,-0.5,11.5,12,-0.5,11.5);
   
   
   NHE1 = f->make<TH1D>("neutralHadronEnergy",";neutralHadronEnergy;Jets",50,0,50);
   NHE2 = f->make<TH1D>("neutralHadronEnergy",";neutralHadronEnergy;Jets",50,0,50);
   NHE2D = f->make<TH2D>("neutralHadronEnergy2D",";neutralHadronEnergy_{Jet UnCleaned};neutralHadronEnergy_{Jet Cleaned}",50,0,50,50,0,50);

   CHE1 = f->make<TH1D>("chargedHadronEnergy",";chargedHadronEnergy;Jets",200,0,200);
   CHE2 = f->make<TH1D>("chargedHadronEnergy",";chargedHadronEnergy;Jets",200,0,200);
   CHE2D =f->make<TH2D>("chargedHadronEnergy2D",";chargedHadronEnergy_{Jet UnCleaned};chargedHadronEnergy_{Jet Cleaned}",40,0,200,40,0,200);
   
   CE2D =f->make<TH2D>("chargedEmEnergy2D",";chargedEmEnergy_{Jet UnCleaned};chargedEmEnergy_{Jet Cleaned}",40,0,200,40,0,200);
   

   nMult1 = f->make<TH1I>("neutralMultiplicity",";neutralMultiplicity;Jets",35,0,35);
   nMult2 = f->make<TH1I>("neutralMultiplicity",";neutralMultiplicity;Jets",35,0,35);
   nMult2D = f->make<TH2I>("neutralMultiplicity2D",";neutralMultiplicity_{Jet UnCleaned};neutralMultiplicity_{Jet Cleaned}",35,0,35,35,0,35);
   
   PE1 = f->make<TH1D>("photonEnergy",";photonEnergy;Jets",70,0,70);
   PE2 = f->make<TH1D>("photonEnergy",";photonEnergy;Jets",70,0,70);
   PE2D = f->make<TH2D>("photonEnergy2D",";photonEnergy_{Jet UnCleaned};photonEnergy_{Jet Cleaned}",70,0,70,70,0,70);
   
   chMult1 = f->make<TH1I>("chargedHadronMultiplicity",";chargedHadronMultiplicity;Jets",50,0,50);
   chMult2 = f->make<TH1I>("chargedHadronMultiplicity",";chargedHadronMultiplicity;Jets",50,0,50);
   chMult2D = f->make<TH2I>("chargedHadronMultiplicity2D",";chargedHadronMultiplicity_{Jet UnCleaned};chargedHadronMultiplicity_{Jet Cleaned}",50,0,50,50,0,50);
   
   cMult2D = f->make<TH2I>("chargedMultiplicity2D",";chargedMultiplicity_{Jet UnCleaned};chargedMultiplicity_{Jet Cleaned}",20,0,100,20,0,100);
   mMult2D=f->make<TH2I>("muonMultiplicity2D",";muonMultiplicity_{Jet UnCleaned};muonMultiplicity_{Jet Cleaned}",5,0,5,5,0,5);
   eMult2D=f->make<TH2I>("electronMultiplicity2D",";electronMultiplicity_{Jet UnCleaned};electronMultiplicity_{Jet Cleaned}",5,0,5,5,0,5);
   

   pMult1 = f->make<TH1I>("photonMultiplicity",";photonMultiplicity;Jets",50,0,50);
   pMult2 = f->make<TH1I>("photonMultiplicity",";photonMultiplicity;Jets",50,0,50);
   pMult2D = f->make<TH2I>("photonMultiplicity2D",";photonMultiplicity_{Jet UnCleaned};photonMultiplicity_{Jet Cleaned}",50,0,50,50,0,50);
   
   nhMult1 = f->make<TH1I>("neutralHadronMultiplicity",";neutralHadronMultiplicity;Jets",12,0,12);
   nhMult2 = f->make<TH1I>("neutralHadronMultiplicity",";neutralHadronMultiplicity;Jets",12,0,12);
   nhMult2D = f->make<TH2I>("neutralHadronMultiplicity2D",";neutralHadronMultiplicity_{Jet UnCleaned};neutralHadronMultiplicity_{Jet Cleaned}",12,0,12,12,0,12);
   JE2D = f->make<TH2I>("JetEnergy2D",";JetEnergy_{Jet UnCleaned};JetEnergy_{Jet Cleaned}",100,0,100,100,0,100);
   chargedIsoPtSum = f->make<TH2D>("chargedIsoPtSum",";ChargedIsoPtSum_{Tau UnCleaned}(GeV);ChargedIsoPtSum_{Tau Cleaned}(GeV)",50,0,50,50,0,50);
   neutralIsoPtSum = f->make<TH2D>("neutralIsoPtSum",";neutraIsoPtSum_{Tau UnCleaned}(GeV);neutralIsoPtSum_{Tau Cleaned}(GeV)",50,0,50,50,0,50);
   Pt2D = f->make<TH2D>("Pt2D",";Pt__{Tau UnCleaned}(GeV);Pt_{Tau Cleaned}(GeV)",50,0,50,50,0,50);

}


TauComparatorAnalyzer::~TauComparatorAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

bool TauComparatorAnalyzer::isSpecificDaughter(const reco::Candidate * particle,int Id)
{
  if ((fabs(particle->pdgId())==Id))
    return true;
  for(size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(isSpecificDaughter(particle->daughter(i),Id)) return true;

    }
  return false;
}


//
// member functions
//


// ------------ method called for each event  ------------
void
TauComparatorAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   Handle<pat::TauCollection> Taus;
   iEvent.getByToken(TauSrc_,Taus);
   
   Handle<pat::TauCollection> TausCleaned;
   iEvent.getByToken(TauCleanedSrc_,TausCleaned);

   Handle<pat::MuonCollection> Muons1;
   iEvent.getByToken(MuonL_,Muons1);

   Handle<pat::MuonCollection> Muons2;
   iEvent.getByToken(MuonT_,Muons2);
   
   Handle<edm::View<reco::GenParticle> > pruned;
   iEvent.getByToken(prunedGenToken_, pruned);
   
   
   edm::Handle<reco::PFJetCollection> pfJets;
   iEvent.getByToken(jetSrc_, pfJets);

   edm::Handle<reco::PFJetCollection> pfJetsCl;
   iEvent.getByToken(jetSrcCl_, pfJetsCl);
   
   double dRTauJet=99999;
   double dRTauJet_min=99999;
   
   double dRTauJetClean=99999;
   double dRTauJetClean_min=99999;


   
   //double dRTauJetClean=99999;
   //double dRTauJetClean_min=99999;
   
   double PseudoTauPhi=99999;
   double PseudoTauEta=99999; 
   
   double DecayTauPhi=99999;
   double DecayTauEta=99999;
   
   bool TauFound=false;
   bool TauDecay=false;

   /*std:: vector<unsigned int> JetKeys;
   int jetIdx=0;
   for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet,++jetIdx)
     {
       //size_t numJets = jets->size();
       //for (size_t iJet = 0; iJet < numJets; ++iJet) {
       //reco::PFJetRef jet(jets, iJet);
       reco::PFJetRef jet(pfJets,jetIdx);
       JetKeys.push_back(jet.key());
       
     }
   */

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
		   if( (!TauFound) && (fabs(Daughter->pdgId())!=13) &&  (fabs(Daughter->pdgId())!=14) && (fabs(Daughter->pdgId())!=15) && (fabs(Daughter->pdgId())!=22) && (fabs(Daughter->pdgId())!=16)  )
		     {
		       //cout<<"possible Hadronic Tau" <<endl;                                                                                                                                                                                                         
		       //cout<<" pdgId: " <<  Tau->pdgId()  << "  Tau Pt: " <<  Tau->pt()  <<  " Tau Eta: "  <<  Tau->eta()  <<endl;                                                                                                                                    
		       //cout<<" pdgId: " <<  Daughter->pdgId()  << "  Daughter Pt: " <<  Daughter->pt()  <<  " Daughter Eta: "  <<  Daughter->eta()  <<endl;                                                                                                          
		       TauFound=true;
		       //PseudoTauPhi.push_back(PseudoTau->phi());
		       //PseudoTauEta.push_back(PseudoTau->eta());
		       PseudoTauPhi=(double)(PseudoTau->phi());
		       PseudoTauEta=(double)(PseudoTau->eta());
		     }
		   bool isHad= false;
		   
		   if(fabs(Daughter->pdgId())==15)
		     {
		       isHad=!isSpecificDaughter(Daughter,13) && !isSpecificDaughter(Daughter,14);
			   if(isHad)
			     {
			       //cout<<" possible Decayed tau "<<endl;
			       TauDecay=true;
			       //DecayTauPhi.push_back(PseudoTau->phi());
			       //DecayTauEta.push_back(PseudoTau->eta());
			       DecayTauPhi=PseudoTau->phi();
			       DecayTauEta=PseudoTau->eta();
			       
			       
			     }
			   
		     }
		   
		 }
	       
	       
	     }
	     
	     
	 }
	 
	 
	 
     }

    
   
   
   
   
   
   for(pat::MuonCollection::const_iterator iMu = Muons1->begin() ; iMu !=Muons1->end() ; ++iMu)
     {
       for(pat::MuonCollection::const_iterator imu = Muons2->begin() ; imu !=Muons2->end() ; ++imu)
	 {
	   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
	     
	     {
	       //reco::PFJetRef JetRef = itau->pfJetRef();
	       //pat::tau::TauPFSpecific::jetRef JetRef=itau.jetRef();
	       //cout<< "pt" <<JetRef->pt() <<endl;
	       //pat::tau::TauPFSpecific tauSpecific = itau->pfSpecific();
	       //reco::PFJetRef Jet = tauSpecific.pfJetRef_;
	       for(pat::TauCollection::const_iterator itau_cl = TausCleaned->begin() ; itau_cl !=TausCleaned->end() ; ++itau_cl)
		 {
		   //for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet)                                                                                                                                                                  
		   //{    
		       
		       dRMu1Tau=reco::deltaR(*iMu,*itau);
		       dRMu2Tau=reco::deltaR(*imu,*itau);
		       dRMu1TauCleaned=reco::deltaR(*iMu,*itau_cl);
		       dRMu2TauCleaned=reco::deltaR(*imu,*itau_cl);
		       dRTauTauCleaned=reco::deltaR(*itau,*itau_cl);
		       //dRTauJet=reco::deltaR(*itau,*iJet);
		       
		       if(TauFound)
		     {
		       dRTauGenTau=reco::deltaR(PseudoTauEta,PseudoTauPhi,itau->eta(),itau->phi());
		       dRTauCleanedGenTau=reco::deltaR(PseudoTauEta,PseudoTauPhi,itau_cl->eta(),itau_cl->phi());
		     }
		       
		       if(TauDecay)
			 {
			   dRTauGenDecay=reco::deltaR(DecayTauEta,DecayTauPhi,itau->eta(),itau->phi());
			   dRTauCleanedGenDecay=reco::deltaR(DecayTauEta,DecayTauPhi,itau_cl->eta(),itau_cl->phi());
			 }
		       dRTaus->Fill(dRTauTauCleaned);
		       
		       bool dRMatch=false;


		       if(((TauFound && (dRTauGenTau < 0.05)) || (TauDecay && (dRTauGenDecay<0.05))) &&  (itau->tauID("decayModeFinding")) && (dRMu1Tau > Mu1TaudRCut_) && (dRMu2Tau  >  Mu2TaudRCut_)   )
			 {
			   ++GenMatchTau;
			 }
		       
		       if(((TauFound && (dRTauCleanedGenTau < 0.05)) || (TauDecay && (dRTauCleanedGenDecay<0.05))) &&  (itau_cl->tauID("decayModeFinding")) && (dRMu1TauCleaned >  Mu1TauCleaneddRCut_) && (dRMu2TauCleaned  >  Mu2TauCleaneddRCut_)  )
                         {
                           ++GenMatchTauCleaned;
			 }


		       
		       dRMatch=((dRMu1Tau > Mu1TaudRCut_) && (dRMu2Tau  >  Mu2TaudRCut_) && (dRMu1TauCleaned >  Mu1TauCleaneddRCut_) && (dRMu2TauCleaned  >  Mu2TauCleaneddRCut_) &&  (dRTauTauCleaned < TauTauCleaneddRCut_) &&  (itau->tauID("decayModeFinding")) && (itau_cl->tauID("decayModeFinding")) &&  ((TauFound && (dRTauGenTau < 0.05) && (dRTauCleanedGenTau<0.05))||(TauDecay && (dRTauGenDecay<0.05) && (dRTauCleanedGenDecay < 0.05))));
		       
		       
		   if(dRMatch)
		     {

		       
		       const reco::CandidatePtrVector  signalCands = itau->signalCands();
		       for (const auto& cands : signalCands) 
			 {
			 
			   std::cout <<"Uncleaned  pdgId: " << cands->pdgId()<< " pt:  " << cands->pt() << " eta: " << cands->pt() << " phi: " << cands->phi()  <<std::endl;
			 }

		       const reco::CandidatePtrVector  signalCandsCleaned = itau_cl->signalCands();
                       for (const auto& cand : signalCandsCleaned)
                         {
			   
			   std::cout <<"Cleaned  pdgId: " << cand->pdgId()<< " pt:  " << cand->pt() << " eta: " << cand->pt() << " phi: " << cand->phi()  <<std::endl;
                         }

		       
		       DMF->Fill(itau->decayMode(),itau_cl->decayMode());
		       DMF->SetOption("COLZ");

		       DiffsignalGammaCands->Fill((int)(itau_cl->signalGammaCands().size()) -(int) (itau->signalGammaCands().size()));
		       DiffsignalNeutrHadrCands->Fill((int)(itau_cl->signalNeutrHadrCands().size()) - (int)(itau->signalNeutrHadrCands().size()));
		       DiffsignalChargedHadrCands->Fill( (int)(itau_cl->signalChargedHadrCands().size()) - (int)(itau->signalChargedHadrCands().size()));
		       
		       DiffisolationChargedHadrCands->Fill((int)(itau_cl->isolationChargedHadrCands().size()) - (int)(itau->isolationChargedHadrCands().size()));
		       DiffisolationGammaCands->Fill((int)(itau_cl->isolationGammaCands().size()) - (int)(itau->isolationGammaCands().size()));
		       //cout<< " Cleaned Size isoGamma: " << itau_cl->isolationGammaCands().size()<<endl;
		       //cout<< " Uncleaned Size isoGamma: " << itau->isolationGammaCands().size()<<endl;
		       //cout<< " diff isoGamma:  " << (int)itau_cl->isolationGammaCands().size() - (int)itau->isolationGammaCands().size()<<endl;
		       
		       DiffisolationNeutrHadrCands->Fill((int)(itau_cl->isolationNeutrHadrCands().size()) - (int)(itau->isolationNeutrHadrCands().size()));
		       
		       
		       
		       IsoGammaCleanedVsUnCleaned->Fill((int)(itau->isolationGammaCands().size()),(int)(itau_cl->isolationGammaCands().size()));
		       IsoGammaCleanedVsUnCleaned->SetOption("COLZ");
		       
		       IsoChargedCleanedVsUnCleaned->Fill((int)(itau->isolationChargedHadrCands().size()),(int)(itau_cl->isolationChargedHadrCands().size()));
		       IsoChargedCleanedVsUnCleaned->SetOption("COLZ");
		       
		       IsoNeutCleanedVsUnCleaned->Fill((int)(itau->isolationNeutrHadrCands().size()),(int)(itau_cl->isolationNeutrHadrCands().size()));
		       IsoNeutCleanedVsUnCleaned->SetOption("COLZ");
		       
		       chargedIsoPtSum->Fill(itau->tauID("chargedIsoPtSum"),itau_cl->tauID("chargedIsoPtSum"));
		       chargedIsoPtSum->SetOption("COLZ");

		       neutralIsoPtSum->Fill(itau->tauID("neutralIsoPtSum"),itau_cl->tauID("neutralIsoPtSum"));
		       neutralIsoPtSum->SetOption("COLZ");
		       //}
		   
		       // int jetIdx=0;
		       reco::PFJet MatchedJet;
		       for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet /*,++jetIdx*/)  
			 {
			   //reco::PFJet MatchedJet;
			   dRTauJet=reco::deltaR(*itau,*iJet);
			   //cout<<"+++++++++++++dR :" << dRTauJet <<endl;
			   if(dRTauJet < dRTauJet_min)
			     {
			       dRTauJet_min=dRTauJet;
			       MatchedJet=*iJet;
			       //cout<< " ##########pt again: "<< MatchedJet.pt()<<endl;
			       //cout<<"----------dR:  "<< dRTauJet_min<<endl;
			     }
			   
			   
			 }
		       NHE1->Fill(MatchedJet.neutralHadronEnergy());
		       CHE1->Fill(MatchedJet.chargedHadronEnergy());
		       nMult1->Fill(MatchedJet.neutralMultiplicity());
		       PE1->Fill(MatchedJet.photonEnergy());
		       chMult1->Fill(MatchedJet.chargedHadronMultiplicity());
		       pMult1->Fill(MatchedJet.photonMultiplicity());
		       nhMult1->Fill(MatchedJet.neutralHadronMultiplicity());

		       //cout<<" MatchedJetEnergy: " <<MatchedJet.energy()<< endl;
		       //cout<<" MatchedJet pt: " <<MatchedJet.pt() << endl;
		       
		       reco::PFJet MatchedJetClean;
		       for (reco::PFJetCollection::const_iterator iJet_cl = pfJetsCl->begin(); iJet_cl != pfJetsCl->end(); ++iJet_cl /*,++jetIdx*/)
                         {
			   dRTauJetClean=reco::deltaR(*itau_cl,*iJet_cl);
			   if(dRTauJetClean < dRTauJetClean_min)
                             {
                               dRTauJetClean_min=dRTauJetClean;
                               MatchedJetClean=*iJet_cl;
			     }

			 }
		       NHE2->Fill(MatchedJetClean.neutralHadronEnergy());
		       CHE2->Fill(MatchedJetClean.chargedHadronEnergy());
		       nMult2->Fill(MatchedJetClean.neutralMultiplicity());
		       PE2->Fill(MatchedJetClean.photonEnergy());
		       chMult2->Fill(MatchedJetClean.chargedHadronMultiplicity());
		       pMult2->Fill(MatchedJetClean.photonMultiplicity());
		       nhMult2->Fill(MatchedJetClean.neutralHadronMultiplicity());

		       //cout<<" MatchedCleanJetEnergy: " <<MatchedJetClean.energy()<< endl;                                                                                                                                                                                             
                       //cout<<" MatchedCleanJet pt: " <<MatchedJetClean.pt() << endl;   
		     
		       NHE2D->Fill(MatchedJet.neutralHadronEnergy(),MatchedJetClean.neutralHadronEnergy());
		       NHE2D->SetOption("COLZ");
		       
		       CHE2D->Fill(MatchedJet.chargedHadronEnergy(),MatchedJetClean.chargedHadronEnergy());
                       CHE2D->SetOption("COLZ");
		       
		       CE2D->Fill(MatchedJet.chargedEmEnergy(),MatchedJetClean.chargedEmEnergy());
		       CE2D->SetOption("COLZ");

		       
		       nMult2D->Fill(MatchedJet.neutralMultiplicity(),MatchedJetClean.neutralMultiplicity());
                       nMult2D->SetOption("COLZ");

		       PE2D->Fill(MatchedJet.photonEnergy(),MatchedJetClean.photonEnergy());
		       PE2D->SetOption("COLZ");

		       
		       chMult2D->Fill(MatchedJet.chargedHadronMultiplicity(),MatchedJetClean.chargedHadronMultiplicity());
		       chMult2D->SetOption("COLZ");
		       
		       cMult2D->Fill(MatchedJet.chargedMultiplicity(),MatchedJetClean.chargedMultiplicity());
		       cMult2D->SetOption("COLZ");
		       
		       mMult2D->Fill(MatchedJet.muonMultiplicity(),MatchedJetClean.muonMultiplicity());
                       mMult2D->SetOption("COLZ");
		       
		       eMult2D->Fill(MatchedJet.electronMultiplicity(),MatchedJetClean.electronMultiplicity());
                       eMult2D->SetOption("COLZ");

		       pMult2D->Fill(MatchedJet.photonMultiplicity(),MatchedJetClean.photonMultiplicity());
		       pMult2D->SetOption("COLZ");;
			 
		       nhMult2D->Fill(MatchedJet.neutralHadronMultiplicity(),MatchedJetClean.neutralHadronMultiplicity());
		       nhMult2D->SetOption("COLZ");
		       
		       JE2D->Fill(MatchedJet.energy(),MatchedJetClean.energy());
		       JE2D->SetOption("COLZ");

		       Pt2D->Fill(itau->pt(),itau_cl->pt());
		       Pt2D->SetOption("COLZ");
		     }
		 }
	       
	     }
	 }
     }
   
   
   /*for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)

     {                                                                                                                                                                                                   
       for(pat::TauCollection::const_iterator itau_cl = TausCleaned->begin() ; itau_cl !=TausCleaned->end() ; ++itau_cl)
	 {
	   Pt2D->Fill(itau->pt(),itau_cl->pt());
	   Pt2D->SetOption("COLZ");
   
	 }
     }   
   */
   std::cout<<" UnCleaned Match: "<< GenMatchTau <<std::endl;
   std::cout<<" Cleaned Match: "<< GenMatchTauCleaned <<std::endl;

}


// ------------ method called once each job just before starting event loop  ------------
void 
TauComparatorAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauComparatorAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TauComparatorAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TauComparatorAnalyzer);
