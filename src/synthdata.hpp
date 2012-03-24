#ifndef SYNTHDATA_H
#define SYNTHDATA_H

#include <stdlib.h>
#include "main.hpp"
#include "macros.hpp"

#define EXP2_DEPTH 15
#define EXP2_BUF_LEN (1<<EXP2_DEPTH)

class SynthData
{

	public:
		float *wave_sine;
		float *wave_saw;
		float *wave_saw2;
		float *wave_rect;
		float *wave_tri;
		float *exp_data;
		static float exp2_data[EXP2_BUF_LEN];
		float edge;

		SynthData(float p_edge);
		~SynthData();

		float exp_table(float x);
		float exp2_table(float) FATTR_FLOAT_ARG;
};

extern SynthData *synthdata;

#endif

