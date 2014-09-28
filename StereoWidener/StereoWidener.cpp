#include "StereoWidener.h"
#include "math.h"

#define SQRT2_2 0.70710678118f

using namespace STRWDNR;

StereoWidener::StereoWidener()
{
    //name_ = "StereoWidener";

	parameter_ = new float[kNumParams];

	for(int i = 0; i < kNumParams; ++i)
	{
		parameter_[i] = 0;
	}

	resetCoeffs();
	resetBuffer();
}

StereoWidener::~StereoWidener()
{
    if(parameter_)
		delete[] parameter_;
	parameter_ = 0;

	fOnOff_ = this->parameter_[kOnOff];
	if(fOnOff_ == 0.f)
		bOnOff_ = true;
	else
		bOnOff_ = false;

	fFreqLow_ = this->parameter_[kFreqLow];
	fFreqMid_ = this->parameter_[kFreqMid];
	fFreqHigh_ = this->parameter_[kFreqHigh];

	fWidthLowpass_ = this->parameter_[kWidthLowpass];
	fWidthLow_ = this->parameter_[kWidthLow];
	fWidthHigh_ = this->parameter_[kWidthHigh];
	fWidthHighpass_ = this->parameter_[kWidthHighpass];

	fGainMidLowpass_ = db2lin(12.f * (1.f - fWidthLowpass_) - 6.f);
	fGainMidLow_ = db2lin(12.f * (1.f - fWidthLow_) - 6.f);
	fGainMidHigh_ = db2lin(12.f * (1.f - fWidthHigh_) - 6.f);
	fGainMidHighpass_ = db2lin(12.f * (1.f - fWidthHighpass_) - 6.f);

	fGainSideLowpass_ = db2lin(12.f * fWidthLowpass_ - 6.f);
	fGainSideLow_ = db2lin(12.f * fWidthLow_ - 6.f);
	fGainSideHigh_ = db2lin(12.f * fWidthHigh_ - 6.f);
	fGainSideHighpass_ = db2lin(12.f * fWidthHighpass_ - 6.f);

	fGainLowpass_ = this->parameter_[kGainLowpass];
	fGainLow_ = this->parameter_[kGainLow];
	fGainHigh_ = this->parameter_[kGainHigh];
	fGainHighpass_ = this->parameter_[kGainHighpass];
	
	fSoloLowpass_ = this->parameter_[kSoloLowpass];
	if(fSoloLowpass_ != 0.f)
		bSoloLowpass_ = true;
	else
		bSoloLowpass_ = false;

	fSoloLow_ = this->parameter_[kSoloLow];
	if(fSoloLow_ =! 0.f)
		bSoloLow_ = true;
	else
		bSoloLow_ = false;

	fSoloHigh_ = this->parameter_[kSoloHigh];
	if(fSoloHigh_ != 0.f)
		bSoloHigh_ = true;
	else
		bSoloHigh_ = false;

	fSoloHighpass_ = this->parameter_[kSoloHighpass];
	if(fSoloHighpass_ != 0.f)
		bSoloHighpass_ = true;
	else
		bSoloHighpass_ = false;

	fDelayLowpass_ = this->parameter_[kDelayLowpass];
	fDelayLow_ = this->parameter_[kDelayLow];
	fDelayHigh_ = this->parameter_[kDelayHigh];
	fDelayHighpass_ = this->parameter_[kDelayHighpass];
	
	
//Output
	fOutput_ = this->parameter_[kOutput];
	dOutputP_ = db2lin((fOutput_ * 40.f) - 20.f);
}

void StereoWidener::resetCoeffs()
{
	//if(rbj_)
		//delete[] rbj_;
}

void StereoWidener::resetBuffer()
{
	//if(fDelayBuffer_)
		//delete[] fDelayBuffer_;
}

