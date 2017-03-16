//
//  Grain.cpp
//  AudioSynthesis
//
//  Created by Steven Novak on 3/15/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#include "Grain.hpp"
#include <cmath>

namespace AudioSynthesis
{
    #pragma mark Constructors
    // -------------------------------------------------- Constructors
    Grain::Grain(WaveFile * & Buffer)
    {
        buffer = Buffer;
        bufferSize = buffer->GetTotalByteSize() * 8 / Buffer->GetSampleSize();
        channelNum = buffer->GetNumChannels();
        sampleRate = Buffer->GetSampleRate();
        grainVelocity = sampleRate;
        SetGrainSize(512);
        frame1 = 0;
        frame2 = 0;
        inc = 1;
    }
    

    #pragma mark Public Methods
    // -------------------------------------------------- Public Methods
    float Grain::tick()
    {
        pos+= inc;
        if(frame1 < 0 )
            frame1 = frame1;
        
        if(pos > grainSize - 1)
        {
            pos = 0;
            frame2 = frame1;
            frame1 += grainVelocity * grainSize;
            if(frame1 > bufferSize)
                frame1 -= bufferSize;
            else if(frame1 < 0)
                frame1 += bufferSize;
        }
        else if(pos < 0)
        {
            pos = grainSize;
            frame2 = frame1;
            frame1 += grainVelocity * grainSize;
            if(frame1 > bufferSize)
                frame1 -= bufferSize;
            else if(frame1 < 0)
                frame1 =+ bufferSize;
        }
        
        if(pos + frame1 > bufferSize)
        {
            frame1 -= bufferSize;
        }
        else if(pos + frame1 < 0)
        {
            frame1 += bufferSize;
        }
        
        
        float temp = buffer->GetSampleFloat(frame1 + pos) * window[pos];
        
        
        return temp;
    }
    
    
    #pragma mark Accessors
    // -------------------------------------------------- Acsessors
    void Grain::SetGrainSize(int FramesPerSecond)
    {
        grainSize = FramesPerSecond;
        offset = pos;
        window.resize(FramesPerSecond);
        for(int i=0; i<FramesPerSecond; i++)
        {
            float I = (float)i;
            float mid = FramesPerSecond / 2.0;
            float temp = (((I - mid) / mid) * ((I - mid) / mid)) * -1.0 + 1.0; // Quadratic
            //float temp = tanh((((I - mid) / mid) * ((I - mid) / mid)) * -1.0 + 1.0); // Quadratic + tanh
            window[i] = temp;
        }
    }
    
    void Grain::SetGrainVelocity(float samplesPerSecond)
    {
        grainVelocity = samplesPerSecond;
    }
    
    void Grain::SetGrainCount(int NumberOfGrains)
    {
        numGrains = NumberOfGrains;
    }
    
    void Grain::SetSampleVelocity(int SampleVelocity)
    {
        inc = SampleVelocity;
    }
    
    void Grain::SetStart(float Position)
    {
        pos = (int) (Position * buffer->GetTotalSampleSize());
    }
    
    #pragma mark Private Methods
    // -------------------------------------------------- Private Methods
    
    

    
} // end AudioSynthesis namespace
