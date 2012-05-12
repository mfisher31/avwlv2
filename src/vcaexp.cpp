#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "lv2plugin/lv2plugin.hpp"
#include "synthdata.hpp"

#include "vcaexp.hpp"

VcaExp::VcaExp(double rate):
Plugin<VcaExp>(p_n_ports)
{
	gain1 = 0;
	gain2 = 0;
	in1 = 1.0;
	in2 = 1.0;
	out = 1.0;

	synthdata = new SynthData(1);

	//configDialog->addSlider(tr("Gain"), gain1, 0, 1);
	//configDialog->addSlider(tr("Gain 1"), gain2, 0, 1);
	//configDialog->addSlider(tr("In 0"), in1, 0, 2);
	//configDialog->addSlider(tr("In 1"), in2, 0, 2);
	//configDialog->addSlider(tr("Output level"), out, 0, 2);
}

void VcaExp::run(uint32_t nframes)
{
	unsigned int l2;
	float  v, g;

	float *gainData1, *gainData2, *inData1, *inData2;

	gain1 = *p(p_gain1);
	gain2 = *p(p_gain2);
	in1 = *p(p_in1);
	in2 = *p(p_in1);
	out = *p(p_outputLevel);


	gainData1 = p(p_gain1Data);		//port_M_gain1->getinputdata ();
	gainData2 = p(p_gain2Data);		//port_M_gain2->getinputdata ();
	inData1 = p(p_in1Data);			//port_M_in1->getinputdata ();
	inData2 = p(p_in2Data);			//port_M_in2->getinputdata ();

	for (l2 = 0; l2 < nframes; l2++)
	{
		v = gain1 + gainData1[l2] + gain2 * gainData2[l2];
		g = (v > 0) ? synthdata->exp_table ((v - 1.0) * 9.21) : 0;  // This gives a range of 80 dB
		p(p_out)[l2] = g * out * (in1 * inData1[l2] + in2 * inData2[l2]);
	}
}

static int _ = VcaExp::register_class("http://avwlv2.sourceforge.net/plugins/avw/vcaexp");
