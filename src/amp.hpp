#ifndef AMP_H
#define AMP_H

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class Amp: public Plugin<Amp>
{
	private:
		float gain;
	public:
		Amp(double rate);
		void run(uint32_t nframes);
};

#endif