void StereoWidener::setSampleRate(float sampleRate)
{
	fSampleRate_ = sampleRate;
}
//-------------------------------------------------------------------------------------------------------
void StereoWidener::resume()
{	
	//fSampleRate_ = getSampleRate();

	for(int i = 0; i < 3; i++)	//filter freq
	{
		for(int j = 0; j < 3; j++)  //filter type (LP, HP, AP)
		{
			for(int k = 0; k < 2; k++)  //filter channel (L or R)
			{
				for(int l = 0; l < 2; l++)  //filter depth
				{
					switch(i)
					{
						case 0:		if(j == 2)
										rbj_[i][j][k][l].calc_filter_coeffs(5, this->parameter_[kFreqLow], fSampleRate_, SQRT2_2, 0.f, 0);
									else
										rbj_[i][j][k][l].calc_filter_coeffs(j, this->parameter_[kFreqLow], fSampleRate_, SQRT2_2, 0.f, 0);
									break;
						case 1:		if(j == 2)
										rbj_[i][j][k][l].calc_filter_coeffs(5, this->parameter_[kFreqMid], fSampleRate_, SQRT2_2, 0.f, 0);
									else
										rbj_[i][j][k][l].calc_filter_coeffs(j, this->parameter_[kFreqMid], fSampleRate_, SQRT2_2, 0.f, 0);
									break;
						case 2:		if(j == 2)
										rbj_[i][j][k][l].calc_filter_coeffs(5, this->parameter_[kFreqHigh], fSampleRate_, SQRT2_2, 0.f, 0);
									else
										rbj_[i][j][k][l].calc_filter_coeffs(j, this->parameter_[kFreqHigh], fSampleRate_, SQRT2_2, 0.f, 0);
									break;
					}
				}
			}
		}
	}
	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8192; j++)
		{
			fDelayBuffer_[i][j] = 0;
		}
	}

	nCounter_ = 0;
	
	ftempFreqLow_ = ftempFreqMid_ = ftempFreqHigh_ = 0;
}


