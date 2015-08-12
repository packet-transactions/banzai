#ifndef STAGE_H_
#define STAGE_H_

#include <tuple>

#include "stage_logic.h"

/// Wrapper class to encapsulate StageLogic and pass data between
/// the input of this stage and the output from this stage i.e. between
/// the read and write pipeline registers on either side of the stage's
/// combinational circuit.
class Stage {
 public:
  /// Tick this stage
  Packet tick(const Packet & input) { return stage_logic_(input); }

 private:
  /// Stage logic within this stage
  StageLogic stage_logic_;
};

#endif  // STAGE_H_
