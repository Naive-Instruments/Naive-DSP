/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NaiveFFT.h"
#include "WavHandler.h"

//==============================================================================
int main (int argc, char* argv[])
{
    NaiveFFT naiveFFT;
    WavHandler wavHandler;

    //wavHandler.readWav(BinaryData::sine_wav, BinaryData::sine_wavSize);

    const int numSamples = 4800;
    const int numChannels = 1;

    juce::AudioBuffer<float> sineBuffer(numChannels, numSamples);
    sineBuffer.clear();

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = sineBuffer.getWritePointer(channel);
        for (int sample = 0; sample < numSamples; ++sample)
        {
            channelData[sample] = std::sin(2.0 * juce::MathConstants<float>::pi * 440.0 * sample / 48000);
        }
    }

    //juce::AudioBuffer<float> audioBuffer(wavHandler.getWavAudioBuffer());

    std::vector<std::complex<float>> sineFFT = naiveFFT.processFFT(sineBuffer, 0, false);
    std::vector<std::complex<float>> sineIFFT = naiveFFT.processFFT(sineFFT, true);

    // 创建一个audio buffer，用于存储IFFT的结果，只需要实部
    juce::AudioBuffer<float> sineIFFTBuffer(1, numSamples);
    sineIFFTBuffer.clear();
    float* channelData = sineIFFTBuffer.getWritePointer(0);
    for (int sample = 0; sample < numSamples; ++sample)
    {
		channelData[sample] = sineIFFT[sample].real();
	}
    wavHandler.writeWav(sineBuffer, "D:\\Github\\TFSpatialAudio\\IRProcess\\sineIFFT.wav");
    
    //wavHandler.writeWav(sineBuffer, "D:\\Github\\TFSpatialAudio\\IRProcess\\sine.wav");

    //naiveFFT.processRealOnlyFFT(sineBuffer, false);
    //wavHandler.writeWav(sineBuffer, "D:\\Github\\TFSpatialAudio\\IRProcess\\sineFFT.wav");

    //naiveFFT.processRealOnlyFFT(sineBuffer, true);
    //sineBuffer.setSize(1, numSamples, true, true);
    //wavHandler.writeWav(sineBuffer, "D:\\Github\\TFSpatialAudio\\IRProcess\\sineIFFT.wav");

    
    //naiveFFT.processFrequencyOnlyFFT(sineBuffer);
    //wavHandler.writeWav(sineBuffer, "D:\\Github\\TFSpatialAudio\\IRProcess\\sineFreq.wav");

    return 0;
}
