/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//namespace STRWDNR{
//	enum t
//{
//    kOnOff = 0,
//	
//    kFreqLow,
//    kFreqMid,
//    kFreqHigh,
//    
//    kWidthLowpass,
//    kWidthLow,
//    kWidthHigh,
//    kWidthHighpass,
//    
//    kGainLowpass,
//    kGainLow,
//    kGainHigh,
//    kGainHighpass,
//    
//    kSoloLowpass,
//    kSoloLow,
//	kSoloHigh,
//	kSoloHighpass,
//	
//	kDelayLowpass,
//	kDelayLow,
//	kDelayHigh,
//	kDelayHighpass,
//
//	kOutput,
//	
//	kNumParams
//};
//};

//==============================================================================
StereoWidenerAudioProcessor::StereoWidenerAudioProcessor()
{
	UserParams[kOnOff]=0.0f;

	UserParams[kFreqLow]=0.25f;
	UserParams[kFreqMid] = 0.5f;
	UserParams[kFreqHigh] = 0.75f;

	UserParams[kWidthLowpass]=0.0f;
	UserParams[kWidthLow] = 0.0f;
	UserParams[kWidthHigh] = 0.0f;
	UserParams[kWidthHighpass] = 0.0f;

	UserParams[kGainLowpass]=0.0f;
	UserParams[kGainLow] = 0.0f;
	UserParams[kGainHigh] = 0.0f;
	UserParams[kGainHighpass] = 0.0f;
	
	UserParams[kSoloLowpass]=0.0f;
	UserParams[kSoloLow] = 0.0f;
	UserParams[kSoloHigh] = 0.0f;
	UserParams[kSoloHighpass] = 0.0f;
	
	UserParams[kDelayLowpass]=0.0f;
	UserParams[kDelayLow] = 0.0f;
	UserParams[kDelayHigh] = 0.0f;
	UserParams[kDelayHighpass] = 0.0f;

	UserParams[kOutput] = 0.5f;
	UIUpdateFlag=true;//Request UI update
}

StereoWidenerAudioProcessor::~StereoWidenerAudioProcessor()
{
	stereoWidener_.resetBuffer();
	stereoWidener_.resetCoeffs();
}

//==============================================================================
const String StereoWidenerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int StereoWidenerAudioProcessor::getNumParameters()
{
    return kNumParams;
}

float StereoWidenerAudioProcessor::getParameter (int index)
{
	switch(index)
	{
		case kOnOff:			return UserParams[kOnOff];
								break;

		case kFreqLow:			return UserParams[kFreqLow];
								break;
		case kFreqMid:			return UserParams[kFreqMid];
								break;
		case kFreqHigh:			return UserParams[kFreqHigh];
								break;

		case kWidthLowpass:		return UserParams[kWidthLowpass];
								break;
		case kWidthLow:			return UserParams[kWidthLow];
								break;
		case kWidthHigh:		return UserParams[kWidthHigh];
								break;
		case kWidthHighpass:	return UserParams[kWidthHighpass];
								break;

		case kGainLowpass:		return UserParams[kGainLowpass];
								break;
		case kGainLow:			return UserParams[kGainLow];
								break;
		case kGainHigh:			return UserParams[kGainHigh];
								break;
		case kGainHighpass:		return UserParams[kGainHighpass];
								break;

		case kSoloLowpass:		return UserParams[kSoloLowpass];
								break;
		case kSoloLow:			return UserParams[kSoloLow];
								break;
		case kSoloHigh:			return UserParams[kSoloHigh];
								break;
		case kSoloHighpass:		return UserParams[kSoloHighpass];
								break;

		case kDelayLowpass:		return UserParams[kDelayLowpass];
								break;
		case kDelayLow:			return UserParams[kDelayLow];
								break;
		case kDelayHigh:		return UserParams[kDelayHigh];
								break;
		case kDelayHighpass:	return UserParams[kDelayHighpass];
								break;

		case kOutput:			return UserParams[kOutput];
								break;
		default: return 0.0f;//invalid index
	}
}

