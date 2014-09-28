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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
StereoWidenerAudioProcessorEditor::StereoWidenerAudioProcessorEditor (StereoWidenerAudioProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    addAndMakeVisible (FreqLowSld = new Slider ("FreqLowSld"));
    FreqLowSld->setExplicitFocusOrder (5);
    FreqLowSld->setRange (0, 10, 0);
    FreqLowSld->setSliderStyle (Slider::ThreeValueHorizontal);
	//FreqLowSld->setMinAndMaxValues(minValue_, maxValue_, NotificationType::dontSendNotification);
    FreqLowSld->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    FreqLowSld->addListener (this);

    addAndMakeVisible (FreqLowLabel = new Label ("FreqLowLabel",
                                                 TRANS("Low")));
    FreqLowLabel->setFont (Font (15.00f, Font::plain));
    FreqLowLabel->setJustificationType (Justification::centred);
    FreqLowLabel->setEditable (false, false, false);
    FreqLowLabel->setColour (TextEditor::textColourId, Colours::black);
    FreqLowLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (slider = new Slider ("new slider"));
    slider->setRange (0, 10, 0);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider->addListener (this);

    addAndMakeVisible (slider2 = new Slider ("new slider"));
    slider2->setRange (0, 10, 0);
    slider2->setSliderStyle (Slider::LinearHorizontal);
    slider2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider2->addListener (this);

    addAndMakeVisible (slider3 = new Slider ("new slider"));
    slider3->setRange (0, 10, 0);
    slider3->setSliderStyle (Slider::LinearHorizontal);
    slider3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider3->addListener (this);

    addAndMakeVisible (slider4 = new Slider ("new slider"));
    slider4->setRange (0, 10, 0);
    slider4->setSliderStyle (Slider::LinearHorizontal);
    slider4->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider4->addListener (this);

    addAndMakeVisible (Band1Label = new Label ("Band1Label",
                                               TRANS("Band 1")));
    Band1Label->setFont (Font (15.00f, Font::plain));
    Band1Label->setJustificationType (Justification::centred);
    Band1Label->setEditable (false, false, false);
    Band1Label->setColour (TextEditor::textColourId, Colours::black);
    Band1Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (Band2Label = new Label ("Band2Label",
                                               TRANS("Band 2")));
    Band2Label->setFont (Font (15.00f, Font::plain));
    Band2Label->setJustificationType (Justification::centred);
    Band2Label->setEditable (false, false, false);
    Band2Label->setColour (TextEditor::textColourId, Colours::black);
    Band2Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (Band3Label = new Label ("Band3Label",
                                               TRANS("Band 3\n")));
    Band3Label->setFont (Font (15.00f, Font::plain));
    Band3Label->setJustificationType (Justification::centredLeft);
    Band3Label->setEditable (false, false, false);
    Band3Label->setColour (TextEditor::textColourId, Colours::black);
    Band3Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

	//addAndMakeVisible (FreqLowPath = new Path ("Frequency Low Path", TRANS("Frequency Low\n")));

    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	getProcessor()->RequestUIUpdate();//UI Update must be done each time a new editor is constructed
	startTimer(200);//starts timer with interval of 200mS
	//InvertStagesBtn->setClickingTogglesState(true);
    //[/Constructor]
}

