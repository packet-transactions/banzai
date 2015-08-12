#ifndef ATOM_H_
#define ATOM_H_

#include "packet.h"

/// Convenience typedef for state
typedef FieldContainer State;

/// A Function object that represents an atomic unit of execution
/// i.e. something that the hardware can finish before the next packet shows up
/// (This includes updates to any underlying hidden state.)
/// The Atom encapsulates a function that captures the functionality of this unit
/// and state that can be mutated between calls to this unit.
class Atom {
 public:
  /// Convenience typedef for a function that takes a packet and returns a
  /// new one. Represents a sequential block of code that executes within a stage.
  /// Could also modify state in the process.
  typedef std::function<Packet(const Packet &, State &)> SequentialFunction;

  /// Constructor to Atom takes a SequentialFunction object and an initial value of state
  Atom(const SequentialFunction & t_sequential_function, const State & t_state)
    : sequential_function_(t_sequential_function), state_(t_state) {}

  /// Overload function call operator
  Packet operator() (const Packet & input) {
    assert(not input.is_bubble());
    return sequential_function_(input, state_);
  }

 private:
  /// Underlying sequential function that implements the atomic action
  SequentialFunction sequential_function_;

  /// Hidden State that is used to implement the atomic action
  State state_;
};

#endif  // ATOM_H_
