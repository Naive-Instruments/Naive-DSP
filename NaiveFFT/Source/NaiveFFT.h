/*
  ==============================================================================

    NaiveFFT.h
    Created: 14 Nov 2023 4:24:55pm
    Author:  TaroPie

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class NaiveFFT
{
public:
    NaiveFFT();

    int calculateNextPowerOfTwo(int num);

    std::vector<std::complex<float>> processFFT(juce::AudioBuffer<float>& audioBuffer, int channel, bool inverse);
    std::vector<std::complex<float>> processFFT(std::vector<std::complex<float>>& input, bool inverse);

    void processRealOnlyFFT(juce::AudioBuffer<float>& audioBuffer, bool inverse);
    void processFrequencyOnlyFFT(juce::AudioBuffer<float>& audioBuffer);

    void removeImaginaryData(juce::AudioBuffer<float>& audioBuffer, int bufferSize);

private:
    int oriNumSamples = 0;
};
