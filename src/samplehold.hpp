#ifndef SAMPLEHOLD_H
#define SAMPLEHOLD_H

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class SampleHold: public Plugin<SampleHold>
{
	private:
		float triggerLevel, sample;bool gate;
	public:
		SampleHold(double rate);
		void run(uint32_t nframes);
};

#endif
