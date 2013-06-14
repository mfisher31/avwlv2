#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "hztovc_gui.hpp"
#include "hztovc.hpp"
#include "dial.hpp"

HzToVCGUI::HzToVCGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	slot<void> p_sloOctave = compose(bind<0>(mem_fun(*this, &HzToVCGUI::write_control), p_octaveOffset), mem_fun(*this,  &HzToVCGUI::get_octaveOffset));
	m_dialOctaveOffset = new LabeledDial("Octave Offset", p_sloOctave, p_octaveOffset, -3, 3, NORMAL, 0.01, 2);
	p_background->add(*m_dialOctaveOffset);

	p_background->set_size_request(100, 80);

	add(*p_background);

	Gtk::manage(p_background);
}

float HzToVCGUI::get_octaveOffset() { return m_dialOctaveOffset->get_value(); }

void HzToVCGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_octaveOffset)
	{
		m_dialOctaveOffset->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = HzToVCGUI::register_class("http://avwlv2.sourceforge.net/plugins/avw/hztovc/gui");
