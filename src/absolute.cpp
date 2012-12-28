#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "absolute.hpp"

using namespace lvtk;

Absolute::Absolute(double rate)
:Plugin<Absolute>(p_n_ports)
 {
 }

void Absolute::run(uint32_t nframes)
{
	unsigned int l2;
	for (l2 = 0; l2 < nframes; l2++)
	{
		if(p(p_input)[l2] < 0)
		{
			p(p_output)[l2] = p(p_input)[l2] * -1;
		}
		else
		{
			p(p_output)[l2] = p(p_input)[l2];
		}
	}
}

static int _ = Absolute::register_class("http://avwlv2.sourceforge.net/plugins/avw/absolute");

