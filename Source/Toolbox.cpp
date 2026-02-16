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


//[Headers] You can add your own extra header files here...

#include "LinJam.h"

//[/Headers]

#include "Toolbox.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Toolbox::Toolbox ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    topicLabel.reset (new juce::Label ("topicLabel",
                                       juce::String()));
    addAndMakeVisible (topicLabel.get());
    topicLabel->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 15.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    topicLabel->setJustificationType (juce::Justification::centredTop);
    topicLabel->setEditable (true, true, true);
    topicLabel->setColour (juce::Label::backgroundColourId, juce::Colour (0x00000000));
    topicLabel->setColour (juce::Label::textColourId, juce::Colours::grey);
    topicLabel->setColour (juce::TextEditor::textColourId, juce::Colours::grey);
    topicLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    topicLabel->setColour (juce::TextEditor::highlightColourId, juce::Colour (0xffbbbbff));
    topicLabel->addListener (this);

    vote.reset (new Vote());
    addAndMakeVisible (vote.get());
    vote->setName ("vote");


    //[UserPreSize]
    //[/UserPreSize]


    setSize (622, 24);


    //[Constructor] You can add your own custom stuff here..

  this->prevTopicText = String() ;
  Font topic_font     = this->topicLabel->getFont().withHeight(GUI::TOPIC_FONT_H) ;

  // set text editor font and colors
  this->topicLabel->setFont(topic_font) ;
  this->topicLabel->setColour(Label::backgroundColourId           , GUI::CHAT_TEXT_BG_COLOR ) ;
  this->topicLabel->setColour(Label::textColourId                 , GUI::TOPIC_TEXT_COLOR   ) ;
  // this->topicLabel->setColour(Label::outlineColourId              , Colour(0xff0000ff));//GUI::CHAT_OUTLINE_COLOR ) ;
  this->topicLabel->setColour(CaretComponent::caretColourId       , GUI::TEXT_CARET_COLOR   ) ;
  this->topicLabel->setColour(TextEditor::textColourId            , GUI::CHAT_TEXT_COLOR    ) ;
  this->topicLabel->setColour(TextEditor::highlightColourId       , GUI::TEXT_HILITEBG_COLOR) ;
  this->topicLabel->setColour(TextEditor::highlightedTextColourId , GUI::TEXT_HILITE_COLOR  ) ;
  this->topicLabel->setColour(TextEditor::outlineColourId         , GUI::CHAT_OUTLINE_COLOR ) ;
  this->topicLabel->setColour(TextEditor::focusedOutlineColourId  , GUI::CHAT_FOCUS_COLOR   ) ;
  this->topicLabel->setColour(TextEditor::shadowColourId          , GUI::CHAT_SHADOW_COLOR  ) ;
  this->topicLabel->setColour(TextEditor::backgroundColourId      , GUI::CHAT_TEXT_BG_COLOR ) ;

    //[/Constructor]
}

Toolbox::~Toolbox()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    topicLabel = nullptr;
    vote = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Toolbox::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    {
        float x = 0.0f, y = 0.0f, width = static_cast<float> (getWidth() - 0), height = 24.0f;
        juce::Colour fillColour = juce::Colour (0xff101010);
        juce::Colour strokeColour = juce::Colours::grey;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    {
        float x = 4.0f, y = 4.0f, width = static_cast<float> (getWidth() - 162), height = 16.0f;
        juce::Colour fillColour = juce::Colour (0xff101010);
        juce::Colour strokeColour = juce::Colours::grey;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 1.000f);
    }

    //[UserPaint] Add your own custom painting code here..

/* from Chat,cpp (prev parent of topicLabel)
 * TODO: decide whether or not JUCER_DRAW_CHAT_PAINT and JUCER_DRAW_CHAT_RESIZED

  // topic border and fill
  g.setColour(topic_background_color) ;
  g.fillRoundedRectangle(GUI::TOPIC_BORDER_X , GUI::TOPIC_BORDER_Y , topic_border_w ,
                         GUI::TOPIC_BORDER_H , GUI::BORDER_RADIUS                   ) ;
  g.setColour(topic_border_color) ;
  g.drawRoundedRectangle(GUI::TOPIC_BORDER_X , GUI::TOPIC_BORDER_Y , topic_border_w ,
                         GUI::TOPIC_BORDER_H , GUI::BORDER_RADIUS  , GUI::BORDER_PX ) ;
*/
    //[/UserPaint]
}

void Toolbox::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    topicLabel->setBounds (4, 4, getWidth() - 162, 16);
    vote->setBounds (getWidth() - 4 - 142, 4, 142, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Toolbox::labelTextChanged (juce::Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == topicLabel.get())
    {
        //[UserLabelCode_topicLabel] -- add your label text handling code here..

      // post topic change message to server but defer updating GUI until ack
      LinJam::SendChat(CLIENT::CHATMSG_CMD_TOPIC + this->topicLabel->getText()) ;
      this->topicLabel->setText(this->prevTopicText , juce::dontSendNotification) ;

        //[/UserLabelCode_topicLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void Toolbox::setTopic(String topic_text)
{
  this->topicLabel->setText(topic_text , juce::dontSendNotification) ;
  this->prevTopicText = topic_text ;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Toolbox" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="0" snapShown="0" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="622" initialHeight="24">
  <BACKGROUND backgroundColour="ff323e44">
    <ROUNDRECT pos="0 0 0M 24" cornerSize="10.0" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff808080"/>
    <ROUNDRECT pos="4 4 162M 16" cornerSize="10.0" fill="solid: ff101010" hasStroke="1"
               stroke="1, mitered, butt" strokeColour="solid: ff808080"/>
  </BACKGROUND>
  <LABEL name="topicLabel" id="3544f00ed11410e1" memberName="topicLabel"
         virtualName="" explicitFocusOrder="0" pos="4 4 162M 16" bkgCol="0"
         textCol="ff808080" edTextCol="ff808080" edBkgCol="0" hiliteCol="ffbbbbff"
         labelText="" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="1" fontname="Default monospaced font" fontsize="15.0"
         kerning="0.0" bold="1" italic="0" justification="12" typefaceStyle="Bold"/>
  <GENERICCOMPONENT name="vote" id="c08b5ed3cabd7fcf" memberName="vote" virtualName=""
                    explicitFocusOrder="0" pos="4Rr 4 142 24" class="Vote" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

