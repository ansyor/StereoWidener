#ifndef STEREOWIDENER_H
#define STEREOWIDENER_H

#include "RBJFilter.h"
#include "KuassaUtilities.h"

namespace STRWDNR{
	enum t
{
    kOnOff = 0,
	
    kFreqLow,
    kFreqMid,
    kFreqHigh,
    
    kWidthLowpass,
    kWidthLow,
    kWidthHigh,
    kWidthHighpass,
    
    kGainLowpass,
    kGainLow,
    kGainHigh,
    kGainHighpass,
    
    kSoloLowpass,
    kSoloLow,
	kSoloHigh,
	kSoloHighpass,
	
	kDelayLowpass,
	kDelayLow,
	kDelayHigh,
	kDelayHighpass,

	kOutput,
	
	kNumParams
};
};

class StereoWidener
{
public:
	StereoWidener();
	~StereoWidener();
	
	void resume();
	void setSampleRate(float sampleRate);
	void setParameter(int index, float value);
	

	void resetBuffer();
	void resetCoeffs();
	
	void process(float *in, int sampleFrames);;
    void process(float *inL, float *inR, int sampleFrames);
	//void process(double &in);
    void process(double *inL, double *inR, int sampleFrames);

protected:
	float* parameter_;
	float fSampleRate_;

	RbjFilter rbj_[3][3][2][2];	//[freq: low 0, mid 1, high 2][type: lowpass 0, highpass 1, allpass 2][channel: left 0, right 1][depth: 1st 0, 2nd 1]	

	float fDelayBuffer_[8][8192];

	float fOnOff_;
	bool bOnOff_;

	float fFreqLow_, fFreqMid_, fFreqHigh_;
	float ftempFreqLow_, ftempFreqMid_, ftempFreqHigh_;

	float fWidthLowpass_, fWidthLow_, fWidthHigh_, fWidthHighpass_;
	float fGainMidLowpass_, fGainMidLow_, fGainMidHigh_, fGainMidHighpass_;
	float fGainSideLowpass_, fGainSideLow_, fGainSideHigh_, fGainSideHighpass_;
	float fGainLowpass_, fGainLow_, fGainHigh_, fGainHighpass_;
	float fDelayLowpass_, fDelayLow_, fDelayHigh_, fDelayHighpass_;
	float ftempDelayLowpassL_, ftempDelayLowL_, ftempDelayHighL_, ftempDelayHighpassL_;
	float ftempDelayLowpassR_, ftempDelayLowR_, ftempDelayHighR_, ftempDelayHighpassR_;
	float fSoloLowpass_, fSoloLow_, fSoloHigh_, fSoloHighpass_;
	bool bSoloLowpass_, bSoloLow_, bSoloHigh_, bSoloHighpass_;

	float fOutput_;
	double dOutputP_;

	int nCounter_;
};

#endif
