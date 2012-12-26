#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "synthdata.hpp"
#include "mixer_cv.hpp"

using namespace lvtk;

MixerCV::MixerCV(double rate)
: Plugin<MixerCV>(p_n_ports)
  {
  }

void MixerCV::run(uint32_t nframes)
{
	unsigned int l2;
	float mixgain;

	mixgain = *p(p_gain) * *p(p_volume1);
	for (l2 = 0; l2 < nframes; l2++)
	{
		p(p_out)[l2]  = mixgain * p(p_in1)[l2];
	}

	mixgain = *p(p_gain) * *p(p_volume2);
	for (l2 = 0; l2 < nframes; l2++)
	{
		p(p_out)[l2]  += mixgain * p(p_in2)[l2];
	}

	mixgain = *p(p_gain) * *p(p_volume3);
	for (l2 = 0; l2 < nframes; l2++)
	{
		p(p_out)[l2]  += mixgain * p(p_in3)[l2];
	}

	mixgain = *p(p_gain) * *p(p_volume4);
	for (l2 = 0; l2 < nframes; l2++)
	{
		p(p_out)[l2]  += mixgain * p(p_in4)[l2];
	}
}

static int _ = MixerCV::register_class("http://avwlv2.sourceforge.net/plugins/avw/mixer_cv");

