/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:               naive_modules
  vendor:           Naive Instruments
  version:          0.0.1
  name:             233
  description:      233

  dependencies:     juce_audio_basics
  OSXFrameworks:    Accelerate
  iOSFrameworks:    Accelerate

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/

#pragma once
#define NAIVE_MODULES_H_INCLUDED

#include <juce_audio_basics/juce_audio_basics.h>

/** Naive DSP Headers*/
#include "naive_dsp/PeakFilter.h"
