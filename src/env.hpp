#ifndef ENV_H
#define ENV_H

#include "synthdata.hpp"
#include "lv2plugin.hpp"

using namespace LV2;

#define ENVELOPE_RESPONSE               256

class Env: public Plugin<Env>
{
	private:
		float delay, attack, hold, decay, sustain, release;
		float e_noteOff, de;
		//Port *port_gate, *port_retrigger, *port_inverse_out, *port_gain_out;

		double m_rate;

	public:
		float e;
		float timeScale;bool gate, retrigger;
		int noteOnOfs;
		float *gateData, *retriggerData;

		Env(double rate);
		void run(uint32_t nframes);
};

#endif
