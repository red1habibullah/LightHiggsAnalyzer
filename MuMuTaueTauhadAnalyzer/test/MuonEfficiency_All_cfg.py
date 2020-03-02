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








# Configure the object that reads the input file
process.source = cms.Source("PoolSource", 
                            fileNames = cms.untracked.vstring(
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_10.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_11.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_12.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_13.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_14.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_15.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_16.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_17.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_18.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_19.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_20.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_21.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_22.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_23.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_5.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_6.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_7.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_8.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_9.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_10.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_11.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_5.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_6.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_7.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_8.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-7_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA07_DiMuDiTau_Fall17DRPremix_v1/200209_083259/0000/mumutautau_MultipleID_9.root'
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_11.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_12.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_13.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_14.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_15.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_16.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_18.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_5.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_6.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_7.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_8.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-4_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA04_DiMuDiTau_Fall17DRPremix_v8/200212_153846/0000/mumutautau_MultipleID_9.root'
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-9_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA09_DiMuDiTau_Fall17DRPremix_v5/200203_064350/0000/mumutautau_MultipleID_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-9_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA09_DiMuDiTau_Fall17DRPremix_v5/200203_064350/0000/mumutautau_MultipleID_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-9_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA09_DiMuDiTau_Fall17DRPremix_v5/200203_064350/0000/mumutautau_MultipleID_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-9_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA09_DiMuDiTau_Fall17DRPremix_v5/200203_064350/0000/mumutautau_MultipleID_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-9_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA09_DiMuDiTau_Fall17DRPremix_v5/200203_064350/0000/mumutautau_MultipleID_5.root'
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-12_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA12_DiMuDiTau_Fall17DRPremix_v2/200212_215740/0000/mumutautau_MultipleID_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-12_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA12_DiMuDiTau_Fall17DRPremix_v2/200212_215740/0000/mumutautau_MultipleID_10.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-12_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA12_DiMuDiTau_Fall17DRPremix_v2/200212_215740/0000/mumutautau_MultipleID_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-12_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA12_DiMuDiTau_Fall17DRPremix_v2/200212_215740/0000/mumutautau_MultipleID_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-12_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA12_DiMuDiTau_Fall17DRPremix_v2/200212_215740/0000/mumutautau_MultipleID_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-12_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA12_DiMuDiTau_Fall17DRPremix_v2/200212_215740/0000/mumutautau_MultipleID_5.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-12_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA12_DiMuDiTau_Fall17DRPremix_v2/200212_215740/0000/mumutautau_MultipleID_6.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-12_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA12_DiMuDiTau_Fall17DRPremix_v2/200212_215740/0000/mumutautau_MultipleID_7.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-12_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA12_DiMuDiTau_Fall17DRPremix_v2/200212_215740/0000/mumutautau_MultipleID_8.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-12_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA12_DiMuDiTau_Fall17DRPremix_v2/200212_215740/0000/mumutautau_MultipleID_9.root'
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v15/200212_220609/0000/mumutautau_MultipleID_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v15/200212_220609/0000/mumutautau_MultipleID_10.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v15/200212_220609/0000/mumutautau_MultipleID_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v15/200212_220609/0000/mumutautau_MultipleID_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v15/200212_220609/0000/mumutautau_MultipleID_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v15/200212_220609/0000/mumutautau_MultipleID_5.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v15/200212_220609/0000/mumutautau_MultipleID_6.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v15/200212_220609/0000/mumutautau_MultipleID_7.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v15/200212_220609/0000/mumutautau_MultipleID_8.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-13_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA13_DiMuDiTau_Fall17DRPremix_v15/200212_220609/0000/mumutautau_MultipleID_9.root'
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_10.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_11.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_5.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_6.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_7.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_8.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-16_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA16_DiMuDiTau_Fall17DRPremix_v5/200203_070307/0000/mumutautau_MultipleID_9.root'
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_10.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_11.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_12.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_5.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_6.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_7.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_8.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-19_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA19_DiMuDiTau_Fall17DRPremix_v4/200203_072651/0000/mumutautau_MultipleID_9.root'
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_1.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_10.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_11.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_12.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_13.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_2.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_3.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_4.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_5.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_6.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_7.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_8.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_9.root'



)
                            
                            )




