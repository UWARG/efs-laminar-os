#ifndef INC_INTERFACE_DATATYPES_HPP_
#define INC_INTERFACE_DATATYPES_HPP_

#include <cstdint>
#include "config.hpp"
#include "telem_datatypes.hpp"

/* LOS_Link */
typedef struct LosLinkRx_t{
  uint8_t rssi;
  uint8_t rx_channels[NUM_RX_CHANNELS];
};

#endif /* INC_INTERFACE_DATATYPES_HPP_ */