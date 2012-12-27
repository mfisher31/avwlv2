#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "vcswitch_cv_gui.hpp"
#include "vcswitch_cv.hpp"

VCSwitchCVGUI::VCSwitchCVGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	slot<void> p_slotSwitchLevel = compose(bind<0>(mem_fun(*this, &VCSwitchCVGUI::write_control), p_switchlevel), mem_fun(*this,  &VCSwitchCVGUI::get_switchLevel));
	m_dialSwitchLevel = new LabeledDial("Switch Level", p_slotSwitchLevel, p_switchlevel, 0, 10, true, 0.0001, 4);
	p_background->add(*m_dialSwitchLevel);

	p_background->set_size_request(100, 80);

	add(*p_background);

	Gtk::manage(p_background);
}

float VCSwitchCVGUI::get_switchLevel() { return m_dialSwitchLevel->get_value(); }

void VCSwitchCVGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_switchlevel)
	{
		m_dialSwitchLevel->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = VCSwitchCVGUI::register_class("http://avwlv2.sourceforge.net/plugins/avw/vcswitch_cv/gui");
