#ifndef NOISE2_H
#define NOISE2_H

#include <lv2-c++-tools/lv2plugin.hpp>

using namespace LV2;

enum Noises {WHITE,RAND,PINK};

class Noise2 : public Plugin<Noise2>
{
    int NoiseType;
    unsigned int count;
    float rate, level;
    float buf[3], r;
    //Port *port_white, *port_pink, *port_random;
    float randmax;

  public:
    Noise2(double rate);
    void run(uint32_t nframes);
};
  
#endif
