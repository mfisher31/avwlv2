#ifndef ADVENV_H
#define ADVENV_H

#include "synthdata.hpp"
#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

#define ADVENVELOPE_RESPONSE               256

class AdvEnv: public Plugin<AdvEnv>
{
	private:
		float attack[8], sustain, release[5];
		//float e_noteOff[MAXPOLY], de[MAXPOLY], de_release[MAXPOLY];
		float e_noteOff, de, de_release;
		//Port *port_gate, *port_retrigger, *port_inverse_out, *port_gain_out;

		double m_rate;

	public:
		//float e[MAXPOLY];
		float e;
		float timeScale;
		//bool noteActive[MAXPOLY], gate[MAXPOLY], retrigger[MAXPOLY];
		bool noteActive, gate, retrigger;
		//int noteOnOfs[MAXPOLY];
		int noteOnOfs;
		//int noteOffOfs[MAXPOLY];
		int noteOffOfs;
		float *gateData, *retriggerData;

		AdvEnv(double rate);
		void run(uint32_t nframes);
};

#endif
