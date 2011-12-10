#ifndef MIXER_H
#define MIXER_H

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

//#define MAX_MIX_IN                       16

class Mixer : public Plugin<Mixer>
{
	// QList<Port*> in_port_list;
	// Port *port_out;
	//float gain;
	//float mixer_gain[MAX_MIX_IN];

public:
	//int in_channels;
	Mixer(double rate);
	void run(uint32_t nframes);
};

#endif