void StereoWidenerAudioProcessor::setParameter (int index, float newValue)
{
	//dummy_.setParameter(index, newValue);
	switch(index) 
	{
			case kOnOff:		
				UserParams[kOnOff] = newValue;
				stereoWidener_.setParameter(0, newValue);
								break;

		case kFreqLow:			
			if((newValue < UserParams[kFreqMid]) && (newValue < UserParams[kFreqHigh]))
			{
				UserParams[kFreqLow] = newValue;
			stereoWidener_.setParameter(1, newValue);
			}
			else
			{
				UserParams[kFreqLow] = UserParams[kFreqMid];
				stereoWidener_.setParameter(1,UserParams[kFreqLow] );
			}
								break;
		
		case kFreqMid:
			if ((newValue > UserParams[kFreqLow] && (newValue < UserParams[kFreqHigh]))
			){
			UserParams[kFreqMid] = newValue;
			stereoWidener_.setParameter(2, newValue);
			}
			else if (newValue < UserParams[kFreqLow])
			{
				UserParams[kFreqMid] = UserParams[kFreqLow];
				stereoWidener_.setParameter(2, UserParams[kFreqMid]);
			}
			else if (newValue > UserParams[kFreqHigh])
			{
				UserParams[kFreqMid] = UserParams[kFreqHigh];
				stereoWidener_.setParameter(2, UserParams[kFreqMid]);
			}
								break;
		case kFreqHigh:			
			if((newValue > UserParams[kFreqMid]) && (newValue > UserParams[kFreqLow]))
			{
				UserParams[kFreqHigh] = newValue;
			stereoWidener_.setParameter(1, newValue);
			}
			else
			{
				UserParams[kFreqHigh] = UserParams[kFreqMid];
				stereoWidener_.setParameter(1,UserParams[kFreqLow] );
			}
								break;

		case kWidthLowpass:		
			UserParams[kWidthLowpass] = newValue;
			stereoWidener_.setParameter(4, newValue);
								break;
		case kWidthLow:			
			UserParams[kWidthLow] = newValue;
			stereoWidener_.setParameter(5, newValue);
								break;
		case kWidthHigh:		
			UserParams[kWidthHigh] = newValue;
			stereoWidener_.setParameter(6, newValue);
								break;
		case kWidthHighpass:	
			UserParams[kWidthHighpass] = newValue;
			stereoWidener_.setParameter(7, newValue);
								break;

		case kGainLowpass:		
			UserParams[kGainLowpass] = newValue;
			stereoWidener_.setParameter(8, newValue);
								break;
		case kGainLow:			
			UserParams[kGainLow] = newValue;
			stereoWidener_.setParameter(9, newValue);
								break;
		case kGainHigh:			
			UserParams[kGainHigh] = newValue;
				stereoWidener_.setParameter(10, newValue);
								break;
		case kGainHighpass:		
			UserParams[kGainHighpass] = newValue;
			stereoWidener_.setParameter(11, newValue);
								break;

		case kSoloLowpass:		
			UserParams[kSoloLowpass] = newValue;
			stereoWidener_.setParameter(12, newValue);
								break;
		case kSoloLow:			
			UserParams[kSoloLow] = newValue;
			stereoWidener_.setParameter(13, newValue);
								break;
		case kSoloHigh:			
			UserParams[kSoloHigh] = newValue;
			stereoWidener_.setParameter(14, newValue);
								break;
		case kSoloHighpass:		
			UserParams[kSoloHighpass] = newValue;
			stereoWidener_.setParameter(15, newValue);
								break;

		case kDelayLowpass:		
			UserParams[kDelayLowpass] = newValue;
				stereoWidener_.setParameter(14, newValue);
								break;
		case kDelayLow:			
			UserParams[kDelayLow] = newValue;
			stereoWidener_.setParameter(15, newValue);
								break;
		case kDelayHigh:		
			UserParams[kDelayHigh] = newValue;
			stereoWidener_.setParameter(16, newValue);
								break;
		case kDelayHighpass:	
			UserParams[kDelayHighpass] = newValue;
			stereoWidener_.setParameter(17, newValue);
								break;

		case kOutput:			
			UserParams[kOutput] = newValue;
			stereoWidener_.setParameter(18, newValue);
								break;
	default: return;
	}
}

