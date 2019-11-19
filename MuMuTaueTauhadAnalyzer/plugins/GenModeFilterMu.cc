// -*- C++ -*-
//
// Package:    GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer
// Class:      GenModeFilterMu	
// 
/**\class GenModeFilterMu	 GenModeFilterMu.cc GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer/plugins/GenModeFilterMu.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Wed, 10 Apr 2019 16:03:15 GMT
//2017 version updated on Mon 17 June 2019
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "TLorentzVector.h"

#include "TMath.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronCore.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PATObject.h"

#include"DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

#include "Math/VectorUtil.h"
#include "Math/LorentzVector.h"


//
// class declaration
//

class GenModeFilterMu : public edm::stream::EDFilter<> {
   public:
      explicit GenModeFilterMu(const edm::ParameterSet&);
      ~GenModeFilterMu();
  bool isAncestor(const reco::Candidate * ancestor, const reco::Candidate * particle);
  bool isDaughter(const reco::Candidate * Daughter, const reco::Candidate * particle);
  bool isPdgMatch(const reco::Candidate * Ancestor, const reco::Candidate * particle, int Id);

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  edm::EDGetTokenT<edm::View<pat::PackedGenParticle> >packedGenToken_;
  int tmth=0;
  int tmtmGlob=0;
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
GenModeFilterMu::GenModeFilterMu(const edm::ParameterSet& iConfig):
  prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  packedGenToken_ (consumes<edm::View<pat::PackedGenParticle> >(iConfig.getParameter<edm::InputTag>("packed")))
  

{
   //now do what ever initialization is needed

}


GenModeFilterMu::~GenModeFilterMu()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//
bool GenModeFilterMu::isAncestor(const reco::Candidate* ancestor, const reco::Candidate * particle)
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


bool GenModeFilterMu::isDaughter(const reco::Candidate* Daughter, const reco::Candidate * particle)
{
  //particle is already the ancestor 
  if(Daughter== particle ) return true;

  //otherwise loop on Daughters, if any and return true if the ancestor is found
  
                                                                                                                                                                                                                                                                               
  for(size_t i=0;i< particle->numberOfDaughters();i++)
    {
      if(isDaughter(Daughter,particle->daughter(i))) return true;
    }
  //if we did not return yet, then particle and ancestor are not relatives                                                                                                                                                                                                    
  return false;
}


bool GenModeFilterMu::isPdgMatch(const reco::Candidate * ancestor, const reco::Candidate * particle, int Id)
{

  //Check the mother in the packed collection and a candidate in the packed collection against a common pdgId->The pdgId can be changed to check for various ancestors                                                                                                         
  if((fabs(ancestor->pdgId())==Id) && (fabs(particle->pdgId())==Id) && (ancestor==particle)) return true;
  for(size_t i=0;i<particle->numberOfMothers();i++)
    {
      if(isPdgMatch(ancestor,particle->mother(i),Id)) return true;
    }
  return false;
}







// ------------ method called on each new Event  ------------
bool
GenModeFilterMu::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;
   int tmthfill=0;
   int tmtm=0;
   
   Handle<edm::View<reco::GenParticle> > pruned;
   iEvent.getByToken(prunedGenToken_, pruned);
   //Handle<pat::PackedGenParticle> packed;                                                                                                                                                                                                                                     
   Handle<edm::View<pat::PackedGenParticle> > packed;
   iEvent.getByToken(packedGenToken_, packed);
   
   vector<pat::PackedGenParticle*>Packed;

   for(size_t i=0; i<(pruned.product())->size();i++)
     {


       if(fabs((*pruned)[i].pdgId())==36)
	 {
	   TLorentzVector invariant_v4_Tau_e;
	   TLorentzVector invariant_v4_Tau_had;
	   TLorentzVector invariant_v4_Tau_mu;
	   const Candidate * PsuedoScalar = &(*pruned)[i];

	   for(size_t j=0; j<(packed.product())->size() ;j++)
	     {
	       const Candidate * motherInPrunedCollection = (*packed)[j].mother(0) ;
	       const GenParticleRef motherInPrunedCollectionRef=(*packed)[j].motherRef();
	       if((motherInPrunedCollection != nullptr) && (isAncestor( PsuedoScalar , motherInPrunedCollection)) && (fabs((motherInPrunedCollection->pdgId()))==15) && (motherInPrunedCollection->status()!=1) )
		 {
		   
		   if( (fabs((*packed)[j].pdgId())==13)  && ((*packed)[j].statusFlags().isFirstCopy()) && ((*packed)[j].isDirectPromptTauDecayProductFinalState()) )

		     
		     {
		       
		       invariant_v4_Tau_mu +=TLorentzVector((*packed)[j].p4().X(),(*packed)[j].p4().Y(),(*packed)[j].p4().Z(),(*packed)[j].p4().T());
		       ++tmtm;
		       
		       
		     }
		   
		   
		   
		   if((fabs((*packed)[j].pdgId())==11) && ((*packed)[j].statusFlags().isFirstCopy()) && ((*packed)[j].isDirectPromptTauDecayProductFinalState())  )

		     {
		       //++tete;
		       invariant_v4_Tau_e +=TLorentzVector((*packed)[j].p4().X(),(*packed)[j].p4().Y(),(*packed)[j].p4().Z(),(*packed)[j].p4().T());
		       

		     }

		   
		 }
	       
	       for( size_t k=0; k<(pruned.product())->size();k++)
		 {
		   
		   if((motherInPrunedCollection != nullptr) && !(isPdgMatch(&(*pruned)[k],motherInPrunedCollection,11)) && !(isPdgMatch(&(*pruned)[k],motherInPrunedCollection,13)) && (isAncestor( PsuedoScalar , motherInPrunedCollection)) && (fabs((*packed)[j].pdgId())!=11) && (fabs((*packed)[j].pdgId())!=13) && (motherInPrunedCollection->status()!=1) && ((*packed)[j].statusFlags().isFirstCopy()) && (isPdgMatch(&(*pruned)[k],motherInPrunedCollection,15)) && (fabs((*packed)[j].pdgId())!=12) && (fabs((*packed)[j].pdgId())!=16)  && (fabs((*packed)[j].pdgId())!=14) && ((*packed)[j].isDirectPromptTauDecayProductFinalState())  )
		     
		     
		     {
		       //cout<<"Tau_had_pdgID: "<<(*packed)[j].pdgId() <<endl;
		       //cout<<"mother pdgID: " <<(*packed)[j].mother(0)->pdgId()<<endl;
		       //cout<<"mother key: " <<(*packed)[j].motherRef().key()<<endl;
		       
		       std::vector<pat::PackedGenParticle*>::iterator check;
		       check=std::find(Packed.begin(),Packed.end(),const_cast<pat::PackedGenParticle*>((*packed).ptrAt(j).get()));
		       if(check==Packed.end())
			 {
			   Packed.push_back(const_cast<pat::PackedGenParticle*>((*packed).ptrAt(j).get()));
			   invariant_v4_Tau_had +=TLorentzVector((*packed)[j].p4().X(),(*packed)[j].p4().Y(),(*packed)[j].p4().Z(),(*packed)[j].p4().T());
			   
			   
			   //cout<<"X: "<<(*packed)[j].p4().X()<<endl;
			   //cout<<"Y: "<<(*packed)[j].p4().Y()<<endl;
			   //cout<<"Z: "<<(*packed)[j].p4().Z()<<endl;
			   //cout<<"T: "<<(*packed)[j].p4().T()<<endl;
			 }
		       
		       
		     }
		 }
	       
	     }
	   
	   

	   if ( invariant_v4_Tau_e.X()==0 &&  invariant_v4_Tau_e.Y()==0 &&  (invariant_v4_Tau_e.Z()==0) &&  (invariant_v4_Tau_e.T()==0) && (invariant_v4_Tau_e.Mag()==0) && (invariant_v4_Tau_had.X()!=0) && (invariant_v4_Tau_had.Y()!=0) && (invariant_v4_Tau_had.Z()!=0) && (invariant_v4_Tau_had.T()!=0) && (invariant_v4_Tau_had.Mag() >0) && (invariant_v4_Tau_mu.X()!=0) && (invariant_v4_Tau_mu.Y()!=0) && (invariant_v4_Tau_mu.Z()!=0) && (invariant_v4_Tau_mu.T()!=0) && (invariant_v4_Tau_mu.Mag()>0) )
	     
	     {
	       ++tmthfill;
	       ++tmth;
	     }
	   
	   //if(tete==2)
	   //{ ++teteGlob;
	   //}
	   
	   /*if ( invariant_v4_Tau_e.X()!=0 &&  invariant_v4_Tau_e.Y()!=0 &&  (invariant_v4_Tau_e.Z()!=0) &&  (invariant_v4_Tau_e.T()!=0) && (invariant_v4_Tau_e.Mag()>0) && (invariant_v4_Tau_had.X()==0) && (invariant_v4_Tau_had.Y()==0) && (invariant_v4_Tau_had.Z()==0) && (invariant_v4_Tau_had.T()==0) && (invariant_v4_Tau_had.Mag() ==0) && (invariant_v4_Tau_mu.X()==0) && (invariant_v4_Tau_mu.Y()==0) && (invariant_v4_Tau_mu.Z()==0) && (invariant_v4_Tau_mu.T()==0) && (invariant_v4_Tau_mu.Mag()==0) )
	     
	     {
	     ++tetefill;
	     
	     }
	   */
	   
	 }
     }
   cout<<" TaumTauHadPointer: " <<tmthfill<<endl;
   cout<< " TaumTauHadCount : " <<tmth<<endl;
   
   bool GoodMode= false;
   bool DoubleMu=false;
   if(tmtm==2)
     { ++tmtmGlob;
     }
   DoubleMu=(tmtm==2);
   /*#ifdef THIS_IS_AN_EVENT_EXAMPLE
     Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
ESHandle<SetupData> pSetup;
iSetup.get<SetupRecord>().get(pSetup);
#endif
   */
   cout<< "mu count " <<tmtm<<endl;
   cout<<" Double mu count " << tmtmGlob<<endl;
   
   GoodMode=((tmthfill> 0) && (!DoubleMu));
   if(DoubleMu)
     {cout<< "lutha!"<<endl;}
   
   if(GoodMode)
     return true;
   else
     return false;
   
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
GenModeFilterMu::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
GenModeFilterMu::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
GenModeFilterMu::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
GenModeFilterMu::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
GenModeFilterMu::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
GenModeFilterMu::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenModeFilterMu::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(GenModeFilterMu);
