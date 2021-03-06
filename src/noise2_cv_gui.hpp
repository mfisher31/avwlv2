#ifndef NOISE2CV_GUI_H
#define NOISE2CV_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "labeleddial.hpp"

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

class Noise2CVGUI: public UI<Noise2CVGUI, GtkUI<true>>
{
	public:
		Noise2CVGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	protected:
		Gtk::ComboBoxText* m_comboNoiseForm;
		LabeledDial* m_dialRandomRate;
		LabeledDial* m_dialRandomLevel;

		float get_randomRate();
		float get_randomLevel();
};

#endif
