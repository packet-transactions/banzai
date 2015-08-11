#ifndef STAGE_H_
#define STAGE_H_

#include <tuple>

#include "field_container.h"
#include "stage_logic.h"
#include "packet_and_state.h"

class Stage {
 public:
  /// Tick this stage
  void tick() { output_ = stage_logic_(input_); }

  /// Move packet output alone into the next stage
  void move_output(Stage & next) const { next.read_incoming(output_.packet); }

  /// Read incoming packet input
  void read_incoming(const FieldContainer & incoming_packet) { input_.packet = incoming_packet; }

  /// Get current packet output
  auto output() const { return output_.packet; }

 private:
  /// Latches to hold packet and state
  /// output from this stage
  PacketAndState output_;

  /// Latch to hold packet and state
  /// input into this stage
  PacketAndState input_;

  /// Stage logic within this stage
  StageLogic stage_logic_;
};

#endif  // STAGE_H_
