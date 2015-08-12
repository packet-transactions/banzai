#ifndef STAGE_LOGIC_H_
#define STAGE_LOGIC_H_

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

#include "packet.h"
#include "atom.h"

/// The core logic that captures the packet processing functionality
/// of a stage. The semantics of a physical stage are parallel execution
/// of all the underlying atoms. All state for a physical stage is encapsulated
/// within these atoms.
class StageLogic {
 public:
  /// Constructor for StageLogic that takes an Atom vector
  StageLogic(std::vector<Atom> & t_atoms) : atoms_(t_atoms) {};

  /// Overload function call operator, by calling all atoms_
  /// and combining their outputs.
  Packet operator() (const Packet & input) {
    Packet ret;
    /// These functions can be executed in any order
    /// A shuffle emulates this non determinisim.
    std::random_shuffle(atoms_.begin(), atoms_.end());
    for (auto & atom : atoms_) {
      ret += atom(input);
    }
    return ret;
  }

 private:
  /// Vector of Atom, to be executed in parallel
  std::vector<Atom> atoms_;
};

#endif  // STAGE_LOGIC_H_
