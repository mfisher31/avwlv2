#ifndef VCAEXP_H
#define VCAEXP_H

#include "synthdata.hpp"
#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class VcaExp : public Plugin<VcaExp>
{
	float gain1, gain2, in1, in2, out;
	//Port *port_M_gain1, *port_M_in1, *port_M_gain2, *port_M_in2, *port_out;
	SynthData *synthdata;

public:
	VcaExp(double rate);
	void run(uint32_t nframes);
};

#endif
