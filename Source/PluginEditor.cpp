/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================


FlavorKnob::FlavorKnob()
{
    addAndMakeVisible(_nameLabel);
    addAndMakeVisible(_gainSlider);
}

void FlavorKnob::initialize(FlavorCode flavorCode)
{
    _flavorCode = flavorCode;

    // Set the label name with the flavor.
    juce::String _flavorName{};
    switch (flavorCode)
    {
    case Vanilla:
    {
        _flavorName = "Vanilla";
        _iceCreamImage = 
            juce::ImageFileFormat::loadFrom(BinaryData::icecream_circle1_png, BinaryData::icecream_circle1_pngSize);
        _sprinkleImage =
            juce::ImageFileFormat::loadFrom(BinaryData::icecream_sprinkle1_png, BinaryData::icecream_sprinkle1_pngSize);

        break;
    }
    case Strawberry:
    {
        _flavorName = "Strawberry";
        _iceCreamImage =
            juce::ImageFileFormat::loadFrom(BinaryData::icecream_circle2_png, BinaryData::icecream_circle2_pngSize);
        _sprinkleImage =
            juce::ImageFileFormat::loadFrom(BinaryData::icecream_sprinkle2_png, BinaryData::icecream_sprinkle2_pngSize);

        break;
    }
    case Chocolate:
    {
        _flavorName = "Chocolate";
        _iceCreamImage =
            juce::ImageFileFormat::loadFrom(BinaryData::icecream_circle3_png, BinaryData::icecream_circle3_pngSize);
        _sprinkleImage = 
            juce::ImageFileFormat::loadFrom(BinaryData::icecream_sprinkle3_png, BinaryData::icecream_sprinkle3_pngSize);

        break;
    }
    default:
    {
        _flavorName = "You fucked up";
        break;
    }
    }
    _nameLabel.setText(_flavorName, juce::dontSendNotification);

    _gainSlider.setTextValueSuffix("dB");
    //_gainSlider.onValueChange = [idx, &slider, this] { _flavorLevels[idx] = juce::Decibels::decibelsToGain((float)slider.getValue()); };
    _gainSlider.setRange(-100.0f, 0.0f);
    _gainSlider.setValue(-100.0f, juce::dontSendNotification);
}


void FlavorKnob::paint(juce::Graphics& g)
{
    switch (_flavorCode)
    {
    case Vanilla:
    {
        g.drawImageAt(_iceCreamImage, 200, 200);
        g.drawImageAt(_sprinkleImage, 200, 200);
    }
    case Strawberry:
    {
    }
    case Chocolate:
    {
    }
    default:
    {
        // TODO: Paint a PATO.
    }
    }
}

void FlavorKnob::resized()
{
    switch (_flavorCode)
    {
    case Vanilla:
    {
        setBounds(256, 360, 150, 150);
    }
    case Strawberry:
    {
    }
    case Chocolate:
    {
    }
    default:
    {
        // TODO: Paint a PATO.
    }
    }
    
}

NeopolitanAudioProcessorEditor::NeopolitanAudioProcessorEditor(NeopolitanAudioProcessor& p)
    : AudioProcessorEditor (&p),audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1024, 720);

    for (auto& knob : _flavorKnobs)
    {
        addAndMakeVisible(knob);
    }
    _flavorKnobs[Vanilla].initialize(Vanilla);
    _flavorKnobs[Strawberry].initialize(Strawberry);
    _flavorKnobs[Chocolate].initialize(Chocolate);

}

NeopolitanAudioProcessorEditor::~NeopolitanAudioProcessorEditor()
{
}

//==============================================================================
void NeopolitanAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // Fill it with this color: #66ffcc.  Below numbers are R,G,B.
    g.fillAll(juce::Colour{152, 184, 174});

    // This sets the text.
    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

    // Draw the flavor knobs
    for (auto& knob : _flavorKnobs)
    {
        knob.paint(g);
    }
}

void NeopolitanAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    for (auto& knob : _flavorKnobs)
    {
        knob.resized();
    }
}

