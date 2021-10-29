# LightHiggsAnalyzer
The following is an independant UL version of the tau_mu-tau_had and tau_e-tau_had final state.It is written to be compatible with 120X.

# Setting up the environment:

```bash
$ setenv SCRAM_ARCH slc7_amd64_gcc900 

$ cmsrel CMSSW_12_0_0_pre4

$ cd CMSSW_12_0_0_pre4/src

$ cmsenv

$ git cms-init

$ git clone --recursive git@github.com:red1habibullah/LightHiggsAnalyzer.git -b LightHiggsAnalyzer_120X 

$ scram b clean

$ scram b -j8
```