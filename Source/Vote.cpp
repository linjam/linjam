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

#include "Vote.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Vote::Vote ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    bpiLabel.reset (new juce::Label ("bpiLabel",
                                     TRANS ("000")));
    addAndMakeVisible (bpiLabel.get());
    bpiLabel->setTooltip (TRANS ("Vote to change the number of beats per jam interval (BPI)"));
    bpiLabel->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 16.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    bpiLabel->setJustificationType (juce::Justification::centredTop);
    bpiLabel->setEditable (true, true, true);
    bpiLabel->setColour (juce::Label::backgroundColourId, juce::Colour (0x00000000));
    bpiLabel->setColour (juce::Label::textColourId, juce::Colours::azure);
    bpiLabel->setColour (juce::Label::outlineColourId, juce::Colour (0x00000000));
    bpiLabel->setColour (juce::TextEditor::textColourId, juce::Colours::grey);
    bpiLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    bpiLabel->setColour (juce::TextEditor::highlightColourId, juce::Colour (0xffbbbbff));
    bpiLabel->addListener (this);

    bpiLabel->setBounds (46, -1, 36, 16);

    bpmLabel.reset (new juce::Label ("bpmLabel",
                                     TRANS ("000")));
    addAndMakeVisible (bpmLabel.get());
    bpmLabel->setTooltip (TRANS ("Vote to change the number of beats per minute (BPM)"));
    bpmLabel->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 16.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
    bpmLabel->setJustificationType (juce::Justification::centredTop);
    bpmLabel->setEditable (true, true, true);
    bpmLabel->setColour (juce::Label::backgroundColourId, juce::Colour (0x00000000));
    bpmLabel->setColour (juce::Label::textColourId, juce::Colours::azure);
    bpmLabel->setColour (juce::TextEditor::textColourId, juce::Colours::grey);
    bpmLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    bpmLabel->setColour (juce::TextEditor::highlightColourId, juce::Colour (0xffbbbbff));
    bpmLabel->addListener (this);

    bpmLabel->setBounds (106, -1, 36, 16);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (142, 24);


    //[Constructor] You can add your own custom stuff here..

  // hide (translated) BPI/BPM "000" jucer design placeholders
  this->bpiLabel->setVisible(false) ;
  this->bpmLabel->setVisible(false) ;

    //[/Constructor]
}

