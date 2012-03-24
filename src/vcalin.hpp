#ifndef VCALIN_H
#define VCALIN_H

#include "synthdata.hpp"
#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class VcaLin: public Plugin<VcaLin>
{
	private:
		float gain1, gain2, in1, in2, out;
		//Port *port_M_gain1, *port_M_in1, *port_M_gain2, *port_M_in2, *port_out;

	public:
		VcaLin(double rate);
		void run(uint32_t nframes);
};

#endif