void StereoWidener::setParameter (int index, float value)
{
	
	switch (index)
	{
		case kOnOff:			fOnOff_ = this->parameter_[kOnOff] = value; 
								if(fOnOff_ == 0.f)
									bOnOff_ = true;
								else
									bOnOff_ = false;
								break;
		//RbjFilter rbj_[3][3][2][2];	//[freq: low 0, mid 1, high 2][type: lowpass 0, highpass 1, allpass 2][channel: left 0, right 1][depth: 1st 0, 2nd 1]

		case kFreqLow:			if((value < fFreqMid_) && (value < fFreqHigh_))
								{
									ftempFreqLow_ = value;
									for(int i = 0; i < 3; i++)
									{
										for(int j = 0; j < 2; j++)
										{
											for(int k = 0; k < 2; k++)
											{
												if(i == 2)
													rbj_[0][i][j][k].calc_filter_coeffs(5, ftempFreqLow_, fSampleRate_, SQRT2_2, 0.f, 0);
												else
													rbj_[0][i][j][k].calc_filter_coeffs(i, ftempFreqLow_, fSampleRate_, SQRT2_2, 0.f, 0);
											}
										}
									}

									fFreqLow_ = this->parameter_[kFreqLow] = ftempFreqLow_;
								}
								else
								{
									ftempFreqLow_ = fFreqMid_;
									for(int i = 0; i < 3; i++)
									{
										for(int j = 0; j < 2; j++)
										{
											for(int k = 0; k < 2; k++)
											{
												if(i == 2)
													rbj_[0][i][j][k].calc_filter_coeffs(5, ftempFreqLow_, fSampleRate_, SQRT2_2, 0.f, 0);
												else
													rbj_[0][i][j][k].calc_filter_coeffs(i, ftempFreqLow_, fSampleRate_, SQRT2_2, 0.f, 0);
											}
										}
									}

									fFreqLow_ = this->parameter_[kFreqLow] = ftempFreqLow_;
								}
								break;

		case kFreqMid:			if((value > fFreqLow_) && (value < fFreqHigh_))
								{
									ftempFreqMid_ = value;
									for(int i = 0; i < 3; i++)
									{
										for(int j = 0; j < 2; j++)
										{
											for(int k = 0; k < 2; k++)
											{
												if(i == 2)
													rbj_[1][i][j][k].calc_filter_coeffs(5, ftempFreqMid_, fSampleRate_, SQRT2_2, 0.f, 0);
												else
													rbj_[1][i][j][k].calc_filter_coeffs(i, ftempFreqMid_, fSampleRate_, SQRT2_2, 0.f, 0);
											}
										}
									}

									fFreqMid_ = this->parameter_[kFreqMid] = ftempFreqMid_;
								}
								break;

		case kFreqHigh:			if((value > fFreqMid_) && (value >fFreqLow_))
								{
									ftempFreqHigh_ = value;
									for(int i = 0; i < 3; i++)
									{
										for(int j = 0; j < 2; j++)
										{
											for(int k = 0; k < 2; k++)
											{
												if(i == 2)
													rbj_[2][i][j][k].calc_filter_coeffs(5, ftempFreqHigh_, fSampleRate_, SQRT2_2, 0.f, 0);
												else
													rbj_[2][i][j][k].calc_filter_coeffs(i, ftempFreqHigh_, fSampleRate_, SQRT2_2, 0.f, 0);
											}
										}
									}

									fFreqHigh_ = this->parameter_[kFreqHigh] = ftempFreqHigh_;
								}
								break;

		case kWidthLowpass:		fWidthLowpass_ = this->parameter_[kWidthLowpass] = value;
								fGainMidLowpass_ = db2lin(6.f) * fWidthLowpass_;
								fGainSideLowpass_ = db2lin(6.f) * fWidthLowpass_;
								break;
		case kWidthLow:			fWidthLow_ = this->parameter_[kWidthLow] = value;
								fGainMidLow_ = db2lin(6.f) * fWidthLow_;
								fGainSideLow_ = db2lin(6.f) * fWidthLow_;
								break;
		case kWidthHigh:		fWidthHigh_ = this->parameter_[kWidthHigh] = value;
								fGainMidHigh_ = db2lin(6.f) * fWidthHigh_;
								fGainSideHigh_ = db2lin(6.f) * fWidthHigh_;
								break;
		case kWidthHighpass:	fWidthHighpass_ = this->parameter_[kWidthHighpass] = value;
								fGainMidHighpass_ = db2lin(6.f) * fWidthHighpass_;
								fGainSideHighpass_ = db2lin(6.f) * fWidthHighpass_;
								break;

		case kGainLowpass:		fGainLowpass_ = this->parameter_[kGainLowpass] = value;
								break;
		case kGainLow:			fGainLow_ = this->parameter_[kGainLow] = value;
								break;
		case kGainHigh:			fGainHigh_ = this->parameter_[kGainHigh] = value;
								break;
		case kGainHighpass:		fGainHighpass_ = this->parameter_[kGainHighpass] = value;
								break;

		case kSoloLowpass:		fSoloLowpass_ = this->parameter_[kSoloLowpass] = value;
								break;
		case kSoloLow:			fSoloLow_ = this->parameter_[kSoloLow] = value;
								break;
		case kSoloHigh:			fSoloHigh_ = this->parameter_[kSoloHigh] = value;
								break;
		case kSoloHighpass:		fSoloHighpass_ = this->parameter_[kSoloHighpass] = value;
								break;

		case kDelayLowpass:		fDelayLowpass_ = this->parameter_[kDelayLowpass] = value;
								ftempDelayLowpassR_ = ((60.f * fDelayLowpass_) - 30.f) * fSampleRate_ / 1000.f;
								if (ftempDelayLowpassR_ < 0)
								{
									ftempDelayLowpassL_ = -ftempDelayLowpassR_;
									ftempDelayLowpassR_ = 0;
								}
								else
									ftempDelayLowpassL_ = 0;
								break;
		case kDelayLow:			fDelayLow_ = this->parameter_[kDelayLow] = value;
								ftempDelayLowR_ = ((60.f * fDelayLow_) - 30.f) * fSampleRate_ / 1000.f;
								if (ftempDelayLowR_ < 0)
								{
									ftempDelayLowL_ = -ftempDelayLowR_;
									ftempDelayLowR_ = 0;
								}
								else 
									ftempDelayLowL_ = 0.f;
								break;
		case kDelayHigh:		fDelayHigh_ = this->parameter_[kDelayHigh] = value;
								ftempDelayHighR_ = ((60.f * fDelayHigh_) - 30.f) * fSampleRate_ / 1000.f;
								if (ftempDelayHighR_ < 0)
								{
									ftempDelayHighL_ = -ftempDelayHighR_;
									ftempDelayHighR_ = 0;
								}
								else 
									ftempDelayHighL_ = 0.f;
								break;
		case kDelayHighpass:	fDelayHighpass_ = this->parameter_[kDelayHighpass] = value;
								ftempDelayHighpassR_ = ((60.f * fDelayHighpass_) - 30.f) * fSampleRate_ / 1000.f;
								if (ftempDelayHighpassR_ < 0)
								{
									ftempDelayHighpassL_ = -ftempDelayHighpassR_;
									ftempDelayHighpassR_ = 0;
									}
								else 
									ftempDelayHighpassL_ = 0.f;
								break;

		case kOutput:			fOutput_ = this->parameter_[kOutput] = value;
								dOutputP_ = db2lin((fOutput_ * 40.f) - 20.f);
								break;
	}

	if(fSoloLowpass_ == 0.f && fSoloLow_ == 0.f && fSoloHigh_ == 0.f && fSoloHighpass_ == 0.f)
	{
		bSoloLowpass_ = bSoloLow_ = bSoloHigh_ = bSoloHighpass_ = true;
	}
	else 
	{
		bSoloLowpass_ = (bool)ceil(fSoloLowpass_);
		bSoloLow_ = (bool)ceil(fSoloLow_);
		bSoloHigh_ = (bool)ceil(fSoloHigh_);
		bSoloHighpass_ = (bool)ceil(fSoloHighpass_);
	}

}

