#ifndef DELAY_H
#define DELAY_H

#define MAX_DELAY_FRAMES                16384

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class Delay: public Plugin<Delay>
{
	public:
		Delay(double rate);
		~Delay();
		void run(uint32_t nframes);

	private:
		float m_delay;
		int read_ofs;
		float *buf;
};

#endif
