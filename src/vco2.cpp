#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "lv2plugin.hpp"
#include "synthdata.hpp"

#include "vco2.hpp"
#include "vco2.peg"

Vco2::Vco2(double rate) :
	Plugin<Vco2> (p_n_ports)
{
	synthdata = new SynthData(1);

	wave_period = (float) WAVE_PERIOD;
	wave_period_2 = wave_period * 0.5f;
	wave_period_3 = wave_period / 3.0;
	Pi2Times = (2.0f * M_PI);
	PKonst = wave_period / Pi2Times;

	freq = 0;
	vcoExpFMGain = 0;
	vcoLinFMGain = 0;
	pwGain = 0;
	phi0 = 0;
	harmonic = 1;
	subharmonic = 1;
	octave = 3;
	edge = 0.95;
	phi = 0;
	pw0 = 0.5;
	waveForm = SINUS;

	m_rate = rate;

	/*
	 cv.in_index = 1;
	 cv.in_off -= cv.step;
	 port_M_freq = new Port(tr("Freq"), PORT_IN, 1, this);
	 port_M_exp = new Port(tr("Exp. FM"), PORT_IN, 2, this);
	 port_M_lin = new Port(tr("Lin. FM"), PORT_IN, 3, this);
	 port_M_pw = new Port(tr("PW"), PORT_IN, 4, this);

	 cv.out_off = 115;
	 port_sine = new Port(tr("Out"), PORT_OUT, 0, this);

	 port_tri = new Port("Triangle", PORT_OUT, 1, this, synthdata);
	 port_saw = new Port("Saw", PORT_OUT, 2, this, synthdata);
	 port_rect = new Port("Rectangle", PORT_OUT, 3, this, synthdata);
	 port_aux = new Port("Aux", PORT_OUT, 4, this, synthdata);

	 configDialog->initTabWidget();
	 QVBoxLayout *freqTab = configDialog->addVBoxTab(tr("Frequency"));
	 QStringList waveFormNames;
	 waveFormNames << tr("Sine");
	 waveFormNames << tr("Triangle");
	 waveFormNames << tr("Sawtooth");
	 waveFormNames << tr("Rectangle");
	 waveFormNames << tr("Aux Saw");
	 waveFormNames << tr("Aux Saw 1");
	 waveFormNames << tr("Aux Saw 2");
	 configDialog->addComboBox(tr("Wave Form"), waveForm, waveFormNames, freqTab);
	 configDialog->addIntSlider(tr("Octave"), octave, 0, 6, freqTab);
	 configDialog->addSlider(tr("Tune"), freq, 0, 1, false, freqTab);
	 configDialog->addIntSlider(tr("Harmonic"), harmonic, 1, 16, freqTab);
	 configDialog->addIntSlider(tr("Subharmonic"), subharmonic, 1, 16, freqTab);

	 QVBoxLayout *pulseTab = configDialog->addVBoxTab(tr("Pulse Width / Phase"));
	 configDialog->addSlider(tr("PW"), pw0, 0.1, 0.9, false, pulseTab);
	 configDialog->addSlider(tr("PW Gain"), pwGain, 0, 1, false, pulseTab);
	 configDialog->addSlider(tr("Phi0"), phi0, 0, 6.283, false, pulseTab);

	 QVBoxLayout *modulationTab = configDialog->addVBoxTab(
	 tr("Modulation / Aux Waveform"));
	 configDialog->addSlider(tr("Exp. FM Gain"), vcoExpFMGain, 0, 10,
	 false, modulationTab);
	 configDialog->addSlider(tr("Lin. FM Gain"), vcoLinFMGain, 0, 10,
	 false, modulationTab);
	 */
}

