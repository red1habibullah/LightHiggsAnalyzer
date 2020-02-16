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
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000))






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
                            fileNames = cms.untracked.vstring('file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_1.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_2.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_3.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_4.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_5.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_6.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_7.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_8.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_9.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_10.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_11.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v1/191028_182143/0000/mumutautau_FinaltesOBt_12.root'
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_5.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_6.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_7.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_8.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_9.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_10.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_11.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_12.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v1/191028_184245/0000/mumutautau_FinaltesOBt_13.root'
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-9_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA09_DiMuDiTau_Fall17DRPremix_v1/191029_022923/0000/mumutautau_FinaltesOBt_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-9_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA09_DiMuDiTau_Fall17DRPremix_v1/191029_022923/0000/mumutautau_FinaltesOBt_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-9_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA09_DiMuDiTau_Fall17DRPremix_v1/191029_022923/0000/mumutautau_FinaltesOBt_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-9_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA09_DiMuDiTau_Fall17DRPremix_v1/191029_022923/0000/mumutautau_FinaltesOBt_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-9_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA09_DiMuDiTau_Fall17DRPremix_v1/191029_022923/0000/mumutautau_FinaltesOBt_5.root'
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v1/191029_023655/0000/mumutautau_FinaltesOBt_1.root',                                                      
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v1/191029_023655/0000/mumutautau_FinaltesOBt_2.root',                                                      
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v1/191029_023655/0000/mumutautau_FinaltesOBt_3.root',                                                      
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v1/191029_023655/0000/mumutautau_FinaltesOBt_4.root',                                                      
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v1/191029_023655/0000/mumutautau_FinaltesOBt_5.root',                                                      
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v1/191029_023655/0000/mumutautau_FinaltesOBt_6.root',                                                      
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v1/191029_023655/0000/mumutautau_FinaltesOBt_7.root',                                                      
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v1/191029_023655/0000/mumutautau_FinaltesOBt_8.root',                                                      
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v1/191029_023655/0000/mumutautau_FinaltesOBt_9.root',                                                      
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v1/191029_023655/0000/mumutautau_FinaltesOBt_10root'   
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_5.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_6.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_7.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_8.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_9.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_10.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v1/191029_023908/0000/mumutautau_FinaltesOBt_11.root'


)
                            
                            )

process.TauEffDMode =cms.EDAnalyzer("TauEfficiency",
                                    Taus=cms.InputTag("slimmedTaus"),
                                    pruned  = cms.InputTag("prunedGenParticles"),
                                    Ele = cms.InputTag("LooseFilter","MiniLooseElectron","complete")


                                 )


                            

process.TauEffEDMode =cms.EDAnalyzer("TauEfficiency",
                                     Taus=cms.InputTag("slimmedTausElectronCleaned"),
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     Ele= cms.InputTag("LooseFilter","MiniLooseElectron","complete")


                                 )


process.GenModeFilter = cms.EDFilter("GenModeFilter",
                              
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     packed =cms.InputTag("packedGenParticles"),
                                     )



process.GenModeFilterMu = cms.EDFilter("GenModeFilterMu",

                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     packed =cms.InputTag("packedGenParticles"),
)




process.PrimaryMuonAnalyzer=cms.EDAnalyzer("PrimaryMuonAnalyzer",
                               muonSrc =cms.InputTag("slimmedMuons"),
                                                            )
process.dRCutAnalyzer=cms.EDAnalyzer("dRAnalyzer",
                                     Cutelectrons = cms.InputTag("Cutter","TestElectron","complete"),
                                     CutTaus=cms.InputTag("Cutter","TestTau","complete")
                                     
                               
                                                            )
                                     
                                     
# Configure an object that produces a new data object
process.LooseFilter = cms.EDFilter("ElectronFilter",
                                   vertex = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                   Rho = cms.InputTag("fixedGridRhoFastjetAll"),
                                   electrons = cms.InputTag("slimmedElectrons"),
                                   conv = cms.InputTag("reducedConversions"),
                                   BM = cms.InputTag("offlineBeamSpot"),
                                   Tracks = cms.InputTag("electronGsfTracks"),
                             )
