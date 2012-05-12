/****************************************************************************

 lv2gui.hpp - Wrapper library to make it easier to write LV2 GUIs in C++

 Copyright (C) 2006-2008 Lars Luthman <lars.luthman@gmail.com>
 Modified by Dave Robillard, 2008 (URI map mixin)

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA  02110-1301  USA

 ****************************************************************************/

#ifndef LV2GUI_HPP
#define LV2GUI_HPP

#include <cstdlib>
#include <cstring>
#include <map>

#include <gtkmm/box.h>
#include <gtkmm/main.h>
#include <gtkmm/widget.h>

#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>
#include <lv2/lv2plug.in/ns/ext/uri-map/uri-map.h>
#include "lv2plugin.hpp"

namespace LV2
{

	/** @internal
	 A convenient typedef that is only used internally. */
	typedef std::vector<LV2UI_Descriptor*> GUIDescList;

	/** @internal
	 This function returns the list of LV2 descriptors. It should only be
	 used internally. */
	GUIDescList& get_lv2g2g_descriptors();

	/** @defgroup guimixins GUI mixins
	 These classes implement extra functionality that you may want to have
	 in your GUI class, just like the @ref pluginmixins "plugin mixins" do
	 for plugin classes. Some of them are template classes with a boolean
	 @c Required parameter - if this is true the GUI will fail to instantiate
	 unless the host supports the extension implemented by that mixin.
	 For example, if you wanted a GUI that wrote a MIDI Note On event to port
	 3 in the plugin whenever the user clicked a button, you could do it like
	 this:
	 */

	/** This is the base class for a plugin GUI. You should inherit it and
	 override any public member functions you want to provide
	 implementations for. All subclasses must have a constructor with
	 the signature

	 where @c plugin_uri is the URI of the plugin that this GUI will
	 control (not the URI for the GUI itself).

	 You can extend your GUI classes, for example adding support for
	 GUI extensions, by passing @ref guimixins "GUI mixin classes" as template
	 parameters to GUI (second template parameter and onwards).
	 */
	template<class Derived>
	class GUI: public Gtk::HBox
	{
		public:

			/** @internal
			 The constructor for the GUI class. You should never use it directly.
			 */
			inline GUI()
			{
				m_ctrl = s_ctrl;
				m_wfunc = s_wfunc;
				m_bundle_path = s_bundle_path;
				s_ctrl = 0;
				s_wfunc = 0;
				s_bundle_path = 0;
			}

			/** Override this if you want your GUI to do something when a control port
			 value changes in the plugin instance. */
			inline void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, void const* buffer)
			{
			}

			/** Use this template function to register a class as a LV2 GUI. */
			static int register_class(char const* uri)
			{
				LV2UI_Descriptor* desc = new LV2UI_Descriptor;
				std::memset(desc, 0, sizeof(LV2UI_Descriptor));
				desc->URI = strdup(uri);
				desc->instantiate = &Derived::create_ui_instance;
				desc->cleanup = &Derived::delete_ui_instance;
				desc->port_event = &Derived::_port_event;
				get_lv2g2g_descriptors().push_back(desc);
				return get_lv2g2g_descriptors().size() - 1;
			}

			bool check_ok() const
			{
				return true;
			}

		protected:

			/** Send a chunk of data to a plugin port. The format of the chunk is
			 determined by the port type and the transfer mechanisms used, you
			 should probably use a wrapper function instead such as write_control().
			 */
			inline void write(uint32_t port, uint32_t buffer_size, uint32_t format, void const* buffer)
			{
				(*m_wfunc)(m_ctrl, port, buffer_size, format, buffer);
			}

			/** Set the value of a control input port in the plugin instance. */
			inline void write_control(uint32_t port, float value)
			{
				write(port, sizeof(float), 0, &value);
			}

			/** Get the filesystem path to the bundle that contains this GUI. */
			inline char const* bundle_path() const
			{
				return m_bundle_path;
			}

		public:
			/** Get the controller - a handle on the plugin instance this GUI
			 is controlling. You only need it if you want to handle extensions
			 yourself. */
			inline void* controller()
			{
				return m_ctrl;
			}

		private:

			/** @internal
			 This function creates an instance of a plugin GUI. It is used
			 as the instantiate() callback in the LV2 descriptor. You should not use
			 it directly. */
			static LV2UI_Handle create_ui_instance(struct _LV2UI_Descriptor const* descriptor, char const* plugin_uri, char const* bundle_path, LV2UI_Write_Function write_func, LV2UI_Controller ctrl, LV2UI_Widget* widget, Feature const* const * features)
			{
				// copy some data to static variables so the subclasses don't have to
				// bother with it - this is threadsafe since hosts are not allowed
				// to instantiate the same plugin concurrently
				s_ctrl = ctrl;
				s_wfunc = write_func;
				//s_features = features;
				s_bundle_path = bundle_path;

				// this is needed to initialise gtkmm stuff in case we're running in
				// a Gtk+ or PyGtk host or some other language
				Gtk::Main::init_gtkmm_internals();

				// create the GUI object
				Derived* t = new Derived(plugin_uri);
				*widget = static_cast<Gtk::Widget*>(t)->gobj();

				// check that everything is OK
				if (t->check_ok())
					return reinterpret_cast<LV2UI_Handle>(t);
				delete t;
				return 0;
			}

			/** @internal
			 This function destroys an instance of a GUI. It is used as the
			 cleanup() callback in the LV2UI descriptor. You should not use it
			 directly. */
			static void delete_ui_instance(LV2UI_Handle instance)
			{
				delete static_cast<Derived*>(instance);
			}

			/** @internal
			 This is the main port_event() callback. You should not use it directly.
			 */
			static void _port_event(LV2UI_Handle instance, uint32_t port, uint32_t buffer_size, uint32_t format, void const* buffer)
			{
				static_cast<Derived*>(instance)->port_event(port, buffer_size, format, buffer);
			}

			void* m_ctrl;
			LV2UI_Write_Function m_wfunc;
			char const* m_bundle_path;

			static void* s_ctrl;
			static LV2UI_Write_Function s_wfunc;
			static char const* s_bundle_path;

	};

	/* Yes, static variables are messy. */
	template<class Derived>
	void* GUI<Derived>::s_ctrl = 0;

	template<class Derived>
	LV2UI_Write_Function GUI<Derived>::s_wfunc = 0;

	template<class Derived>
	char const* GUI<Derived>::s_bundle_path = 0;
}

#endif
