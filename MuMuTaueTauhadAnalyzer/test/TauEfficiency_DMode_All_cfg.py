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
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_1.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_10.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_11.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_12.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_13.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_14.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_15.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_16.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_17.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_18.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_19.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_2.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_20.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_21.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_22.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_23.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_3.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_4.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_5.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_6.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_7.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_8.root',
'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-5_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA05_DiMuDiTau_Fall17DRPremix_v6/200203_051006/0000/mumutautau_MultipleID_9.root',
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
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_1.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_10.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_11.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_12.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_13.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_2.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_3.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_4.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_5.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_6.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_7.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_8.root',
# 'file:/eos/uscms/store/user/rhabibul/SUSYGluGluToHToAA_AToMuMu_AToTauTau_M-125_M-20_TuneCUETP8M1_13TeV_madgraph_pythia8/MiniAOD_H125AA20_DiMuDiTau_Fall17DRPremix_v5/200203_073712/0000/mumutautau_MultipleID_9.root'



)
                            
                            )

process.TauEffDModeLoose =cms.EDAnalyzer("TauEfficiency",
                                    Taus=cms.InputTag("slimmedTaus"),
                                    pruned  = cms.InputTag("prunedGenParticles"),
                                    Ele = cms.InputTag("LooseFilter","MiniLooseElectron","complete"),
                                    jetSrc = cms.InputTag("ak4PFJets")


                                 )


                            

process.TauEffEDModeLoose =cms.EDAnalyzer("TauEfficiency",
                                     Taus=cms.InputTag("slimmedTausElectronCleaned"),
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     Ele= cms.InputTag("LooseFilter","MiniLooseElectron","complete"),
                                     jetSrc= cms.InputTag("ak4PFJetsElectronCleaned")

                                 )
process.TauEffDModeMedium =cms.EDAnalyzer("TauEfficiency",
                                    Taus=cms.InputTag("slimmedTaus"),
                                    pruned  = cms.InputTag("prunedGenParticles"),
                                    Ele = cms.InputTag("MediumFilter","MiniMediumElectron","complete"),
                                    jetSrc = cms.InputTag("ak4PFJets")


                                 )




process.TauEffEDModeMedium =cms.EDAnalyzer("TauEfficiency",
                                     Taus=cms.InputTag("slimmedTausElectronCleanedMedium"),
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     Ele= cms.InputTag("MediumFilter","MiniMediumElectron","complete"),
                                     jetSrc= cms.InputTag("ak4PFJetsElectronCleanedMedium")

                                 )
process.TauEffDModeTight =cms.EDAnalyzer("TauEfficiency",
                                    Taus=cms.InputTag("slimmedTaus"),
                                    pruned  = cms.InputTag("prunedGenParticles"),
                                    Ele = cms.InputTag("TightFilter","MiniTightElectron","complete"),
                                    jetSrc = cms.InputTag("ak4PFJets")


                                 )




process.TauEffEDModeTight =cms.EDAnalyzer("TauEfficiency",
                                     Taus=cms.InputTag("slimmedTausElectronCleanedTight"),
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     Ele= cms.InputTag("TightFilter","MiniTightElectron","complete"),
                                     jetSrc= cms.InputTag("ak4PFJetsElectronCleanedTight")

                                 )


process.GenModeFilter = cms.EDFilter("GenModeFilter",
                              
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     packed =cms.InputTag("packedGenParticles"),
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
process.MediumFilter = cms.EDFilter("ElectronFilterMedium",
                                   vertex = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                   Rho = cms.InputTag("fixedGridRhoFastjetAll"),
                                   electrons = cms.InputTag("slimmedElectrons"),
                                   conv = cms.InputTag("reducedConversions"),
                                   BM = cms.InputTag("offlineBeamSpot"),
                                   Tracks = cms.InputTag("electronGsfTracks"),
                             )

process.TightFilter = cms.EDFilter("ElectronFilterTight",
                                   vertex = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                   Rho = cms.InputTag("fixedGridRhoFastjetAll"),
                                   electrons = cms.InputTag("slimmedElectrons"),
                                   conv = cms.InputTag("reducedConversions"),
                                   BM = cms.InputTag("offlineBeamSpot"),
                                   Tracks = cms.InputTag("electronGsfTracks"),
                             )

process.EleEffLoose=cms.EDAnalyzer("ElectronEfficiency",
                                   pruned  = cms.InputTag("prunedGenParticles"),
                                   electronSrc =cms.InputTag("LooseFilter","MiniLooseElectron","complete"),
                                   FullelectronSrc =cms.InputTag("slimmedElectrons"),


)
process.EleEffMedium=cms.EDAnalyzer("ElectronEfficiency",
                                    pruned  = cms.InputTag("prunedGenParticles"),
                                    electronSrc =cms.InputTag("MediumFilter","MiniMediumElectron","complete"),
                                    FullelectronSrc =cms.InputTag("slimmedElectrons"),

                                    )

process.EleEffTight=cms.EDAnalyzer("ElectronEfficiency",
                                   pruned  = cms.InputTag("prunedGenParticles"),
                                   electronSrc =cms.InputTag("TightFilter","MiniTightElectron","complete"),
                                   FullelectronSrc =cms.InputTag("slimmedElectrons"),

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




process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )




process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string('file:test_Validate_NumberCompare_MMatched_Ini.root')
                                   fileName = cms.string('file:TauEfficiency_ElectronAllID_mA5_OldTauID.root')
                                   )
                                   




process.p_l = cms.Path(process.GenModeFilter*process.DiMuFilter*process.LooseFilter*process.EleEffLoose*process.TauEffDModeLoose*process.TauEffEDModeLoose)
process.p_m = cms.Path(process.GenModeFilter*process.DiMuFilter*process.MediumFilter*process.EleEffMedium*process.TauEffDModeMedium*process.TauEffEDModeMedium)
process.p_t = cms.Path(process.GenModeFilter*process.DiMuFilter*process.TightFilter*process.EleEffTight*process.TauEffDModeTight*process.TauEffEDModeTight)
process.schedule=cms.Schedule(process.p_l,process.p_m,process.p_t)