void Vco2::run(uint32_t nframes)
{
	unsigned int l2;
	unsigned phint;
	float dphi, phi1, phi_const, pw, d, dd, dsaw, half_wave, third_wave;
	float freq_const, freq_tune, gain_linfm, pw_low, pw_high;

	waveForm = floor(*p(p_waveForm));
	octave = floor(*p(p_octave));
	freq = *p(p_tune);
	harmonic = *p(p_harmonic);
	subharmonic = *p(p_subharmonic);
	pw0 = *p(p_pw0);
	pwGain = *p(p_pwGain);
	phi0 = *p(p_phi0);
	vcoExpFMGain = *p(p_expFMGain);
	vcoLinFMGain = *p(p_linFMGain);

	edge = 0.01f + 1.8f * synthdata->edge;

	freqData = p(p_freq); //port_M_freq->getinputdata();
	expFMData = p(p_expFM); //port_M_exp->getinputdata();
	linFMData = p(p_linFM); //port_M_lin->getinputdata();
	pwData = p(p_pwPort); //port_M_pw->getinputdata();

	freq_const = wave_period / (float) m_rate * (float) harmonic / (float) subharmonic;
	freq_tune = 4.0313842f + octave + freq;
	gain_linfm = 1000.0f * vcoLinFMGain;
	phi_const = phi0 * PKonst;
	pw_low = 0.1f * wave_period;
	pw_high = 0.9f * wave_period;

	if (phi0 > 0.0f)
	{
		for (l2 = 0; l2 < nframes; ++l2)
		{
			dphi = freq_const * (synthdata->exp2_table(freq_tune + freqData[l2] + vcoExpFMGain * expFMData[l2]) + gain_linfm * linFMData[l2]);
			if (dphi > wave_period_2)
				dphi = wave_period_2;
			phi1 = phi + phi_const;
			if (phi1 < 0.0f)
				phi1 += wave_period;
			else if (phi1 >= wave_period)
				phi1 -= wave_period;
			phint = (int) phi1;

			switch (waveForm)
			{
				case SINUS:
					p(p_out)[l2] = synthdata->wave_sine[phint];
					break;
				case TRIANGLE:
					p(p_out)[l2] = synthdata->wave_tri[phint];
					break;
				case AWAVE_SAW:
					p(p_out)[l2] = synthdata->wave_saw2[phint];
					break;
				case AWAVE_SAW2:
					half_wave = wave_period_2;// * 0.5f;// / 2.0;
					p(p_out)[l2] = (phi1 < half_wave) ? synthdata->wave_saw2[(int) (2.0f * phi1)] : 0.0f;
					break;
				case AWAVE_SAW3:
					third_wave = wave_period_3;// * 0.3333333333334f;// / 3.0f;
					p(p_out)[l2] = (phi1 < third_wave) ? synthdata->wave_saw2[(int) (3.0f * phi1)] : 0.0f;
					break;

				case SAWTOOTH:
				{
					pw = (pw0 + pwGain * pwData[l2]) * wave_period;
					if (pw < pw_low)
						pw = pw_low;
					else if (pw > pw_high)
						pw = pw_high;
					d = edge * dphi;
					dd = 1.0f / d;
					dsaw = 2.0f / (wave_period - 2.0f * d);
					if (phi1 <= d)
					{
						p(p_out)[l2] = phi1 * dd;
					}
					else
					{
						if (phi1 <= pw - d)
						{
							p(p_out)[l2] = 1.0f - (phi1 - d) * dsaw;
						}
						else
						{
							if (phi1 <= pw + d)
							{
								p(p_out)[l2] = 1.0f - (phi1 - d) * dsaw;
							}
							else
							{
								if (phi1 <= wave_period - d)
								{
									p(p_out)[l2] = 1.0f - (phi1 - d) * dsaw;
								}
								else
								{
									p(p_out)[l2] = (phi1 - wave_period) * dd;
								}
							}
						}
					}
				}
					break;
				case RECTANGLE:
				{
					pw = (pw0 + pwGain * pwData[l2]) * wave_period;
					if (pw < pw_low)
						pw = pw_low;
					else if (pw > pw_high)
						pw = pw_high;
					d = edge * dphi;
					dd = 1.0f / d;
					if (phi1 <= d)
					{
						p(p_out)[l2] = phi1 * dd;
					}
					else
					{
						if (phi1 <= pw - d)
						{
							p(p_out)[l2] = 1.0f;
						}
						else
						{
							if (phi1 <= pw + d)
							{
								p(p_out)[l2] = (pw - phi1) * dd;
							}
							else
							{
								if (phi1 <= wave_period - d)
								{
									p(p_out)[l2] = -1.0f;
								}
								else
								{
									p(p_out)[l2] = (phi1 - wave_period) * dd;
								}
							}
						}
					}
				}
					break;
			} // end of case
			phi += dphi;
			while (phi < 0.0f)
				phi += wave_period;
			while (phi >= wave_period)
				phi -= wave_period;
		}
	}
	else
	{
		for (l2 = 0; l2 < nframes; ++l2)
		{
			dphi = freq_const * (synthdata->exp2_table(freq_tune + freqData[l2] + vcoExpFMGain * expFMData[l2]) + gain_linfm * linFMData[l2]);
			if (dphi > wave_period_2)
				dphi = wave_period_2;
			phint = (int) phi;
			switch (waveForm)
			{
				case SINUS:
					p(p_out)[l2] = synthdata->wave_sine[phint];
					break;
				case TRIANGLE:
					p(p_out)[l2] = synthdata->wave_tri[phint];
					break;
				case AWAVE_SAW:
					p(p_out)[l2] = synthdata->wave_saw2[phint];
					break;
				case AWAVE_SAW2:
					half_wave = wave_period_2;// * 0.5f; // / 2.0;
					p(p_out)[l2] = (phi < half_wave) ? synthdata->wave_saw2[(int) (2.0f * phi)] : 0.0f;
					break;
				case AWAVE_SAW3:
					third_wave = wave_period_3;// * 0.3333333333334f;// / 3.0f;
					p(p_out)[l2] = (phi < third_wave) ? synthdata->wave_saw2[(int) (3.0f * phi)] : 0.0f;
					break;

				case SAWTOOTH:
				{
					pw = (pw0 + pwGain * pwData[l2]) * wave_period;
					if (pw < pw_low)
						pw = pw_low;
					else if (pw > pw_high)
						pw = pw_high;
					d = edge * dphi;
					dd = 1.0f / d;
					dsaw = 2.0f / (wave_period - 2.0f * d);
					if (phi <= d)
					{
						p(p_out)[l2] = phi * dd;
					}
					else
					{
						if (phi <= pw - d)
						{
							p(p_out)[l2] = 1.0f - (phi - d) * dsaw;
						}
						else
						{
							if (phi <= pw + d)
							{
								p(p_out)[l2] = 1.0f - (phi - d) * dsaw;
							}
							else
							{
								if (phi <= wave_period - d)
								{
									p(p_out)[l2] = 1.0f - (phi - d) * dsaw;
								}
								else
								{
									p(p_out)[l2] = (phi - wave_period) * dd;
								}
							}
						}
					}
				}
					break;
				case RECTANGLE:
				{
					pw = (pw0 + pwGain * pwData[l2]) * wave_period;
					if (pw < pw_low)
						pw = pw_low;
					else if (pw > pw_high)
						pw = pw_high;
					d = edge * dphi;
					dd = 1.0f / d;
					if (phi <= d)
					{
						p(p_out)[l2] = phi * dd;
					}
					else
					{
						if (phi <= pw - d)
						{
							p(p_out)[l2] = 1.0f;
						}
						else
						{
							if (phi <= pw + d)
							{
								p(p_out)[l2] = (pw - phi) * dd;
							}
							else
							{
								if (phi <= wave_period - d)
								{
									p(p_out)[l2] = -1.0f;
								}
								else
								{
									p(p_out)[l2] = (phi - wave_period) * dd;
								}
							}
						}
					}
				}
					break;
			}// end of case
			phi += dphi;
			while (phi < 0.0f)
				phi += wave_period;
			while (phi >= wave_period)
				phi -= wave_period;
		}
	}
}

static int _ = Vco2::register_class("http://avwlv2.sourceforge.net/plugins/avw/vco2");

