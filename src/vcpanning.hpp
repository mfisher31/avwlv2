#ifndef VCPANNING_H
#define VCPANNING_H

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class VCPanning: public Plugin<VCPanning>
{
	private:
		float panPos, pan[2], oldpan[2];
	public:
		VCPanning(double rate);
		void run(uint32_t nframes);

};

#endif
