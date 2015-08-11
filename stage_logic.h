#ifndef STAGE_LOGIC_H_
#define STAGE_LOGIC_H_

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

#include "packet_and_state.h"

class StageLogic {
 public:
  /// Convenience typedef for a function that takes a pair of packet and state
  /// objects and returns a new pair of both objects. Represents a sequential
  /// block of code that executes within a stage.
  typedef std::function<PacketAndState(const PacketAndState &)> AtomicAction;

  /// Constructor for StageLogic that takes a vector of AtomicActions
  StageLogic(std::vector<AtomicAction> & t_atomic_actions) : atomic_actions_(t_atomic_actions) {};

  /// Overload function call operator, by calling all seq_pkt_functions_ and combining their outputs.
  PacketAndState operator() (const PacketAndState & input) {
    PacketAndState ret;
    /// These functions can be executed in any order
    std::random_shuffle(atomic_actions_.begin(), atomic_actions_.end());
    for (const auto & atomic_actions : atomic_actions_) {
      ret += atomic_actions(input);
    }
    return ret;
  }

 private:
  /// Vector of AtomicActions, each of which is executed in parallel
  std::vector<AtomicAction> atomic_actions_;
};

#endif  // STAGE_LOGIC_H_
