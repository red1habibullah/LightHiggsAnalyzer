import FWCore.ParameterSet.Config as cms

process = cms.Process("Redo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('Redo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit = cms.untracked.int32(-1)
    )

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                            # replace 'myfile.root' with the source file you want to use
                            fileNames = cms.untracked.vstring(#'file:/afs/cern.ch/work/r/rhabibul/Prospectus/mA_11_filtered.root'
                                                              'file:/uscms_data/d3/rhabibul/BoostedDiTau2017_v3/CMSSW_9_4_13/src/LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/test/mumutautau_numEvent10000.root'
                                                              )
                            )

process.demo = cms.EDFilter("GenModeFilter",
                              #electrons = cms.InputTag("Loose","MiniLooseElectron","USER"),
                              #Taus=cms.InputTag("slimmedTausElectronCleaned"),
                              #vertex=cms.InputTag("offlineSlimmedPrimaryVertices"),
                              #BM = cms.InputTag("offlineBeamSpot"),
                              pruned  = cms.InputTag("prunedGenParticles"),
                              packed =cms.InputTag("packedGenParticles"),
                              
                                                            )


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('file:/uscms_data/d3/rhabibul/BoostedDiTau2017_v3/CMSSW_9_4_13/src/LightHiggsAnalyzer/MuMuTaueTauhadAnalyzer/test/mumutautau_test1.root')
                                   )


process.p = cms.Path(process.demo)

