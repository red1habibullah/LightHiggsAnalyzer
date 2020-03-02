// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      ElectronEfficiency
// 
/**\class ElectronEfficiency ElectronEfficiency.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/ElectronEfficiency.cc

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

#include "DataFormats/PatCandidates/interface/Electron.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class ElectronEfficiency : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit ElectronEfficiency(const edm::ParameterSet&);
  ~ElectronEfficiency();
  std::vector<const reco::Candidate*>FindStat1Vis( const reco::Candidate * particle);
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------

  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  edm::EDGetTokenT<pat::ElectronCollection> electronSrc_;
  edm::EDGetTokenT<pat::ElectronCollection> FullelectronSrc_;

  TH1D *NumElectron;
  TH1D *DenomElectron;

  TH1D *NumElecID;
  TH1D *DenomElecID;



  double dREleGenEle=99999;
  double dREleGenDecay=99999;

  double dRRecoGenEle=99999;
  double dRRecoGenDecay=99999;

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
ElectronEfficiency::ElectronEfficiency(const edm::ParameterSet& iConfig):
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  electronSrc_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electronSrc"))),
  FullelectronSrc_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("FullelectronSrc")))

{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;
   const int nbins=5;
   double edgesElectron[nbins+1]={0,10,20,30,50,100};

   NumElectron = f->make<TH1D>("NumElectron","Numerator for Electron (Reco + ID) Efficiency;#tau_{e} Pt(GeV);#epsilon",nbins,edgesElectron);
   DenomElectron= f->make<TH1D>("DenomElectron","Denominator for Electron (reco + ID) Efficiency;#tau_{e} Pt (GeV);#epsilon",nbins,edgesElectron);
   NumElecID = f->make<TH1D>("NumElecID","Numerator for Electron ID Efficiency; #tau_{e} Pt(GeV);#epsilon",nbins,edgesElectron);
   DenomElecID= f->make<TH1D>("DenomElecID","Denominator for Electron ID Efficiency; #tau_{e} Pt (GeV);#epsilon",nbins,edgesElectron);


}


ElectronEfficiency::~ElectronEfficiency()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}




std::vector<const reco::Candidate*>ElectronEfficiency::FindStat1Vis( const reco::Candidate * particle)

{
  
  std::vector<const reco::Candidate*> visParticles;
  if (particle->status() == 1)
    {
      if (fabs(particle->pdgId()) != 12 && fabs(particle->pdgId()) != 16)

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
	      if(fabs(GrandDaughter->pdgId()) != 12 && fabs(GrandDaughter->pdgId()) != 16)
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
ElectronEfficiency::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   Handle<edm::View<reco::GenParticle> > pruned;
   iEvent.getByToken(prunedGenToken_, pruned);
   
   Handle<pat::ElectronCollection> Electron;
   iEvent.getByToken(electronSrc_,Electron);

   Handle<pat::ElectronCollection> FullElectron;
   iEvent.getByToken(FullelectronSrc_,FullElectron);


   double ElePhi=99999;
   double EleEta=99999;
   double ElePt=99999;
   
   double EleDecayEta=99999;
   double EleDecayPhi=99999;
   
   TLorentzVector VisDecayElectron;
   //int MatchCount=0;
   vector <double> DRs;
   vector <double> DRDecays;
   bool EleFound=false;
   bool EleDecay=false;

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
		   
		   bool isElectron=false;
		   
		   //--------------------------Tau_mu--------------------
		   
		   if ((fabs(Daughter->pdgId())==11) && ((Daughter->pt())>7) && (abs(Daughter->eta()) < 2.5) && (Daughter->status()==1))
		     {
		     
		       EleFound=true;
		              
                       EleEta=(double)(Daughter->eta());
		       ElePhi=(double)(Daughter->phi());
		       ElePt=(double)(Daughter->pt());
		       
		     }
		   
		   if(fabs(Daughter->pdgId())==15)
                     {

		       Decaydaughters=FindStat1Vis(Daughter);
		       
		       for (unsigned int jDau = 0; jDau < Decaydaughters.size(); jDau++)
			 {
			 
			   if(fabs(Decaydaughters[jDau]->pdgId())==11)
			     {
			          
			       VisDecayElectron +=TLorentzVector(Decaydaughters[jDau]->p4().px(),Decaydaughters[jDau]->p4().py(),Decaydaughters[jDau]->p4().pz(),Decaydaughters[jDau]->p4().e());
			          
			       //cout<<" Recursively Identified Muon pdgId : " << Decaydaughters[jDau]->pdgId() << " Recursively identified Muon  Status:    "<<   Decaydaughters[jDau]->status()  <<" Recursively Identified Muon Pt: "<< Decaydaughters[jDau]->pt()<<endl;

			       isElectron=true;
			     }
			 
			 
			 
			 
			 }

		       if(isElectron && (VisDecayElectron.Pt() >7) && (fabs(VisDecayElectron.Eta()) <2.5) )
			 {
			          
			   EleDecay=true;
			   EleDecayEta=VisDecayElectron.Eta();
			          
			   EleDecayPhi=VisDecayElectron.Phi();
			   cout<< " Decay Electron Pt: "<< VisDecayElectron.Pt()<<endl;
			   cout<< " Decay Electron Eta: "<< VisDecayElectron.Eta()<<endl;
			   cout<< " Decay Electron Phi: "<< VisDecayElectron.Phi()<<endl;


			 }
		       
		     
		     }

		 
		 
		 }
	     
	     
	     
	     }
	 
	 
	 
	 
	 
	 }


     }


   if(EleFound)
     {
       DenomElectron->Fill(ElePt);

     }
   if(EleDecay)
     {
       DenomElectron->Fill((double)VisDecayElectron.Pt());

     }

   cout<< "No of Electrons: " << Electron->size() <<endl;
   
   
   

   
   for(pat::ElectronCollection::const_iterator iEle= FullElectron->begin() ; iEle !=FullElectron->end() ; ++iEle)
     {
       
       
       if((iEle->pt() > 7) && abs(iEle->eta())<2.5)
	 {


	   if(EleFound)
	     {
	       dRRecoGenEle=reco::deltaR(EleEta,ElePhi,iEle->eta(),iEle->phi());
	       //cout<<" dRRecoGenEle: "<< dRRecoGenEle<<endl;
	       
	     }
	   
	   
	   if(EleDecay)
	     {
	       dRRecoGenDecay=reco::deltaR(EleDecayEta,EleDecayPhi,iEle->eta(),iEle->phi());
	       //cout<<" dRRecoGenDecay: "<< dRRecoGenDecay <<endl;
	     }
	   
	   if(EleFound && (dRRecoGenEle < 0.1))
	     
	     {
	       DenomElecID->Fill(ElePt);
	       
	       
	     }
	   if(EleDecay && (dRRecoGenDecay <0.1))
	     {
	       
	       DenomElecID->Fill((double)VisDecayElectron.Pt());
	       
	     }
	   
	   double dRRecoPassReco=99999;
	   
	   if((EleFound && (dRRecoGenEle < 0.1)) || (EleDecay && (dREleGenDecay <0.1)))
	     {
	       
	       for(pat::ElectronCollection::const_iterator iElectron=Electron->begin() ; iElectron !=Electron->end() ; ++iElectron)
		 {
		   
		   dRRecoPassReco=deltaR(*iElectron,*iEle);
		   cout<<"RecoPassRecoEle: "<< dRRecoPassReco <<endl;
		   
		   if(EleFound && (dRRecoPassReco <0.05))
		     {
		       NumElecID->Fill(ElePt);
		
		     }
		   if(EleDecay && (dRRecoPassReco <0.05))
		     {
		       NumElecID->Fill((double)VisDecayElectron.Pt());
		       
		     }
		   
		   
		   
		 }
	       
	       
	       
	     }
	 }	   
       
     }
       
       



   









   for(pat::ElectronCollection::const_iterator iElectron = Electron->begin() ; iElectron !=Electron->end() ; ++iElectron)
     {
          
     
       if(EleFound)
	 {
	   dREleGenEle=reco::deltaR(EleEta,ElePhi,iElectron->eta(),iElectron->phi());
	   cout<<" dREleGenEle: "<< dREleGenEle<<endl;

	 }
       if(EleDecay)
	 {
	   dREleGenDecay=reco::deltaR(EleDecayEta,EleDecayPhi,iElectron->eta(),iElectron->phi());
	   cout<<" dREleGenDecay: "<< dREleGenDecay <<endl;
	 }
       
  
       
       
       
       if(EleFound && (dREleGenEle < 0.1))
	 
       	 {
       
	   DRs.push_back(dREleGenEle);
       	 }
       if(EleDecay && (dREleGenDecay <0.1))
       	 {
     
       	 
	   DRDecays.push_back(dREleGenDecay);
	 }
     
     
     
     }


   

   
   



   ///////////////////condition to fill Numerator///////////////////
  
   double dR_min=99999;
   double dRMatch=false;
   if(EleFound && (DRs.size()) >=2)
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
	   
	   NumElectron->Fill(ElePt);
	 }
     }
   
   double dR_Decay_min=99999;
   double dRDecayMatch=false;
   if(EleFound && (DRDecays.size()) >=2)
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

	   NumElectron->Fill((double)VisDecayElectron.Pt());

         }
     }








   if(EleFound && (DRs.size())==1)
     {
       NumElectron->Fill(ElePt);
     }
   if(EleDecay && (DRDecays.size())==1)
     {
       NumElectron->Fill((double)VisDecayElectron.Pt());  
     }
   
}

// ------------ method called once each job just before starting event loop  ------------
void 
ElectronEfficiency::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ElectronEfficiency::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ElectronEfficiency::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ElectronEfficiency);
