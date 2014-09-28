/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_B91085D11E395EEB__
#define __JUCE_HEADER_B91085D11E395EEB__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class StereoWidenerAudioProcessorEditor  : public AudioProcessorEditor,
                                           public Timer,
                                           public SliderListener
										  
						
{
public:
    //==============================================================================
    StereoWidenerAudioProcessorEditor (StereoWidenerAudioProcessor* ownerFilter);
    ~StereoWidenerAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void timerCallback();
	StereoWidenerAudioProcessor* getProcessor() const
     {return static_cast <StereoWidenerAudioProcessor*>(getAudioProcessor());}

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);

	//double getMinValue(Slider* sliderThatwasMoved);
	//double getMaxValue(Slider* sliderThatwasMoved);
	
	void drawLine(Graphics& g);

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    double minValue_;
	double maxValue_;

	ScopedPointer<Path> FreqLowPath;
	ScopedPointer<Slider> FreqLowSld;
    ScopedPointer<Label> FreqLowLabel;
    ScopedPointer<Slider> slider;
    ScopedPointer<Slider> slider2;
    ScopedPointer<Slider> slider3;
    ScopedPointer<Slider> slider4;
    ScopedPointer<Label> Band1Label;
    ScopedPointer<Label> Band2Label;
    ScopedPointer<Label> Band3Label;

	StereoWidener stereoWidener_;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoWidenerAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_B91085D11E395EEB__
