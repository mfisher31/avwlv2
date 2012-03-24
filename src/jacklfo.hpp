#ifndef JACKLFO_H
#define JACKLFO_H

#include <jack/jack.h>

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class JackLfo: public Plugin<JackLfo>
{
	private:
		float freq, phi0;
		double si, old_si;
		double sa, old_sa;
		double t, old_t;
		double r, old_r;
		double sh, old_sh;
		int state;
		double dt, wave_period;bool trigger;
		//Port *port_M_trigger, *port_sine, *port_tri, *port_sawup, *port_sawdown, *port_rect, *port_sh;

		double m_rate;
		jack_client_t *client;

	public:
		JackLfo(double rate);
		void run(uint32_t nframes);
};

#endif
