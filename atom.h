#ifndef ATOM_H_
#define ATOM_H_

#include <functional>

#include "dynamic_match_action_table.h"
#include "packet.h"

/// A Function object that represents an atomic unit of execution
/// i.e. something that the hardware can finish before the next packet shows up
/// (This includes updates to any underlying hidden state.)
/// The Atom encapsulates a function that captures the functionality of this unit
/// and state that can be mutated between calls to this unit.
class Atom {
 public:
  typedef int StateType;
  typedef std::function<void(const Packet &, StateType &)> Updater;
  typedef std::function<int(const Packet &)> Initializer;

  /// Constructor to Atom takes a SequentialFunction object and an initial value of state
  Atom(const PacketFieldSet & t_field_names,
       const Updater & t_updater,
       const Initializer & t_initializer)
    : dynamic_mat_(t_field_names, t_updater, t_initializer) {}

  /// Overload function call operator
  void operator() (Packet & input) {
    // Dummy call to dynamic_mat_
    assert(not input.is_bubble());
    dynamic_mat_.update(input);
  }

 private:
  /// Match-action table that permits data-plane inserts and deletes
  DynamicMatchActionTable dynamic_mat_ = DynamicMatchActionTable({}, Updater(), Initializer());
};

#endif  // ATOM_H_
