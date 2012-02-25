#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <lv2-c++-tools/lv2plugin.hpp>

#include "synthdata.hpp"
#include "inv.hpp"
#include "inv.peg"

using namespace LV2;

Inv::Inv(double rate)
:Plugin<Inv>(p_n_ports)
 {
 }

void Inv::run(uint32_t nframes)
{
	unsigned int l2;
	for (l2 = 0; l2 < nframes; l2++)
	{
		p(p_output)[l2] = p(p_input)[l2] * -1;
	}
}

static int _ = Inv::register_class("http://lv2plug.in/plugins/avw/inv");
