#ifndef avw_lv__amplitude_ttl_hpp
#define avw_lv__amplitude_ttl_hpp


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

/* <http://avwlv2.sourceforge.net/plugins/avw/amplitude> */

static const char p_uri[] = "http://avwlv2.sourceforge.net/plugins/avw/amplitude";

enum p_port_enum {
  p_input,
  p_oldMin,
  p_oldMax,
  p_newMin,
  p_newMax,
  p_output,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, -1, 0, 0, 0 }, 
  { -1, 1, 1, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 1, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* avw_lv__amplitude_ttl_hpp */