const String StereoWidenerAudioProcessor::getParameterName (int index)
{
	switch(index)
	{
		case kOnOff:		return "On / Off";
								break;

		case kFreqLow:			return "Low Pass Frequency";
								break;
		case kFreqMid:			return "Mid Frequency";
								break;
		case kFreqHigh:			return "High Pass Frequency";
								break;

		case kWidthLowpass:		return "Band 1 Width";
								break;
		case kWidthLow:			return "Band 2 Width";
								break;
		case kWidthHigh:		return "Band 3 Width";
								break;
		case kWidthHighpass:	return "Band 4 Width";
								break;

		case kGainLowpass:		return "Band 1 Gain";
								break;
		case kGainLow:			return "Band 2 Gain";
								break;
		case kGainHigh:			return "Band 3 Gain";
								break;
		case kGainHighpass:		return "Band 4 Gain";
								break;

		case kSoloLowpass:		return "Band 1 Solo";
								break;
		case kSoloLow:			return "Band 2 Solo";
								break;
		case kSoloHigh:			return "Band 3 Solo";
								break;
		case kSoloHighpass:		return "Band 4 Solo";
								break;

		case kDelayLowpass:		return  "Band 1 Delay";
								break;
		case kDelayLow:			return "Band 2 Delay";
								break;
		case kDelayHigh:		return  "Band 3 Delay";
								break;
		case kDelayHighpass:	return "Band 4 Delay";
								break;

		case kOutput:			return  "Output";
								break;
	default:return String::empty;
	}
}

const String StereoWidenerAudioProcessor::getParameterText (int index)
{
	if(index>=0 && index<kNumParams)
		return String(UserParams[index]);//return parameter value as string
	else return String::empty;
}

const String StereoWidenerAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String StereoWidenerAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool StereoWidenerAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool StereoWidenerAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool StereoWidenerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoWidenerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StereoWidenerAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double StereoWidenerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoWidenerAudioProcessor::getNumPrograms()
{
    return 0;
}

int StereoWidenerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoWidenerAudioProcessor::setCurrentProgram (int index)
{
}

const String StereoWidenerAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void StereoWidenerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StereoWidenerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	stereoWidener_.setSampleRate((float)sampleRate);
}

void StereoWidenerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

void StereoWidenerAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	if(getNumInputChannels()<2)
	{
		
	}
	else
	{
		float* inL = buffer.getSampleData(0);
		float* inR = buffer.getSampleData(1);
		
		int i = buffer.getNumSamples();
		stereoWidener_.process(inL, inR, i);
	}
}

//==============================================================================
bool StereoWidenerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StereoWidenerAudioProcessor::createEditor()
{
    return new StereoWidenerAudioProcessorEditor (this);
}

//==============================================================================
void StereoWidenerAudioProcessor::getStateInformation (MemoryBlock& destData)
{//Save UserParams/Data to file
	XmlElement root("Root");
	XmlElement *el;
	el = root.createNewChildElement("On / Off"); 
	el->addTextElement(String(UserParams[kOnOff]));

	el = root.createNewChildElement("Low Pass Frequency");
	el->addTextElement(String(UserParams[kFreqLow]));
	el = root.createNewChildElement("Mid Frequency");
	el->addTextElement(String(UserParams[kFreqMid]));
	el = root.createNewChildElement("High Pass Frequency");
	el->addTextElement(String(UserParams[kFreqHigh]));

	el = root.createNewChildElement("Band Width 1"); 
	el->addTextElement(String(UserParams[kWidthLowpass]));
	el = root.createNewChildElement("Band Width 2");
	el->addTextElement(String(UserParams[kWidthLow]));
	el = root.createNewChildElement("Band Width 3");
	el->addTextElement(String(UserParams[kWidthHigh]));
	el = root.createNewChildElement("Band Width 4");
	el->addTextElement(String(UserParams[kWidthHighpass]));

	el = root.createNewChildElement("Band Gain 1"); 
	el->addTextElement(String(UserParams[kGainLowpass]));
	el = root.createNewChildElement("Band Gain 2");
	el->addTextElement(String(UserParams[kGainLow]));
	el = root.createNewChildElement("Band Gain 3");
	el->addTextElement(String(UserParams[kGainHigh]));
	el = root.createNewChildElement("Band Gain 4");
	el->addTextElement(String(UserParams[kGainHighpass]));

	el = root.createNewChildElement("Band Solo 1"); 
	el->addTextElement(String(UserParams[kSoloLowpass]));
	el = root.createNewChildElement("Band Solo 2");
	el->addTextElement(String(UserParams[kSoloLow]));
	el = root.createNewChildElement("Band Solo 3");
	el->addTextElement(String(UserParams[kSoloHigh]));
	el = root.createNewChildElement("Band Solo 4");
	el->addTextElement(String(UserParams[kSoloHighpass]));

	el = root.createNewChildElement("Band Delay 1"); 
	el->addTextElement(String(UserParams[kDelayLowpass]));
	el = root.createNewChildElement("Band Delay 2");
	el->addTextElement(String(UserParams[kDelayLow]));
	el = root.createNewChildElement("Band Delay 3");
	el->addTextElement(String(UserParams[kDelayHigh]));
	el = root.createNewChildElement("Band Delay 4");
	el->addTextElement(String(UserParams[kDelayHighpass]));

	el = root.createNewChildElement("Output"); 
	el->addTextElement(String(UserParams[kOutput]));
	copyXmlToBinary(root,destData);
}

void StereoWidenerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{//Load UserParams/Data from file
	XmlElement* pRoot = getXmlFromBinary(data,sizeInBytes);
	if(pRoot!=NULL)
	{
		forEachXmlChildElement((*pRoot),pChild)
		{
			if(pChild->hasTagName("On / Off"))
			{
				String text = pChild->getAllSubText();
				setParameter(kOnOff,text.getFloatValue());
			}
			else if(pChild->hasTagName("High Pass Frequency"))
			{
				String text = pChild->getAllSubText();
				setParameter(kFreqHigh,text.getFloatValue());
			}
			else if(pChild->hasTagName("Mid Frequency"))
			{
				String text = pChild->getAllSubText();
				setParameter(kFreqMid,text.getFloatValue());
			} 
			else if(pChild->hasTagName("Low Pass Frequency"))
			{
				String text = pChild->getAllSubText();
				setParameter(kFreqLow,text.getFloatValue());
			}

			else if(pChild->hasTagName("Band Width 1"))
			{
				String text = pChild->getAllSubText();
				setParameter(kWidthLowpass,text.getFloatValue());
			}
			else if(pChild->hasTagName("Band Width 2"))
			{
				String text = pChild->getAllSubText();
				setParameter(kWidthLow,text.getFloatValue());
			} 
			else if(pChild->hasTagName("Band Width 3"))
			{
				String text = pChild->getAllSubText();
				setParameter(kWidthHigh,text.getFloatValue());
			}
			else if(pChild->hasTagName("Band Width 4"))
			{
				String text = pChild->getAllSubText();
				setParameter(kWidthHighpass,text.getFloatValue());
			}

			else if(pChild->hasTagName("Band Gain 1 "))
			{
				String text = pChild->getAllSubText();
				setParameter(kGainLowpass,text.getFloatValue());
			} 
			else if(pChild->hasTagName("Band Gain 2"))
			{
				String text = pChild->getAllSubText();
				setParameter(kGainLow,text.getFloatValue());
			}
			else if(pChild->hasTagName("Band Gain 3"))
			{
				String text = pChild->getAllSubText();
				setParameter(kGainHigh,text.getFloatValue());
			}
			else if(pChild->hasTagName("Band Gain 4"))
			{
				String text = pChild->getAllSubText();
				setParameter(kGainHighpass,text.getFloatValue());
			} 

			else if(pChild->hasTagName("Band Solo 1 "))
			{
				String text = pChild->getAllSubText();
				setParameter(kSoloLowpass,text.getFloatValue());
			} 
			else if(pChild->hasTagName("Band Solo 2"))
			{
				String text = pChild->getAllSubText();
				setParameter(kSoloLow,text.getFloatValue());
			}
			else if(pChild->hasTagName("Band Solo 3"))
			{
				String text = pChild->getAllSubText();
				setParameter(kSoloHigh,text.getFloatValue());
			}
			else if(pChild->hasTagName("Band Solo 4"))
			{
				String text = pChild->getAllSubText();
				setParameter(kSoloHighpass,text.getFloatValue());
			} 

		else if(pChild->hasTagName("Band Delay 1 "))
			{
				String text = pChild->getAllSubText();
				setParameter(kDelayLowpass,text.getFloatValue());
			} 
			else if(pChild->hasTagName("Band Delay 2"))
			{
				String text = pChild->getAllSubText();
				setParameter(kDelayLow,text.getFloatValue());
			}
			else if(pChild->hasTagName("Band Delay 3"))
			{
				String text = pChild->getAllSubText();
				setParameter(kDelayHigh,text.getFloatValue());
			}
			else if(pChild->hasTagName("Band Delay 4"))
			{
				String text = pChild->getAllSubText();
				setParameter(kDelayHighpass,text.getFloatValue());
			} 

			else if(pChild->hasTagName("Output"))
			{
				String text = pChild->getAllSubText();
				setParameter(kOutput,text.getFloatValue());
			}
		}
		delete pRoot;
		UIUpdateFlag=true;//Request UI update
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoWidenerAudioProcessor();
}
