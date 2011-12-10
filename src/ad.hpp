#ifndef AD_H
#define AD_H

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class Ad : public Plugin<Ad>
{
private:
	float detune_a, detune_c;
	float drift_a[MAX_ANALOGUE_DRIVER_OUT],	drift_c[MAX_ANALOGUE_DRIVER_OUT];
	int detuneCount, driftCount, voice[2];
	double m_rate;
	SynthData *synthdata;

public:
	Ad(double rate);
	void run(uint32_t nframes);
};

#endif