process.MuonLoose=cms.EDAnalyzer("TauIDTester",
                                 Taus=cms.InputTag("slimmedTausMuonCleaned"),
                                 ObjectID=cms.InputTag("ak4PFJetsMuonCleaned","MuonsPassingID"),
                                 ObjectRemoved=cms.InputTag("ak4PFJetsMuonCleaned","MuonsRemoved"),
                                 JetCleaned=cms.InputTag("ak4PFJetsMuonCleaned","NumJetsMuonsCleaned"),
)

process.MuonMedium=cms.EDAnalyzer("TauIDTester",
                                 Taus=cms.InputTag("slimmedTausMuonCleanedMedium"),
                                 ObjectID=cms.InputTag("ak4PFJetsMuonCleanedMedium","MuonsPassingID"),
                                 ObjectRemoved=cms.InputTag("ak4PFJetsMuonCleanedMedium","MuonsRemoved"),
                                 JetCleaned=cms.InputTag("ak4PFJetsMuonCleanedMedium","NumJetsMuonsCleaned"),
)
process.MuonTight=cms.EDAnalyzer("TauIDTester",
                                 Taus=cms.InputTag("slimmedTausMuonCleanedTight"),
                                 ObjectID=cms.InputTag("ak4PFJetsMuonCleanedTight","MuonsPassingID"),
                                 ObjectRemoved=cms.InputTag("ak4PFJetsMuonCleanedTight","MuonsRemoved"),
                                 JetCleaned=cms.InputTag("ak4PFJetsMuonCleanedTight","NumJetsMuonsCleaned"),
)
########################################################################################################
process.TauEffDModeLoose =cms.EDAnalyzer("TauEfficiencyMu",
                                    Taus=cms.InputTag("slimmedTaus"),
                                    pruned  = cms.InputTag("prunedGenParticles"),
                                    muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                    jetSrc = cms.InputTag("ak4PFJets")


                                 )
process.TauEffDModeMedium =cms.EDAnalyzer("TauEfficiencyMu",
                                    Taus=cms.InputTag("slimmedTaus"),
                                    pruned  = cms.InputTag("prunedGenParticles"),
                                    muonSrc =cms.InputTag("ThirdMuFilterMedium","ThirdMuon","complete"),
                                    jetSrc = cms.InputTag("ak4PFJets")


                                 )


process.TauEffDModeTight =cms.EDAnalyzer("TauEfficiencyMu",
                                    Taus=cms.InputTag("slimmedTaus"),
                                    pruned  = cms.InputTag("prunedGenParticles"),
                                    muonSrc =cms.InputTag("ThirdMuFilterTight","ThirdMuon","complete"),
                                    jetSrc = cms.InputTag("ak4PFJets")


                                 )


                            

process.TauEffMDModeLoose =cms.EDAnalyzer("TauEfficiencyMu",
                                     Taus=cms.InputTag("slimmedTausMuonCleaned"),
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                     jetSrc= cms.InputTag("ak4PFJetsMuonCleaned")
                                     

                                 )





process.TauEffMDModeMedium =cms.EDAnalyzer("TauEfficiencyMu",
                                     Taus=cms.InputTag("slimmedTausMuonCleanedMedium"),
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     muonSrc =cms.InputTag("ThirdMuFilterMedium","ThirdMuon","complete"),
                                     jetSrc= cms.InputTag("ak4PFJetsMuonCleanedMedium")


                                 )
