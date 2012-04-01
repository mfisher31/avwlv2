#ifndef RINGMODULATOR_H
#define RINGMODULATOR_H

#include "lv2plugin.hpp"

using namespace LV2;

class RingModulator: public Plugin<RingModulator>
{
	private:
		float gain;
	public:
		RingModulator(double rate);
		void run(uint32_t nframes);
};

#endif
