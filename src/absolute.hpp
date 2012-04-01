#ifndef ABSOLUTE_H
#define ABSOLUTE_H

#include "lv2plugin.hpp"

using namespace LV2;

class Absolute
: public Plugin<Absolute>
{

public:
	Absolute(double rate);
	void run(uint32_t nframes);
};

#endif
