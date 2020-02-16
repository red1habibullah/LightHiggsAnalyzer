# Import CMS python class definitions such as Process, Source, and EDProducer
import FWCore.ParameterSet.Config as cms
#this should be used finally


# Set up a process, named RECO in this case
process = cms.Process("complete")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('complete')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
    )

#process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


#Include the number of events to run over
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))






process.ValidateTau= cms.EDAnalyzer("TauValidationAnalyzer",
                                    #Taus=cms.InputTag("slimmedTaus"),
                                    #Taus=cms.InputTag("selectedPatTausElectronCleaned"),
                                    Taus=cms.InputTag("slimmedTausElectronCleaned"),
                                    #Taus=cms.InputTag("slimmedTausMuonCleaned"),
                                    Muons1 = cms.InputTag("DiMuFilter","LeadingMuon","complete"),
                                    Muons2=cms.InputTag("DiMuFilter","TrailingMuon","complete"),
                                    Mu1TaudRCut=cms.double(0.4),
                                    Mu2TaudRCut=cms.double(0.4),
                                    
                                    )



process.CompareTauE= cms.EDAnalyzer("TauComparatorAnalyzer",
                                    Taus=cms.InputTag("slimmedTaus"),                                                                                                                                                                                                         
                                    #Taus=cms.InputTag("selectedPatTausElectronCleaned"),
                                    TausCleaned=cms.InputTag("slimmedTausElectronCleaned"),
                                    #TausCleaned=cms.InputTag("slimmedTausMuonCleaned"),
                                    Muons1 = cms.InputTag("DiMuFilter","LeadingMuon","complete"),
                                    Muons2=cms.InputTag("DiMuFilter","TrailingMuon","complete"),
                                    pruned  = cms.InputTag("prunedGenParticles"),
                                    #jetSrc = cms.InputTag("ak4PFJets"),
                                    jetSrc = cms.InputTag("ak4PFJets"),
                                    jetSrcCl = cms.InputTag("ak4PFJetsElectronCleaned"),

                                    Mu1TaudRCut=cms.double(0.4),
                                    Mu2TaudRCut=cms.double(0.4),
                                    Mu1TauCleaneddRCut=cms.double(0.4),
                                    Mu2TauCleaneddRCut=cms.double(0.4),
                                    TauTauCleaneddRCut=cms.double(0.03),
                                    )

process.CompareTauM= cms.EDAnalyzer("TauComparatorAnalyzer",
                                    Taus=cms.InputTag("slimmedTaus"),                                                                                                                                                                                                         
                                    #Taus=cms.InputTag("selectedPatTausElectronCleaned"),                                                                                                                                                                                      
                                    #Taus=cms.InputTag("slimmedTausElectronCleaned"),                                                                                                                                                                                          
                                    TausCleaned=cms.InputTag("slimmedTausMuonCleaned"),
                                    Muons1 = cms.InputTag("DiMuFilter","LeadingMuon","complete"),
                                    Muons2=cms.InputTag("DiMuFilter","TrailingMuon","complete"),
                                    pruned  = cms.InputTag("prunedGenParticles"),
                                    jetSrc = cms.InputTag("ak4PFJets"),
                                    jetSrcCl = cms.InputTag("ak4PFJetsMuonCleaned"),

                                    Mu1TaudRCut=cms.double(0.4),
                                    Mu2TaudRCut=cms.double(0.4),
                                    Mu1TauCleaneddRCut=cms.double(0.4),
                                    Mu2TauCleaneddRCut=cms.double(0.4),
                                    TauTauCleaneddRCut=cms.double(0.03),
                                    )



# Configure the object that reads the input file
process.source = cms.Source("PoolSource", 
                            #fileNames = cms.untracked.vstring('file:mumutautau_numEvent10000.root')
                            #fileNames = cms.untracked.vstring('file:mumutautau_new_numEvent500.root')
                            #fileNames = cms.untracked.vstring('file:mumutautau_new_tag_numEvent500.root')
                            #fileNames = cms.untracked.vstring('file:mumutautau_new_PF_numEvent500.root')
                            #fileNames = cms.untracked.vstring('file:mumutautau_new_Slimmed_numEvent5000.root')
                            #fileNames = cms.untracked.vstring('file:mumutautau_new_MuonSlimmed_numEvent5000.root')  
                            #fileNames = cms.untracked.vstring('file:mumutautau_NoCleanIso_numEvent5000.root')
                            #fileNames = cms.untracked.vstring('file:mumutautau_LowBoost_numEvent5000.root')   
                            fileNames = cms.untracked.vstring('file:mumutautau_NewCollectionTest_numEvent5000.root')
                            
                            )


process.GenModeFilter = cms.EDFilter("GenModeFilter",
                              
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     packed =cms.InputTag("packedGenParticles"),
)


process.GenModeFilterMu = cms.EDFilter("GenModeFilterMu",

                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     packed =cms.InputTag("packedGenParticles"),
)




                                     
# Configure an object that produces a new data object

process.DiMuFilter= cms.EDFilter("DiMuonFilter",  
                                 vertex=cms.InputTag("offlineSlimmedPrimaryVertices"), 
                                 muonSrc =cms.InputTag("slimmedMuons"),
                                 bits = cms.InputTag("TriggerResults","","HLT"),
                                 #prescales = cms.InputTag("patTrigger"),
                                 #objects = cms.InputTag("selectedPatTrigger"),
                                 objects = cms.InputTag("slimmedPatTrigger"),
                                 trigNames = cms.vstring("HLT_IsoMu27_v","HLT_IsoTkMu27_v","HLT_IsoMu24_v","HLT_IsoTkMu24_v"),
                                 #electrons = cms.InputTag("High","CutElectron","complete"),
                                 #Taus=cms.InputTag("High","CutTaus","complete")

                              )






process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )




process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string('file:test_Validate_NumberCompare_MMatched_Ini.root')
                                   fileName = cms.string('file:test_JetMatched_NewColl.root')
                                   )




process.p = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.CompareTauM)
#process.p = cms.Path(process.GenModeFilter*process.DiMuFilter*process.CompareTauE)
