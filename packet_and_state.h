#ifndef PACKET_AND_STATE_H_
#define PACKET_AND_STATE_H_

#include "field_container.h"

/// Convenience struct for a pair of FieldContainers
/// one for a packet and another for state
struct PacketAndState {
  FieldContainer packet = {};
  FieldContainer state  = {};
  PacketAndState & operator +=(const PacketAndState & other) {
    this->packet += other.packet;
    this->state  += other.state;
    return *this;
  }
};

#endif  // PACKET_AND_STATE_H_
