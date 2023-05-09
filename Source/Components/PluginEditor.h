/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <array>

#include <JuceHeader.h>

#include "PluginProcessor.h"

#include "FlavorKnob.h"
#include "MainScene.h"
#include "NeopolitanConstants.h"
//==============================================================================
/**
 */
namespace Neopolitan
{

struct AttachedSlider
{
    using Slider = juce::Slider;
    using Attachment = juce::SliderParameterAttachment;
	using Component = juce::Component;

    AttachedSlider(NeopolitanAudioProcessor& processor, param::PID pID) :
        slider(),
        attachment(*processor.Params()[static_cast<int>(pID)], slider, nullptr)
    {
		slider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    }

    Slider slider;
    Attachment attachment;
};
class NeopolitanAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
   NeopolitanAudioProcessorEditor(NeopolitanAudioProcessor&);
   ~NeopolitanAudioProcessorEditor() override;

   //==============================================================================
   void paint(juce::Graphics& g) override { _mainScene.paint(g); }
   void resized() override { _mainScene.resized();
       auto w = static_cast<float>(getWidth());
	auto h = static_cast<float>(getHeight());

    auto x = 0.f;
    auto y = 0.f;
    auto sliderWidth = w / static_cast<float>(sliders.size());
    for (auto i = 0; i < sliders.size(); ++i)
    {
        sliders[i].slider.setBounds(juce::Rectangle<float>(x, y, sliderWidth, h).toNearestInt());
		x += sliderWidth;
    } }

private:
   // This reference is provided as a quick way for your editor to
   // access the processor object that created it.
   NeopolitanAudioProcessor& audioProcessor;
   MainScene                 _mainScene;
   std::array<Neopolitan::AttachedSlider, 2> sliders;

   JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(
      NeopolitanAudioProcessorEditor)
};
}