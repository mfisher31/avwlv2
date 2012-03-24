#ifndef SLEW_H
#define SLEW_H

#include "synthdata.hpp"
#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class Slew: public Plugin<Slew>
{
	private:
		//Port *port_M_in, *port_out;
		//float timeUp, timeDown;
		float lastData;
		double m_rate;

		//public:
		float *inData;

	public:
		Slew(double rate);
		void run(uint32_t nframes);
};

#endif
