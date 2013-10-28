#ifndef avw_lv__scope_ttl_hpp
#define avw_lv__scope_ttl_hpp


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

/* <http://avwlv2.sourceforge.net/plugins/avw/scope> */

static const char p_uri[] = "http://avwlv2.sourceforge.net/plugins/avw/scope";

enum p_port_enum {
  p_input,
  p_notify,
  p_n_ports
};

static const peg_data_t p_ports[] = {
  { -1, 1, 0, 0, 0, 0 }, 
  { -3.40282e+38, 3.40282e+38, -3.40282e+38, 0, 0, 0 }, 
};


#endif /* avw_lv__scope_ttl_hpp */
