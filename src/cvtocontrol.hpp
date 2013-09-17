#ifndef CVTOCONTROL_H
#define CVTOCONTROL_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "cvtocontrol.peg"

using namespace lvtk;

class CVToControl: public Plugin<CVToControl>
{
	public:
		CVToControl(double rate);
		void run(uint32_t nframes);
};

#endif
