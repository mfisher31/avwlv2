#ifndef avw_lv__ringmodulator_cv_ttl_hpp
#define avw_lv__ringmodulator_cv_ttl_hpp


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

/* <http://avwlv2.sourceforge.net/plugins/avw/ringmodulator_cv> */

static const char p_uri[] = "http://avwlv2.sourceforge.net/plugins/avw/ringmodulator_cv";

enum p_port_enum {
  p_gain,
  p_carrier,
  p_modulation,
  p_output,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 5, 0.5, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* avw_lv__ringmodulator_cv_ttl_hpp */