process.ElectronAnalyzer = cms.EDAnalyzer("MiniLooseAnalyzer",
                                          electrons = cms.InputTag("LooseFilter","MiniLooseElectron","complete"),
                                          Rho = cms.InputTag("fixedGridRhoFastjetAll"),
                                          #pruned  = cms.InputTag("prunedGenParticles"),
                                          #packed =cms.InputTag("packedGenParticles"),
                                          
)
process.PrimaryElectronAnalyzer = cms.EDAnalyzer("PrimaryElectronAnalyzer",
                                                 electrons = cms.InputTag("slimmedElectrons"),
                                                 pruned  = cms.InputTag("prunedGenParticles"),
                                                 packed =cms.InputTag("packedGenParticles"),


)




process.PairFilter = cms.EDFilter("TauEleFilter",
                                  electrons = cms.InputTag("LooseFilter","MiniLooseElectron","complete"),
                                  #Taus=cms.InputTag("selectedPatTausElectronCleaned"),
                                  Taus=cms.InputTag("selectedPatTausMuonCleaned"),
                                  #Taus=cms.InputTag("slimmedTaus"),
                                  vertex=cms.InputTag("offlineSlimmedPrimaryVertices"),
                                  BM = cms.InputTag("offlineBeamSpot"),
                                  particleSrc  = cms.InputTag("prunedGenParticles"),


                              )
process.PairAnalyzer = cms.EDAnalyzer("PostPrimarySelectionAnalyzer",
                                      electrons = cms.InputTag("PairFilter","PassedElectron","complete"), 
                                      Taus=cms.InputTag("PairFilter","PassedTau","complete"),
                                      Cutelectrons = cms.InputTag("PairFilter","CutElectron","complete"),
                                      CutTaus=cms.InputTag("PairFilter","CutTaus","complete"),
                                      pruned  = cms.InputTag("prunedGenParticles"),
                                      packed =cms.InputTag("packedGenParticles"),

                                 )
process.Cutter=cms.EDFilter("DeltaRCut",
                            electrons = cms.InputTag("PairFilter","PassedElectron","complete"),
                            Taus=cms.InputTag("PairFilter","PassedTau","complete"),
                            
                            )
process.PrimaryTauAnalyzer=cms.EDAnalyzer("PrimaryTauAnalyzer",
                                          Taus=cms.InputTag("selectedPatTausElectronCleaned"),
                                          #Taus=cms.InputTag("slimmedTaus"),
                                          vertex=cms.InputTag("offlineSlimmedPrimaryVertices"),
                                          
                                          )
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


process.DiMuAnalyzer = cms.EDAnalyzer("DiMuonAnalyzer",
                                     Muons1 = cms.InputTag("DiMuFilter","LeadingMuon","complete"),
                                     Muons2=cms.InputTag("DiMuFilter","TrailingMuon","complete"),
                                     #electrons = cms.InputTag("High","CutElectron","complete"),
                                     #Taus=cms.InputTag("High","CutTaus","complete"),
                                     
                                     #Taus=cms.InputTag("slimmedTaus"),                                                                                                                                                                                                            
                                 )

process.CrossCleanFilter=cms.EDFilter("CrossCleaner",
                               electrons = cms.InputTag("Cutter","TestElectron","complete"),
                               Taus=cms.InputTag("Cutter","TestTau","complete"),
                               Muons1 = cms.InputTag("DiMuFilter","LeadingMuon","complete"),
                               Muons2=cms.InputTag("DiMuFilter","TrailingMuon","complete"),
                               Mu1TaudRCut=cms.double(0.8),
                               Mu2TaudRCut=cms.double(0.8),
                               Mu1EledRCut=cms.double(0.4),
                               Mu2EledRCut=cms.double(0.4)


                                )
