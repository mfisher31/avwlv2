#ifndef VCTOHZ_H
#define VCTOHZ_H

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

class VcToHz
: public Plugin<VcToHz>
{
    int convMode, octave;
    double m_rate;

  public:
    VcToHz(double rate);
    void run(uint32_t nframes);
};
  
#endif
