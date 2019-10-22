// -*- C++ -*-

// Package:    GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer
// Class:      DiMuonFilter
// 
/**\class DiMuonFilter DiMuonFilter.cc GGHAA2Mu2TauAnalysis/MuMuTauTauRecoAnalyzer/plugins/DiMuonFilter.cc

Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Redwan Habibullah
//         Created:  Fri, 01 Mar 2019 02:51:15 GMT
//
//


// system include files
#include <memory>
#include <string>
#include <regex>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
//#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "TH1.h"
#include "TH2.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "TLatex.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

#include"DataFormats/PatCandidates/interface/Tau.h"


typedef math::XYZPoint Point;

//
// class declaration
//

class DiMuonFilter : public edm::stream::EDFilter<> {
   public:
      explicit DiMuonFilter(const edm::ParameterSet&);
      ~DiMuonFilter();

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
  edm::EDGetTokenT<pat::MuonCollection> muonSrc_;
  edm::EDGetTokenT<reco::VertexCollection> vtx_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<std::vector<pat::TriggerObjectStandAlone> >triggerObjects_;
  std::vector<std::string> trigNames_;
  //edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;
  //edm::EDGetTokenT<pat::ElectronCollection> electronSrc_;
  //edm::EDGetTokenT<pat::TauCollection> TauSrc_;


  //int Trigcount=0;
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
DiMuonFilter::DiMuonFilter(const edm::ParameterSet& iConfig):
  muonSrc_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonSrc"))),
  vtx_ (consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertex"))),
  triggerBits_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("bits"))),
  triggerObjects_(consumes<std::vector<pat::TriggerObjectStandAlone> >(iConfig.getParameter<edm::InputTag>("objects")))
  //triggerPrescales_(consumes<pat::PackedTriggerPrescales>(iConfig.getParameter<edm::InputTag>("prescales")))
  //electronSrc_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons")))
  //TauSrc_(consumes<pat::TauCollection>(iConfig.getParameter<edm::InputTag>("Taus")))
{
  produces<std::vector<pat::Muon>>("LeadingMuon");
  produces<std::vector<pat::Muon>>("TrailingMuon");
  trigNames_ = iConfig.getParameter<std::vector<std::string>>("trigNames");
   //now do what ever initialization is needed

}


DiMuonFilter::~DiMuonFilter()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
DiMuonFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
   using namespace edm;
   using namespace std;
   using namespace reco;
   using namespace pat;
   

   Handle<pat::MuonCollection> Muons;
   iEvent.getByToken(muonSrc_,Muons);
   
   Handle<reco::VertexCollection> Vertex;
   iEvent.getByToken(vtx_,Vertex);
   
   Handle<edm::TriggerResults> triggerBits;
   iEvent.getByToken(triggerBits_, triggerBits);
   
   Handle<std::vector<pat::TriggerObjectStandAlone> > triggerObjects;
   iEvent.getByToken(triggerObjects_, triggerObjects);
   
   //Handle<pat::PackedTriggerPrescales> triggerPrescales;
   //iEvent.getByToken(triggerPrescales_, triggerPrescales);
   
   /*
   Handle<pat::ElectronCollection> electrons;
   iEvent.getByToken(electronSrc_,electrons);

   Handle<pat::TauCollection> Taus;
   iEvent.getByToken(TauSrc_,Taus);
   */



   unique_ptr <vector<pat::Muon>>Leadingmu(new vector<pat::Muon>);
   unique_ptr <vector<pat::Muon>>Trailingmu(new vector<pat::Muon>);
   vector<pat::Muon> SelectedMuons;
   vector<pat::TriggerObjectStandAlone> SelectedTrigObj;
   /*
   vector<pat::Electron> CheckElectrons;
   vector<pat::Tau>CheckTaus;
   */
   //vector<pat::Muon> MaxCheck;
   //vector<pat::Muon>SubCheck;
   double dR_Mu_Trig=99999;
   double dR_Trig_Cut=0.1;
   double Mu1_Pt_Cut=26.0;
   double Mu2_Pt_Cut=3.0;
   double dR_Mu1_Mu2=99999;
   double dR_Mu1_Mu2_Cut=1.0;
   double InvMass_Mu1Mu2=99999;
   double InvMass_Cut=30;
   
   //////////////////////////////////////Trigger Object Selection///////////////////////////////////
   const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);
   std::vector<unsigned int> TrigSpot;
   




   ///////////////////Check that the Triggers in 2016/2017 is passed by the event//////////////////
   bool TriggerPass=0;
   bool TriggerPass_2017=0;
   for (unsigned int i = 0, n = triggerBits->size(); i < n; ++i) 
     {
     
///////////////Old implementation of trigger checkig for 2016/2017///////////////////
       std::string Trigger;
       Trigger=names.triggerName(i);
       std::regex Trigger1("(HLT_IsoMu24_v)(.*)");
       std::regex Trigger2("(HLT_IsoTkMu24_v)(.*)");
       std::regex Trigger1_94X("(HLT_IsoMu27_v)(.*)");
       std::regex Trigger2_94X("(HLT_IsoTkMu27_v)(.*)");

       TriggerPass=((std::regex_match(Trigger,Trigger1) && (triggerBits->accept(i))==1) || (std::regex_match(Trigger,Trigger2) && (triggerBits->accept(i))==1));
       if(TriggerPass)
	 {
	   //std::cout<<"Trigger Passed for 2016  "<<std::endl;
	   
	
	 }
       
       TriggerPass_2017=((std::regex_match(Trigger,Trigger1_94X) && (triggerBits->accept(i))==1) || (std::regex_match(Trigger,Trigger2_94X) && (triggerBits->accept(i))==1));
       if(TriggerPass_2017)
	 {
	   //std::cout<<"##########Trigger Passed for 2017##############  "<<std::endl;

	 }
     
       // --- find the user customized trigger path names in the existing trigger path list in TriggerResults of HLT ---//
       
       for ( std::string iName : trigNames_ ){
	 if (names.triggerName(i).find(iName) != std::string::npos )
           {
	     TrigSpot.push_back(i);
	   }
	 
       }


     }
   //bool isTrigObj_1=0;
   //bool isTrigObj_2=0; 
   //bool isTrigObj_3=0;
   //bool isTrigObj_4=0;
   
   for ( size_t iTrigObj = 0; iTrigObj < triggerObjects->size(); ++iTrigObj ) 
   { 
    
     
     pat::TriggerObjectStandAlone obj =triggerObjects->at(iTrigObj);
     obj.unpackPathNames(names);
     
     //std::string path_Name1("HLT_IsoMu24_v4");
     //std::string path_Name2("HLT_IsoTkMu24_v4");
     //std::string path_Name3("HLT_IsoMu27_v4");
     //std::string path_Name4("HLT_IsoTkMu27_v4");
     //std::vector<std::string> pathNamesAll =obj.pathNames(false);
     //std::vector<std::string> pathNamesLast = obj.pathNames(true);
     //isTrigObj_1 = obj.hasPathName(path_Name1, true, true );
     // isTrigObj_2 = obj.hasPathName(path_Name2,true, true);
     //isTrigObj_3 = obj.hasPathName(path_Name3, true,true);
     //isTrigObj_4 = obj.hasPathName(path_Name4,true,true);

     /*if ( isTrigObj_1 || isTrigObj_2)
       {
	 std::cout << "\tTrigger object@2016:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << std::endl; 
	 //SelectedTrigObj.push_back(obj);
	 
       }
     */
     for (unsigned int num : TrigSpot) //Loop through the customized trigger paths
       {
	 const std::string& name = names.triggerName(num);
	   if (obj.hasPathName(name, true))
	     {
	     
	       SelectedTrigObj.push_back(obj);
	       //std::cout << "\tTrigger object:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << std::endl;
	       
	       
	     }
       }
     
     
     /*
     if ( isTrigObj_3 || isTrigObj_4)
       {
	 std::cout << "\tTrigger object:  pt " << obj.pt() << ", eta " << obj.eta() << ", phi " << obj.phi() << std::endl;
         SelectedTrigObj.push_back(obj);

       }
     */
     
     
   }
   double max_pt_Trig=0;
   pat::TriggerObjectStandAlone FinalTrig;
   
   for(unsigned i=0; i<SelectedTrigObj.size();i++)
     {
       //cout<< "  Trigger Object: " <<  i  << " pt: " << SelectedTrigObj[i].pt() << "  eta: " << SelectedTrigObj[i].eta() << " phi: " << SelectedTrigObj[i].phi() << " pdgId: " <<  SelectedTrigObj[i].pdgId()  << endl;
       if(SelectedTrigObj[i].pt() > max_pt_Trig)
	 {
	   max_pt_Trig=SelectedTrigObj[i].pt();
	   FinalTrig=SelectedTrigObj[i];//Final Trigger Obj Selected
	 
	 }
       //std::cout<< " FinalTrig_pt: " << FinalTrig.pt()  <<std::endl;
       
     }


   
   
   ////////////////////////////////////////////////////////////////Muon Selection/////////////////////////////
   
   


   bool Loose=0;
   const reco::Vertex& pv=*Vertex->begin();
   Point p;
   p=pv.position();
   int MuonCount=0;
   int iMuon_Id=0;
   double reliso=0;
   
   for(pat::MuonCollection::const_iterator iMuon = Muons->begin() ; iMuon !=Muons->end();++iMuon,++iMuon_Id)
     {
       Loose=muon::isLooseMuon(*iMuon);
       reco::MuonPFIsolation iso = iMuon->pfIsolationR04();
       reliso = (iso.sumChargedHadronPt+TMath::Max(0.,iso.sumNeutralHadronEt+iso.sumPhotonEt-0.5*iso.sumPUPt))/iMuon->pt();
       if(Loose && (fabs(iMuon->eta()) < 2.4) && (fabs(iMuon->innerTrack()->dxy(p)) < 0.2) && fabs(iMuon->innerTrack()->dz(p)) < 0.5 && ((iMuon->pt())>3) && reliso < 0.25 )
	 { 
	   ++MuonCount;
	   SelectedMuons.push_back(*iMuon);
	 }
       
       
     }
   
   if (SelectedMuons.size()>= 2 && SelectedTrigObj.size()>0 )
     {
       double max_pt_Muon=0;
       pat::Muon MaxMuon;
       pat::Muon SecondMuon;
       pat::Muon TempMuon;
       int CountSecondMuon=0;
       
       
       for(unsigned i=0;i<SelectedMuons.size();i++)
	 
	 {
	   //cout<< " Muon: " <<  i  << " Pt: " << SelectedMuons[i].pt() << "  eta: " << SelectedMuons[i].eta() << " phi: " << SelectedMuons[i].phi() << " pdgId: " <<  SelectedMuons[i].pdgId()  << endl;
	   if(SelectedMuons[i].pt()>max_pt_Muon)
	     {
	       max_pt_Muon=SelectedMuons[i].pt();
	       MaxMuon=SelectedMuons[i];
	     }
	   
	   //std::cout<< " FinalMuonPt: " << MaxMuon.pt()<<endl;;
	   
	 }
       /* dR_Mu_Trig=reco::deltaR(MaxMuon.eta(),MaxMuon.phi(),FinalTrig.eta(),FinalTrig.phi());
       //std::cout<< " DeltaR: " <<dR_Mu_Trig<<std::endl;
       if((dR_Mu_Trig < dR_Trig_Cut) && (MaxMuon.pt() > Mu1_Pt_Cut))  
	 {
	   Leadingmu->push_back(MaxMuon);
	   
	 }
       */
       for(unsigned i=0;i<SelectedMuons.size();i++)

	 {
	   bool PtCondMet=false;
	   bool SignCondMet=false;
	   bool dRCondMet=false;
	   dR_Mu1_Mu2=reco::deltaR(MaxMuon.eta(),MaxMuon.phi(),SelectedMuons[i].eta(),SelectedMuons[i].phi());
	   PtCondMet =((SelectedMuons[i].pt() < MaxMuon.pt()) && (SelectedMuons[i].pt() > Mu2_Pt_Cut) && (MaxMuon.pt()>Mu1_Pt_Cut));
	   SignCondMet = (SelectedMuons[i].pdgId()==(-1)*MaxMuon.pdgId());
	   dRCondMet = (dR_Mu1_Mu2 < dR_Mu1_Mu2_Cut);
	   
	   if(PtCondMet && SignCondMet && dRCondMet)
	     {
	       ++CountSecondMuon;
	       if(CountSecondMuon==1)
		 {
		   SecondMuon=SelectedMuons[i];
		   continue;
		 }
	       TempMuon=SelectedMuons[i];
	       if(TempMuon.pt() > SecondMuon.pt())
		 {
		   SecondMuon=TempMuon;
		   
		 }
	     }
	 }
       
       if(CountSecondMuon==0)
	 {
	   return 0; 
	 }
       
       //std::cout<< " SecondMuonPt: " <<SecondMuon.pt()<<endl;
       //bool Both=false;
       dR_Mu_Trig=reco::deltaR(MaxMuon.eta(),MaxMuon.phi(),FinalTrig.eta(),FinalTrig.phi());
       InvMass_Mu1Mu2=abs((MaxMuon.p4()+SecondMuon.p4()).mass());
       //std::cout<< " DeltaR: " <<dR_Mu_Trig<<std::endl;
       if((dR_Mu_Trig < dR_Trig_Cut) && (MaxMuon.pt() > Mu1_Pt_Cut) && (InvMass_Mu1Mu2 < InvMass_Cut))  
	 {
	   //std::vector<pat::Muon>::iterator MaxIt;
	   //MaxIt=std::find(MaxCheck.begin(),MaxCheck.end(),);
	   //if (MaxIt==MaxCheck.end())
	   //{
	       
	       Leadingmu->push_back(MaxMuon);
	       Trailingmu->push_back(SecondMuon);
	       //std::cout<<"poopali!!"<<std::endl; 
	       //MaxCheck.push_back(MaxMuon);
	       
	       //}
	 }
       
       
     }
   /*   for(pat::ElectronCollection::const_iterator iele = electrons->begin() ; iele !=electrons->end() ; ++iele)
     {
       CheckElectrons.push_back(*iele);
     }
     
       for(pat::TauCollection::const_iterator itau = Taus->begin() ; itau !=Taus->end() ; ++itau)

	 {
	   CheckTaus.push_back(*itau);
	 }
   */  
   bool Both=false;
   
   Both=(((Leadingmu->size() > 0)) && ((Trailingmu->size()) > 0)  /*&&  ((CheckElectrons.size()) > 0) && ((CheckTaus.size()) > 0)*/ );
   //cout<<" Number of Leading Muons: " << Leadingmu->size() <<endl;
   //cout<<" Number of Trailng Muons: " << Trailingmu->size() <<endl;
   //cout<<" Events Passing Trigger "<<Trigcount<<endl;
   iEvent.put(move(Leadingmu), "LeadingMuon");
   iEvent.put(move(Trailingmu), "TrailingMuon");
   if(Both) 
     return true;
   else
     return false;
   
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
DiMuonFilter::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
DiMuonFilter::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
DiMuonFilter::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
DiMuonFilter::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
DiMuonFilter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
DiMuonFilter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DiMuonFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonFilter);
