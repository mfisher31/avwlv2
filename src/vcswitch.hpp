#ifndef VCSWITCH_H
#define VCSWITCH_H

#include "lv2plugin.hpp"

using namespace LV2;

class VCSwitch: public Plugin<VCSwitch>
{
	private:
		float switchlevel;
	public:
		VCSwitch(double rate);
		void run(uint32_t nframes);
};

#endif
