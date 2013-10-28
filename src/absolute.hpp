#ifndef ABSOLUTE_H
#define ABSOLUTE_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "absolute_ttl.hpp"

using namespace lvtk;

class Absolute: public Plugin<Absolute>
{

	public:
		Absolute(double rate);
		void run(uint32_t nframes);
};

#endif
