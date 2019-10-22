// -*- C++ -*-
//
// Package:    GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer
// Class:      PostPrimarySelectionAnalyzer
// 
/**\class PostPrimarySelectionAnalyzer PostPrimarySelectionAnalyzer.cc GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer/plugins/PostPrimarySelectionAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Wed, 27 Mar 2019 17:44:06 GMT
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


#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

#include"DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "TH1.h"
#include "TH2.h"

#include "TLatex.h"
#include "TAttFill.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"






//


// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class PostPrimarySelectionAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit PostPrimarySelectionAnalyzer(const edm::ParameterSet&);
  ~PostPrimarySelectionAnalyzer();
  bool isSpecificDaughter(const reco::Candidate * particle,int Id);
  double RefToDaughterPhi(const reco::Candidate * particle,int Id);
  double RefToDaughterEta(const reco::Candidate * particle,int Id);
  double RefToDaughterPdg(const reco::Candidate * particle,int Id);
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<pat::ElectronCollection> electronSrc_;
  edm::EDGetTokenT<pat::TauCollection> TauSrc_;
  
  edm::EDGetTokenT<pat::ElectronCollection> Cutelectron_;
  edm::EDGetTokenT<pat::TauCollection> CutTau_;
  
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  edm::EDGetTokenT<edm::View<pat::PackedGenParticle> >packedGenToken_;


  //
  TH1D *Mvisible;
  //TH1D *Mvisiblecut;
  //TH1D *PtTau;
  TH1I *NumPairs;
  //TH1I *MatchCount;
  TH1I *TauCount;
  TH1I *EleCount;
  TH2I *EleTau;
  //TH1I *ModeDiff;
  TH1I *ModeDiffEvent;
  TH1D *dRTest;
  TH1D *MvisibleCutL;
  TH1I *NumPairCheck;
  TH1I *NumPairdR;
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
PostPrimarySelectionAnalyzer::PostPrimarySelectionAnalyzer(const edm::ParameterSet& iConfig):
  electronSrc_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
  TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus"))),
  Cutelectron_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("Cutelectrons"))),
  CutTau_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("CutTaus"))),
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  packedGenToken_ (consumes<edm::View<pat::PackedGenParticle> >(iConfig.getParameter<edm::InputTag>("packed")))

{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> fl;
   Mvisible = fl->make<TH1D>("Mvisible" , "Mass_{visible} after the Primary Selection" , 100 ,-0.5 , 99.5 );
   //Mvisiblecut =fl->make<TH1D>("Mvisiblecut" , "Mass_{visible} after dR > 0.05 and < 0.8  cut" , 100 ,-0.5 , 99.5 );
   //PtTau =fl->make<TH1D>("PtTau" , "Tau Pt after passing dR(Tau,ele) > 0.05 and > 0.05" ,150,0,150 );
   NumPairs =fl->make<TH1I>("NumPairs" , "Number of Pairs" ,40 ,-0.5 ,39.5 );
   TauCount =fl->make<TH1I>("TauCount" , "Number of Taus in every event" ,10 ,-0.5 ,9.5 );
   EleCount =fl->make<TH1I>("EleCount" , "Number of electrons in every event" ,10 ,-0.5 ,9.5 );
   EleTau =fl->make<TH2I>("EleTau" , "Number of Taus vs Number of Taus in every event" ,10 ,-0.5 ,9.5,40,-0.5,39.5);
   //ModeDiff =fl->make<TH1I>("ModeDiff" , "Differentiating pairs on whether Tau/Ele is GenMatched" ,5 ,-0.5 ,4.5 );
   ModeDiffEvent =fl->make<TH1I>("ModeDiffEvent" , "Differentiating events on whether Tau/Ele is GenMatched" ,5 ,-0.5 ,4.5 );
   dRTest = fl->make<TH1D>("dRTest" , "dR for Tau/Ele pairs with Mass_{visible} <= 14GeV",100 ,0.0,1.0 );
   MvisibleCutL =fl->make<TH1D>("MvisibleCutL" , "Mass_{visible}  mass points after dR > 0.05 and < 0.8  cut" , 100 ,-0.5 , 99.5 );
   NumPairCheck =fl->make<TH1I>("NumPairCheck" , "Number of Pairs with Mass_{visible} <= 14GeV" ,16,-0.5 ,15.5 );
   NumPairdR =fl->make<TH1I>("NumPairdR" , "Number of Pairs in events passing dR(Tau,Ele) >0.05 and < 0.8 Cut " ,16,-0.5 ,15.5 );

}


PostPrimarySelectionAnalyzer::~PostPrimarySelectionAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

bool PostPrimarySelectionAnalyzer::isSpecificDaughter(const reco::Candidate * particle,int Id)
{
  if ((fabs(particle->pdgId())==Id))
    return true;
  for(size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(isSpecificDaughter(particle->daughter(i),Id)) return true;

    }
  return false;
}
double PostPrimarySelectionAnalyzer::RefToDaughterPhi(const reco::Candidate * particle,int Id)
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
double PostPrimarySelectionAnalyzer::RefToDaughterEta(const reco::Candidate * particle,int Id)
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
double PostPrimarySelectionAnalyzer::RefToDaughterPdg(const reco::Candidate * particle,int Id)
{

  double Pdg=0;
  if ((fabs(particle->pdgId())==Id))
    return particle->pdgId();
  for( size_t i=0;i <particle->numberOfDaughters();i++)
    {
      if(RefToDaughterPdg(particle->daughter(i),Id))
        Pdg=particle->daughter(i)->pdgId();

    }
  return Pdg;
}

//
// member functions
//

// ------------ method called for each event  ------------
void
PostPrimarySelectionAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  Handle<pat::ElectronCollection> electrons;
  iEvent.getByToken(electronSrc_,electrons);
  Handle<pat::TauCollection> Taus;
  iEvent.getByToken(TauSrc_,Taus);
  
  Handle<pat::ElectronCollection> electrons_c;
  iEvent.getByToken(Cutelectron_,electrons_c);
  Handle<pat::TauCollection> Taus_c;
  iEvent.getByToken(CutTau_,Taus_c);
  
  Handle<edm::View<reco::GenParticle> > pruned;
  iEvent.getByToken(prunedGenToken_, pruned);
 
  Handle<edm::View<pat::PackedGenParticle> > packed;
  iEvent.getByToken(packedGenToken_, packed);


  //double VmassCut=99999;
  double Vmass=99999;
  double delR=99999;
  int iele_Id=0;
  int paircount=0;
  int CheckCount=0;
  int dRCount=0;
  //int Taucount=0;
  int TauIcount=0;
  int elecount=0;
  
  int TauPassCount=0;
  int ElePassCount=0;
  int TauFailCount=0;
  int EleFailCount=0;
  

  
  for(pat::ElectronCollection::const_iterator iele = electrons->begin() ; iele !=electrons->end() ; ++iele,++iele_Id)
    {
      ++elecount;
      cout<< "Electron Number  "<< iele_Id << " Electron Pt  : " << iele->pt() << " Electron eta : " << iele->eta() <<endl;
      
    }
  for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)

    {
      ++TauIcount;                                                                                                                                                                                                                                                        
      
    }
  TauCount->Fill(TauIcount);
  EleCount->Fill(elecount);
  cout<< "Electron Count : "<< elecount<<endl;
  EleTau->Fill(elecount,TauIcount);

  
  for(pat::ElectronCollection::const_iterator iele = electrons->begin() ; iele !=electrons->end() ; ++iele)
    {
      for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)

        {
	  ++paircount;
          Vmass=abs((iele->p4() + itau->p4()).mass());
	  delR=reco::deltaR(*iele,*itau);
	  if(Vmass <=14)
	    {
	      ++CheckCount;
	      dRTest->Fill(delR);
	    }
	  if(delR < 0.8 && delR >0.05)
	    {
	    
	      ++dRCount;
	    }
	  if(delR < 0.8 && delR >0.05  /*&& Vmass <=14*/)

	    {
	      MvisibleCutL->Fill(Vmass);
	      //++dRCount;
	    }
	  Mvisible->Fill(Vmass);
          Mvisible->SetFillColor(kYellow);

          Mvisible->GetXaxis()->SetTitle("M_{v} after Primary Selection ");
          Mvisible->GetYaxis()->SetTitle("# of events");
	  

	}
    }
  NumPairs->Fill(paircount);
  NumPairCheck->Fill(CheckCount);
  NumPairdR->Fill(dRCount);
  /*for(pat::ElectronCollection::const_iterator iele = electrons_c->begin() ; iele !=electrons_c->end();++iele)
    {
      for(pat::TauCollection::const_iterator itau = Taus_c->begin() ; itau !=Taus_c->end() ; ++itau)

	{
	  VmassCut=abs((iele->p4() + itau->p4()).mass());
	  Mvisiblecut->Fill(VmassCut);
	  Mvisiblecut->SetFillColor(kYellow);

	  Mvisiblecut->GetXaxis()->SetTitle("M_{v} after dR  cut ");
	  Mvisiblecut->GetYaxis()->SetTitle("# of events");
	  PtTau->Fill(itau->pt());

	}
    }
  */
  bool ElecFound=false;
  bool TauFound=false;
  bool ElecDecay=false;
  bool TauDecay=false;
  bool dRTauMatch=false;
  bool dREleMatch=false;
  bool dRTauDecayMatch=false;
  bool dREleDecayMatch=false;
  for(size_t i=0; i<(pruned.product())->size() ;i++)
    {
      for(pat::ElectronCollection::const_iterator iele = electrons->begin() ; iele !=electrons->end() ; ++iele)
	{
 
	  for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)
	    {      
	      if(fabs((*pruned)[i].pdgId())==15)
		{
		  const Candidate * Tau = &(*pruned)[i];
		  if (fabs(Tau->mother()->pdgId())==36)
		    
		    {
		      // bool ElecFound=false;
		      // bool TauFound=false;
		      // bool ElecDecay=false;
		      // bool TauDecay=false;
		      // bool dRTauMatch=false;
		      // bool dREleMatch=false;
		      // bool dRTauDecayMatch=false;
		      // bool dREleDecayMatch=false;

		      const Candidate *PseudoTau = &(*pruned)[i];
		      unsigned  n=PseudoTau->numberOfDaughters();
		      for ( size_t j =0; j < n ; j++)
			{
			  const Candidate * Daughter=PseudoTau->daughter(j);
			  //cout<< " Daughter No: " << j << " pdgId " <<  Daughter->pdgId()  << "  Daughter Pt: " <<  Daughter->pt()  <<  " Daughter Eta: "  <<  Daughter->eta()  <<endl;
			  
			  if ((fabs(Daughter->pdgId())==11))
			    {
			      
			      cout<<"Electron to match" <<endl;
			      ElecFound=true;
			    }
			  //cout<<" pdgId: " <<  Daughter->pdgId()  << "  Electron Pt: " <<  Daughter->pt()  <<  " Electron Eta: "  <<  Daughter->eta()  <<endl;
			      if(ElecFound)
				{
			  dREleMatch=(reco::deltaR(Daughter->eta(),Daughter->phi(),iele->eta(),iele->phi()) < 0.2);
				}
			      if(dREleMatch)
				{
				  ++ElePassCount;
				}
			      if(ElecFound && !dREleMatch)
				{
				  ++EleFailCount;
				}
				
				
			  if( (!TauFound) && (fabs(Daughter->pdgId())!=11) &&  (fabs(Daughter->pdgId())!=12) && (fabs(Daughter->pdgId())!=15) && (fabs(Daughter->pdgId())!=22) && (fabs(Daughter->pdgId())!=16)  )
			    {
			      cout<<"possible Hadronic Tau" <<endl;
			      //cout<<" pdgId: " <<  Tau->pdgId()  << "  Tau Pt: " <<  Tau->pt()  <<  " Tau Eta: "  <<  Tau->eta()  <<endl;
			      cout<<" pdgId: " <<  Daughter->pdgId()  << "  Daughter Pt: " <<  Daughter->pt()  <<  " Daughter Eta: "  <<  Daughter->eta()  <<endl;   
			      TauFound=true;
			    }
			  if(TauFound)
			    {
			  dRTauMatch=(reco::deltaR(PseudoTau->eta(),PseudoTau->phi(),itau->eta(),itau->phi()) <0.2);
			    }
			  if(dRTauMatch)
			    {
			      ++TauPassCount;
			    }
			  if(TauFound && !dRTauMatch)
			    {
			      ++TauFailCount;
			    }
			  bool isHad= false;
			  bool isElectron =false;
			  
			  if(fabs(Daughter->pdgId())==15)
			    {
			      isHad=!isSpecificDaughter(Daughter,11) && !isSpecificDaughter(Daughter,12);
			      isElectron=isSpecificDaughter(Daughter,11);
			      
			      if(/*!TauDecay &&*/ isHad)
				{
				  cout<< "####possible Decayed Hadronic Tau###" <<endl; 
				  //cout<<" pdgId: " <<  Tau->pdgId()  << "  Tau Pt: " <<  Tau->pt()  <<  " Tau Eta: "  <<  Tau->eta()  <<endl;
				  TauDecay=true;
				  cout<<  " Daughter pdg for 211 if present: " <<  RefToDaughterPdg(Daughter,211)  <<endl;
				  cout<<  " Daughter pdg for 311 if present: " <<  RefToDaughterPdg(Daughter,311)  <<endl; 
                                  cout<<  " Daughter pdg for 321 if present: " <<  RefToDaughterPdg(Daughter,321)  <<endl; 
				  //cout<<  " Daughter Eta: " << RefToDaughterEta(Daughter,11) <<endl;
				  //isHad=isSpecificDaughter(Daughter,111) || isSpecificDaughter(Daughter,211) || isSpecificDaughter(Daughter,311) ||  isSpecificDaughter(Daughter,321) || isSpecificDaughter(Daughter,130) || isSpecificDaughter(Daughter,310) ;
				}
				 
			      if(TauDecay)
				{
				dRTauDecayMatch=(reco::deltaR(PseudoTau->eta(),PseudoTau->phi(),itau->eta(),itau->phi()) <0.2);
				} 
			      if(dRTauDecayMatch)
				{
				  ++TauPassCount;
				}
			      if(TauDecay && !dRTauDecayMatch)
				{
				  ++TauFailCount;
				}
			      if(isElectron)
				{
				  cout<< "possible Tau decaying to Electron"<<endl;
				  //cout<<  " Daughter Pt: " <<  RefToDaughterPt(Daughter,11)  <<endl;
				  //cout<<  " Daughter Eta: " << RefToDaughterEta(Daughter,11) <<endl;
				  //dREleDecayMatch=(reco::deltaR(->eta(),Daughter->phi(),iele->eta(),iele->phi()) <0.2);
				  
				  ElecDecay=true;
				}  
				  if(ElecDecay)	 
				    {
				      dREleDecayMatch=(reco::deltaR(RefToDaughterEta(Daughter,11),RefToDaughterPhi(Daughter,11),iele->eta(),iele->phi()) <0.2); 
				    }
				  if(dREleDecayMatch)
				    {
				      ++ElePassCount;
				    }
				  if(ElecDecay && !dREleDecayMatch)
				    {
				      ++EleFailCount;
				    }
			    }
			}
		      //}
		      //}
		      /*if(((TauFound) && (ElecFound) && (dRTauMatch) && (dREleMatch)) || ((TauDecay) && (ElecDecay) && (dRTauDecayMatch) && (dREleDecayMatch)))
			{
			  ModeDiff->Fill(0);
			}
		      

		      if(( (TauFound) && (ElecFound) && (dRTauMatch) && (!dREleMatch)) || ((TauDecay) && (ElecDecay) && (dRTauDecayMatch) && (!dREleDecayMatch)))
			{
                          ModeDiff->Fill(1);
			}

                      

		      if(( (TauFound) && (ElecFound) && (!dRTauMatch) && (dREleMatch)) || ((TauDecay) && (ElecDecay) && (!dRTauDecayMatch) && (dREleDecayMatch)))
			{
                          ModeDiff->Fill(2);
			}
		      

		      if(((TauFound) && (ElecFound) &&  (!dRTauMatch) && (!dREleMatch)) ||  ((TauDecay) && (ElecDecay) && (!dRTauDecayMatch) && (!dREleDecayMatch)))
                        {
                          ModeDiff->Fill(3);
                        }
		      */ 
		      /* if(((TauFound) && (!ElecFound)) || ((!TauFound) && (ElecFound)))
			{
			  ModeDiff->Fill(4);
			  
			}
		      if(((TauDecay) && (!ElecDecay)) || ((!TauDecay) && (ElecDecay)))
			{
			  ModeDiff->Fill(4);
			}
		      */
		    }
		}
	    }
	  
	}
      
    }
  if((TauPassCount > 0) && (ElePassCount >0) /* && (TauFailCount==0) && (EleFailCount==0) */) 
    {
      ModeDiffEvent->Fill(0);
    }
  if((TauPassCount==0) && (ElePassCount==0) /*&& (EleFailCount >0) && (TauFailCount > 0)*/)
    {
      ModeDiffEvent->Fill(3);
    }
  if((ElePassCount ==0) && (TauPassCount > 0) )
    {
      ModeDiffEvent->Fill(1);
    }
  if((TauPassCount== 0) && (ElePassCount > 0))
    {
      ModeDiffEvent->Fill(2);
    }
  
  /*#ifdef THIS_IS_AN_EVENT_EXAMPLE
    Handle<ExampleData> pIn;
    iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
   */

}


// ------------ method called once each job just before starting event loop  ------------
void 
PostPrimarySelectionAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PostPrimarySelectionAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PostPrimarySelectionAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PostPrimarySelectionAnalyzer);
