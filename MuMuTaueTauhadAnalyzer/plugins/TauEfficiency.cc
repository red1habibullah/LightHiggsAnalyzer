// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      TauEfficiency
// 
/**\class TauEfficiency TauEfficiency.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/TauEfficiency.cc

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
#include <string>
#include <iostream>


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

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
#include "TH2D.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/PatCandidates/interface/TauPFSpecific.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "TEfficiency.h"


#include "Math/VectorUtil.h"
#include "TLorentzVector.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TauEfficiency : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TauEfficiency(const edm::ParameterSet&);
      ~TauEfficiency();
  bool isSpecificDaughter(const reco::Candidate * particle,int Id);
  double RefToDaughterPhi(const reco::Candidate * particle,int Id);
  double RefToDaughterEta(const reco::Candidate * particle,int Id);
  std::vector<const reco::Candidate*>FindStat1Vis( const reco::Candidate * particle);

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
      // ----------member data ---------------------------
  //std::string moduleLabel_;
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;

  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  
  edm::EDGetTokenT<pat::ElectronCollection> Ele_;
  
  edm::EDGetTokenT<reco::PFJetCollection> jetSrc_;


  TEfficiency* TauEff;
  
  TH1F* NumDMode;
  TH1F* DenomDMode;

  TH1D* NumdR;
  TH1D* DenomdR;

  TH1D *NumVis;
  TH1D *DenomVis;
  
  TH1D* NumTotaldR;
  TH1D* DenomTotaldR;
  
  TH1D *NumTotalVis;
  TH1D *DenomTotalVis;
  
  TH1D *NumIsoVis;
  TH1D *DenomIsoVis;

  
  
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
  double dRJetGenTau=99999;
  
  double dRTauGenDecay=99999;
  double dRJetGenDecay=99999;

  double dREleGenEle=99999;
  double dREleGenDecay=99999;
  
  double dRTauJet=99999;


  double dRTauEle=99999;
  double dRDecayTauEle=99999;
  double dRTauDecayEle=99999;
  double dRDecayTauDecayEle=99999;

  int NumCount=0;
  int DenomCount=0;
  
  int NumCount0=0;
  int DenomCount0=0;

  int NumCountIso=0;
  int DenomCountIso=0;
  
  //int verbosity_;
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
TauEfficiency::TauEfficiency(const edm::ParameterSet& iConfig):
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  Ele_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("Ele"))),
  jetSrc_(consumes<reco::PFJetCollection>(iConfig.getParameter<edm::InputTag>("jetSrc")))
{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;

   //TauEff = f->make<TEfficiency>("TauEff","Tau Reconstruction  Efficiency;Pt(GeV);#epsilon",20,0,100);
   const int  nbins =5;
   double edges[nbins+1]={10,15,20,30,50,100};
   TauEff = f->make<TEfficiency>("TauEff","Tau Isolation  Efficiency;Pt(GeV);#epsilon",nbins,edges);
   

   NumDMode = f->make<TH1F>("NumDMode","Numerator for Reconstruction Efficiency;Jet Pt(GeV);# of Events",nbins,edges);
   DenomDMode = f->make<TH1F>("DenomDMode","Denominator for Reconstruction Efficiency;Jet Pt(GeV);# of Events",nbins,edges);
   
   NumdR = f->make<TH1D>("NumdR","Numerator for Reconstruction Efficiency;dR(#tau_{had},#tau_{lep});# of Events",10,0,1);
   DenomdR = f->make<TH1D>("DenomdR","Denominator for Reconstruction Efficiency;dR(#tau_{had},#tau_{lep});# of Events",10,0,1);
   
   NumVis = f->make<TH1D>("NumVis","Numerator for Reconstruction Efficiency;#tau_{had} Visible Pt(GeV);# of Events",nbins,edges);
   DenomVis = f->make<TH1D>("DenomVis","Denominator for Reconstruction Efficiency;#tau_{had} Visible Pt (GeV);# of Events",nbins,edges);

   NumTotaldR = f->make<TH1D>("NumTotaldR","Numerator for Total Reconstruction Efficiency;dR(#tau_{had},#tau_{lep});# of Events",10,0,1);
   DenomTotaldR = f->make<TH1D>("DenomTotaldR","Denominator for Total Reconstruction Efficiency;dR(#tau_{had},#tau_{lep});# of Events",10,0,1);
   
   NumTotalVis = f->make<TH1D>("NumTotalVis","Numerator for Total Reconstruction Efficiency;#tau_{had} Visible Pt(GeV);# of Events",nbins,edges);
   DenomTotalVis = f->make<TH1D>("DenomTotalVis","Denominator for Total Reconstruction Efficiency;#tau_{had} Visible Pt (GeV);# of Events",nbins,edges);

   NumIsoVis = f->make<TH1D>("NumIsoVis","Numerator for Isolation Efficiency;#tau_{had} Visible Pt(GeV);# of Events",nbins,edges);
   DenomIsoVis = f->make<TH1D>("DenomIsoVis","Denominator for Isolation Efficiency;#tau_{had} Visible Pt (GeV);# of Events",nbins,edges);


   TauEffDMode = f->make<TEfficiency>("TauEffDMode","Tau DecayMode  Efficiency;Pt(GeV);#epsilon",nbins,edges);
   TauEffDModes = f->make<TEfficiency>("TauEffDModes","Tau DecayMode  Efficiency;DecayModes;#epsilon",12,-0.5,11.5);
   
   
   NumDMode0 = f->make<TH1F>("NumDMode0","Numerator for Reconstruction Efficiency for Decay Mode 0 -> 1 Prong ;Jet Pt(GeV);# of Events",nbins,edges);
   TauEffDMode0 = f->make<TEfficiency>("TauEffDMode0","Tau DecayMode  Efficiency for Decay Mode 0 -> 1 Prong ;Pt(GeV);#epsilon",nbins,edges);
   
   NumDMode1 = f->make<TH1F>("NumDMode1","Numerator for Reconstruction Efficiency for Decay Mode 1 -> 1 Prong + 1 #pi 0  ;Jet Pt(GeV);# of Events",nbins,edges);
   TauEffDMode1 = f->make<TEfficiency>("TauEffDMode1","Tau DecayMode  Efficiency for Decay Mode 1 -> 1 Prong 1 #pi 0 ;Pt(GeV);#epsilon",nbins,edges);
   
   
   NumDMode5 = f->make<TH1F>("NumDMode5","Numerator for Reconstruction Efficiency for Decay Mode 5 -> 1 Prong + N #pi 0  ;Jet Pt(GeV);# of Events",nbins,edges);
   TauEffDMode5 = f->make<TEfficiency>("TauEffDMode5","Tau DecayMode  Efficiency for Decay Mode 5 -> 1 Prong + N #pi 0  ;Pt(GeV);#epsilon",nbins,edges);
   
   
   NumDMode6 = f->make<TH1F>("NumDMode6","Numerator for Reconstruction Efficiency for Decay Mode 6 -> 2 Prong ;Jet Pt(GeV);# of Events",nbins,edges);
   TauEffDMode6= f->make<TEfficiency>("TauEffDMode6","Tau DecayMode  Efficiency for Decay Mode 6 -> 2 Prong ;Pt(GeV);#epsilon",nbins,edges);
   
   
   NumDMode10 = f->make<TH1F>("NumDMode10","Numerator for Reconstruction Efficiency for Decay Mode 10 -> 3 Prong ;Jet Pt(GeV);# of Events",nbins,edges);
   TauEffDMode10 = f->make<TEfficiency>("TauEffDMode10","Tau DecayMode  Efficiency for Decay Mode 10 -> 3 Prong ;Pt(GeV);#epsilon",nbins,edges);

   TauPt= f->make<TH1D>("TauPt","Tau Pt distribution;Pt(GeV);# of Events",100,0,100);
   JetPt= f->make<TH1D>("JetPt","Jet Pt distribution;Pt(GeV);# of Events",200,0,200);
   //verbosity_ = ( iConfig.exists("verbosity") ) ?
   //iConfig.getParameter<int>("verbosity") : 0;



}


TauEfficiency::~TauEfficiency()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}




bool TauEfficiency::isSpecificDaughter(const reco::Candidate * particle,int Id)
{
  if ((fabs(particle->pdgId())==Id))
    return true;
  for(size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(isSpecificDaughter(particle->daughter(i),Id)) return true;

    }
  return false;
}

double TauEfficiency::RefToDaughterPhi(const reco::Candidate * particle,int Id)
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

double TauEfficiency::RefToDaughterEta(const reco::Candidate * particle,int Id)
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


std::vector<const reco::Candidate*>TauEfficiency::FindStat1Vis( const reco::Candidate * particle)
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
TauEfficiency::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;
   /*if ( verbosity_ )
     {
   std::cout << " inputJets = " << jetSrc_<< std::endl;
   std::cout << " inputTaus = " << TauSrc_ << std::endl;
     }
   */
   Handle<pat::TauCollection> Taus;
   iEvent.getByToken(TauSrc_,Taus);

   Handle<edm::View<reco::GenParticle> > pruned;
   iEvent.getByToken(prunedGenToken_, pruned);

  
   edm::Handle<pat::ElectronCollection> electron;
   iEvent.getByToken(Ele_,electron);
   
   edm::Handle<reco::PFJetCollection> pfJets;
   iEvent.getByToken(jetSrc_, pfJets);


   double PseudoTauPhi=99999;
   double PseudoTauEta=99999;

   double DecayTauPhi=99999;
   double DecayTauEta=99999;

   double ElePhi=99999;
   double EleEta=99999;
   
   double EleDecayEta=99999;
   double EleDecayPhi=99999;


   TLorentzVector VisHad;
   TLorentzVector VisDecayElectron;
   TLorentzVector VisDecayHad;
   // double DecayElePhi=99999;
   //double DecayEleEta=99999;
   double Tau_had_pt_v2=99999;

   bool TauFound=false;
   bool TauDecay=false;

   bool EleFound=false;
   bool EleDecay=false;
   
   
   
   
   for(size_t i=0; i<(pruned.product())->size() ;i++)
     {
       if(fabs((*pruned)[i].pdgId())==15)
         {
           const Candidate * Tau = &(*pruned)[i];
           if (fabs(Tau->mother()->pdgId())==36)
             {
	       cout << " Tau from PseudoScalar " <<endl;

               const Candidate *PseudoTau = &(*pruned)[i];
	       
	       cout<< " Tau Pt: " << PseudoTau->pt() <<endl;

	       
               unsigned  n=PseudoTau->numberOfDaughters();

               for ( size_t j =0; j < n ; j++)
                 {
                   



		   const Candidate * Daughter=PseudoTau->daughter(j);
		   
		   std::vector <const reco::Candidate*> daughters;
		   daughters.clear();
		   
		   std::vector<const reco::Candidate*> Decaydaughters;
		   Decaydaughters.clear();
		   


		   cout<< " Daughter no:  "<< j << "  pdgId: " << Daughter->pdgId() <<" Daughter Pt: " << Daughter->pt()<<" Daughter Status: " << Daughter->status()<<endl;

		   bool isHad= false;
		   bool isElectron =false;


		            if(fabs(Daughter->pdgId())==15)
			      {
				
				Decaydaughters=FindStat1Vis(Daughter);
				
				for (unsigned int jDau = 0; jDau < Decaydaughters.size(); jDau++)
				  {
				    cout<<" Recursive Visible  Decaydaughter pdgId :  " <<  Decaydaughters[jDau]->pdgId() << "  Recursive Visible Decaydaughter Status: "<<   Decaydaughters[jDau]->status()  <<" Recursive Visible Decaydaughter Pt:"<< Decaydaughters[jDau]->pt()<<endl;
				           
				   ///------------------------Decayed Tau_e-----------------------------------------------
				    if(fabs(Decaydaughters[jDau]->pdgId())==11)
				      {
					   
					VisDecayElectron +=TLorentzVector(Decaydaughters[jDau]->p4().px(),Decaydaughters[jDau]->p4().py(),Decaydaughters[jDau]->p4().pz(),Decaydaughters[jDau]->p4().e());
					   
					cout<<" Recursively Identified Electon pdgId : " <<  Decaydaughters[jDau]->pdgId()  << " Recursively identified Electron  Status:    "<<   Decaydaughters[jDau]->status()  <<"  Recursively Identified Electron Pt: "<< Decaydaughters[jDau]->pt()<<endl;

					isElectron=true;
				      }
				   ///-------------------------------Decayed viz Tau_Had------------------------------------
				    else
				      {
					VisDecayHad+=TLorentzVector(Decaydaughters[jDau]->p4().px(),Decaydaughters[jDau]->p4().py(),Decaydaughters[jDau]->p4().pz(),Decaydaughters[jDau]->p4().e());
					
					cout<<"  Recursively Identified Hadron pdgId:  " <<  Decaydaughters[jDau]->pdgId()  << "   Recursively identified Hadron  Status:  "<<   Decaydaughters[jDau]->status()  <<"  Recursive Identified  Hadron Pt: "<< Decaydaughters[jDau]->pt()<<endl;
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




			    ///----------------------------------------------Tau_ele-------------------------------------------------------------
			    
			    if ((fabs(Daughter->pdgId())==11)  && (Daughter->status()==1) && ((Daughter->pt())>7) && (abs(Daughter->eta()) < 2.5))
			      {                                                                                                                                                                                  
				EleFound=true;
				
				EleEta=(double)(Daughter->eta());
				ElePhi=(double)(Daughter->phi());
				cout<< " Electron Pt: "<< Daughter->pt()<<endl;
				cout<< " Electron Eta: "<< Daughter->eta()<<endl;
				cout<< " Electron Phi: "<< Daughter->phi()<<endl;


				
			      }


// if( (!TauFound) && (fabs(Daughter->pdgId())!=11) &&  (fabs(Daughter->pdgId())!=12) && (fabs(Daughter->pdgId())!=15) && (fabs(Daughter->pdgId())!=22) && (fabs(Daughter->pdgId())!=16)  )
//                      {
                                                                                                                                       
//                        TauFound=true;
                                                                                          
//                        PseudoTauPhi=(double)(PseudoTau->phi());
//                        PseudoTauEta=(double)(PseudoTau->eta());
//                      }

///---------------------------viz Tau_had--------------------------------------------------------------------------
			    if((fabs(Daughter->pdgId())!=11) &&  (fabs(Daughter->pdgId())!=12) && (fabs(Daughter->pdgId())!=15) &&  (fabs(Daughter->pdgId())!=16)  && (fabs(Daughter->pdgId())!=22) // && ((PseudoTau->pt()) > 10) && (abs(PseudoTau->eta()) <2.3 
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
					cout<<" Recursive daughter pdgId : " << daughters[jDau]->pdgId() << "Recursive Daughter Status:    "<<   daughters[jDau]->status()  <<" Recursive Daughter Pt:"<< daughters[jDau]->pt()<<endl; 
				      }
				       
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
       Tau_had_pt_v2=(double)VisHad.Pt();
       cout<<" Vis Had Pt_v1: "<<Tau_had_pt_v2<<endl;
       cout<< "Vis Had Pt : "<<(double)VisHad.Pt()<<endl; 
       cout<< "Vis Had Eta: "<<(double)VisHad.Eta()<<endl;

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
       
       

       GenMatched=((TauFound && (dRTauGenTau < 0.1)) || (TauDecay && (dRTauGenDecay<0.1)))  && ((EleFound && (dREleGenEle < 0.1)) || (EleDecay && (dREleGenDecay<0.1)));   
       AnalysisCuts= ((itau->pt()) > 10 && (abs(itau->eta()) <2.3));
       if ( PassDecayMode && GenMatched && AnalysisCuts)
	 {
	   ++DenomCountIso;
	   PassMVA=((itau->tauID("byIsolationMVArun2v1DBoldDMwLTraw") >-0.5) && (itau->tauID("byMediumIsolationMVArun2v1DBoldDMwLT")));
	   
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


 
   for (reco::PFJetCollection::const_iterator iJet = pfJets->begin(); iJet != pfJets->end(); ++iJet)
     {
       for(pat::ElectronCollection::const_iterator iele = electron->begin() ; iele !=electron->end() ; ++iele)
	 {
	   
	   //(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
	     
	   //{
	   //bool PassDecayMode= false;
	       //bool AnalysisCuts= false;
	       bool GenMatched =false;
	       bool TauEle =false;
	       bool TauDecayEle = false;
	       bool DecayTauEle = false;
	       bool DecayTauDecayEle= false;
	       //bool JetTauMatch=false;
	       
	       if(TauFound)
		 {
		   // dRTauGenTau=reco::deltaR(PseudoTauEta,PseudoTauPhi,itau->eta(),itau->phi());
		   //dRTauCleanedGenTau=reco::deltaR(PseudoTauEta,PseudoTauPhi,itau_cl->eta(),itau_cl->phi());                                                                                                                                                               
		   dRJetGenTau=reco::deltaR(PseudoTauEta,PseudoTauPhi,iJet->eta(),iJet->phi()); 
		 }
	       
	       if(TauDecay)
		 {
		   //dRTauGenDecay=reco::deltaR(DecayTauEta,DecayTauPhi,itau->eta(),itau->phi());
		   dRJetGenDecay=reco::deltaR(DecayTauEta,DecayTauPhi,iJet->eta(),iJet->phi());
 
		 }
	       if(EleFound)
		 {
		   dREleGenEle=reco::deltaR(EleEta,ElePhi,iele->eta(),iele->phi());
		   
		 }
	       if(EleDecay)
		 {
		   dREleGenDecay=reco::deltaR(EleDecayEta,EleDecayPhi,iele->eta(),iele->phi());
		   
		 }
	       
	       if(TauFound && EleFound)
		 {
		   dRTauEle=reco::deltaR(PseudoTauEta,PseudoTauPhi,EleEta,ElePhi);
		   TauEle=true;
		   cout<<" dRTauEle: "<< dRTauEle<<endl;

		 }
	       if(TauFound && EleDecay)
		 {
		   dRTauDecayEle=reco::deltaR(PseudoTauEta,PseudoTauPhi,EleDecayEta,EleDecayPhi);
		   TauDecayEle = true;
		   cout<<" dRTauDecayEle: "<< dRTauDecayEle<<endl;

		 }
	       if(TauDecay && EleFound)
		 {
		   dRDecayTauEle=reco::deltaR(DecayTauEta,DecayTauPhi,EleEta,ElePhi);
		   DecayTauEle = true;
		   cout<<" dRDecayTauEle: "<< dRDecayTauEle<<endl;

		 }
	       if(TauDecay && EleDecay)
		 {
		   dRDecayTauDecayEle=reco::deltaR(DecayTauEta,DecayTauPhi,EleDecayEta,EleDecayPhi);
		   DecayTauDecayEle= true;
		   cout<<" dRDecayTauDecayEle: "<< dRDecayTauDecayEle<<endl;
		 }








	       GenMatched=((TauFound && (dRJetGenTau < 0.1)) || (TauDecay && (dRJetGenDecay<0.1))) && ((EleFound && (dREleGenEle < 0.1)) || (EleDecay && (dREleGenDecay<0.1)));
	       //AnalysisCuts= ((itau->pt()) > 10 && (abs(itau->eta()) <2.3)) && ((iJet->pt() > 10) && (fabs(iJet->eta()) <2.3));
	       
	       
	       if(GenMatched /*&& AnalysisCuts*/ )
		 {
		   
		   ++DenomCount;
		   
		   DenomDMode->Fill(iJet->pt());
		   if(TauEle)
		     {
		       DenomdR->Fill(dRTauEle);
		     }
		   if(TauDecayEle)
		     {
		       DenomdR->Fill(dRTauDecayEle);
		     }
		   if(DecayTauEle)
		     {
		       DenomdR->Fill(dRDecayTauEle);
		     }
		   if (DecayTauDecayEle)
		     {
		       DenomdR->Fill(dRDecayTauDecayEle);
		     }

		   
		   
		   if(TauFound)
		     {
		       DenomVis->Fill((double)VisHad.Pt());
		              
		     }
		   if(TauDecay)
                     {
                       DenomVis->Fill((double)VisDecayHad.Pt());

                     }
		      
		      
		   if(TauEle)
                     {
                       DenomTotaldR->Fill(dRTauEle);
                     }
                   if(TauDecayEle)
                     {
                       DenomTotaldR->Fill(dRTauDecayEle);
                     }
                   if(DecayTauEle)
                     {
                       DenomTotaldR->Fill(dRDecayTauEle);
                     }
                   if (DecayTauDecayEle)
                     {
                       DenomTotaldR->Fill(dRDecayTauDecayEle);
		     }
		   
		   if(TauFound)
                     {
                       DenomTotalVis->Fill((double)VisHad.Pt());

                     }
                   if(TauDecay)
                     {
		       DenomTotalVis->Fill((double)VisDecayHad.Pt());

                     }
		   
		   bool PassDecayMode= false;
		   bool PassDecayModePassMVA=false;
		   for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau) 
		     {
		     
		   dRTauJet=reco::deltaR(*itau,*iJet);
		   PassDecayMode=(itau->tauID("decayModeFinding")) && (dRTauJet< 0.1);
		   PassDecayModePassMVA=(itau->tauID("decayModeFinding")) && (dRTauJet< 0.1) && ((itau->tauID("byIsolationMVArun2v1DBoldDMwLTraw") >-0.5) && (itau->tauID("byMediumIsolationMVArun2v1DBoldDMwLT")));
		   
		   
		   
		   
		   if(PassDecayMode)
		     {
		       ++NumCount;
		       NumDMode->Fill(iJet->pt());
		     }
		   
		   
		   if(PassDecayMode)
		     {
		   if(TauEle)
		     {
		       NumdR->Fill(dRTauEle);
		     }
		   if(TauDecayEle)
		     {
		       NumdR->Fill(dRTauDecayEle);
		     }
		   if(DecayTauEle)
		     {
		       NumdR->Fill(dRDecayTauEle);
		     }
		   if (DecayTauDecayEle)
		     {
		       NumdR->Fill(dRDecayTauDecayEle);
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
		       if(TauEle)
			 {
			   NumTotaldR->Fill(dRTauEle);
			 }
		       if(TauDecayEle)
			 {
			   NumTotaldR->Fill(dRTauDecayEle);
			 }
		       if(DecayTauEle)
			 {
			   NumTotaldR->Fill(dRDecayTauEle);
			 }
		       if (DecayTauDecayEle)
			 {
			   NumTotaldR->Fill(dRDecayTauDecayEle);
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

		     }















		   
		   TauEffDMode->Fill(PassDecayMode,itau->pt());
		   TauEffDModes->Fill(PassDecayMode,itau->decayMode());
		   
		   if((itau->decayMode())==0)
		     {
		       ++DenomCount0;
		       TauEffDMode0->Fill(PassDecayMode,itau->pt());

		       // if(PassDecayMode)
		       // 	 {
		       // 	   ++NumCount0;
		       // 	 }
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
		   
		     if(((itau->decayMode())==10) && PassDecayMode)
		       {
			 TauEffDMode10->Fill(PassDecayMode,itau->pt());
			 NumDMode10->Fill(iJet->pt());
		       }
		   
		   
		     }


		   
		 }
	       
	       
	       
	       //}
	   
	   
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
   std::cout<< " denominator Iso: " <<  DenomCountIso  <<endl;
   std::cout<< " Numerator Iso: " <<  NumCountIso <<endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
TauEfficiency::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TauEfficiency::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TauEfficiency::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TauEfficiency);
