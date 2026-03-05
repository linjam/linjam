/*\
|*|  Copyright 2014,2015,2020,2026 bill-auger <bill-auger@programmer.net>
|*|
|*|  This file is part of the LinJam program.
|*|
|*|  LinJam is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  LinJam is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with LinJam.  If not, see <http://www.gnu.org/licenses/>.
\*/


#pragma once

//[Headers]     -- You can add your own extra header files here --

#include "JuceHeader.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
  instances of Channel represent individual mixer channel slices
  they are contained within a Channels group
                                                                    //[/Comments]
*/
class Channel  : public Component,
                 public Button::Listener,
                 public Value::Listener,
                 public juce::Slider::Listener,
                 public juce::Label::Listener
{
public:
    //==============================================================================
    Channel (ValueTree channel_store);
    ~Channel() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

#if DEBUG
friend class Channels ;
#endif // DEBUG

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void labelTextChanged (juce::Label* labelThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

  Value channelName ;
  Value stereoStatus ;
  Value vuLeft ;
  Value vuRight ;
  Value isXmit ;


  void buttonClicked(Button* a_button) override ;
  void valueChanged( Value& a_value)   override ;

  void updateVU  (Slider* a_vu_slider , Label* a_vu_label , Value vu_var) ;
  void setConfig (Identifier a_key , var a_value) ;
  void refreshGui() ;

protected:

  ValueTree channelStore ;

  void setTickColor(Button* a_button) ;
  bool handleButtonClicked(Button* a_button) ;
  void setStereoState() ;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ToggleButton> xmitButton;
    std::unique_ptr<juce::ToggleButton> muteButton;
    std::unique_ptr<juce::ToggleButton> soloButton;
    std::unique_ptr<juce::TextButton> removeButton;
    std::unique_ptr<juce::TextButton> configButton;
    std::unique_ptr<juce::Slider> panSlider;
    std::unique_ptr<juce::Slider> gainSlider;
    std::unique_ptr<juce::Label> nameLabel;
    std::unique_ptr<juce::Label> stereoLabel;
    std::unique_ptr<juce::Slider> vuLeftSlider;
    std::unique_ptr<juce::Slider> vuRightSlider;
    std::unique_ptr<juce::Label> vuLeftLabel;
    std::unique_ptr<juce::Label> vuRightLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Channel)
};

//[EndFile] You can add extra defines here...

class MasterChannel : public Channel
{
  friend class MasterChannels ;

  MasterChannel(ValueTree channel_store) ;
} ;

class LocalChannel  : public Channel
{
  friend class LocalChannels ;

  LocalChannel(ValueTree channel_store) ;

  void buttonClicked(Button* a_button) ;
} ;

class RemoteChannel : public Channel
{
  friend class RemoteChannels ;

  RemoteChannel(ValueTree channel_store) ;
} ;

//[/EndFile]

