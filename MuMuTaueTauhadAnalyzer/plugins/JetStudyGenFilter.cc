// -*- C++ -*-
//
// Package:    LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer
// Class:      JetStudyGenFilter
// 
/**\class JetStudyGenFilter JetStudyGenFilter.cc LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/plugins/JetStudyGenFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Thu, 09 Jan 2020 19:09:35 GMT
//
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

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


//
// class declaration
//

class JetStudyGenFilter : public edm::stream::EDFilter<> {
   public:
      explicit JetStudyGenFilter(const edm::ParameterSet&);
      ~JetStudyGenFilter();
  std::vector<const reco::Candidate*>FindStat1( const reco::Candidate * particle);

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
JetStudyGenFilter::JetStudyGenFilter(const edm::ParameterSet& iConfig):
prunedGenToken_ (consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned")))

{
   //now do what ever initialization is needed

}


JetStudyGenFilter::~JetStudyGenFilter()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}




std::vector<const reco::Candidate*>JetStudyGenFilter::FindStat1( const reco::Candidate * particle)
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
	  //std::cout<< "Daughter no:  "<< i << "  pdgId: " << Daughter->pdgId() <<" Daughter Pt: " << Daughter->pt()<<" Daughter Status: " << Daughter->status()<<std::endl;
	  
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

// ------------ method called on each new Event  ------------
bool
JetStudyGenFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace reco;
  vector< const Candidate*> Muons;


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
	      //cout<<" Final Muon pt: "<< Muon->pt() <<" Muon Status: "<< Muon->status() << " Muon Mother pdgId: " << Muon->mother()->pdgId() <<endl;
	      Muons.push_back(Muon);
	    
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
		      Muons.push_back(daughters[jDau]);
		    }
		}	      
	      
	      
	      
	    }
	  
	}
    }
  
  bool MuonEvent=false;
  //cout<<"Size of Muon Vector: "<< Muons.size() <<endl;
  MuonEvent=(Muons.size() >0);
  if(MuonEvent)
    return true;
  else
    return false;

// #endif
//    return true;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
JetStudyGenFilter::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
JetStudyGenFilter::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
JetStudyGenFilter::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
JetStudyGenFilter::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
JetStudyGenFilter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
JetStudyGenFilter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetStudyGenFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(JetStudyGenFilter);
