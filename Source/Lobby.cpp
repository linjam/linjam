/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.12

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "Lobby.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Lobby::Lobby (ValueTree login_store, ValueTree servers_store)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    setName ("Lobby");
    login.reset (new Login (login_store , servers_store));
    addAndMakeVisible (login.get());
    login->setName ("login");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (622, 442);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Lobby::~Lobby()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    login = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Lobby::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Lobby::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    login->setBounds (8, 8, getWidth() - 8, getHeight() - 8);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

bool Lobby::quickLogin(String host) { return this->login->quickLogin(host) ; }

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="Lobby" componentName="Lobby"
                 parentClasses="public juce::Component" constructorParams="ValueTree login_store, ValueTree servers_store"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="622" initialHeight="442">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GENERICCOMPONENT name="login" id="cc229b476f003b83" memberName="login" virtualName=""
                    explicitFocusOrder="0" pos="8 8 8M 8M" class="Login" params="login_store , servers_store"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

