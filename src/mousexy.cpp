#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "lv2plugin.hpp"
#include "synthdata.hpp"
#include "mousexy.hpp"
#include "mousexy.peg"

using namespace LV2;

MouseXY::MouseXY(double rate) :
		Plugin<MouseXY>(p_n_ports)
{
	dsp = XOpenDisplay(NULL);
	max_x = DisplayWidth(dsp, DefaultScreen(dsp));
	max_y = DisplayHeight(dsp, DefaultScreen(dsp));
	current_x = 0;
	current_y = 0;

	UpdateMouse();
}

MouseXY::~MouseXY()
{
	XCloseDisplay (dsp);
}

void MouseXY::UpdateMouse()
{
    XEvent event;
    XQueryPointer(dsp, RootWindow(dsp, DefaultScreen(dsp)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    current_x = event.xbutton.x;
    current_y = event.xbutton.y;
}

void MouseXY::run(uint32_t nframes)
{
	UpdateMouse();

	unsigned int l2;

	float x = 0, y = 0;

	x = (float) current_x / max_x;
	y = (float) (max_y - current_y) / max_y;

	for (l2 = 0; l2 < nframes; l2++)
	{
		p(p_outX)[l2] = x;
		p(p_outY)[l2] = y;
	}
}

static int _ = MouseXY::register_class("http://avwlv2.sourceforge.net/plugins/avw/mousexy");