process.TauEffMDModeTight =cms.EDAnalyzer("TauEfficiencyMu",
                                     Taus=cms.InputTag("slimmedTausMuonCleanedTight"),
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     muonSrc =cms.InputTag("ThirdMuFilterTight","ThirdMuon","complete"),
                                     jetSrc= cms.InputTag("ak4PFJetsMuonCleanedTight")


                                 )






process.ThirdMu = cms.EDProducer("ThirdMuonSelector",
                                   muonSrc =cms.InputTag("slimmedMuons"),
                                   Muons1 = cms.InputTag("DiMuFilter","LeadingMuon","complete"),
                                   Muons2=cms.InputTag("DiMuFilter","TrailingMuon","complete")

)

process.ThirdMuFilter = cms.EDFilter("ThirdMuonFilter",
                                   muonSrc =cms.InputTag("slimmedMuons"),
                                   Muons1 = cms.InputTag("DiMuFilter","LeadingMuon","complete"),
                                   Muons2=cms.InputTag("DiMuFilter","TrailingMuon","complete")

)
process.ThirdMuFilterMedium = cms.EDFilter("ThirdMuonFilterMedium",
                                   muonSrc =cms.InputTag("slimmedMuons"),
                                   Muons1 = cms.InputTag("DiMuFilter","LeadingMuon","complete"),
                                   Muons2=cms.InputTag("DiMuFilter","TrailingMuon","complete")

)

process.ThirdMuFilterTight = cms.EDFilter("ThirdMuonFilterTight",
                                   muonSrc =cms.InputTag("slimmedMuons"),
                                   Muons1 = cms.InputTag("DiMuFilter","LeadingMuon","complete"),
                                   Muons2=cms.InputTag("DiMuFilter","TrailingMuon","complete")

)








process.GenModeFilterMu = cms.EDFilter("GenModeFilterMu",

                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     packed =cms.InputTag("packedGenParticles"),
)





process.DiMuFilter= cms.EDFilter("DiMuonFilter",  
                                 vertex=cms.InputTag("offlineSlimmedPrimaryVertices"), 
                                 muonSrc =cms.InputTag("slimmedMuons"),
                                 bits = cms.InputTag("TriggerResults","","HLT"),
                                 objects = cms.InputTag("slimmedPatTrigger"),
                                 trigNames = cms.vstring("HLT_IsoMu27_v","HLT_IsoTkMu27_v","HLT_IsoMu24_v","HLT_IsoTkMu24_v"),
                                 
                              )
#################################################################################################
process.MuEffLoose=cms.EDAnalyzer("MuonEfficiency",
                           pruned  = cms.InputTag("prunedGenParticles"),
                           muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
)
process.MuEffMedium=cms.EDAnalyzer("MuonEfficiency",
                           pruned  = cms.InputTag("prunedGenParticles"),
                           muonSrc =cms.InputTag("ThirdMuFilterMedium","ThirdMuon","complete"),
)

process.MuEffTight=cms.EDAnalyzer("MuonEfficiency",
                           pruned  = cms.InputTag("prunedGenParticles"),
                           muonSrc =cms.InputTag("ThirdMuFilterTight","ThirdMuon","complete"),
)









#################################################################################################

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )




process.TFileService = cms.Service("TFileService",
                                
                                   fileName = cms.string('file:MuonEfficiency_mA20.root')
                                   )




# process.p_l = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilter*process.TauEffDModeLoose*process.TauEffMDModeLoose);
# process.p_m = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilterMedium*process.TauEffDModeMedium*process.TauEffMDModeMedium);
# process.p_t = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilterTight*process.TauEffDModeTight*process.TauEffMDModeTight);
# process.schedule=cms.Schedule(process.p_l,process.p_m,process.p_t)


process.p_l = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilter*process.MuEffLoose);
process.p_m = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilterMedium*process.MuEffMedium);
process.p_t = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilterTight*process.MuEffTight);
process.schedule=cms.Schedule(process.p_l,process.p_m,process.p_t)
