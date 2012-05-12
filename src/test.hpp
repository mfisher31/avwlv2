#ifndef TEST_H
#define TEST_H

#include "lv2plugin.hpp"

using namespace LV2;

enum p_port_enum {
  p_freq,
  p_octave,
  p_tune,
  p_harmonic,
  p_subharmonic,
  p_pw0,
  p_pwGain,
  p_phi0,
  p_expFMGain,
  p_linFMGain,
  p_out,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 },
  { 0, 6, 3, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0 },
  { 1, 16, 1, 0, 0, 0 },
  { 1, 16, 1, 0, 0, 0 },
  { 0.1, 0.9, 0.5, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0 },
  { 0, 6.283, 0, 0, 0, 0 },
  { 0, 10, 0, 0, 0, 0 },
  { 0, 10, 0, 0, 0, 0 },
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 },
};

class Test: public Plugin<Test>
{
	public:
		Test(double rate);
		void run(uint32_t nframes);
};

#endif
