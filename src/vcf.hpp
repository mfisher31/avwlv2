#ifndef VCF_H
#define VCF_H

#include <lvtk-1/lvtk/plugin.hpp>

#include "synthdata.hpp"

#include "vcf.peg"

using namespace lvtk;

#define MIN_FREQ                         20
#define MAX_FREQ                      20000
#define MAX_FREQ2                     22000

enum vcfTypeEnum { VCF_LR, VCF_LPF, VCF_HPF, VCF_BPF_I, VCF_BPF_II, VCF_NF, VCF_MOOG1, VCF_MOOG2 };

class Vcf : public Plugin<Vcf>
{
private:
    float gain, freq, resonance, dBgain;
    float vcfExpFMGain, vcfLinFMGain, resonanceGain;
    float freq_const;
    float fInvertRandMax ;
    float pi2_rate,inv2_rate;
    float freq_tune, gain_linfm, qr, moog_f, revMoog, moog2times;
    double b_noise;
    double in_lr[5], buf_lr[5];
    double in_lpf[5], buf_lpf[5];
    double in_hpf[5], buf_hpf[5];
    double in_bpf_i[5], buf_bpf_i[5];
    double in_bpf_ii[5], buf_bpf_ii[5];
    double in_nf[5], buf_nf[5];
    double in_moog1[5], buf_moog1[5];
    double in_moog2[5], buf_moog2[5];

    SynthData *synthdata;

    int vcfType;
    void initBuf();
    //Port *port_M_in, *port_M_resonance, *port_M_freq, *port_M_exp, *port_M_lin, *port_out;
//public:
    float *inData, *resonanceData, *freqData, *linFMData, *expFMData;

public:
    Vcf(double rate);
    void run(uint32_t nframes);

//public slots:
//    void initBuf(int index);
};

#endif
