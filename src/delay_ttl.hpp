#ifndef avw_lv__delay_ttl_hpp
#define avw_lv__delay_ttl_hpp


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

/* <http://avwlv2.sourceforge.net/plugins/avw/delay> */

static const char p_uri[] = "http://avwlv2.sourceforge.net/plugins/avw/delay";

enum p_port_enum {
  p_delay,
  p_input,
  p_output,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { 0, 10, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
  { -1, 1, 0, 0, 0, 0 }, 
};


#endif /* avw_lv__delay_ttl_hpp */
