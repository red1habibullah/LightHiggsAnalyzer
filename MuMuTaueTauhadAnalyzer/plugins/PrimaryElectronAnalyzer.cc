// -*- C++ -*-
//
// Package:    GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer
// Class:      PrimaryElectronAnalyzer
// 
/**\class PrimaryElectronAnalyzer PrimaryElectronAnalyzer.cc GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer/plugins/PrimaryElectronAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Thu, 11 Apr 2019 09:17:12 GMT
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
#include "DataFormats/EgammaCandidates/interface/GsfElectronCore.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PATObject.h"

#include "TH1.h"
#include "TLatex.h"
#include "TH2.h"
#include "TAttFill.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class PrimaryElectronAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit PrimaryElectronAnalyzer(const edm::ParameterSet&);
      ~PrimaryElectronAnalyzer();
  bool isAncestor(const reco::Candidate * ancestor, const reco::Candidate * particle);
  bool isPdgMatch(const reco::Candidate * Ancestor, const reco::Candidate * particle, int Id);

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  
  edm::EDGetTokenT<pat::ElectronCollection> electronSrc_;
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  edm::EDGetTokenT<edm::View<pat::PackedGenParticle> >packedGenToken_;
  
  TH1D *Pt;
  TH1D *pt;
  TH1D *PtGen;
  TH2F *PtEta;
  TH2F *PtEtaFail;
  TH2F *PtEtaPass;
  
  int dcount=0;
  //TH2F *PtEtaGen;
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
PrimaryElectronAnalyzer::PrimaryElectronAnalyzer(const edm::ParameterSet& iConfig):
  electronSrc_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  packedGenToken_ (consumes<edm::View<pat::PackedGenParticle> >(iConfig.getParameter<edm::InputTag>("packed")))
  

{
   //now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> f;
   Pt =f->make<TH1D>("Pt","Pt of Highest Pt Electron per event",200,-0.5,199.5);
   pt =f->make<TH1D>("pt","Pt of all the electrons in every event",200,-0.5,199.5); 
   PtGen=f->make<TH1D>("PtGen","Pt of Gen Level electrons from Tau_e",200,-0.5,199.5);
   PtEta=f->make<TH2F>("PtEta","Pt vs Eta Distribution of Gen Level electrons",100,-5,5,200,-0.5,199.5);
   PtEtaFail =f->make<TH2F>("PtEtaFail","Pt vs Eta Distribution of Gen Level Electrons with no reconstructed counterparts",100,-5,5,200,-0.5,199.5);
   PtEtaPass =f->make<TH2F>("PtEtaPass","Pt vs Eta Distribution of Gen Level Electrons with reconstructed counterparts",100,-5,5,200,-0.5,199.5);

}


PrimaryElectronAnalyzer::~PrimaryElectronAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//
bool PrimaryElectronAnalyzer::isAncestor(const reco::Candidate* ancestor, const reco::Candidate * particle)
{
  //particle is already the ancestor                                                                                                                                                                                                                                           
  if(ancestor == particle ) return true;

  //otherwise loop on mothers, if any and return true if the ancestor is found                                                                                                                                                                                                 
  for(size_t i=0;i< particle->numberOfMothers();i++)
    {
      if(isAncestor(ancestor,particle->mother(i))) return true;
    }
  //if we did not return yet, then particle and ancestor are not relatives                                                                                                                                                                                                     
  return false;
}

bool PrimaryElectronAnalyzer::isPdgMatch(const reco::Candidate * ancestor, const reco::Candidate * particle, int Id)
{

  //Check the mother in the packed collection and a candidate in the packed collection against a common pdgId->The pdgId can be changed to check for various ancestors                     
                                                                                                                                                                                                                                                                               
  if((fabs(ancestor->pdgId())==Id) && (fabs(particle->pdgId())==Id) && (ancestor==particle)) return true;
  for(size_t i=0;i<particle->numberOfMothers();i++)
    {
      if(isPdgMatch(ancestor,particle->mother(i),Id)) return true;
    }
  return false;
}





// ------------ method called for each event  ------------
void
PrimaryElectronAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;
   int Tau_e=0;
   Handle<pat::ElectronCollection> electrons;
   iEvent.getByToken(electronSrc_,electrons);
   
   Handle<edm::View<reco::GenParticle> > pruned;
   iEvent.getByToken(prunedGenToken_, pruned);
   
   Handle<edm::View<pat::PackedGenParticle> > packed;
   iEvent.getByToken(packedGenToken_, packed);


   
   
   
   double Highest_Pt_ele= 0;
   pat::Electron MaxElectron;
   double Ele_Pt=99999;
   bool NonEmpty= false;
   NonEmpty=((electrons->size()) > 0);
   //cout<< "  size: "<< electrons->size() <<endl;
   if(NonEmpty)
     {
   for(pat::ElectronCollection::const_iterator iele = electrons->begin() ; iele !=electrons->end() ; ++iele)
     {
       pt->Fill(iele->pt());
       // NonEmpty=(((electrons.product())->size()) >0);
       //if(NonEmpty)
       //{
       if(iele->pt() > Highest_Pt_ele)
	 {
	   Highest_Pt_ele=iele->pt();
	   MaxElectron=(*iele);
	   
	 }
       //}
     }
     
   //cout<< " Pt: " <<MaxElectron.pt()<<endl;
   Ele_Pt=MaxElectron.pt();
   Pt->Fill(Ele_Pt);
     }
   
   
   bool twice=false;
   
   for(size_t i=0; i<(pruned.product())->size();i++)
     {
       if(fabs((*pruned)[i].pdgId())==36)
         {
           const Candidate * PsuedoScalar = &(*pruned)[i];
           for(size_t j=0; j<(packed.product())->size() ;j++)
             {
               const Candidate * motherInPrunedCollection = (*packed)[j].mother(0) ;
               if((motherInPrunedCollection != nullptr) && (isAncestor( PsuedoScalar , motherInPrunedCollection)) && (fabs((motherInPrunedCollection->pdgId()))==15) && (motherInPrunedCollection->status()!=1) )
                 {
                   if((fabs((*packed)[j].pdgId())==11) && ((*packed)[j].statusFlags().isFirstCopy()) && ((*packed)[j].isDirectPromptTauDecayProductFinalState()) )

                     {
                       ++Tau_e;
		       //cout<<"Electron Pt: "<<(*packed)[j].p4().pt()<<endl;
		       //cout<<"X: "<<(*packed)[j].p4().X()<<endl;                                                                                                                                                                                                         
		       //cout<<"Y: "<<(*packed)[j].p4().Y()<<endl;                                                                                                                                                                                                         
		       //cout<<"Z: "<<(*packed)[j].p4().Z()<<endl;                                                                                                                                                                                                         
		       //cout<<"T: "<<(*packed)[j].p4().T()<<endl;  
		       

                       
                     }
                 }

             }
         }


     }
   
   twice=(Tau_e==2);
   if(twice)
     {
       cout<<" ========================== "<<endl;
       cout<<" two electrons in the event "<<endl;
       ++dcount;
     }








   for(size_t i=0; i<(pruned.product())->size();i++)
     {
       if(fabs((*pruned)[i].pdgId())==36)
	 {
	   const Candidate * PsuedoScalar = &(*pruned)[i];
	   
	   for(size_t j=0; j<(packed.product())->size() ;j++)
	     {
	       const Candidate * motherInPrunedCollection = (*packed)[j].mother(0) ;
	       //for(size_t k=0; k<(pruned.product())->size() ;k++)
	       //{ //2
		 //if(fabs((*pruned)[k].pdgId())==15)
		     //{ //1
		       //const Candidate * Tau =&(*pruned)[k];
	       
	       if((motherInPrunedCollection != nullptr) && (isAncestor( PsuedoScalar , motherInPrunedCollection)) && (fabs((motherInPrunedCollection->pdgId()))==15) && (motherInPrunedCollection->status()!=1) )
		 {
		   if((fabs((*packed)[j].pdgId())==11) && ((*packed)[j].statusFlags().isFirstCopy()) && ((*packed)[j].isDirectPromptTauDecayProductFinalState()) )
		     		     
		     {
		       //++Tau_e;
			   
		       
			   PtGen->Fill((*packed)[j].p4().pt());
			   PtEta->Fill((*packed)[j].p4().eta(),(*packed)[j].p4().pt());
			   PtEta->GetYaxis()->SetTitle("Pt(Gev)");
			   PtEta->GetXaxis()->SetTitle("#eta");
			   PtEta->SetOption("COLZ");

			   if(!NonEmpty)
			     {
			       PtEtaFail->Fill((*packed)[j].p4().eta(),(*packed)[j].p4().pt());
			       PtEtaFail->GetYaxis()->SetTitle("Pt(Gev)");
			       PtEtaFail->GetXaxis()->SetTitle("#eta");
			       PtEtaFail->SetOption("COLZ");
			     }
			   if(NonEmpty)
			     {
			       PtEtaPass->Fill((*packed)[j].p4().eta(),(*packed)[j].p4().pt());
                               PtEtaPass->GetYaxis()->SetTitle("Pt(Gev)");
                               PtEtaPass->GetXaxis()->SetTitle("#eta");
                               PtEtaPass->SetOption("COLZ");

			     
			     
			     }
		     }
		   
		 }
	       //} //1
	       //}//2 
	     }
	   
	 }
       
     }
   cout<< "Number of Electrons: "<<Tau_e<<endl;
   
   
   
   
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
PrimaryElectronAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PrimaryElectronAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PrimaryElectronAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(PrimaryElectronAnalyzer);
