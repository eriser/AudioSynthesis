//
//  Enumerations.h
//  AudioSynthesis
//
//  Created by Steven Novak on 3/24/17.
//  Copyright © 2017 Steven Novak. All rights reserved.
//

#ifndef Enumerations_h
#define Enumerations_h

namespace AudioSynthesis
{
    enum class WindowType {TRIANGLE, PARZEN, WELCH, HANN, HAMMING, BLACKMAN, NUTTALL, BLACKMAN_NUTTALL, BLACKMAN_HARRIS, FLATTOP, GAUSSIAN, CONFINED_GAUSSIAN, NORMAL, TUKEY, PLANCK_TAPER, SLEPIAN, KAISER, DOLPH_CHEBYSHEV, ULTRASPHERICAL, POISSON, BARTLETT_HANN, PLANCK_BESSEL, HANN_POISSON, LANCZOS};

    enum class EnvelopeState {IDLE, DELAY, ATTACK, HOLD, DECAY, LOOP, SUSTAIN, RELEASE};
    
    enum class DelayDirection {FORWARD, REVERSE};
}


#endif /* Enumerations_h */
