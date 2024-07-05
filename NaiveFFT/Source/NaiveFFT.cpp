/*
  ==============================================================================

    NaiveFFT.cpp
    Created: 14 Nov 2023 4:24:55pm
    Author:  TaroPie

  ==============================================================================
*/

#include "NaiveFFT.h"

NaiveFFT::NaiveFFT()
{
}

// e.g. 488 -> 9(512)
int NaiveFFT::calculateNextPowerOfTwo(int num)
{
    int power = 0;
    while ((1 << power) < num) {
        power++;
    }
    return power;
}

std::vector<std::complex<float>> NaiveFFT::processFFT(juce::AudioBuffer<float>& audioBuffer, int channel, bool inverse)
{
    int fftOrder = calculateNextPowerOfTwo(audioBuffer.getNumSamples());
    size_t fftSize = static_cast<size_t>(1) << fftOrder;

    std::unique_ptr<juce::dsp::FFT> fft(std::make_unique<juce::dsp::FFT>(fftOrder));

    std::vector<float> vecBuffer(fftSize, 0);
    float* sample = audioBuffer.getWritePointer(channel);
    for (int i = 0; i < audioBuffer.getNumSamples(); ++i)
    {
        vecBuffer[i] = sample[i];
    }

    std::vector<std::complex<float>> input(vecBuffer.begin(), vecBuffer.end());
    std::vector<std::complex<float>> output(input.size());

    fft->perform(input.data(), output.data(), inverse);

    return output;
}

std::vector<std::complex<float>> NaiveFFT::processFFT(std::vector<std::complex<float>>& input, bool inverse)
{
    int fftOrder = calculateNextPowerOfTwo(input.size());
    size_t fftSize = static_cast<size_t>(1) << fftOrder;

    std::unique_ptr<juce::dsp::FFT> fft(std::make_unique<juce::dsp::FFT>(fftOrder));

    std::vector<std::complex<float>> output(input.size());

    fft->perform(input.data(), output.data(), inverse);

    return output;
}

void NaiveFFT::processRealOnlyFFT(juce::AudioBuffer<float>& audioBuffer, bool inverse)
{
    int numSamples = audioBuffer.getNumSamples();
    oriNumSamples = numSamples;

    int fftOrder = calculateNextPowerOfTwo(audioBuffer.getNumSamples());
    size_t fftSize = static_cast<size_t>(1) << fftOrder;

    if (!inverse)
    {
        audioBuffer.setSize(audioBuffer.getNumChannels(), fftSize * 2, true, true);
    }
    else if (inverse && numSamples == fftSize)
    {
        fftOrder -= 1;
	}
	else
    {
        jassertfalse;
    }

    std::unique_ptr<juce::dsp::FFT> fft(std::make_unique<juce::dsp::FFT>(fftOrder));

    for (int channel = 0; channel < audioBuffer.getNumChannels(); ++channel)
    {
        !inverse ? fft->performRealOnlyForwardTransform(audioBuffer.getWritePointer(channel), true)
                 : fft->performRealOnlyInverseTransform(audioBuffer.getWritePointer(channel));
    }
}

void NaiveFFT::processFrequencyOnlyFFT(juce::AudioBuffer<float>& audioBuffer)
{
    int fftOrder = calculateNextPowerOfTwo(audioBuffer.getNumSamples());
    size_t fftSize = static_cast<size_t>(1) << fftOrder;

    audioBuffer.setSize(audioBuffer.getNumChannels(), fftSize * 2, true, true);

    std::unique_ptr<juce::dsp::FFT> fft(std::make_unique<juce::dsp::FFT>(fftOrder));
    juce::dsp::WindowingFunction<float> window(fftSize, juce::dsp::WindowingFunction<float>::hamming);
    window.multiplyWithWindowingTable(audioBuffer.getWritePointer(0), fftSize);

    for (int channel = 0; channel < audioBuffer.getNumChannels(); ++channel)
    {
        fft->performFrequencyOnlyForwardTransform(audioBuffer.getWritePointer(channel));
    }
}

void NaiveFFT::removeImaginaryData(juce::AudioBuffer<float>& audioBuffer, int bufferSize)
{ 
    if (2 * bufferSize > audioBuffer.getNumSamples())
    {
        jassertfalse;
    }
    float* sample = audioBuffer.getWritePointer(0);
    for (size_t i = 0; i < bufferSize; ++i)
    {
        sample[i] = sample[2 * i];
    }
    audioBuffer.setSize(audioBuffer.getNumChannels(), bufferSize, true, true);
}