Vote::~Vote()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    bpiLabel = nullptr;
    bpmLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Vote::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        int x = 0, y = 1, width = 42, height = 12;
        juce::String text (TRANS ("Vote:"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 16.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 46.0f, y = 0.0f, width = 36.0f, height = 16.0f;
        juce::Colour fillColour = juce::Colours::green;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 86, y = 1, width = 16, height = 12;
        juce::String text (TRANS ("@"));
        juce::Colour fillColour = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 16.00f, juce::Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 106.0f, y = 0.0f, width = 36.0f, height = 16.0f;
        juce::Colour fillColour = juce::Colours::green;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Vote::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Vote::labelTextChanged (juce::Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == bpiLabel.get())
    {
        //[UserLabelCode_bpiLabel] -- add your label text handling code here..

      vote("bpi" , this->bpiLabel.get()) ;

        //[/UserLabelCode_bpiLabel]
    }
    else if (labelThatHasChanged == bpmLabel.get())
    {
        //[UserLabelCode_bpmLabel] -- add your label text handling code here..

      vote("bpm" , this->bpmLabel.get()) ;

        //[/UserLabelCode_bpmLabel]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

/* Vote private instance methods */

void Vote::setBpi(uint8 bpi , bool should_cancel_vote)
{
  if (this->isVoting           && ! should_cancel_vote) return ;
  if (this->voteBpiPending > 0 && ! should_cancel_vote) return ;

  this->voteBpiPending = 0 ;

  this->bpiLabel->setVisible(true) ;
  this->bpiLabel->setText(String(bpi) , juce::dontSendNotification) ;
  this->bpiLabel->setColour(Label::textColourId , Colour(0xFFFFFFFF)) ;
}

void Vote::setBpm(uint8 bpm , bool should_cancel_vote)
{
  if (this->isVoting           && ! should_cancel_vote) return ;
  if (this->voteBpmPending > 0 && ! should_cancel_vote) return ;

  this->voteBpmPending = 0 ;

  this->bpmLabel->setVisible(true) ;
  this->bpmLabel->setText(String(bpm) , juce::dontSendNotification) ;
  this->bpmLabel->setColour(Label::textColourId , Colour(0xFFFFFFFF)) ;
}


/* event handlers */

void Vote::editorShown(Label* vote_label , TextEditor& /*unused*/)
{
  if (vote_label == this->bpiLabel.get() || vote_label == this->bpmLabel.get())
    this->isVoting = true ;
}

void Vote::editorHidden(Label* vote_label , TextEditor& /*unused*/)
{
  if (vote_label == this->bpiLabel.get() || vote_label == this->bpmLabel.get())
    this->isVoting = false ;
}


/* helpers */

void Vote::vote(String vote , Label* vote_label)
{
  bool   is_bpi        = vote_label == this->bpiLabel.get() ;
  bool   is_bpm        = vote_label == this->bpmLabel.get() ;
  String bpi_or_bpm    = vote_label->getText() ;
  bool   is_valid_bpi  = is_bpi                                  &&
                         bpi_or_bpm.containsOnly(CONFIG::DIGITS) &&
                         bpi_or_bpm.getIntValue() >=  2          &&
                         bpi_or_bpm.getIntValue() <= 64           ;
  bool   is_valid_bpm  = is_bpm                                  &&
                         bpi_or_bpm.containsOnly(CONFIG::DIGITS) &&
                         bpi_or_bpm.getIntValue() >=  40         &&
                         bpi_or_bpm.getIntValue() <= 400          ;
  String vote_chat_cmd = CLIENT::CHATMSG_CMD_VOTE + vote + " " + bpi_or_bpm ;

  if (is_valid_bpi || is_valid_bpm)
  {
    if      (is_bpi) this->voteBpiPending = APP::VOTE_TIMEOUT ;
    else if (is_bpm) this->voteBpmPending = APP::VOTE_TIMEOUT ;

    vote_label->setColour(Label::textColourId , Colour(0xFFFFFF00)) ;
    LinJam::SendChat(vote_chat_cmd) ;
  }
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Vote" componentName="" parentClasses="public juce::Component"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="0"
                 snapShown="0" overlayOpacity="0.330" fixedSize="0" initialWidth="142"
                 initialHeight="24">
  <BACKGROUND backgroundColour="0">
    <TEXT pos="0 1 42 12" fill="solid: ffffffff" hasStroke="0" text="Vote:"
          fontname="Default monospaced font" fontsize="16.0" kerning="0.0"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <ROUNDRECT pos="46 0 36 16" cornerSize="10.0" fill="solid: ff008000" hasStroke="0"/>
    <TEXT pos="86 1 16 12" fill="solid: ffffffff" hasStroke="0" text="@"
          fontname="Default monospaced font" fontsize="16.0" kerning="0.0"
          bold="1" italic="0" justification="36" typefaceStyle="Bold"/>
    <ROUNDRECT pos="106 0 36 16" cornerSize="10.0" fill="solid: ff008000" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="bpiLabel" id="82c13353bf4eac9" memberName="bpiLabel" virtualName=""
         explicitFocusOrder="0" pos="46 -1 36 16" tooltip="Vote to change the number of beats per jam interval (BPI)"
         bkgCol="0" textCol="fff0ffff" outlineCol="0" edTextCol="ff808080"
         edBkgCol="0" hiliteCol="ffbbbbff" labelText="000" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="1" fontname="Default monospaced font"
         fontsize="16.0" kerning="0.0" bold="1" italic="0" justification="12"
         typefaceStyle="Bold"/>
  <LABEL name="bpmLabel" id="397cf47096f095ad" memberName="bpmLabel" virtualName=""
         explicitFocusOrder="0" pos="106 -1 36 16" tooltip="Vote to change the number of beats per minute (BPM)"
         bkgCol="0" textCol="fff0ffff" edTextCol="ff808080" edBkgCol="0"
         hiliteCol="ffbbbbff" labelText="000" editableSingleClick="1"
         editableDoubleClick="1" focusDiscardsChanges="1" fontname="Default monospaced font"
         fontsize="16.0" kerning="0.0" bold="1" italic="0" justification="12"
         typefaceStyle="Bold"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

