#ifndef CVS_H
#define CVS_H

#include "synthdata.hpp"
#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class Cvs: public Plugin<Cvs>
{
	public:
		Cvs(double rate);
		void run(uint32_t nframes);
};

#endif
