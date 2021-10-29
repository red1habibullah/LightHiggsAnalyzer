// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      TauEfficiencyMuMVA
// 
/**\class TauEfficiencyMuMVA TauEfficiencyMuMVA.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/TauEfficiencyMuMVA.cc

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
#include "Math/LorentzVector.h"

#include "Math/VectorUtil.h"
#include "TLorentzVector.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TauEfficiencyMuMVA : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TauEfficiencyMuMVA(const edm::ParameterSet&);
      ~TauEfficiencyMuMVA();
  bool isSpecificDaughter(const reco::Candidate * particle,int Id);
  double RefToDaughterPhi(const reco::Candidate * particle,int Id);
  double RefToDaughterEta(const reco::Candidate * particle,int Id);
  double RefToDaughterPt(const reco::Candidate * particle,int Id);
  bool isFSR(const reco::Candidate * daughter);
  std::vector<const reco::Candidate*>FindStat1Vis( const reco::Candidate * particle);
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
  
  TH1D* NumdR;
  TH1D* DenomdR;
  
  TH1D* NumIsodR;
  TH1D* DenomIsodR;


  TH1D *NumVis;
  TH1D *DenomVis;
  
  TH1D *NumTotalLep;
  TH1D *DenomTotalLep;
  
  TH1D *NumComboLep;
  TH1D* DenomComboLep;
  
  TH1D *NumIsoLep;
  TH1D *DenomIsoLep;

  TH1D* NumTotaldR;
  TH1D* DenomTotaldR;
  
  TH1D *NumTotalVis;
  TH1D *DenomTotalVis;

  TH1D *NumComboVis;
  TH1D *DenomComboVis;

  //TH1D* NumIsodR;
  //TH1D* DenomIsodR;

  TH1D *NumIsoVis;
  TH1D *DenomIsoVis;
  
  TH2D *NumdRLep;
  TH2D *DenomdRLep;
  
  
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

  double dRJetGenTauRep=99999;
  double dRJetGenDecayRep=99999;

  double dRMuGenMu=99999;
  double dRMuGenDecay=99999;
  
  double dRMuGenMuRep=99999;
  double dRMuGenDecayRep=99999;
  
  double dRMuTau=99999;
  double dRTauJet=99999;
  double dRTauJetCombo=99999;
  
  double dRTauMu=99999;
  double dRDecayTauMu=99999;
  double dRTauDecayMu=99999;
  double dRDecayTauDecayMu=99999;

  int NumCount=0;
  int DenomCount=0;
  

  int NumCountIso=0;
  int DenomCountIso=0;

  int NumCount0=0;
  int DenomCount0=0;

  int Counter=0;
  int TauHad_Counter=0;
  int TauDecay_Counter=0;
  //Make the Isolation discriminators a variable
  std::string TauIdRawValue_;
  std::string TauIdMVAWP_;
};

//
//
// constants, enums and type//
// static data member definitions
//

//
// constructors and destructor
//
TauEfficiencyMuMVA::TauEfficiencyMuMVA(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  muonSrc_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonSrc"))),
  jetSrc_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("jetSrc"))),
  TauIdRawValue_(iConfig.getParameter<std::string>("TauIdRawValue")),
  TauIdMVAWP_(iConfig.getParameter<std::string>("TauIdMVAWP"))
  
{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;
   const int  nbins =5;
   double edges[nbins+1]={10,15,20,30,50,100};
   double edgesLep[nbins+1]={0,10,20,30,50,100};
   TauEff = f->make<TEfficiency>("TauEff","Tau Reconstruction  Efficiency;Pt(GeV);#epsilon",nbins,edges);
   
   NumDMode = f->make<TH1F>("NumDMode","Numerator for Reconstruction Efficiency;Jet Pt(GeV);# of Events",nbins,edges);
   DenomDMode = f->make<TH1F>("DenomDMode","Denominator for Reconstruction Efficiency;Jet Pt(GeV);# of Events",nbins,edges);
  
   NumdR = f->make<TH1D>("NumdR","Numerator for Reconstruction Efficiency;dR(#tau_{had},#tau_{#mu});# of Events",10,0,1);
   DenomdR = f->make<TH1D>("DenomdR","Denominator for Reconstruction Efficiency;dR(#tau_{had},#tau_{#mu});# of Events",10,0,1);
   
   NumIsodR = f->make<TH1D>("NumIsodR","Numerator for Isolation Efficiency;dR(#tau_{had},#tau_{#mu});# of Events",10,0,1);
   DenomIsodR = f->make<TH1D>("DenomIsodR","Denominator for Isolation Efficiency;dR(#tau_{had},#tau_{#mu});# of Events",10,0,1);
   
   NumTotalLep = f->make<TH1D>("NumTotalLep","Numerator for Reconstruction Efficiency;#tau_{#mu} Pt(GeV);# of Events",nbins,edgesLep);
   DenomTotalLep = f->make<TH1D>("DenomTotalLep","Denominator for Reconstruction Efficiency;#tau_{#mu} Pt (GeV);# of Events",nbins,edgesLep);
   
   
   NumComboLep = f->make<TH1D>("NumComboLep","Numerator for  #tau_{#mu}#tau_{had} Efficiency; #tau_{#mu}#tau_{had} Pt(GeV);# of Events",nbins,edgesLep);
   DenomComboLep = f->make<TH1D>("DenomComboLep","Denominator for  #tau_{#mu}#tau_{had} Efficiency; #tau_{#mu}#tau_{had} Pt (GeV);# of Events",nbins,edgesLep);
   
   
   NumIsoLep = f->make<TH1D>("NumIsoLep","Numerator for Reconstruction Efficiency;#tau_{#mu} Pt(GeV);# of Events",nbins,edgesLep);
   DenomIsoLep = f->make<TH1D>("DenomIsoLep","Denominator for Reconstruction Efficiency;#tau_{#mu} Pt (GeV);# of Events",nbins,edgesLep);

   
   
   NumVis = f->make<TH1D>("NumVis","Numerator for Reconstruction Efficiency;#tau_{had} Visible Pt(GeV);# of Events",nbins,edges);
   DenomVis = f->make<TH1D>("DenomVis","Denominator for Reconstruction Efficiency;#tau_{had} Visible Pt (GeV);# of Events",nbins,edges);
   
   NumTotaldR = f->make<TH1D>("NumTotaldR","Numerator for Total Reconstruction Efficiency;dR(#tau_{had},#tau_{#mu});# of Events",10,0,1);
   DenomTotaldR = f->make<TH1D>("DenomTotaldR","Denominator for Total Reconstruction Efficiency;dR(#tau_{had},#tau_{#mu});# of Events",10,0,1);

   NumTotalVis = f->make<TH1D>("NumTotalVis","Numerator for Total Reconstruction Efficiency;#tau_{had} Visible Pt(GeV);# of Events",nbins,edges);
   DenomTotalVis = f->make<TH1D>("DenomTotalVis","Denominator for Total Reconstruction Efficiency;#tau_{had} Visible Pt (GeV);# of Events",nbins,edges);

   NumComboVis = f->make<TH1D>("NumComboVis","Numerator for #tau_{#mu}#tau_{had} Efficiency;#tau_{had} Visible Pt(GeV);# of Events",nbins,edges);
   DenomComboVis = f->make<TH1D>("DenomComboVis","Denominator for #tau_{#mu}#tau_{had} Efficiency;#tau_{had} Visible Pt (GeV);# of Events",nbins,edges);

   //NumIsodR = f->make<TH1D>("NumIsodR","Numerator for Isolation Efficiency;dR(#tau_{had},#tau_{lep});# of Events",10,0,1);
   //DenomIsodR = f->make<TH1D>("DenomIsodR","Denominator for Isolation Efficiency;dR(#tau_{had},#tau_{lep});# of Events",10,0,1);

   NumIsoVis = f->make<TH1D>("NumIsoVis","Numerator for Isolation Efficiency;#tau_{had} Visible Pt(GeV);# of Events",nbins,edges);
   DenomIsoVis = f->make<TH1D>("DenomIsoVis","Denominator for Isolation Efficiency;#tau_{had} Visible Pt (GeV);# of Events",nbins,edges);

   NumdRLep= f->make<TH2D>("NumdRLep","#tau_{#mu} Pt (GeV) vs dR(#tau_{had},#tau_{#mu});dR(#tau_{had},#tau_{#mu});#tau_{#mu} Pt (GeV)",10,0,1,nbins,edgesLep);
   DenomdRLep= f->make<TH2D>("DenomdRLep","#tau_{#mu} Pt (GeV) vs dR(#tau_{had}),#tau_{#mu};dR(#tau_{had},#tau_{#mu});#tau_{#mu} Pt (GeV)",10,0,1,nbins,edgesLep);

   
   
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


TauEfficiencyMuMVA::~TauEfficiencyMuMVA()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}




bool TauEfficiencyMuMVA::isSpecificDaughter(const reco::Candidate * particle,int Id)
{
  if ((fabs(particle->pdgId())==Id) && (particle->status()==1))
    return true;
  for(size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(isSpecificDaughter(particle->daughter(i),Id)) return true;

    }
  return false;
}

double TauEfficiencyMuMVA::RefToDaughterPhi(const reco::Candidate * particle,int Id)
{

  double Phi=0;
  if ((fabs(particle->pdgId())==Id) && (particle->status()==1))
    return particle->phi();
  for( size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(RefToDaughterPhi(particle->daughter(i),Id))
        Phi=particle->daughter(i)->phi();

    }
  return Phi;
}



double TauEfficiencyMuMVA::RefToDaughterEta(const reco::Candidate * particle,int Id)
{

  double Eta=0;
  if ((fabs(particle->pdgId())==Id) && (particle->status()==1))
    return particle->eta();
  for( size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(RefToDaughterEta(particle->daughter(i),Id))
        Eta=particle->daughter(i)->eta();

    }
  return Eta;
}

double TauEfficiencyMuMVA::RefToDaughterPt(const reco::Candidate * particle,int Id)
{

  double Pt=0;
  if ((fabs(particle->pdgId())==Id) && (particle->status()==1))
    return particle->pt();
  for( size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(RefToDaughterPt(particle->daughter(i),Id))
        Pt=particle->daughter(i)->pt();

    }
  return Pt;
}



std::vector<const reco::Candidate*>TauEfficiencyMuMVA::FindStat1Vis( const reco::Candidate * particle)

{
  
  std::vector<const reco::Candidate*> visParticles;
  if (particle->status() == 1)
    {
      if (fabs(particle->pdgId()) != 14 && fabs(particle->pdgId()) != 16)

      {
	visParticles.push_back(particle);
	
      }
    }
  else
    { 
      
      int nGrandDaughters= particle->numberOfDaughters();
      for (int i=0; i < nGrandDaughters; i++)
	{
	  const reco::Candidate* GrandDaughter= particle->daughter(i);
	  std::cout<< " GrandDaughter no:  "<< i << "  pdgId: " << GrandDaughter->pdgId() <<" GrandDaughter Pt: " << GrandDaughter->pt()<<" GrandDaughter Status: " << GrandDaughter->status()<<std::endl;

	  if(GrandDaughter->status() == 1)
	    {
	      if(fabs(GrandDaughter->pdgId()) != 14 && fabs(GrandDaughter->pdgId()) != 16)
		{
		  visParticles.push_back(GrandDaughter);
		  
		}
	    }
	  else
	    {
	      auto auxVisParticles = FindStat1Vis(GrandDaughter);
	      visParticles.insert(visParticles.end(), auxVisParticles.begin(), auxVisParticles.end());
	    }
	}
    }
  return visParticles;
}




bool TauEfficiencyMuMVA::isFSR(const reco::Candidate * Daughter)
{
  if ((Daughter->status()==1) && (fabs(Daughter->pdgId())== 15))
    return true;
  
  for( size_t i=0;i <Daughter->numberOfDaughters();i++)
    {
     
	  if(isFSR(Daughter->daughter(i))) return true;
	
	 
      
    }
  return false;

}



//
// member functions
//

// ------------ method called for each event  ------------
void
TauEfficiencyMuMVA::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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
   double MuPt=99999;
   
   vector <double> DRs;
   DRs.clear();
   vector <double> DRDecays;
   DRDecays.clear();
   
   vector <double> DRsRep;
   DRsRep.clear();
   vector <double> DRDecaysRep;
   DRDecaysRep.clear();

   double MuDecayEta=99999;
   double MuDecayPhi=99999;
   
   TLorentzVector VisProducts;
   TLorentzVector VisHad;
   TLorentzVector VisDecayMuon;
   TLorentzVector VisDecayHad;
   
   double Tau_had_pt_v2=99999;
    
   
   bool TauFound=false;
   bool TauDecay=false;
   
   //bool TauCalc= false;
   

   bool MuFound=false;
   bool MuDecay=false;

   bool TmuThad=false;
   








   //-----------------------Determination of Gen Tau_mu Tau_Had-------------------------------------
   for(size_t i=0; i<(pruned.product())->size() ;i++)
     {
       if(fabs((*pruned)[i].pdgId())==15)
         {
	   
	   const Candidate * Tau = &(*pruned)[i];
           if (fabs(Tau->mother()->pdgId())==36)
             {
	       //cout << " Tau from PseudoScalar " <<endl;
	       
               const Candidate *PseudoTau = &(*pruned)[i];
	       //cout<< " Tau Pt: " << PseudoTau->pt() <<endl;
               unsigned  n=PseudoTau->numberOfDaughters();
	       
               for ( size_t j =0; j < n ; j++)
                 {
                   
		   
		   const Candidate * Daughter=PseudoTau->daughter(j);
                   std::vector <const reco::Candidate*> daughters;
		   daughters.clear();
		   std::vector<const reco::Candidate*> Decaydaughters;
		   Decaydaughters.clear();
		   
		   //cout<< " Daughter no:  "<< j << "  pdgId: " << Daughter->pdgId() <<" Daughter Pt: " << Daughter->pt()<<" Daughter Status: " << Daughter->status()<<endl;
		   bool isHad= false;
		   bool isMuon=false;
		   bool FSR=false;
		   
		   
		   if(fabs(Daughter->pdgId())==15)
                     {
                      
		       FSR=isFSR(Daughter);
		       
		       
		       //cout<<" ************** FSR Flag****************: " << FSR <<endl; 
		       if(!FSR)    
			 {
			   Decaydaughters=FindStat1Vis(Daughter);
			   
			   for (unsigned int jDau = 0; jDau < Decaydaughters.size(); jDau++)
                             {
			       //cout<<" Recursive Visible  Decaydaughter pdgId :  " <<  Decaydaughters[jDau]->pdgId() << "  Recursive Visible Decaydaughter Status: "<<   Decaydaughters[jDau]->status()  <<" Recursive Visible Decaydaughter Pt:"<< Decaydaughters[jDau]->pt()<<endl;
			       
			       //------------------------Decayed Tau_mu-----------------------------------------------
			       if(fabs(Decaydaughters[jDau]->pdgId())==13)
				 {
				   
				   VisDecayMuon +=TLorentzVector(Decaydaughters[jDau]->p4().px(),Decaydaughters[jDau]->p4().py(),Decaydaughters[jDau]->p4().pz(),Decaydaughters[jDau]->p4().e());
				   
				   //cout<<" Recursively Identified Muon pdgId : " << Decaydaughters[jDau]->pdgId() << " Recursively identified Muon  Status:    "<<   Decaydaughters[jDau]->status()  <<" Recursively Identified Muon Pt: "<< Decaydaughters[jDau]->pt()<<endl;

				   isMuon=true;
				 }
			       //-------------------------------Decayed viz Tau_Had------------------------------------
			       else
				 {
				   VisDecayHad+=TLorentzVector(Decaydaughters[jDau]->p4().px(),Decaydaughters[jDau]->p4().py(),Decaydaughters[jDau]->p4().pz(),Decaydaughters[jDau]->p4().e());
				   //cout<<"  Recursively Identified Hadron pdgId : " << Decaydaughters[jDau]->pdgId() << " Recursively identified Hadron  Status:  "<<   Decaydaughters[jDau]->status()  <<"  Recursive Identified  Hadron Pt:"<< Decaydaughters[jDau]->pt()<<endl;
				   isHad=true;
				 }
			       
			       
			       
			     }
			   

			 
			   
			   if(isHad && (VisDecayHad.Pt() >10) && (fabs(VisDecayHad.Eta()) <2.3))
			     {
			       
			       TauDecay=true;
			       
			       DecayTauPhi=VisDecayHad.Phi();
			       DecayTauEta=VisDecayHad.Eta();			       
			       cout<< " Decay Had Pt: "<< VisDecayHad.Pt()<<endl;
			       cout<< " Decay Had Eta: "<< VisDecayHad.Eta()<<endl;
			       cout<< " Decay Had Phi: "<< VisDecayHad.Phi()<<endl;


			     }
			   if(isMuon && (VisDecayMuon.Pt() >3) && (fabs(VisDecayMuon.Eta()) <2.4) )
			     {
			       
			       MuDecay=true;
			       MuDecayEta=VisDecayMuon.Eta();
			       
			       MuDecayPhi=VisDecayMuon.Phi();
			       cout<< " Decay Muon Pt: "<< VisDecayMuon.Pt()<<endl;
			       cout<< " Decay Muon Eta: "<< VisDecayMuon.Eta()<<endl;
			       cout<< " Decay Muon Phi: "<< VisDecayMuon.Phi()<<endl;


			     }
			   
			 }
			 
		     }
		   
		   ///----------------------------------------------Tau_mu-------------------------------------------------------------
		   if ((fabs(Daughter->pdgId())==13) && ((Daughter->pt())>3) && (abs(Daughter->eta()) < 2.4) && (Daughter->status()==1))
                     {   

                       MuFound=true;
		       
                       MuEta=(double)(Daughter->eta());
		       MuPhi=(double)(Daughter->phi());
		       MuPt=(double)(Daughter->pt());

                     }
      		   ///---------------------------viz Tau_had--------------------------------------------------------------------------
		   if((fabs(Daughter->pdgId())!=13) &&  (fabs(Daughter->pdgId())!=14) && (fabs(Daughter->pdgId())!=15) &&  (fabs(Daughter->pdgId())!=16)  && (fabs(Daughter->pdgId())!=22) // && ((PseudoTau->pt()) > 10) && (abs(PseudoTau->eta()) <2.3 
		      )
																											   
		     {
		       if(Daughter->status()==1)
			 {
			   VisHad +=TLorentzVector(Daughter->p4().px(),Daughter->p4().py(),Daughter->p4().pz(),Daughter->p4().e());

			 } 
			 
		       else
			 {
			   daughters = FindStat1Vis(Daughter);
			   
			   for (unsigned int jDau = 0; jDau < daughters.size(); jDau++)
			     {
			       VisHad +=TLorentzVector(daughters[jDau]->p4().px(),daughters[jDau]->p4().py(),daughters[jDau]->p4().pz(),daughters[jDau]->p4().e());
			       //cout<<" Recursive daughter pdgId : " << daughters[jDau]->pdgId() << "Recursive Daughter Status:    "<<   daughters[jDau]->status()  <<" Recursive Daughter Pt:"<< daughters[jDau]->pt()<<endl; 
			     }
			   
			 }
		     }
		     
		     

		   
		   
		   if((fabs(Daughter->pdgId())!=13) &&  (fabs(Daughter->pdgId())!=14) && (fabs(Daughter->pdgId())!=15) && (fabs(Daughter->pdgId())!=22) // && ((PseudoTau->pt()) > 10) && (abs(PseudoTau->eta()) <2.3)
		      )
                     {
		       

		       if((fabs(Daughter->pdgId())!=16))
			 {
		       //cout<< " Daughter in Tau Had:  "<< j << "  pdgId: " << Daughter->pdgId() <<" Pt:     "<< Daughter->pt()<<endl;
			   VisProducts +=TLorentzVector(Daughter->p4().px(),Daughter->p4().py(),Daughter->p4().pz(),Daughter->p4().e());
 
			 }
		     }
		   
		 

		   
		   
		   
		   
		   
		   
		   
		   
		   
		 



		 }

	       
             }
	   
	   
         }
       
       
       
     }
      
   if( (VisHad.Pt() >10) && (fabs(VisHad.Eta()) <2.3))
 
     {
       TauFound=true;
       PseudoTauPhi=(double)(VisHad.Phi() );
       PseudoTauEta=(double)(VisHad.Eta());

     }
   if(TauFound)
     {
     Tau_had_pt_v2=(double)VisProducts.Pt();
     cout<<" Vis Had Pt_v1: "<<Tau_had_pt_v2<<endl;
     cout<< "Vis Had Pt : "<<(double)VisHad.Pt()<<endl; 
     cout<< "Vis Had Eta: "<<(double)VisHad.Eta()<<endl;

     }
   
   



   //-------------------_Tau_mu Tau_had count-----------------------------
   TmuThad=((TauFound) || (TauDecay )) && ((MuFound) || (MuDecay));
   if(TmuThad)
     {
       ++Counter;
     }
   if(TauFound)
     {
       ++TauHad_Counter;
     }
   if(TauDecay)
     {
       ++TauDecay_Counter;
     }

   
   //-------------------------- Tau_mu Tau_had Efficiency-------------------
   for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet)
     {
       
       if(TauFound)
	 {
	   
	   dRJetGenTau=reco::deltaR(PseudoTauEta,PseudoTauPhi,iJet->eta(),iJet->phi());
	   
	 }
       
       if(TauDecay)
	 {
	   
	   dRJetGenDecay=reco::deltaR(DecayTauEta,DecayTauPhi,iJet->eta(),iJet->phi());
	   
	 }
       bool GenMatchedCombo=false;                                                                                                                                                                                                                                      
       bool AnalysisCutCombo=false;
       

       GenMatchedCombo=((TauFound && (dRJetGenTau < 0.1)) || (TauDecay && (dRJetGenDecay<0.1))) && (MuFound || MuDecay);        
       AnalysisCutCombo=((iJet->pt() > 10) && (fabs(iJet->eta()) <2.3));  
       
       if(GenMatchedCombo && AnalysisCutCombo)
	 {

	   if(TauFound)                                                                                                           
	     {                                                                                                                      
	       DenomComboVis->Fill((double)VisHad.Pt());                                                                            
	     }                                                                                                                      
	   if(TauDecay)                                                                                                           
	     {                                                                                                                    
	       DenomComboVis->Fill((double)VisDecayHad.Pt());                                                                     
	     }                                                                                                                    
                                                                                                                                      
	   if(MuFound)                                                                                                            
	     {                                                                                                                    
	       DenomComboLep->Fill(MuPt);                                                                                         
	     }                                                                                                                    
	   if(MuDecay)                                                                                                            
	     {                                                                                                                    
	       DenomComboLep->Fill((double)VisDecayMuon.Pt());                                                                    
	     }                                                                                                                    
	   bool PassMVACombo=false;
	   //for(pat::TauCollection::const_iterator iTau = Taus->begin() ; iTau !=Taus->end() ; ++iTau)                             
	   //{ 
	       
	       
	       for(pat::MuonCollection::const_iterator iMuon = Muon->begin() ; iMuon !=Muon->end() ; ++iMuon)
		 {

		   bool AnalysisCutsRep= false;
		   bool GenMatchedRep=false;
		   if(TauFound)
		     {
		       
		       dRJetGenTauRep=reco::deltaR(PseudoTauEta,PseudoTauPhi,iJet->eta(),iJet->phi());
		       
		     }
		   
		   if(TauDecay)
		     {
		       
		       dRJetGenDecayRep=reco::deltaR(DecayTauEta,DecayTauPhi,iJet->eta(),iJet->phi());
		       
		     }
		   if(MuFound)
		     {
		       dRMuGenMuRep=reco::deltaR(MuEta,MuPhi,iMuon->eta(),iMuon->phi());
		       
		     }
		   if(MuDecay)
		     {
		       dRMuGenDecayRep=reco::deltaR(MuDecayEta,MuDecayPhi,iMuon->eta(),iMuon->phi());
		       
		     }
		   GenMatchedRep= ((TauFound && (dRJetGenTauRep < 0.1)) || (TauDecay && (dRJetGenDecayRep <0.1))) && ((MuFound && (dRMuGenMuRep < 0.1)) || (MuDecay && (dRMuGenDecayRep <0.1)));
		   AnalysisCutsRep= ((iJet->pt() > 10) && (fabs(iJet->eta()) <2.3));
		   
		   
		   if(GenMatchedRep && AnalysisCutsRep)
		     {
		       if((MuFound || MuDecay) && (dRMuGenMuRep < 0.1))
			 {
			   DRsRep.push_back(dRMuGenMuRep);
			 }				
		       if((MuDecay|| MuFound) && (dRMuGenDecayRep <0.1))
			 {
			   
			   DRDecaysRep.push_back(dRMuGenDecayRep);
			 }            
		       
		       
		     }
		   
		   
		   
		   
		   
		   
		 }
	       
	       double dR_min=99999;
	       bool dRMatch=false;
	       if( (MuFound || MuDecay) && (DRsRep.size()) >=2)
		 {

		   for( unsigned int i=0; i <DRsRep.size() ; i++)
		     
		     {
		       if(DRsRep[i]< dR_min)
			 {
			   dR_min=DRsRep[i];
			   dRMatch=true;
			 }
		       
		     }
		 }
	       
	       double dR_Decay_min=99999;
	       double dRDecayMatch=false;
	       if((MuDecay || MuFound) && (DRDecaysRep.size()) >=2)
		 {
		   
		   for(unsigned int i=0; i <DRDecaysRep.size() ; i++)
		     
		     {
		       if(DRDecaysRep[i]< dR_Decay_min)
			 {
			   dR_Decay_min=DRDecaysRep[i];
			   dRDecayMatch=true;
			 }
		       
		     }
		   
		   
		 }
	       
	       if((MuFound || MuDecay) && (DRsRep.size())==1)
		 {
		   dR_min=DRsRep[0];
		   
		   dRMatch=true;
		 }
	       if((MuDecay || MuFound) && (DRDecaysRep.size())==1)
		 {
		   dR_Decay_min=DRDecaysRep[0];
		   dRDecayMatch=true;
		 }
	       
	       
	       for(pat::MuonCollection::const_iterator iMuon = Muon->begin() ; iMuon !=Muon->end() ; ++iMuon)
		 {
		   if(MuFound)
		     {
		       dRMuGenMu=reco::deltaR(MuEta,MuPhi,iMuon->eta(),iMuon->phi());
		       
		     }
		   if(MuDecay)
		     {
		       dRMuGenDecay=reco::deltaR(MuDecayEta,MuDecayPhi,iMuon->eta(),iMuon->phi());
		       
		     }
		   for(pat::TauCollection::const_iterator iTau = Taus->begin() ; iTau !=Taus->end() ; ++iTau)
		     {
		       
		       
		       dRMuTau=reco::deltaR(*iTau,*iMuon);
		       dRTauJetCombo=reco::deltaR(*iTau,*iJet);
		       PassMVACombo=(dRMuTau <0.8) && (dRTauJetCombo < 0.1) &&  ((iTau->tauID(TauIdRawValue_) >-0.5) && (iTau->tauID(TauIdMVAWP_))) && ((MuFound && ((dRMuGenMu==dR_min) && (dRMatch))) || (MuDecay && ((dRMuGenDecay==dR_Decay_min) && (dRDecayMatch))));
		       
		       if(PassMVACombo)
			 {
			   
			   
			   
			   if(MuFound)
			     {
			       NumComboLep->Fill(MuPt);
			     }
			   if(MuDecay)
			     {
			       NumComboLep->Fill((double)VisDecayMuon.Pt());
			     }
			   
			   
			   if(TauFound)
			     {
			       NumComboVis->Fill((double)VisHad.Pt());
			     }
			   if(TauDecay)
			     {
			       NumComboVis->Fill((double)VisDecayHad.Pt());
			     }
			   
			   
			   
			   
			 }
		     }
		 }
	       
	       //}
	 }
     }
   


	 






   




   //-------------------------------Tau had efficiency------------------------------------------
   for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet)
     {
       
       
       //Need to Create a replica of the conditions below to fill the vectors appropriately without the chance of running into a rogue for loop problem
       


       for(pat::MuonCollection::const_iterator iMuon = Muon->begin() ; iMuon !=Muon->end() ; ++iMuon)
         {

	   bool AnalysisCutsRep= false;
           bool GenMatchedRep=false;
	   if(TauFound)
             {

               dRJetGenTauRep=reco::deltaR(PseudoTauEta,PseudoTauPhi,iJet->eta(),iJet->phi());

	     }

           if(TauDecay)
             {

               dRJetGenDecayRep=reco::deltaR(DecayTauEta,DecayTauPhi,iJet->eta(),iJet->phi());

             }
           if(MuFound)
             {
               dRMuGenMuRep=reco::deltaR(MuEta,MuPhi,iMuon->eta(),iMuon->phi());

             }
           if(MuDecay)
             {
	       dRMuGenDecayRep=reco::deltaR(MuDecayEta,MuDecayPhi,iMuon->eta(),iMuon->phi());

             }
	   GenMatchedRep= ((TauFound && (dRJetGenTauRep < 0.1)) || (TauDecay && (dRJetGenDecayRep <0.1))) && ((MuFound && (dRMuGenMuRep < 0.1)) || (MuDecay && (dRMuGenDecayRep <0.1)));
           AnalysisCutsRep= ((iJet->pt() > 10) && (fabs(iJet->eta()) <2.3));


	   if(GenMatchedRep && AnalysisCutsRep)
	     {
	       if((MuFound || MuDecay) && (dRMuGenMuRep < 0.1))
		 {
		   DRsRep.push_back(dRMuGenMuRep);
		 }				
	       if((MuDecay|| MuFound) && (dRMuGenDecayRep <0.1))
		 {
		   
		   DRDecaysRep.push_back(dRMuGenDecayRep);
		 }            
	       
	       
	     }
	   
	 
	 
	 


	 }
       
       double dR_min=99999;
       bool dRMatch=false;
       if( (MuFound || MuDecay) && (DRsRep.size()) >=2)
	 {
	   
	   for( unsigned int i=0; i <DRsRep.size() ; i++)
	     
	     {
	       if(DRsRep[i]< dR_min)
		 {
		   dR_min=DRsRep[i];
		   dRMatch=true;
		 }
	       
	     }
	 }
       
       double dR_Decay_min=99999;
       double dRDecayMatch=false;
       if((MuDecay || MuFound) && (DRDecaysRep.size()) >=2)
	 {
	   
	   for(unsigned int i=0; i <DRDecaysRep.size() ; i++)
	     
	     {
	       if(DRDecaysRep[i]< dR_Decay_min)
		 {
		   dR_Decay_min=DRDecaysRep[i];
		   dRDecayMatch=true;
		 }
	       
	     }
	  

	 }
	  
        if((MuFound || MuDecay) && (DRsRep.size())==1)
	 {
	   dR_min=DRsRep[0];

	   dRMatch=true;
	 }
       if((MuDecay || MuFound) && (DRDecaysRep.size())==1)
	 {
	   dR_Decay_min=DRDecaysRep[0];
	   dRDecayMatch=true;
	 }
      
       
       for(pat::MuonCollection::const_iterator iMuon = Muon->begin() ; iMuon !=Muon->end() ; ++iMuon)
	 {
	   
	   
	   

	   bool AnalysisCuts= false;
	   bool GenMatched =false;
	   bool TauMu =false;
	   bool TauDecayMu = false;
	   bool DecayTauMu = false;
	   bool DecayTauDecayMu= false;
	       
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
	   
	   if(TauFound && MuFound)
	     {
	       dRTauMu=reco::deltaR(PseudoTauEta,PseudoTauPhi,MuEta,MuPhi);
	       TauMu=true;
	       //cout<<" dRTauMu: "<< dRTauMu<<endl;

	     }
	   if(TauFound && MuDecay)
	     {
	       dRTauDecayMu=reco::deltaR(PseudoTauEta,PseudoTauPhi,MuDecayEta,MuDecayPhi);
	       TauDecayMu = true;
	       //cout<<" dRTauDecayMu: "<< dRTauDecayMu<<endl;

	     }
	   if(TauDecay && MuFound)
	     {
	       dRDecayTauMu=reco::deltaR(DecayTauEta,DecayTauPhi,MuEta,MuPhi);
	       DecayTauMu = true;
	       //cout<<" dRDecayTauMu: "<< dRDecayTauMu<<endl;

	     }
	   if(TauDecay && MuDecay)
	     {
	       dRDecayTauDecayMu=reco::deltaR(DecayTauEta,DecayTauPhi,MuDecayEta,MuDecayPhi);
	       DecayTauDecayMu= true;
	       //cout<<" dRDecayTauDecayMu: "<< dRDecayTauDecayMu<<endl;
	     }
	   
	
	   GenMatched= ((TauFound && (dRJetGenTau < 0.1)) || (TauDecay && (dRJetGenDecay<0.1))) && ((MuFound && ((dRMuGenMu==dR_min) && (dRMatch))) || (MuDecay && ((dRMuGenDecay==dR_Decay_min) && (dRDecayMatch))));
	   AnalysisCuts= ((iJet->pt() > 10) && (fabs(iJet->eta()) <2.3));
	       
	   
	       


	   
	   
	   
	   if(GenMatched && AnalysisCuts)
		 {
		   ++DenomCount;
		   DenomDMode->Fill(iJet->pt());
		   if(TauMu)
		     {
		       DenomdR->Fill(dRTauMu);
		     }
		   if(TauDecayMu)
		     {
		       DenomdR->Fill(dRTauDecayMu);
		     }
		   if(DecayTauMu)
		     {
		       DenomdR->Fill(dRDecayTauMu);
		     }
		   if (DecayTauDecayMu)
		     {
		       DenomdR->Fill(dRDecayTauDecayMu);
		     }
		   
		   if(TauFound)
		     {
		       DenomVis->Fill((double)VisHad.Pt());
		       
		     }
		   if(TauDecay)
                     {
                       DenomVis->Fill((double)VisDecayHad.Pt());

                     }
		   
		   
		     
		   if(TauMu)
                     {
                       DenomIsodR->Fill(dRTauMu);
                     }
                   if(TauDecayMu)
                     {
                       DenomIsodR->Fill(dRTauDecayMu);
                     }
                   if(DecayTauMu)
                     {
                       DenomIsodR->Fill(dRDecayTauMu);
                     }
                   if (DecayTauDecayMu)
                     {
                       DenomIsodR->Fill(dRDecayTauDecayMu);
                     }

		   if(TauMu)
                     {
                       DenomdRLep->Fill(dRTauMu,MuPt);
		       DenomdRLep->SetDrawOption("COLZ");
		     }
                   if(TauDecayMu)
                     {
                       DenomdRLep->Fill(dRTauDecayMu,(double)VisDecayMuon.Pt());
                       DenomdRLep->SetDrawOption("COLZ");

		     }
                   if(DecayTauMu)
                     {
                       DenomdRLep->Fill(dRDecayTauMu,MuPt);
		       DenomdRLep->SetDrawOption("COLZ");

                     }
                   if (DecayTauDecayMu)
                     {
                       DenomdRLep->Fill(dRDecayTauDecayMu,(double)VisDecayMuon.Pt());
		       DenomdRLep->SetDrawOption("COLZ"); 
		     }
		   
	   
		   if(MuFound)
                     {
                       DenomIsoLep->Fill(MuPt);

                     }
                   if(MuDecay)
                     {
                       DenomIsoLep->Fill((double)VisDecayMuon.Pt());

                     }

		   
		   if(TauMu)
		     {
		       DenomTotaldR->Fill(dRTauMu);
		     }
		   if(TauDecayMu)
		     {
		       DenomTotaldR->Fill(dRTauDecayMu);
		     }
		   if(DecayTauMu)
		     {
		       DenomTotaldR->Fill(dRDecayTauMu);
		     }
		   if (DecayTauDecayMu)
		     {
		       DenomTotaldR->Fill(dRDecayTauDecayMu);
		     }
		   
		   
		   if(MuFound)
		     {
		       DenomTotalLep->Fill(MuPt);
		       
		     }
		   if(MuDecay)
		     {
		       DenomTotalLep->Fill((double)VisDecayMuon.Pt());
		       
		     }
		   
		   if(TauFound)
		     {
                       DenomTotalVis->Fill((double)VisHad.Pt());

                     }
                   if(TauDecay)
                     {
                       DenomTotalVis->Fill((double)VisDecayHad.Pt());

                     }

		     
		     
		       //}
		   ///##################################################



		   bool PassDecayMode =false;
		   bool PassDecayModePassMVA=false;
		   bool PassMVA=false;

		   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau) 
		     {
		       //bool PassDecayMode= false;
		       dRTauJet=reco::deltaR(*itau,*iJet);
		       
		       
		       PassDecayMode=(itau->tauID("decayModeFinding")) && (dRTauJet< 0.1);
		       PassDecayModePassMVA=(itau->tauID("decayModeFinding")) && (dRTauJet< 0.1) && ((itau->tauID(TauIdRawValue_) >-0.5) && (itau->tauID(TauIdMVAWP_)));
		       PassMVA= (dRTauJet< 0.1) && ((itau->tauID(TauIdRawValue_) >-0.5) && (itau->tauID(TauIdMVAWP_)));

		       if(PassDecayMode)
			 {
			   ++NumCount;
			   NumDMode->Fill(iJet->pt());
			 }

		       if(PassDecayMode)
                         {
                           if(TauMu)
			     {
			       NumdR->Fill(dRTauMu);
			     }
			   if(TauDecayMu)
			     {
			       NumdR->Fill(dRTauDecayMu);
			     }
			   if(DecayTauMu)
			     {
			       NumdR->Fill(dRDecayTauMu);
			     }
			   if (DecayTauDecayMu)
			     {
			       NumdR->Fill(dRDecayTauDecayMu);
			     }
			 }



		       if(PassMVA)
			 {
			 
			   if(TauMu)
			     {
			       NumIsodR->Fill(dRTauMu);
			     }
			   if(TauDecayMu)
			     {
			       NumIsodR->Fill(dRTauDecayMu);
			     }
			   if(DecayTauMu)
			     {
			       NumIsodR->Fill(dRDecayTauMu);
			     }
			   if (DecayTauDecayMu)
			     {
			       NumIsodR->Fill(dRDecayTauDecayMu);
			     }
			 
			   if(MuFound)
			     {
			       NumIsoLep->Fill(MuPt);

			     }
			   if(MuDecay)
			     {
			       NumIsoLep->Fill((double)VisDecayMuon.Pt());

			     }

			 
			 
			 
			 
			 
			 
			 
			 
			 }
		       if(PassDecayMode)
			 {
			   if(TauFound)
			     {
			       NumVis->Fill((double)VisHad.Pt());
			       
			     }
			   if(TauDecay)
			     {
			       NumVis->Fill((double)VisDecayHad.Pt());
			       
			     }
			 }
		       
		       if(PassDecayModePassMVA)
			 { 
		       if(TauMu)
			 {
			   NumTotaldR->Fill(dRTauMu);
			 }
		       if(TauDecayMu)
			 {
			   NumTotaldR->Fill(dRTauDecayMu);
			 }
		       if(DecayTauMu)
			 {
			   NumTotaldR->Fill(dRDecayTauMu);
			 }
		       if (DecayTauDecayMu)
			 {
			   NumTotaldR->Fill(dRDecayTauDecayMu);
			 }

			 }

		       
		       if(PassDecayModePassMVA)
                         {
			   if(TauFound)
                             {
                               NumTotalVis->Fill((double)VisHad.Pt());

                             }
                           if(TauDecay)
                             {
                               NumTotalVis->Fill((double)VisDecayHad.Pt());

                             }
			   if(MuFound)
			     {
			       NumTotalLep->Fill(MuPt);

			     }
			   if(MuDecay)
			     {
			       NumTotalLep->Fill((double)VisDecayMuon.Pt());

			     }
			   
			   if(TauMu)
			     {
			       NumdRLep->Fill(dRTauMu,MuPt);
			       NumdRLep->SetDrawOption("COLZ"); 
			     }
			   if(TauDecayMu)
			     {
			       NumdRLep->Fill(dRTauDecayMu,(double)VisDecayMuon.Pt());
			       NumdRLep->SetDrawOption("COLZ");
			     }
			   if(DecayTauMu)
			     {
			       NumdRLep->Fill(dRDecayTauMu,MuPt);
			       NumdRLep->SetDrawOption("COLZ");
			     }
			   if (DecayTauDecayMu)
			     {
			       NumdRLep->Fill(dRDecayTauDecayMu,(double)VisDecayMuon.Pt());
			       NumdRLep->SetDrawOption("COLZ"); 
			     }
			   //NumdRLep->SetDrawOption("COLZ");

			   
			   
			 
			 
			 
			 
			 
			 
			 
			 
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

		   
		   
		   
		   
	 }
	       
     	       //}
	       
     }

       
   
   
   //TauEffDMode->TEfficiency(NumDMode,DenomDMode);
   














   
   //Just Tau_Had Isolation Efficiency
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
	   PassMVA=((itau->tauID(TauIdRawValue_) >-0.5) && (itau->tauID(TauIdMVAWP_)));
	   
	   if(TauFound)
	     {
	       DenomIsoVis->Fill((double)VisHad.Pt());

	     }
	   if(TauDecay)
	     {
	       DenomIsoVis->Fill((double)VisDecayHad.Pt());

	     }

	   if(PassMVA)
	     {
	       ++NumCountIso;
	       if(TauFound)
		 {
		   NumIsoVis->Fill((double)VisHad.Pt());

		 }
	       if(TauDecay)
		 {
		   NumIsoVis->Fill((double)VisDecayHad.Pt());

		 }

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

   std::cout<< " denominator DMode0: " <<  DenomCount<<std::endl;
   std::cout<< " Numerator DMode0: " <<  NumCount0 <<std::endl;  
   std::cout<< "************************"<<std::endl;
   
   std::cout<< "TaumuTauhad: "<< Counter <<std::endl;
   std::cout<< "TauHad_Count : "<< TauHad_Counter <<std::endl;
   std::cout<< "TauDecay_Count : "<< TauDecay_Counter <<std::endl;
}



// ------------ method called once each job just before starting event loop  ------------
void 
TauEfficiencyMuMVA::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauEfficiencyMuMVA::endJob() 
{
  //TauEffDMode->TauEffDMode(*DenomDMode,*NumDMode);
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TauEfficiencyMuMVA::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TauEfficiencyMuMVA);
