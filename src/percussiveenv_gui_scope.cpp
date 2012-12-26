#include "percussiveenv_gui_scope.hpp"
#include <cairomm/context.h>

PercussiveEnvGUIScope::PercussiveEnvGUIScope()
{
	set_size_request(100, 80);
}

PercussiveEnvGUIScope::~PercussiveEnvGUIScope()
{
}

bool PercussiveEnvGUIScope::on_expose_event(GdkEventExpose* event)
{
	Glib::RefPtr<Gdk::Window> window = get_window();
	if (window)
	{
		float len, x, y, xscale, yscale;

		Gtk::Allocation allocation = get_allocation();
		const int width = allocation.get_width();
		const int height = allocation.get_height();

		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		cr->set_line_width(2.0);
		cr->set_source_rgb(0.0, 0.0, 0.0);
		cr->paint();

		cr->set_source_rgb(0.0, 0.8, 0.0);

		cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
		cr->clip();

		cr->move_to(width, height);

		len = m_delayValue + m_attackValue + m_holdValue + m_decayValue;
		xscale = (float) width / len;
		yscale = (float) (height - 6);
		x = m_delayValue * xscale;
		cr->line_to((int) x, height);
		x += m_attackValue * xscale;
		cr->line_to((int) x, 6);
		x += m_holdValue * xscale;
		cr->line_to((int) x, 6);
		x += m_decayValue * xscale;
		cr->line_to((int) x, height - (int) y);
		cr->line_to((int) x, height - 1);
		x = m_delayValue * xscale;
		cr->line_to((int) x, height - 1);

		cr->stroke();
	}

	return true;
}

bool PercussiveEnvGUIScope::Redraw()
{
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win)
	{
		Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
		win->invalidate_rect(r, false);
	}
	return true;
}
