/*
  ==============================================================================

    ClipWDFa.h
    Created: 16 May 2023 3:19:25pm
    Author:  Omar Sanchez

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include <Modules/include/chowdsp_wdf/chowdsp_wdf.h>

namespace wdft = chowdsp::wdft;

class ClipWDFa
{
public:
    ClipWDFa() = default;

    void prepare(double sampleRate)
    {
        C2.prepare((float)sampleRate);
    }

    void reset()
    {
        C2.reset();
    }

    // takes voltage and returns voltage
    inline float processSample(float x)
    {
        Vs.setVoltage(x);

        Vs.incident(S3.reflected());
        auto y = voltage<float>(R5);
        S3.incident(Vs.reflected());

        return y;
    }

private:
    ResistorT<float> Rin{ 1.0f    };
    ResistorT<float> RA { 220.0f  };
    ResistorT<float> R5 { 10000.0f };

    CapacitorT<float> C2{ 1.0e-6f, 48000.0f };

    WDFSeriesT<float, decltype (RA), decltype (R5)> S1{ RA, R5 };
    WDFSeriesT<float, decltype (C2), decltype (S1)> S2{ C2, S1 };
    WDFSeriesT<float, decltype (Rin), decltype (S2)> S3{ Rin, S2 };

    IdealVoltageSourceT<float, decltype (S3)> Vs{ S3 };
};
