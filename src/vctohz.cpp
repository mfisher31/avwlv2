#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "synthdata.hpp"
#include "vctohz.hpp"

using namespace LV2;

VcToHz::VcToHz(double rate)
:Plugin<VcToHz>(p_n_ports)
 {
	m_rate = rate;
 }

void VcToHz::run(uint32_t nframes)
{
	unsigned int l2;
	float offset;

	float *inData = p(p_input);
	convMode = floor(*p(p_conversionMode));
	octave = floor(*p(p_octaveOffset));

	offset = octave + 5.0313842;
	if (convMode == 0)
	{
		for (l2 = 0; l2 < nframes; l2++)
		{
			p(p_output)[l2] = exp(M_LN2 * (offset + inData[l2]));
		}
	}
	else if (convMode == 1)
	{
		for (l2 = 0; l2 < nframes; l2++)
		{
			p(p_output)[l2] = 2.0 * exp(M_LN2 * (offset + inData[l2])) / m_rate;
		}
	}
	else if (convMode == 2)
	{
		for (l2 = 0; l2 < nframes; l2++)
		{
			p(p_output)[l2] = exp(M_LN2 * (offset + inData[l2])) / 20000.0;
		}
	}
}

static int _ = VcToHz::register_class("http://avwlv2.sourceforge.net/plugins/avw/vctohz");

