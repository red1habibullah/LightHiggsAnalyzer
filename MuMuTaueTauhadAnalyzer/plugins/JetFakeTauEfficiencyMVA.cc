// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      JetFakeTauEfficiencyMVA
// 
/**\class JetFakeTauEfficiencyMVA JetFakeTauEfficiencyMVA.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/JetFakeTauEfficiencyMVA.cc

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

class JetFakeTauEfficiencyMVA : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit JetFakeTauEfficiencyMVA(const edm::ParameterSet&);
      ~JetFakeTauEfficiencyMVA();
  std::vector<const reco::Candidate*>FindStat1( const reco::Candidate * particle);

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;
  edm::EDGetTokenT<reco::PFJetCollection> jetSrc_;
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;

  TEfficiency* JetTauFake;;
  double dRJetTauMatch=999999;
  int NumCount=0;
  int DenomCount=0;

  int NumDMCount=0;
  int DenomDMCount=0;
  
  int NumTauCount=0;
  int DenomTauCount=0;


  TH1F* NumIn;
  TH1F* DenomIn;


  TH1F* NumDM;
  TH1F* DenomDM;
 
  TH1F* NumTau;
  TH1F* DenomTau;
  TH1D* TauPt;
  //int MuDecay=0;
  std::string TauIdRawValue_;
  std::string TauIdMVAWP_;


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
JetFakeTauEfficiencyMVA::JetFakeTauEfficiencyMVA(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  jetSrc_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("jetSrc"))),
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  TauIdRawValue_(iConfig.getParameter<std::string>("TauIdRawValue")),
  TauIdMVAWP_(iConfig.getParameter<std::string>("TauIdMVAWP"))



{
  //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;

   const int  nbins =5;
   double edges[nbins+1]={10,15,20,30,50,100};
   JetTauFake = f->make<TEfficiency>("JetTauFake","Jet Fake Tau Probability ;Pt(GeV);#epsilon",nbins,edges);
   
   NumIn = f->make<TH1F>("NumIn","Numerator for Jet Fake Tau Efficiency;Jet Pt(GeV);# of Events",nbins,edges);
   DenomIn = f->make<TH1F>("DenomIn","Denominator for Jet Fake Tau Efficiency;Jet Pt(GeV);# of Events",nbins,edges);
   
   NumDM = f->make<TH1F>("NumDM","Numerator for Jet Fake Tau Efficiency;Tau Pt(GeV);# of Events",nbins,edges);
   DenomDM = f->make<TH1F>("DenomDM","Denominator for Jet Fake Tau Efficiency;Tau Pt(GeV);# of Events",nbins,edges);
   
   NumTau = f->make<TH1F>("NumTau","Numerator for Jet Fake Tau Efficiency;Jet Pt(GeV);# of Events",nbins,edges);
   DenomTau = f->make<TH1F>("DenomTau","Denominator for Jet Fake Tau Efficiency;Tau Pt(GeV);# of Events",nbins,edges);
   TauPt= f->make<TH1D>("TauPt","Tau Pt distribution;Pt(GeV);# of Events",100,0,100);


}


JetFakeTauEfficiencyMVA::~JetFakeTauEfficiencyMVA()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

std::vector<const reco::Candidate*>JetFakeTauEfficiencyMVA::FindStat1( const reco::Candidate * particle)
{

  std::vector<const reco::Candidate*> visParticles;
  if (particle->status() == 1)
    {
      visParticles.push_back(particle);
    }
  else
    {

      int nDaughters= particle->numberOfDaughters();
      for (int i=0; i < nDaughters; i++)
        {
          const reco::Candidate* Daughter= particle->daughter(i);
	  // std::cout<< "Daughter no:  "<< i << "  pdgId: " << Daughter->pdgId() <<" Daughter Pt: " << Daughter->pt()<<" Daughter Status: " << Daughter->status()<<std::endl;

          if(Daughter->status() == 1)
            {
              visParticles.push_back(Daughter);


            }
          else
            {
              auto auxVisParticles = FindStat1(Daughter);
              visParticles.insert(visParticles.end(), auxVisParticles.begin(), auxVisParticles.end());
            }
        }
    }
  return visParticles;
}

















//
// member functions
//

// ------------ method called for each event  ------------
void
JetFakeTauEfficiencyMVA::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;

  vector< const Candidate*> Fix;
  double dR_JetGenLepton=999999;
  double dR_TauGenLepton=999999;
  

  Handle<pat::TauCollection> Taus;
  
  iEvent.getByToken(TauSrc_,Taus);

  edm::Handle<reco::PFJetCollection> pfJets;
  iEvent.getByToken(jetSrc_, pfJets);

  Handle<edm::View<reco::GenParticle> > pruned;
  iEvent.getByToken(prunedGenToken_, pruned);
     
  for(size_t i=0; i<(pruned.product())->size() ;i++)
    {
      std::vector <const reco::Candidate*> daughters;
      daughters.clear();
      
      
      if(fabs((*pruned)[i].pdgId())==13 && ((*pruned)[i].isHardProcess()))
        {
          const Candidate *Muon = &(*pruned)[i];
          //cout<<" Muon Pt: "<< Muon->pt() <<" Muon Status: "<< Muon->status() <<endl;
	  
          if((Muon->status()==1) && fabs(Muon->mother()->pdgId())==23)
            {
              //cout<<" Final Muon pt: "<< Muon->pt() <<" Muon Status: "<< Muon->status() << " Muon Mother pdgId: " << Muon->mother()->0	pdgId() <<endl;
              Fix.push_back(Muon);
	      
            }
	  else
            {
              //cout<<" We have a Muon of status: " << Muon->status() << " With a mother of pdgId: " << Muon->mother()->pdgId() << " And status: " << Muon->mother()->status()<<endl;
              daughters=FindStat1(Muon);
              for (unsigned int jDau = 0; jDau < daughters.size(); jDau++)
                {
                  //cout<<" Recursive daughter pdgId :  " <<  daughters[jDau]->pdgId() << "  Recursive daughter Status: "<< daughters[jDau]->status()  <<" Recursive daughter Pt:"<< daughters[jDau]->pt()<<endl;
                  if(fabs(daughters[jDau]->pdgId())==13)
                    {
                      Fix.push_back(daughters[jDau]);
                    }
                }
	      
	      
	      
            }
	  
        }
    }
  //cout<< "vector size:"<< Fix.size() <<endl;
  
  
  
  


  

  for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet)
    {
      
      double dR_min=99999;
      bool JetKinematicCut= false;
      bool dRMatch= false;
      



      JetKinematicCut= ((iJet->pt() > 10) && (fabs(iJet->eta()) <2.3));
      
      for(unsigned i=0;i<Fix.size();i++)
	{
	  
	  dR_JetGenLepton=reco::deltaR((Fix[i])->eta(),(Fix[i])->phi(),iJet->eta(),iJet->phi());
	  
	  
	  if(dR_JetGenLepton < dR_min)
	    {
	      
	      dR_min=dR_JetGenLepton;
	    }
	  
	  
	}
      dRMatch=(dR_min>0.4);
      

      
      if(JetKinematicCut && dRMatch)
	{
	  /////////////?DecayMode Not in Denominator
	  bool PassMVAnDMode= false;
	  ++DenomCount;
	  DenomIn->Fill(iJet->pt());
	       for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
		 {
		   
		   dRJetTauMatch=reco::deltaR(*iJet,*itau);
		   
		   PassMVAnDMode=((itau->tauID(TauIdRawValue_) >-0.5) && (itau->tauID(TauIdMVAWP_)) && (itau->tauID("decayModeFinding")) && (dRJetTauMatch < 0.1));
		   
		   if(PassMVAnDMode)
		     {
		       
		       ++NumCount;
		       NumIn->Fill(iJet->pt());
		     }
		   
		   JetTauFake->Fill(PassMVAnDMode,iJet->pt());
		   bool Denom=false;
		   ////////////////////////////////DecayMode in Denomintor/////////////////////////
		   Denom=(dRJetTauMatch < 0.1) && (itau->tauID("decayModeFinding")) ;
		   
		   if(Denom)
		     {
		       ++DenomDMCount;
		       DenomDM->Fill(itau->pt());
		       
		       bool Num=false;
		       Num=(itau->tauID(TauIdRawValue_) >-0.5) && (itau->tauID(TauIdMVAWP_));
		       if(Num)
			 {
			   NumDM->Fill(itau->pt());
			   ++NumDMCount;
			 }
		       
		       
		     }
		   
		 }
	       
	       
	       
	       
	       
	       
	       
	    
	}
	  
	  
	  
   
	  
	  
    }


 










for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
   {
     TauPt->Fill(itau->pt());
     


     double dR_min_Tau=99999;
     bool dRMatchTau=false;
     bool TauKinematicCut=false;
     




    
     
     
    


     for(unsigned i=0;i<Fix.size();i++)
       {

	 dR_TauGenLepton=reco::deltaR((Fix[i])->eta(),(Fix[i])->phi(),itau->eta(),itau->phi());
	 
	 
	 if(dR_TauGenLepton < dR_min_Tau)
	   {

	     dR_min_Tau=dR_TauGenLepton;
	   }


       }

     dRMatchTau=(dR_min_Tau>0.4);
     //cout<<" dR_min_Tau: " << dR_min_Tau <<endl;
     


     TauKinematicCut= ((itau->pt() > 10) && (fabs(itau->eta()) <2.3));
     
     
     

     if(TauKinematicCut && dRMatchTau)
       {

	 
	 bool DenomCond=false;
	 DenomCond=(itau->tauID("decayModeFinding"));
	 
	 if(DenomCond)
	   {
	     
	     ++DenomTauCount;
	     DenomTau->Fill(itau->pt());

	     bool NumCond=false; 
	     NumCond= (itau->tauID(TauIdMVAWP_)) && (itau->tauID(TauIdRawValue_) >-0.5);
	 
	     if (NumCond)
	       {
		 ++NumTauCount;
		 NumTau->Fill(itau->pt());
	       }
	     
	     
	   }
	 
	 
       }
     
     
}
 
 
 

//cout<<" Numerator Tau: " << NumTauCount<<endl;
//cout<<" Denominator Tau: " << DenomTauCount<<endl;  

}



// ------------ method called once each job just before starting event loop  ------------
void 
JetFakeTauEfficiencyMVA::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetFakeTauEfficiencyMVA::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetFakeTauEfficiencyMVA::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetFakeTauEfficiencyMVA);
