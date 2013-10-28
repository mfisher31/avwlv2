#include <gtkmm-2.4/gtkmm.h>


#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>
#include <lvtk-1/lvtk/ext/bufsize.hpp>
#include <lvtk-1/lvtk/ext/options.hpp>

#include "scope_gui.hpp"
#include "scope.hpp"
#include "dial.hpp"

ScopeGUI::ScopeGUI(const std::string& URI)
{
    OptionsIter *p_optIter = new OptionsIter(get_supplied_options());
    std::cout << "Collection Size: " << p_optIter->size() <<  std::endl;
    for (int i = 0 ; i<p_optIter->size(); i++)
    {
        const Option* p_oneOpt = p_optIter->next();
        std::cout <<  "\nKey:" << unmap(p_oneOpt->key) <<  std::endl;
        std::cout <<  "Type:" << unmap(p_oneOpt->type) << " - " << p_oneOpt->type <<  std::endl;
        std::cout <<  "Size:" << p_oneOpt->size << std::endl;
        switch(p_oneOpt->type)
        {
        case 5:
            //_uris.forge.str(value)
            std::cout <<  "Value:" << ((const LV2_Atom_Float*)p_oneOpt->value)->body <<  std::endl;
            break;
        case 6:
            std::cout <<  "Value:" << ((const LV2_Atom_Int*)p_oneOpt->value)->body <<  std::endl;
            break;
        case 67:
            std::cout <<  "Value:" << *(const int32_t*)p_oneOpt->value << std::endl;
            break;
        case 108:
            std::cout <<  "Value:" << *(const uint32_t*)p_oneOpt->value << std::endl;
            break;
        }
    }

    EventBox *p_background = manage (new EventBox());
    Gdk::Color* color = new  Gdk::Color();
    color->set_rgb(7710, 8738, 9252);
    p_background->modify_bg(Gtk::STATE_NORMAL, *color);

    p_background->set_size_request(100, 80);

    add(*p_background);

    Gtk::manage(p_background);
}

void ScopeGUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
    std::cout << port << " - " << format << std::endl;
}

static int _ = ScopeGUI::register_class("http://avwlv2.sourceforge.net/plugins/avw/scope/gui");
