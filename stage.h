#ifndef STAGE_H_
#define STAGE_H_

#include <tuple>

#include "packet.h"
#include "state.h"

template <class StageLogic>
class Stage {
 public:
  /// Tick this stage
  void tick() { std::tie(packet_output_, state_output_)= stage_logic_(std::tie(packet_input_, state_input_)); }

  /// Move packet output alone into the next stage
  void move_output(Stage & next) const { next.read(packet_output_); }

  /// Read incoming packet input
  void read_incoming(const Packet & incoming) { packet_input_ = incoming; }

  /// Get current packet output
  auto output() const { return packet_output_; }

 private:
  /// Latches to hold packet output from this stage
  Packet packet_output_;

  /// Latch to hold packet input into this stage
  Packet packet_input_;

  /// Latch to hold state output from this stage
  State state_output_;

  /// Latch to hold state input into this stage
  State state_input_;

  /// Stage logic within this stage
  StageLogic stage_logic_;
};

#endif  // STAGE_H_
