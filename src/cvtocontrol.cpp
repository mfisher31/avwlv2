#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <lvtk-1/lvtk/plugin.hpp>

#include "cvtocontrol.hpp"

using namespace lvtk;

CVToControl::CVToControl(double rate)
:Plugin<CVToControl>(p_n_ports)
 {
 }

void CVToControl::run(uint32_t nframes)
{
	float p_total = 0;
	for (unsigned int l2 = 0; l2 < nframes; l2++)
	{
		p_total += p(p_input)[l2];
	}

	*p(p_output) = p_total/nframes;
}

static int _ = CVToControl::register_class("http://avwlv2.sourceforge.net/plugins/avw/cvtocontrol");

