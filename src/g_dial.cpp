#include <cairomm/context.h>
#include <cmath>

#include "g_dial.hpp"

using namespace std;

Dial::Dial(const sigc::slot<void> toggle_slot, double Value, double Min, double Max, bool Log, double Step)
{
	m_log = Log;
	m_adj = new Gtk::Adjustment(Value, Min, Max, Step, Step);
	this->m_mouseDelta = 0;
	this->m_mouseDown = false;

	add_events(Gdk::EXPOSURE_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK| Gdk::POINTER_MOTION_MASK);
	signal_button_press_event().connect(sigc::mem_fun(*this, &Dial::on_button_press_event) );
	signal_button_release_event().connect(sigc::mem_fun(*this, &Dial::on_button_release_event) );
	signal_motion_notify_event().connect( sigc::mem_fun( *this, &Dial::onMouseMove ) );

	set_size_request(48, 48);

	m_adj->signal_value_changed().connect(mem_fun(*this, &Dial::value_changed));
	m_adj->signal_value_changed().connect(toggle_slot);
}

Dial::~Dial()
{
}

void Dial::value_changed()
{
	Redraw();
}

float Dial::get_value()
{
	return m_adj->get_value();
}

void Dial::set_value(float Value)
{
	m_adj->set_value(Value);
	Redraw();
}

bool Dial::on_expose_event(GdkEventExpose* event)
{
	Glib::RefPtr<Gdk::Window> window = get_window();
	if (window)
	{
		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

		cr->set_source_rgb(0.118,0.133, 0.141);
		cr->paint();

		cr->set_source_rgb(0.0, 0.8, 0.0);

		cr->rectangle((double)event->area.x, (double)event->area.y, (double)event->area.width, (double)event->area.height);
		cr->clip();

		int xc = event->area.width/2;
		int yc = event->area.height/2;

		float radius = 14;

		cr->set_line_cap( Cairo::LINE_CAP_ROUND );
		cr->set_line_join( Cairo::LINE_JOIN_ROUND);
		cr->set_line_width(2.8);

		// Arc Angle Value
		cr->set_line_width(2.4);
		cr->move_to(xc, yc);
		cr->set_source_rgba(0, 0, 0, 0);
		cr->stroke();

		cr->set_source_rgba(  66 / 255.f,  66 / 255.f ,  66 / 255.f , 1.f );

		cr->arc(xc, yc, radius, 2.46, 0.75);
		cr->move_to(xc, yc);
		cr->stroke();

		cr->set_line_width(2.8);
		float angle= 2.46 + (4.54 * ((m_adj->get_value()-m_adj->get_lower()) / (m_adj->get_upper()-m_adj->get_lower())));

		cr->set_source_rgba( 255 / 255.f, 104 / 255.f ,   0 / 255.f , 1.f );

		cr->set_line_width(1.7);
		cr->arc(xc,yc, 13, 2.46, angle );
		cr->line_to(xc,yc);
		cr->stroke();
		cr->arc(xc,yc, 17, 2.46, angle );
		cr->line_to(xc,yc);
		cr->stroke();
	}
	return true;
}

bool Dial::Redraw()
{
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
		win->invalidate_rect(r, false);
	}
	return true;
}

double Dial::CalculateLogStep()
{
	double p_perc = (m_adj->get_value()-m_adj->get_lower())/(m_adj->get_upper()-m_adj->get_lower())*100;
	if(p_perc<1)
		return m_adj->get_step_increment()/1000;
	if(p_perc<5)
		return m_adj->get_step_increment()/100;
	if(p_perc<15)
			return m_adj->get_step_increment()/10;
	if(p_perc<30)
				return m_adj->get_step_increment()/2;

	return m_adj->get_step_increment();
}

bool Dial::onMouseMove(GdkEventMotion* event)
{
	if (m_mouseDown)
	{
		if(m_adj->get_value()<m_adj->get_upper() && m_mouseDelta>event->y)
		{
			if(!m_log)
			{
				set_value(m_adj->get_value()+m_adj->get_step_increment());
			}
			else
			{
				std::cout << "step " << CalculateLogStep() << std::endl;
				set_value(m_adj->get_value()+CalculateLogStep());
			}
			std::cout << "up " << m_adj->get_value() << std::endl;
		}
		else if(m_adj->get_value()>m_adj->get_lower() && m_mouseDelta<event->y)
		{
			if(!m_log)
			{
				set_value(m_adj->get_value()-m_adj->get_step_increment());
			}
			else
			{
				std::cout << "step " << CalculateLogStep() << std::endl;
				set_value(m_adj->get_value()-CalculateLogStep());
			}
			std::cout << "down " << m_adj->get_value() << std::endl;
		}
		m_mouseDelta = event->y;
		Redraw();

		return true;
	}
	else
	{
		return false;
	}
}

bool Dial::on_button_press_event(GdkEventButton* event)
{
	if( event->type == GDK_BUTTON_PRESS  ) // && event->button == 3
	{
		m_mouseDown = true; // for pointer motion "drag" operations
		m_mouseDelta = event->x;

		return true;
	}
	else
	{
		return false;
	}
}

bool Dial::on_button_release_event(GdkEventButton* event)
{
	if( event->type == GDK_BUTTON_RELEASE  ) // && event->button == 3
	{
		m_mouseDown = false;

		return true; //It's been handled.
	}
	else
	{
		return false;
	}
}