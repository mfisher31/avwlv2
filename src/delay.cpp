#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "lv2plugin.hpp"
#include "synthdata.hpp"
#include "delay.hpp"

using namespace LV2;

Delay::Delay(double rate) :
	Plugin<Delay> (p_n_ports)
{
	m_delay = 0;

	buf = (float *) malloc(MAX_DELAY_FRAMES * sizeof(float));
	memset(buf, 0, MAX_DELAY_FRAMES * sizeof(float));

	read_ofs = 0;
}

Delay::~Delay()
{
	free(buf);
}

void Delay::run(uint32_t nframes)
{
	m_delay = *p(p_delay);

	int ofs, delay_frames;
	unsigned int l2;

	delay_frames = (int) ((float) (MAX_DELAY_FRAMES - 3) * m_delay / 10.0);
	for (l2 = 0; l2 < nframes; l2++)
	{
		buf[read_ofs] =  p(p_input)[l2];
		ofs = read_ofs - delay_frames;
		if (ofs < 0)
		{
			ofs += MAX_DELAY_FRAMES;
		}
		p(p_output)[l2] = buf[ofs];

		read_ofs++;
		if (read_ofs >= MAX_DELAY_FRAMES)
		{
			read_ofs = 0;
		}
	}
}

static int _ = Delay::register_class("http://avwlv2.sourceforge.net/plugins/avw/delay");

