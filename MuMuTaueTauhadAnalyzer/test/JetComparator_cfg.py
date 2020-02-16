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




process.CompareJet=cms.EDAnalyzer("JetAnalyzer",
                                  jetSrc = cms.InputTag("ak4PFJets"),
                                  )
process.CompareJetECleaned=cms.EDAnalyzer("JetAnalyzer",
                                  jetSrc = cms.InputTag("ak4PFJetsElectronCleaned"),
                                  )
process.CompareJetMCleaned=cms.EDAnalyzer("JetAnalyzer",
                                  jetSrc = cms.InputTag("ak4PFJetsMuonCleaned"),
                                  )





# Configure the object that reads the input file
process.source = cms.Source("PoolSource", 

                            fileNames = cms.untracked.vstring('file:mumutautau_new_AddJets_numEvent5000.root')  
                            )




process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )




process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('file:test_JetCompare.root')
                                   )



# Configure a path and endpath to run the producer and output modules

process.p =cms.Path(process.CompareJet*process.CompareJetECleaned*process.CompareJetMCleaned)
