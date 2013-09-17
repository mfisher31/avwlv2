#ifndef CONTROLTOCV_H
#define CONTROLTOCV_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "controltocv.peg"

using namespace lvtk;

class ControlToCV: public Plugin<ControlToCV>
{
	public:
		ControlToCV(double rate);
		void run(uint32_t nframes);
};

#endif