//-----------------------------------------------------------------------------------------
void StereoWidener::process(float *in, int sampleFrames)
{

}

void StereoWidener::process(float *inL, float *inR, int sampleFrames)
{
    double dInput1, dInput2;
	bool bOnOff = bOnOff_;
	float fOutput = dOutputP_;

	double lowpassL, lowpassR, lowL, lowR, highL, highR, highpassL, highpassR;
	double templowpassL, templowpassR, templowL, templowR, temphighL, temphighR;
	double midLowpass, midLow, midHigh, midHighpass;
	double sideLowpass, sideLow, sideHigh, sideHighpass;

	float midgainLowpass = fGainMidLowpass_;
	float sidegainLowpass = fGainSideLowpass_;
	float midgainLow = fGainMidLow_;
	float sidegainLow = fGainSideLow_;
	float midgainHigh = fGainMidHigh_;
	float sidegainHigh = fGainSideHigh_;
	float midgainHighpass = fGainMidHighpass_;
	float sidegainHighpass = fGainSideHighpass_;

	float gainLowpass = db2lin(12.f * fGainLowpass_);
	float gainLow = db2lin(12.f * fGainLow_);
	float gainHigh = db2lin (12.f * fGainHigh_);
	float gainHighpass = db2lin (12.f * fGainHighpass_);

	int delayLowpassL = (int)ftempDelayLowpassL_;
	int delayLowpassR = (int)ftempDelayLowpassR_;
	int delayLowL = (int)ftempDelayLowL_;
	int delayLowR = (int)ftempDelayLowR_;
	int delayHighL = (int)ftempDelayHighL_;
	int delayHighR = (int)ftempDelayHighR_;
	int delayHighpassL = (int)ftempDelayHighpassL_;
	int delayHighpassR = (int)ftempDelayHighpassR_;

	int pos = nCounter_;

	float adjust = db2lin(-6.0f);

	if(bOnOff)
	{
		 for(int i = 0; i < sampleFrames; i++)
		{
			dInput1 = (double)inL[i];
			dInput2 = (double)inR[i];

			pos = pos & 8191;
			
			//rbj_[freq][type][channel][depth].process()

			lowpassL = rbj_[0][0][0][0].process(dInput1);
			lowpassL = rbj_[0][0][0][1].process(lowpassL);
			lowpassL = rbj_[1][2][0][0].process(lowpassL);
			lowpassL = rbj_[2][2][0][1].process(lowpassL);

			lowpassR = rbj_[0][0][1][0].process(dInput2);
			lowpassR = rbj_[0][0][1][1].process(lowpassR);
			lowpassR = rbj_[1][2][1][0].process(lowpassR);
			lowpassR = rbj_[2][2][1][1].process(lowpassR);

			midLowpass = SQRT2_2 * (lowpassL + lowpassR);
			sideLowpass = SQRT2_2 * (lowpassL - lowpassR);
			lowpassL = SQRT2_2 * (midLowpass + midgainLowpass * sideLowpass);
			lowpassR = SQRT2_2 * (midLowpass - sidegainLowpass * sideLowpass);

			fDelayBuffer_[0][pos] = lowpassL;
			lowpassL = fDelayBuffer_[0][(pos - delayLowpassL) & 8191];
			fDelayBuffer_[1][pos] = lowpassR;
			lowpassR = fDelayBuffer_[1][(pos - delayLowpassR) & 8191];

			//----------------------------------------------------------

			lowL = rbj_[0][1][0][0].process(dInput1);
			lowL = rbj_[0][1][0][1].process(lowL);
			templowL = lowL;
			lowL = rbj_[1][0][0][0].process(lowL);
			lowL = rbj_[1][0][0][1].process(lowL);
			lowL = rbj_[2][2][0][0].process(lowL);
			//lowL = rbj_[2][2][0][1].process(lowL);

			lowR = rbj_[0][1][1][0].process(dInput2);
			lowR = rbj_[0][1][1][1].process(lowR);
			templowR = lowR;
			lowR = rbj_[1][0][1][0].process(lowR);
			lowR = rbj_[1][0][1][1].process(lowR);
			lowR = rbj_[2][2][1][0].process(lowR);
			//lowR = rbj_[2][2][1][1].process(lowR);

			midLow = SQRT2_2 * (lowL + lowR);
			sideLow = SQRT2_2 * (lowL - lowR);
			lowL = SQRT2_2 * (midLow + midgainLow * sideLow);
			lowR = SQRT2_2 * (midLow - sidegainLow * sideLow);

			fDelayBuffer_[2][pos] = lowL;
			lowL = fDelayBuffer_[2][(pos - delayLowL) & 8191];
			fDelayBuffer_[3][pos] = lowR;
			lowR = fDelayBuffer_[3][(pos - delayLowR) & 8191];

			//---------------------------------------------------------

			highL = rbj_[1][1][0][0].process(templowL);
			highL = rbj_[1][1][0][1].process(highL);
			temphighL = highL;
			highL = rbj_[2][0][0][0].process(highL);
			highL = rbj_[2][0][0][1].process(highL);
			//highL = rbj_[2][2][0][0].process(highL);
			//highL = rbj_[2][2][0][1].process(highL);

			highR = rbj_[1][1][1][0].process(templowR);
			highR = rbj_[1][1][1][1].process(highR);
			temphighR = highR;
			highR = rbj_[2][0][1][0].process(highR);
			highR = rbj_[2][0][1][1].process(highR);
			//highR = rbj_[2][2][1][0].process(highR);
			//highR = rbj_[2][2][1][1].process(highR);

			midHigh = SQRT2_2 * (highL + highR);
			sideHigh = SQRT2_2 * (highL - highR);
			highL = SQRT2_2 * (midHigh + midgainHigh * sideHigh);
			highR = SQRT2_2 * (midHigh - sidegainHigh * sideHigh);

			fDelayBuffer_[4][pos] = highL;
			highL = fDelayBuffer_[4][(pos - delayHighL) & 8191];
			fDelayBuffer_[5][pos] = highR;
			highR = fDelayBuffer_[5][(pos - delayHighR) & 8191];

			//----------------------------------------------------------

			highpassL = rbj_[2][1][0][0].process(temphighL);
			highpassL = rbj_[2][1][0][1].process(highpassL);

			highpassR = rbj_[2][1][1][0].process(temphighR);
			highpassR = rbj_[2][1][1][1].process(highpassR);

			midHighpass = SQRT2_2 * (highpassL + highpassR);
			sideHighpass = SQRT2_2 * (highpassL - highpassR);
			highpassL = SQRT2_2 * (midHighpass + midgainHighpass * sideHighpass);
			highpassR = SQRT2_2 * (midHighpass - sidegainHighpass * sideHighpass);

			fDelayBuffer_[6][pos] = highpassL;
			highpassL = fDelayBuffer_[6][(pos - delayHighpassL) & 8191];
			fDelayBuffer_[7][pos] = highpassR;
			highpassR = fDelayBuffer_[7][(pos - delayHighpassR) & 8191];

			//----------------------------------------------------------

			inL[i] = fOutput * adjust * (lowpassL * gainLowpass * bSoloLowpass_ + lowL * gainLow * bSoloLow_ + highL * gainHigh * bSoloHigh_ + highpassL * gainHighpass * bSoloHighpass_);
			inR[i] = fOutput * adjust * (lowpassR * gainLowpass * bSoloLowpass_ + lowR * gainLow * bSoloLow_ + highR * gainHigh * bSoloHigh_ + highpassR * gainHighpass * bSoloHighpass_);

			pos++;
		}

		nCounter_ = pos;
	}
}

