#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "mixer_2ch_cv.hpp"

using namespace lvtk;

Mixer2ChCV::Mixer2ChCV(double rate)
: Plugin<Mixer2ChCV>(p_n_ports)
  {
  }

void Mixer2ChCV::run(uint32_t nframes)
{
	float mixgain1 = *p(p_gain) * *p(p_volume1);
	float mixgain2 = *p(p_gain) * *p(p_volume2);
	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		p(p_out)[l2]  = mixgain1 * p(p_in1)[l2] + mixgain2 * p(p_in2)[l2];
	}
}

static int _ = Mixer2ChCV::register_class("http://avwlv2.sourceforge.net/plugins/avw/mixer_2ch_cv");

