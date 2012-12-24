#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "amp_gui.hpp"
#include "amp.hpp"

AmpGUI::AmpGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	slot<void> p_slotGain = compose(bind<0>(mem_fun(*this, &AmpGUI::write_control), p_gain), mem_fun(*this,  &AmpGUI::get_gain));
	m_dialGain = new LabeledDial("Gain", p_slotGain, p_gain, -10, 10, false, 0.01, 2);
	p_background->add(*m_dialGain);

	p_background->set_size_request(100, 80);

	add(*p_background);

	Gtk::manage(p_background);
}

float AmpGUI::get_gain() { return m_dialGain->get_value(); }

void AmpGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_gain)
	{
		m_dialGain->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = AmpGUI::register_class("http://avwlv2.sourceforge.net/plugins/avw/amp/gui");
