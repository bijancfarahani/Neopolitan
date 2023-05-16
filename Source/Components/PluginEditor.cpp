/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
namespace Neopolitan
{

NeopolitanAudioProcessorEditor::NeopolitanAudioProcessorEditor(
   NeopolitanAudioProcessor& p)
   : AudioProcessorEditor(&p), audioProcessor(p), _mainScene()
{
   // Make sure that before the constructor has finished, you've set the
   // editor's size to whatever you need it to be.
   setSize(1024, 720);

   _mainScene.setSize(getWidth(), getHeight());
   addAndMakeVisible(_mainScene);

   addAndMakeVisible(gainSlider);
       gainSlider.setSliderStyle(Juce::Slider::StiderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(Juce::Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(-48.0, 0.0);
    gainSlider.setValue(-1.0);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
}

NeopolitanAudioProcessorEditor::~NeopolitanAudioProcessorEditor() {}

//==============================================================================

void NeopolitanAudioProcessorEditor::resized() 
{
     gainSlider.setBounds(getLocalBounds());
} 

void NeopolitanAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
   if (slider == &gainSlider)
   {
    audioProcessor.rawVlume = pow (10, gainSlider.getValue() / 20);
   }

}






}