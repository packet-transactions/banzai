#ifndef ATOM_H_
#define ATOM_H_

#include "packet.h"

/// A Function object that represents an atomic unit of execution
/// i.e. something that the hardware can finish before the next packet shows up
/// (This includes updates to any underlying hidden state.)
/// The Atom encapsulates a function that captures the functionality of this unit
/// and state that can be mutated between calls to this unit.
class Atom {
 public:
  /// Convenience typedef for state
  typedef FieldContainer State;

  /// Convenience typedef for a function that takes a packet and returns a
  /// new one. Represents a sequential block of code that executes within a stage.
  /// Could also modify state in the process.
  typedef std::function<Packet(const Packet &, State &)> SequentialFunction;

  /// Overload function call operator
  Packet operator() (const Packet & input) { return sequential_function_(input, state_); }

 private:
  /// Underlying sequential function that implements the atomic action
  SequentialFunction sequential_function_;

  /// Hidden State that is used to implement the atomic action
  FieldContainer state_;

  /// TODO: Initialize the state to the right value here.
};

#endif  // ATOM_H_
