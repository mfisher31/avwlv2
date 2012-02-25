#ifndef INV_H
#define INV_H

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class Inv
: public Plugin<Inv>
{

public:
	Inv(double rate);
	void run(uint32_t nframes);
};

#endif
