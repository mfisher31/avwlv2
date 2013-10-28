#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sstream>

#include "scope.hpp"

using namespace lvtk;

Scope::Scope(double rate) : Plugin<Scope, URID<true>, Options<true>>(p_n_ports)
{
    m_forge = new AtomForge(p_map);
}

void Scope::run(uint32_t nframes)
{
    // you're sending things in an atom sequence so get the size information
    // from the port buffer

    LV2_Atom_Sequence* aseq = (LV2_Atom_Sequence*) p (p_notify);
    m_forge->set_buffer ((uint8_t*) aseq, aseq->atom.size);

    m_forge->sequence_head(m_notify_frame, 0);

    // sequences need a timestamp for each event added
    m_forge->frame_time(0);

    m_forge->write_float(1604);
}

static int _ = Scope::register_class("http://avwlv2.sourceforge.net/plugins/avw/scope");

