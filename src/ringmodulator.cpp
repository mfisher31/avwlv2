#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "synthdata.hpp"
#include "ringmodulator.hpp"

using namespace lvtk;

RingModulator::RingModulator(double rate)
:Plugin<RingModulator>(p_n_ports)
 {
	gain=0.5;
 }

void RingModulator::run(uint32_t nframes)
{
	gain = *p(p_gain);
	unsigned int l2;
	for (l2 = 0; l2 < nframes; l2++)
	{
		p(p_output)[l2] = gain * p(p_in1)[l2] * p(p_in2)[l2];
	}
}

static int _ = RingModulator::register_class("http://avwlv2.sourceforge.net/plugins/avw/ringmodulator");

