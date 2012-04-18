#ifndef VCO2_H
#define VCO2_H

#include "synthdata.hpp"
#include "lv2plugin.hpp"

using namespace LV2;

enum WaveFormType
{
	SINUS, TRIANGLE, SAWTOOTH, RECTANGLE, AWAVE_SAW, AWAVE_SAW2, AWAVE_SAW3
};

class Vco2: public Plugin<Vco2>
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
		//float *freqData;
		//float *pwData;
		//float *expFMData;
		//float *linFMData;

		Vco2(double rate);
		void run(uint32_t nframes);
};

#endif
