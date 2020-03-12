# Import CMS python class definitions such as Process, Source, and EDProducer
import FWCore.ParameterSet.Config as cms
#this should be used finally

#Load the tools for cloning the sequences
import PhysicsTools.PatAlgos.tools.helpers as configtools
from PhysicsTools.PatAlgos.tools.helpers import cloneProcessingSnippet
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag

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
#'file:Muon_mA20_NewTauID.root'
#'file:Muon_mA5_NewTauID.root'
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




##################################################Modules for Tau_mu Efficiency######################################################
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




###############################################Modles for the 3rd Muon#########################

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


############################################Modules for Muon Efficiency########################################################
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



#############################Filter to get Gen level Tau_mu Tau_had################## 

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
############################################################## embed 2017v2 tauID into the miniAOD #################################################


############################ Load the Tau New ID Embedder###################
from LightHiggsAnalyzer.MuMuTaueTauhadAnalyzer.RerunTauIdMVA_slimmedTaus import *
IdEmbed = TauIDEmbedder(process, cms,
                        debug = True,
                        toKeep = ["2017v2"]
                        )
IdEmbed.runTauID()
#####################################################################################################
process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )






process.rerunTauIDSequence = cms.Sequence(process.rerunMvaIsolationSequence * process.slimmedTausNewID)

####################################### Clone and redo the process for all the other Tau collections###########################

process.rerunTauIDSequenceMuonCleaned=cloneProcessingSnippet(process,process.rerunTauIDSequence,'MuonCleaned', addToTask =False)
massSearchReplaceAnyInputTag(process.rerunTauIDSequenceMuonCleaned,cms.InputTag('slimmedTaus'),cms.InputTag('slimmedTausMuonCleaned'))

process.rerunTauIDSequenceMuonCleanedMedium=cloneProcessingSnippet(process,process.rerunTauIDSequence,'MuonCleanedMedium', addToTask =False)
massSearchReplaceAnyInputTag(process.rerunTauIDSequenceMuonCleanedMedium,cms.InputTag('slimmedTaus'),cms.InputTag('slimmedTausMuonCleanedMedium'))

process.rerunTauIDSequenceMuonCleanedTight=cloneProcessingSnippet(process,process.rerunTauIDSequence,'MuonCleanedTight', addToTask =False)
massSearchReplaceAnyInputTag(process.rerunTauIDSequenceMuonCleanedTight,cms.InputTag('slimmedTaus'),cms.InputTag('slimmedTausMuonCleanedTight'))

process.rerunTauIDSequenceElectronCleaned=cloneProcessingSnippet(process,process.rerunTauIDSequence,'ElectronCleaned', addToTask =False)
massSearchReplaceAnyInputTag(process.rerunTauIDSequenceElectronCleaned,cms.InputTag('slimmedTaus'),cms.InputTag('slimmedTausElectronCleaned'))

process.rerunTauIDSequenceElectronCleanedMedium=cloneProcessingSnippet(process,process.rerunTauIDSequence,'ElectronCleanedMedium', addToTask =False)
massSearchReplaceAnyInputTag(process.rerunTauIDSequenceElectronCleanedMedium,cms.InputTag('slimmedTaus'),cms.InputTag('slimmedTausElectronCleanedMedium'))


process.rerunTauIDSequenceElectronCleanedTight=cloneProcessingSnippet(process,process.rerunTauIDSequence,'ElectronCleanedTight', addToTask =False)
massSearchReplaceAnyInputTag(process.rerunTauIDSequenceElectronCleanedTight,cms.InputTag('slimmedTaus'),cms.InputTag('slimmedTausElectronCleanedTight'))
######################################################## MVA Isolation variable based Tau Efficiency Modules###########################################
################################### Muon Cleaned Versions #############################################################################################
process.TauEffMuVVLoose =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewIDMuonCleaned"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJetsMuonCleaned"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byVVLooseIsolationMVArun2017v2DBoldDMwLT2017"),

)
process.TauEffMuVLoose =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewIDMuonCleaned"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJetsMuonCleaned"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byVLooseIsolationMVArun2017v2DBoldDMwLT2017"),
)

process.TauEffMuLoose =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewIDMuonCleaned"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJetsMuonCleaned"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byLooseIsolationMVArun2017v2DBoldDMwLT2017"),

)

