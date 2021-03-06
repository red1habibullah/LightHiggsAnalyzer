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

'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_10.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_100.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_101.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_102.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_103.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_104.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_105.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_106.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_107.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_108.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_109.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_11.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_110.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_111.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_112.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_113.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_114.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_115.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_116.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_117.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_118.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_119.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_12.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_120.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_121.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_122.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_123.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_124.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_125.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_126.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_127.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_128.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_129.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_13.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_130.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_131.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_132.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_133.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_134.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_135.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_136.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_137.root',
'file:eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_138.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_139.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_14.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_15.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_16.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_17.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_18.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_19.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_2.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_20.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_21.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_22.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_23.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_24.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_25.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_26.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_27.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_28.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_29.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_3.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_30.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_31.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_32.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_33.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_34.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_35.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_36.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_37.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_38.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_39.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_4.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_40.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_41.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_42.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_43.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_44.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_45.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_46.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_47.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_48.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_49.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_5.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_50.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_51.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_52.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_53.root',
'file:eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_54.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_55.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_56.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_57.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_58.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_59.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_6.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_60.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_61.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_62.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_63.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_64.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_65.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_66.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_67.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_68.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_69.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_7.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_70.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_71.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_72.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_73.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_74.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_75.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_76.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_77.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_78.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_79.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_8.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_80.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_81.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_82.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_83.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_84.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_85.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_86.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_87.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_88.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_89.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_9.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_90.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_91.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_92.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_93.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_94.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_95.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_96.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_97.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_98.root',
'file:/eos/uscms/store/user/rhabibul/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/MiniAOD_DYJetsToLL_M50_Fall17DRPremix_v8/200220_200220/0000/mumutautau_BG_Final_zskim_99.root'


)
)






                            
process.JetFakeTau =cms.EDAnalyzer("JetFakeTauEfficiency",
                                   Taus=cms.InputTag("slimmedTaus"),
                                   jetSrc=cms.InputTag("ak4PFJets"),
                                   pruned  = cms.InputTag("prunedGenParticles"),
                                   )

process.JetFakeTauELoose =cms.EDAnalyzer("JetFakeTauEfficiency",
                                   Taus=cms.InputTag("slimmedTausElectronCleaned"),
                                   jetSrc=cms.InputTag("ak4PFJetsElectronCleaned"),
                                   pruned  = cms.InputTag("prunedGenParticles"),
                                   )

process.JetFakeTauEMedium =cms.EDAnalyzer("JetFakeTauEfficiency",
                                   Taus=cms.InputTag("slimmedTausElectronCleanedMedium"),
                                   jetSrc=cms.InputTag("ak4PFJetsElectronCleanedMedium"),
                                   pruned  = cms.InputTag("prunedGenParticles"),
                                   )

process.JetFakeTauETight =cms.EDAnalyzer("JetFakeTauEfficiency",
                                   Taus=cms.InputTag("slimmedTausElectronCleanedTight"),
                                   jetSrc=cms.InputTag("ak4PFJetsElectronCleanedTight"),
                                   pruned  = cms.InputTag("prunedGenParticles"),
                                   )


process.JetFakeTauMLoose =cms.EDAnalyzer("JetFakeTauEfficiency",
                                   Taus=cms.InputTag("slimmedTausMuonCleaned"),
                                   jetSrc=cms.InputTag("ak4PFJetsMuonCleaned"),
                                   pruned  = cms.InputTag("prunedGenParticles")
                                   )
                            
process.JetFakeTauMMedium =cms.EDAnalyzer("JetFakeTauEfficiency",
                                   Taus=cms.InputTag("slimmedTausMuonCleanedMedium"),
                                   jetSrc=cms.InputTag("ak4PFJetsMuonCleanedMedium"),
                                   pruned  = cms.InputTag("prunedGenParticles")
                                   )

process.JetFakeTauMTight =cms.EDAnalyzer("JetFakeTauEfficiency",
                                   Taus=cms.InputTag("slimmedTausMuonCleanedTight"),
                                   jetSrc=cms.InputTag("ak4PFJetsMuonCleanedTight"),
                                   pruned  = cms.InputTag("prunedGenParticles")
                                   )


process.JetGenFilter = cms.EDFilter("JetStudyGenFilter",
                                     pruned  = cms.InputTag("prunedGenParticles"),
                                     )





process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )




process.TFileService = cms.Service("TFileService",
                                   #fileName = cms.string('file:test_Validate_NumberCompare_MMatched_Ini.root')
                                   fileName = cms.string('file:JetFakeTau_AllID_Rebin.root')
                                   )














process.p =cms.Path(process.JetGenFilter*process.JetFakeTau*process.JetFakeTauELoose*process.JetFakeTauEMedium*process.JetFakeTauETight*process.JetFakeTauMLoose*process.JetFakeTauMMedium*process.JetFakeTauMTight)
