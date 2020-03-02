// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      MuonEfficiency
// 
/**\class MuonEfficiency MuonEfficiency.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/MuonEfficiency.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Thu, 20 Feb 2020 05:28:56 GMT
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
#include "TH1D.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "TEfficiency.h"


#include "TLorentzVector.h"
#include "Math/LorentzVector.h"


#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"


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

class MuonEfficiency : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit MuonEfficiency(const edm::ParameterSet&);
  ~MuonEfficiency();
  std::vector<const reco::Candidate*>FindStat1Vis( const reco::Candidate * particle);
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------

  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  edm::EDGetTokenT<pat::MuonCollection> muonSrc_;
  
  TH1D *NumMuon;
  TH1D *DenomMuon;



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
MuonEfficiency::MuonEfficiency(const edm::ParameterSet& iConfig):
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  muonSrc_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonSrc")))
{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;
   const int nbins=5;
   double edgesMuon[nbins+1]={0,10,20,30,50,100};

   NumMuon = f->make<TH1D>("NumMuon","Numerator for Muon Efficiency;#tau_{#mu} Pt(GeV);#epsilon",nbins,edgesMuon);
   DenomMuon= f->make<TH1D>("DenomMuon","Denominator for Muon Efficiency;#tau_{#mu} Pt (GeV);#epsilon",nbins,edgesMuon);


}


MuonEfficiency::~MuonEfficiency()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}




std::vector<const reco::Candidate*>MuonEfficiency::FindStat1Vis( const reco::Candidate * particle)

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
//
// member functions
//

// ------------ method called for each event  ------------
void
MuonEfficiency::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   Handle<edm::View<reco::GenParticle> > pruned;
   iEvent.getByToken(prunedGenToken_, pruned);
   
   Handle<pat::MuonCollection> Muon;
   iEvent.getByToken(muonSrc_,Muon);

   double MuPhi=99999;
   double MuEta=99999;
   double MuPt=99999;
   
   double MuDecayEta=99999;
   double MuDecayPhi=99999;
   
   TLorentzVector VisDecayMuon;
   //int MatchCount=0;
   vector <double> DRs;
   vector <double> DRDecays;
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
		   std::vector <const reco::Candidate*> daughters;
		   daughters.clear();
		   std::vector<const reco::Candidate*> Decaydaughters;
		   Decaydaughters.clear();
		   
		   bool isMuon=false;
		   
		   //--------------------------Tau_mu--------------------
		   
		   if ((fabs(Daughter->pdgId())==13) && ((Daughter->pt())>3) && (abs(Daughter->eta()) < 2.4) && (Daughter->status()==1))
		     {
		     
		       MuFound=true;
		              
                       MuEta=(double)(Daughter->eta());
		       MuPhi=(double)(Daughter->phi());
		       MuPt=(double)(Daughter->pt());
		       
		     }
		   
		   if(fabs(Daughter->pdgId())==15)
                     {

		       Decaydaughters=FindStat1Vis(Daughter);
		       
		       for (unsigned int jDau = 0; jDau < Decaydaughters.size(); jDau++)
			 {
			 
			   if(fabs(Decaydaughters[jDau]->pdgId())==13)
			     {
			          
			       VisDecayMuon +=TLorentzVector(Decaydaughters[jDau]->p4().px(),Decaydaughters[jDau]->p4().py(),Decaydaughters[jDau]->p4().pz(),Decaydaughters[jDau]->p4().e());
			          
			       //cout<<" Recursively Identified Muon pdgId : " << Decaydaughters[jDau]->pdgId() << " Recursively identified Muon  Status:    "<<   Decaydaughters[jDau]->status()  <<" Recursively Identified Muon Pt: "<< Decaydaughters[jDau]->pt()<<endl;

			       isMuon=true;
			     }
			 
			 
			 
			 
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
	     
	     
	     
	     }
	 
	 
	 
	 
	 
	 }


     }


   if(MuFound)
     {
       DenomMuon->Fill(MuPt);

     }
   if(MuDecay)
     {
       DenomMuon->Fill((double)VisDecayMuon.Pt());

     }

   cout<< "No of Muons: " << Muon->size() <<endl;
   
   
   








   for(pat::MuonCollection::const_iterator iMuon = Muon->begin() ; iMuon !=Muon->end() ; ++iMuon)
     {
          
     
       if(MuFound)
	 {
	   dRMuGenMu=reco::deltaR(MuEta,MuPhi,iMuon->eta(),iMuon->phi());
	   cout<<" dRMuGenMu: "<< dRMuGenMu<<endl;

	 }
       if(MuDecay)
	 {
	   dRMuGenDecay=reco::deltaR(MuDecayEta,MuDecayPhi,iMuon->eta(),iMuon->phi());
	   cout<<" dRMuGenDecay: "<< dRMuGenDecay <<endl;
	 }
       
  
       
       
       
       if(MuFound && (dRMuGenMu < 0.1))
	 
       	 {
       	   //NumMuon->Fill(MuPt);
	   DRs.push_back(dRMuGenMu);
       	 }
       if(MuDecay && (dRMuGenDecay <0.1))
       	 {
       	   //NumMuon->Fill((double)VisDecayMuon.Pt());
       	 
	   DRDecays.push_back(dRMuGenDecay);
	 }
     
     
     
     }


   

   
   



   ///////////////////condition to fill Numerator///////////////////
  
   double dR_min=99999;
   double dRMatch=false;
   if(MuFound && (DRs.size()) >=2)
     {
       
       for( unsigned int i=0; i <DRs.size() ; i++)
	 
	 {
	   if(DRs[i]< dR_min)
	     {
	       dR_min=DRs[i];
	     }
	   
	 }
       
       dRMatch=(dR_min <0.1);
       if(dRMatch)
	 {
	   
	   NumMuon->Fill(MuPt);
	 }
     }
   
   double dR_Decay_min=99999;
   double dRDecayMatch=false;
   if(MuFound && (DRDecays.size()) >=2)
     {

       for(unsigned int i=0; i <DRDecays.size() ; i++)
	 
         {
           if(DRDecays[i]< dR_Decay_min)
             {
               dR_Decay_min=DRDecays[i];
             }

         }
       
       dRDecayMatch=(dR_Decay_min <0.1);
       if(dRDecayMatch)
         {

	   NumMuon->Fill((double)VisDecayMuon.Pt());

         }
     }








   if(MuFound && (DRs.size())==1)
     {
       NumMuon->Fill(MuPt);
     }
   if(MuDecay && (DRDecays.size())==1)
     {
       NumMuon->Fill((double)VisDecayMuon.Pt());  
     }
   
}

// ------------ method called once each job just before starting event loop  ------------
void 
MuonEfficiency::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MuonEfficiency::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MuonEfficiency::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonEfficiency);
