#ifndef avw_lv__env_ttl_hpp
#define avw_lv__env_ttl_hpp


#ifndef PEG_STRUCT
#define PEG_STRUCT
typedef struct {
  float min;
  float max;
  float default_value;
  char toggled;
  char integer;
  char logarithmic;
} peg_data_t;
#endif

/* <http://avwlv2.sourceforge.net/plugins/avw/env> */

static const char p_uri[] = "http://avwlv2.sourceforge.net/plugins/avw/env";

enum p_port_enum {
  p_gate,
  p_retrigger,
  p_attack,
  p_decay,
  p_sustain,
  p_release,
  p_delay,
  p_hold,
  p_timeScale,
  p_out,
  p_invOut,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0, 1, 0, 0 }, 
  { 0, 1, 0.05, 0, 0, 0 }, 
  { 0, 1, 0.1, 0, 0, 0 }, 
  { 0, 1, 0.7, 0, 0, 0 }, 
  { 0, 1, 0.05, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { 0, 1, 0.02, 0, 0, 0 }, 
  { 1, 10, 0.1, 0, 0, 0 }, 
  { 0, 1, 0, 0, 0, 0 }, 
  { -1, 0, 0, 0, 0, 0 }, 
};


#endif /* avw_lv__env_ttl_hpp */
