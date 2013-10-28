#ifndef SCOPE_H
#define SCOPE_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/ext/urid.hpp>
#include <lvtk-1/lvtk/ext/atom.hpp>

#include "scope_ttl.hpp"

using namespace lvtk;

class Scope: public Plugin<Scope, URID<true>, Options<true>>
{
public:
    Scope(double rate);
    ~Scope();

    void run(uint32_t nframes);

private:

    AtomForge *m_forge;
    ForgeFrame m_notify_frame;

    struct SilenceURIs
    {
        LV2_URID atom_String;
        LV2_URID atom_value;
    } urids;
};

#endif
