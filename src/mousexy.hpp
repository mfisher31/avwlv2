#ifndef MOUSEXY_H
#define MOUSEXY_H

#include <X11/Xlib.h>

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class MouseXY: public Plugin<MouseXY>
{
	private:
		Display * dsp;
		int max_x, max_y;
		int current_x, current_y;

		void UpdateMouse();
	public:
		MouseXY(double rate);
		~MouseXY();
		void run(uint32_t nframes);
};

#endif