StereoWidenerAudioProcessorEditor::~StereoWidenerAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    FreqLowSld = nullptr;
    FreqLowLabel = nullptr;
    slider = nullptr;
    slider2 = nullptr;
    slider3 = nullptr;
    slider4 = nullptr;
    Band1Label = nullptr;
    Band2Label = nullptr;
    Band3Label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void StereoWidenerAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xfff9f1f1));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void StereoWidenerAudioProcessorEditor::resized()
{
    FreqLowSld->setBounds (48, 8, 128, 104);
    FreqLowLabel->setBounds (96, 120, 77, 24);
    slider->setBounds (8, 184, 120, 24);
    slider2->setBounds (8, 239, 120, 24);
    slider3->setBounds (8, 290, 120, 24);
    slider4->setBounds (8, 344, 120, 24);
    Band1Label->setBounds (8, 152, 104, 24);
    Band2Label->setBounds (160, 152, 96, 24);
    Band3Label->setBounds (249, 216, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void StereoWidenerAudioProcessorEditor::drawLine(Graphics& g)
{
	g.drawVerticalLine(2, 10, 100);
	g.drawLine(40, 100, 100, 140, 2);
	//drawpath
	int x=10;
    int top=10;
    int bottom=top+40;
    Point<float> pt[6];
    pt[0].setXY( x+1.5, top+17.5 );
    pt[1].setXY( x+8.5, top+1.5 );

    // these next two points form the messed up segment of the stroke
    pt[2].setXY( x+8.5, top+0.5 );
    pt[3].setXY( x-7.5, top+0.5 );

    pt[4].setXY( x-7.5, top+1.5 );
    pt[5].setXY( x-0.5, top+17.5 );
    Path p;
    p.startNewSubPath (pt[0].getX(), pt[0].getY());
    for( int i=1; i<6; i++ )
      p.lineTo (pt[i].getX(), pt[i].getY());
    p.closeSubPath();
    g.setColour (Colours::black);
}

void StereoWidenerAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]
	//pimpl->

    if (sliderThatWasMoved == FreqLowSld)
    {
        
    }
    else if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }
    else if (sliderThatWasMoved == slider2)
    {
        //[UserSliderCode_slider2] -- add your slider handling code here..
        //[/UserSliderCode_slider2]
    }
    else if (sliderThatWasMoved == slider3)
    {
        //[UserSliderCode_slider3] -- add your slider handling code here..
        //[/UserSliderCode_slider3]
    }
    else if (sliderThatWasMoved == slider4)
    {
        //[UserSliderCode_slider4] -- add your slider handling code here..
        //[/UserSliderCode_slider4]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}


//double StereoWidenerAudioProcessorEditor::getMinValue(Slider* sliderThatwasMoved)
//{

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void StereoWidenerAudioProcessorEditor::timerCallback()
{
	StereoWidenerAudioProcessor* ourProcessor = getProcessor();
	//exchange any data you want between UI elements and the Plugin "ourProcessor"
	/*if(ourProcessor->NeedsUIUpdate())
	{
		InvertStagesBtn->setToggleState(1.0f == ourProcessor->getParameter(0), false);
		AtanPosSld->setValue(ourProcessor->getParameter(1), juce::dontSendNotification);
		AtanNegSld->setValue(ourProcessor->getParameter(2), juce::dontSendNotification);
		StagesSld->setValue(ourProcessor->getParameter(3), juce::dontSendNotification);
		ourProcessor->ClearUIUpdateFlag();
	}*/
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="StereoWidenerAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="StereoWidenerAudioProcessor* ownerFilter"
                 variableInitialisers="AudioProcessorEditor(ownerFilter)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="fff9f1f1"/>
  <SLIDER name="FreqLowSld" id="aee7f0ce0677bac8" memberName="FreqLowSld"
          virtualName="" explicitFocusOrder="5" pos="48 8 128 104" min="1"
          max="10" int="0" style="ThreeValueHorizontal" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="FreqLowLabel" id="a1b78e474a5a9cff" memberName="FreqLowLabel"
         virtualName="" explicitFocusOrder="0" pos="96 120 77 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Low" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="de930441974d12f0" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="8 184 120 24" min="0" max="10" int="0"
          style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="55cbbaa26c5059ce" memberName="slider2"
          virtualName="" explicitFocusOrder="0" pos="8 239 120 24" min="0"
          max="10" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="8c32f6b4653ea6fa" memberName="slider3"
          virtualName="" explicitFocusOrder="0" pos="8 290 120 24" min="0"
          max="10" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="6c845954ac6562f" memberName="slider4" virtualName=""
          explicitFocusOrder="0" pos="8 344 120 24" min="0" max="10" int="0"
          style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Band1Label" id="88e66d6f7b3fc225" memberName="Band1Label"
         virtualName="" explicitFocusOrder="0" pos="8 152 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Band 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Band2Label" id="7982a7301e608e37" memberName="Band2Label"
         virtualName="" explicitFocusOrder="0" pos="160 152 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Band 2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Band3Label" id="a9b93f8000a76645" memberName="Band3Label"
         virtualName="" explicitFocusOrder="0" pos="249 216 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Band 3&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
