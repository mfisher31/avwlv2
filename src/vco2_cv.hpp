#ifndef VCO2_CV_H
#define VCO2_CV_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "synthdata.hpp"
#include "vco2_cv.peg"

using namespace lvtk;

enum WaveFormType
{
	SINUS, TRIANGLE, SAWTOOTH, RECTANGLE, AWAVE_SAW1, AWAVE_SAW2, AWAVE_SAW3
};

class Vco2CV: public Plugin<Vco2CV>
{
	private:
		float freq, phi0, pw0;
		float edge;
		float wave_period;
		float phi;
		float wave_period_2, wave_period_3, Pi2Times, PKonst;
		float vcoExpFMGain, vcoLinFMGain, pwGain;
		int waveForm;
		int harmonic, subharmonic, octave;

		double m_rate;

		SynthData *synthdata;

	public:
		Vco2CV(double rate);
		void run(uint32_t nframes);
};

#endif
