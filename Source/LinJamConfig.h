/*
  ==============================================================================

    LinJamConfig.h
    Created: 12 Jun 2014 7:05:12am
    Author:  me

  ==============================================================================
*/

#ifndef LINJAMCONFIG_H_INCLUDED
#define LINJAMCONFIG_H_INCLUDED

#include "Constants.h"
#include "Trace.h"

#include "../JuceLibraryCode/JuceHeader.h"


class LinJamConfig
{
public:

  LinJamConfig() ;
  ~LinJamConfig() ;

  ValueTree servers ;
  Value     masterVolume ;
  Value     currentHost ;
  Value     currentLogin ;
  Value     currentPass ;
  Value     currentIsAnonymous ;
  Value     currentIsAgreed ; // TODO: ?? this exists only so OnLicense doesnt block (issue #14)


  void      setServerConfig() ;
  ValueTree getServerConfig(String host) ;
  ValueTree getCurrentServerConfig() ;
  void      setShouldAgree( bool should_agree) ;


private:

  File        configXmlFile ;
  ValueTree   configValueTree ;
  UndoManager configUndoManager ;
  Value       dummyValue ;


  ValueTree sanitizeConfig(ValueTree default_config , ValueTree stored_config) ;
  void      storeConfig() ;
  Value     getConfigValueObj(Identifier node_id , Identifier key) ;
  ValueTree addServerConfig(String host , String login , String pass , bool is_anonymous) ;

void DBGConfigValueType(String val_name , Value a_value) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinJamConfig) ;
} ;

#endif  // LINJAMCONFIG_H_INCLUDED