process.TauEffMuMedium =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewIDMuonCleaned"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJetsMuonCleaned"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byMediumIsolationMVArun2017v2DBoldDMwLT2017"),

)

process.TauEffMuTight =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewIDMuonCleaned"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJetsMuonCleaned"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byTightIsolationMVArun2017v2DBoldDMwLT2017"),

)

process.TauEffMuVTight =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewIDMuonCleaned"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJetsMuonCleaned"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byVTightIsolationMVArun2017v2DBoldDMwLT2017"),

)



process.TauEffMuVVTight =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewIDMuonCleaned"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJetsMuonCleaned"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byVVTightIsolationMVArun2017v2DBoldDMwLT2017"),

)
#############################################################UnCleaned versions #####################################################################
process.TauEffVVLoose =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewID"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJets"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byVVLooseIsolationMVArun2017v2DBoldDMwLT2017"),

)
process.TauEffVLoose =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewID"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJets"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byVLooseIsolationMVArun2017v2DBoldDMwLT2017"),

)
process.TauEffLoose =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewID"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJets"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byLooseIsolationMVArun2017v2DBoldDMwLT2017"),

)

process.TauEffMedium =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewID"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJets"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byMediumIsolationMVArun2017v2DBoldDMwLT2017"),

)

process.TauEffTight =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewID"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJets"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byTightIsolationMVArun2017v2DBoldDMwLT2017"),

)

process.TauEffVTight =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewID"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJets"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byVTightIsolationMVArun2017v2DBoldDMwLT2017"),


)

process.TauEffVVTight =cms.EDAnalyzer("TauEfficiencyMuMVA",
                                          Taus=cms.InputTag("slimmedTausNewID"),
                                          pruned  = cms.InputTag("prunedGenParticles"),
                                          muonSrc =cms.InputTag("ThirdMuFilter","ThirdMuon","complete"),
                                          jetSrc= cms.InputTag("ak4PFJets"),
                                          TauIdRawValue=cms.string("byIsolationMVArun2017v2DBoldDMwLTraw2017"),
                                          TauIdMVAWP=cms.string("byVVTightIsolationMVArun2017v2DBoldDMwLT2017"),

)










#######################################################################################################################################################
# process.out = cms.OutputModule("PoolOutputModule",
#     fileName = cms.untracked.string('Muon_mA5_NewTauID.root')

# )


####### Declare process to calculate the effciencies for the differentMVa discriminanants for both the Muon Cleaned and the UnCleaned Case#############
process.m=cms.Path(process.rerunTauIDSequence*process.rerunTauIDSequenceMuonCleaned*process.rerunTauIDSequenceMuonCleanedMedium*process.rerunTauIDSequenceMuonCleanedTight)
#process.e=cms.Path(process.rerunTauIDSequence*process.rerunTauIDSequenceElectronCleaned*process.rerunTauIDSequenceElectronCleanedMedium*process.rerunTauIDSequenceElectronCleanedTight)
process.effmu=cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilter*process.TauEffMuVVLoose*process.TauEffMuVLoose*process.TauEffMuLoose*process.TauEffMuMedium*process.TauEffMuTight*process.TauEffMuVTight*process.TauEffMuVVTight)
process.effu=cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilter*process.TauEffVVLoose*process.TauEffVLoose*process.TauEffLoose*process.TauEffMedium*process.TauEffTight*process.TauEffVTight*process.TauEffVVTight)

#process.ep=cms.EndPath(process.out)

process.TFileService = cms.Service("TFileService",
                                
                                   fileName = cms.string('file:TauEfficiencyMu_ma5_NewTauID.root')
                                   )




process.schedule=cms.Schedule(process.m,process.effu,process.effmu)
#process.schedule=cms.Schedule(process.effu) #,process.effmu)
#process.ep=cms.EndPath(process.out)



#process.p_l = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilter*process.MuEffLoose*process.TauEffDModeLoose*process.TauEffMDModeLoose);
# process.p_m = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilterMedium*process.MuEffMedium*process.TauEffDModeMedium*process.TauEffMDModeMedium);
# process.p_t = cms.Path(process.GenModeFilterMu*process.DiMuFilter*process.ThirdMuFilterTight*process.MuEffTight*process.TauEffDModeTight*process.TauEffMDModeTight);



# process.schedule=cms.Schedule(process.p_l,process.p_m,process.p_t)
#process.schedule=cms.Schedule(process.rerunTauIDPath)