//-----------------------------------------------------------------------------------------
void StereoWidener::process (double *inL, double *inR, int sampleFrames)
{
    double dInput1, dInput2;
	bool bOnOff = bOnOff_;
	float fOutput = fOutput_;

	double lowpassL, lowpassR, lowL, lowR, highL, highR, highpassL, highpassR;
	double templowpassL, templowpassR, templowL, templowR, temphighL, temphighR;
	double midLowpass, midLow, midHigh, midHighpass;
	double sideLowpass, sideLow, sideHigh, sideHighpass;

	float midgainLowpass = fGainMidLowpass_;
	float sidegainLowpass = fGainSideLowpass_;
	float midgainLow = fGainMidLow_;
	float sidegainLow = fGainSideLow_;
	float midgainHigh = fGainMidHigh_;
	float sidegainHigh = fGainSideHigh_;
	float midgainHighpass = fGainMidHighpass_;
	float sidegainHighpass = fGainSideHighpass_;

	float gainLowpass = db2lin(12.f * fGainLowpass_);
	float gainLow = db2lin(12.f * fGainLow_);
	float gainHigh = db2lin (12.f * fGainHigh_);
	float gainHighpass = db2lin (12.f * fGainHighpass_);

	int delayLowpassL = (int)ftempDelayLowpassL_;
	int delayLowpassR = (int)ftempDelayLowpassR_;
	int delayLowL = (int)ftempDelayLowL_;
	int delayLowR = (int)ftempDelayLowR_;
	int delayHighL = (int)ftempDelayHighL_;
	int delayHighR = (int)ftempDelayHighR_;
	int delayHighpassL = (int)ftempDelayHighpassL_;
	int delayHighpassR = (int)ftempDelayHighpassR_;

	int pos = nCounter_;

	float adjust = db2lin(-6.0f);

	if(bOnOff)
	{
		for(int i = 0; i < sampleFrames; i++)
		{
			dInput1 = (double)inL[i];
			dInput2 = (double)inR[i];

			pos = pos & 8191;
			
			//		   rbj_[freq][type][channel][depth].process()

			lowpassL = rbj_[0][0][0][0].process(dInput1);
			lowpassL = rbj_[0][0][0][1].process(lowpassL);
			lowpassL = rbj_[1][2][0][0].process(lowpassL);
			lowpassL = rbj_[2][2][0][1].process(lowpassL);

			lowpassR = rbj_[0][0][1][0].process(dInput2);
			lowpassR = rbj_[0][0][1][1].process(lowpassR);
			lowpassR = rbj_[1][2][1][0].process(lowpassR);
			lowpassR = rbj_[2][2][1][1].process(lowpassR);

			midLowpass = SQRT2_2 * (lowpassL + lowpassR);
			sideLowpass = SQRT2_2 * (lowpassL - lowpassR);
			lowpassL = SQRT2_2 * (midLowpass + midgainLowpass * sideLowpass);
			lowpassR = SQRT2_2 * (midLowpass - sidegainLowpass * sideLowpass);

			fDelayBuffer_[0][pos] = lowpassL;
			lowpassL = fDelayBuffer_[0][(pos - delayLowpassL) & 8191];
			fDelayBuffer_[1][pos] = lowpassR;
			lowpassR = fDelayBuffer_[1][(pos - delayLowpassR) & 8191];

			//----------------------------------------------------------

			lowL = rbj_[0][1][0][0].process(dInput1);
			lowL = rbj_[0][1][0][1].process(lowL);
			templowL = lowL;
			lowL = rbj_[1][0][0][0].process(lowL);
			lowL = rbj_[1][0][0][1].process(lowL);
			lowL = rbj_[2][2][0][0].process(lowL);
			//lowL = rbj_[2][2][0][1].process(lowL);

			lowR = rbj_[0][1][1][0].process(dInput2);
			lowR = rbj_[0][1][1][1].process(lowR);
			templowR = lowR;
			lowR = rbj_[1][0][1][0].process(lowR);
			lowR = rbj_[1][0][1][1].process(lowR);
			lowR = rbj_[2][2][1][0].process(lowR);
			//lowR = rbj_[2][2][1][1].process(lowR);

			midLow = SQRT2_2 * (lowL + lowR);
			sideLow = SQRT2_2 * (lowL - lowR);
			lowL = SQRT2_2 * (midLow + midgainLow * sideLow);
			lowR = SQRT2_2 * (midLow - sidegainLow * sideLow);

			fDelayBuffer_[2][pos] = lowL;
			lowL = fDelayBuffer_[2][(pos - delayLowL) & 8191];
			fDelayBuffer_[3][pos] = lowR;
			lowR = fDelayBuffer_[3][(pos - delayLowR) & 8191];

			//---------------------------------------------------------

			highL = rbj_[1][1][0][0].process(templowL);
			highL = rbj_[1][1][0][1].process(highL);
			temphighL = highL;
			highL = rbj_[2][0][0][0].process(highL);
			highL = rbj_[2][0][0][1].process(highL);
			//highL = rbj_[2][2][0][0].process(highL);
			//highL = rbj_[2][2][0][1].process(highL);

			highR = rbj_[1][1][1][0].process(templowR);
			highR = rbj_[1][1][1][1].process(highR);
			temphighR = highR;
			highR = rbj_[2][0][1][0].process(highR);
			highR = rbj_[2][0][1][1].process(highR);
			//highR = rbj_[2][2][1][0].process(highR);
			//highR = rbj_[2][2][1][1].process(highR);

			midHigh = SQRT2_2 * (highL + highR);
			sideHigh = SQRT2_2 * (highL - highR);
			highL = SQRT2_2 * (midHigh + midgainHigh * sideHigh);
			highR = SQRT2_2 * (midHigh - sidegainHigh * sideHigh);

			fDelayBuffer_[4][pos] = highL;
			highL = fDelayBuffer_[4][(pos - delayHighL) & 8191] = highL;
			fDelayBuffer_[5][pos] = highR;
			highR = fDelayBuffer_[5][(pos - delayHighR) & 8191];

			//----------------------------------------------------------

			highpassL = rbj_[2][1][0][0].process(temphighL);
			highpassL = rbj_[2][1][0][1].process(highpassL);

			highpassR = rbj_[2][1][1][0].process(temphighR);
			highpassR = rbj_[2][1][1][1].process(highpassR);

			midHighpass = SQRT2_2 * (highpassL + highpassR);
			sideHighpass = SQRT2_2 * (highpassL - highpassR);
			highpassL = SQRT2_2 * (midHighpass + midgainHighpass * sideHighpass);
			highpassR = SQRT2_2 * (midHighpass - sidegainHighpass * sideHighpass);

			fDelayBuffer_[6][pos] = highpassL;
			highpassL = fDelayBuffer_[6][(pos - delayHighpassL) & 8191];
			fDelayBuffer_[7][pos] = highpassR;
			highpassR = fDelayBuffer_[7][(pos - delayHighpassR) & 8191];

			//----------------------------------------------------------

			(*inL) = fOutput * adjust * (lowpassL * gainLowpass * bSoloLowpass_ + lowL * gainLow * bSoloLow_ + highL * gainHigh * bSoloHigh_ + highpassL * gainHighpass * bSoloHighpass_);
			(*inR) = fOutput * adjust * (lowpassR * gainLowpass * bSoloLowpass_ + lowR * gainLow * bSoloLow_ + highR * gainHigh * bSoloHigh_ + highpassR * gainHighpass * bSoloHighpass_);

			pos++;
		}

		nCounter_ = pos;
	}
}