process.FinalAnalyzer = cms.EDAnalyzer("MuMuTaueTauhadAnalyzer",
                                       electrons = cms.InputTag("PairFilter","PassedElectron","complete"),
                                       Taus=cms.InputTag("PairFilter","PassedTau","complete"),
                                       Cutelectrons = cms.InputTag("PairFilter","ReuseElectron","complete"),
                                       CutTaus=cms.InputTag("PairFilter","ReuseTaus","complete"),
                                       Tau_mass_select =cms.InputTag("CrossCleanFilter","CrossCleanedHighMassTaus","complete"),
                                       Ele_mass_select=cms.InputTag("CrossCleanFilter","CrossCleanedHighMassElectron","complete"),
                                       Tau_pt_select =cms.InputTag("CrossCleanFilter","CrossCleanedHighPtTaus","complete"),
                                       Ele_pt_select =cms.InputTag("CrossCleanFilter","CrossCleanedHighPtElectron","complete"),
                                       Ele_dR_select=cms.InputTag("CrossCleanFilter","CrossCleaneddRElectron","complete"),
                                       Tau_dR_select=cms.InputTag("CrossCleanFilter","CrossCleaneddRTaus","complete"),
                                       Muons1 = cms.InputTag("CrossCleanFilter","CrossCleanedLeadingMuon","complete"),
                                       Muons2=cms.InputTag("CrossCleanFilter","CrossCleanedTrailingMuon","complete"),
                                       pruned  = cms.InputTag("prunedGenParticles"),
                                       packed =cms.InputTag("packedGenParticles")


                                #packed=cms.InputTag("demo","TaueleGenParticle","Demo"),
                                 )

process.ThirdMuon = cms.EDProducer("ThirdMuonSelector",
                                   muonSrc =cms.InputTag("slimmedMuons"),
                                   Muons1 = cms.InputTag("DiMuFilter","LeadingMuon","complete"),
                                   Muons2=cms.InputTag("DiMuFilter","TrailingMuon","complete")
                                   
                                   
)



process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )




process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string('file:test_Validate_NumberCompare_MMatched_Ini.root')
                                   fileName = cms.string('file:teset_thirdMuon.root')
                                   )



# Configure a path and endpath to run the producer and output modules
#process.p = cms.Path(process.Loose*process.PairFilter*process.Primary*process.DiMuon*process.DiMuAnalyze*process.CrossClean*process.Analyze)
#process.p = cms.Path(process.GenModeFilter*process.PrimaryMuonAnalyzer*process.DiMuFilter*process.DiMuAnalyzer*process.PrimaryElectronAnalyzer*process.LooseFilter*process.ElectronAnalyzer*process.PrimaryTauAnalyzer*process.PairFilter*process.PairAnalyzer*process.Cutter*process.dRCutAnalyzer*process.CrossCleanFilter*process.FinalAnalyzer)

#process.p = cms.Path(process.GenModeFilter*process.PrimaryMuonAnalyzer*process.DiMuFilter*process.DiMuAnalyzer*process.PrimaryElectronAnalyzer*process.LooseFilter*process.ElectronAnalyzer*process.PrimaryTauAnalyzer*process.PairFilter*process.PairAnalyzer*process.Cutter*process.dRCutAnalyzer*process.CrossCleanFilter*process.FinalAnalyzer)
#process.p = cms.Path(process.GenModeFilter*process.PrimaryTauAnalyzer)                                                                                                                                                                                                        
#process.p = cms.Path(process.DiMuFilter*process.ValidateTau)
#process.p = cms.Path(process.DiMuFilter*process.CompareTau)
#process.p = cms.Path(process.DiMuFilter*process.CompareTauE*process.CompareTauM)
#process.p = cms.Path(process.GenModeFilter*process.DiMuFilter*process.CompareTauE)
#process.p = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.CompareTauM)
#process.p = cms.Path(process.GenModeFilterMu*process.TauEff)
#process.p = cms.Path(process.GenModeFilter*process.LooseFilter*process.TauEffDMode*process.TauEffEDMode)
process.p= cms.Path(process.DiMuFilter*process.ThirdMuon)
