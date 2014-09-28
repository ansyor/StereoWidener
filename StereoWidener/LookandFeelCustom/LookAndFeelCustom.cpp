/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "LookAndFeelCustom.h"




//==============================================================================
LookAndFeelCustom::LookAndFeelCustom()
{
    setColour (TextButton::buttonColourId,          Colours::yellow);
    setColour (ListBox::outlineColourId,            findColour (ComboBox::outlineColourId));
    setColour (ScrollBar::thumbColourId,            Colour (0xffbbbbdd));
    setColour (ScrollBar::backgroundColourId,       Colours::transparentBlack);
    setColour (Slider::thumbColourId,               Colours::yellow);
    setColour (Slider::trackColourId,               Colour (0x7f000000));
    setColour (Slider::textBoxOutlineColourId,      Colours::green);
    setColour (ProgressBar::backgroundColourId,     Colours::white.withAlpha (0.6f));
    setColour (ProgressBar::foregroundColourId,     Colours::green.withAlpha (0.7f));
    setColour (PopupMenu::backgroundColourId,             Colour (0xffeef5f8));
    setColour (PopupMenu::highlightedBackgroundColourId,  Colour (0xbfa4c2ce));
    setColour (PopupMenu::highlightedTextColourId,        Colours::black);
    setColour (TextEditor::focusedOutlineColourId,  findColour (TextButton::buttonColourId));

    //scrollbarShadow.setShadowProperties (2.2f, 0.5f, 0, 0);
}

LookAndFeelCustom::~LookAndFeelCustom()
{
}

static void drawTriangle (Graphics& g, float x1, float y1, float x2, float y2, float x3, float y3, const Colour& fill, const Colour& outline) noexcept
{
    Path p;
    p.addTriangle (x1, y1, x2, y2, x3, y3);
    g.setColour (fill);
    g.fillPath (p);

    g.setColour (outline);
    g.strokePath (p, PathStrokeType (0.3f));
}

void LookAndFeelCustom::drawLinearSlider (Graphics& g,
                                             int x, int y,
                                             int w, int h,
                                             float sliderPos,
                                             float minSliderPos,
                                             float maxSliderPos,
                                             const Slider::SliderStyle style,
                                             Slider& slider)
{
    g.fillAll (slider.findColour (Slider::backgroundColourId));

    if (style == Slider::LinearBar)
    {
        g.setColour (slider.findColour (Slider::thumbColourId));
        g.fillRect (x, y, (int) sliderPos - x, h);

        g.setColour (slider.findColour (Slider::textBoxTextColourId).withMultipliedAlpha (0.5f));
        g.drawRect (x, y, (int) sliderPos - x, h);
    }
    else
    {
        g.setColour (slider.findColour (Slider::trackColourId)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.3f));

        if (slider.isHorizontal())
        {
            g.fillRect (x, y + roundToInt (h * 0.8f),
                        w, roundToInt (h * 0.2f));
        }
        else
        {
            g.fillRect (x + roundToInt (w * 0.5f - jmin (3.0f, w * 0.1f)), y,
                        jmin (4, roundToInt (w * 0.2f)), h);
        }

        float alpha = 0.35f;

        if (slider.isEnabled())
            alpha = slider.isMouseOverOrDragging() ? 1.0f : 0.7f;

        const Colour fill (slider.findColour (Slider::thumbColourId).withAlpha (alpha));
        const Colour outline (Colours::black.withAlpha (slider.isEnabled() ? 0.7f : 0.35f));

        if (style == Slider::TwoValueVertical || style == Slider::ThreeValueVertical)
        {
            drawTriangle (g, x + w * 0.5f + jmin (4.0f, w * 0.3f), minSliderPos,
                          x + w * 0.5f - jmin (8.0f, w * 0.4f), minSliderPos - 7.0f,
                          x + w * 0.5f - jmin (8.0f, w * 0.4f), minSliderPos,
                          fill, outline);

            drawTriangle (g, x + w * 0.5f + jmin (4.0f, w * 0.3f), maxSliderPos,
                          x + w * 0.5f - jmin (8.0f, w * 0.4f), maxSliderPos,
                          x + w * 0.5f - jmin (8.0f, w * 0.4f), maxSliderPos + 7.0f,
                          fill, outline);
        }
        else if (style == Slider::TwoValueHorizontal || style == Slider::ThreeValueHorizontal)
        {
            drawTriangle (g, minSliderPos, y + h * 0.6f - jmin (4.0f, h * 0.3f),
                          minSliderPos - 7.0f, y + h * 0.9f ,
                          minSliderPos, y + h * 0.9f,
                          fill, outline);

            drawTriangle (g, maxSliderPos, y + h * 0.6f - jmin (4.0f, h * 0.3f),
                          maxSliderPos, y + h * 0.9f,
                          maxSliderPos + 7.0f, y + h * 0.9f,
                          fill, outline);
        }

        if (style == Slider::LinearHorizontal || style == Slider::ThreeValueHorizontal)
        {
            drawTriangle (g, sliderPos, y + h * 0.9f,
                          sliderPos - 7.0f, y + h * 0.2f,
                          sliderPos + 7.0f, y + h * 0.2f,
                          fill, outline);
        }
        else if (style == Slider::LinearVertical || style == Slider::ThreeValueVertical)
        {
            drawTriangle (g, x + w * 0.5f - jmin (4.0f, w * 0.3f), sliderPos,
                          x + w * 0.5f + jmin (8.0f, w * 0.4f), sliderPos - 7.0f,
                          x + w * 0.5f + jmin (8.0f, w * 0.4f), sliderPos + 7.0f,
                          fill, outline);
        }
    }
}



//END_JUCE_NAMESPACE