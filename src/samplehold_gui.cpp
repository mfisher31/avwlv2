#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "samplehold_gui.hpp"
#include "samplehold.hpp"
#include "dial.hpp"

SampleHoldGUI::SampleHoldGUI(const std::string& URI)
{
	EventBox *p_background = manage (new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);

	slot<void> p_slotTriggerLevel = compose(bind<0>(mem_fun(*this, &SampleHoldGUI::write_control), p_triggerlevel), mem_fun(*this,  &SampleHoldGUI::get_triggerLevel));
	m_dialTriggerLevel = new LabeledDial("Trigger Level", p_slotTriggerLevel, p_triggerlevel, 0, 10, LOG, 0.0001, 4);
	p_background->add(*m_dialTriggerLevel);

	p_background->set_size_request(100, 80);

	add(*p_background);

	Gtk::manage(p_background);
}

float SampleHoldGUI::get_triggerLevel() { return m_dialTriggerLevel->get_value(); }

void SampleHoldGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_triggerlevel)
	{
		m_dialTriggerLevel->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = SampleHoldGUI::register_class("http://avwlv2.sourceforge.net/plugins/avw/samplehold/gui");
