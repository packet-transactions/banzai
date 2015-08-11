#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <iostream>
#include <algorithm>
#include <vector>

#include "packet.h"
#include "stage.h"

template <class StageLogic>
class Pipeline {
 public:
  /// Tick the pipeline synchronously
  void tick() {
    /// Feed input to the first stage of the pipeline
    stages_.front().read_incoming(generate_random_packet());

    /// Execute all stages
    std::for_each(stages_.begin(), stages_.end(), [] (const auto & x) { x.tick(); });
    /// Move outputs of one stage into inputs of the next
    for (uint32_t i = 0; i < stages_.size() - 1; i++)
      stages_.at(i).move_output(stages_.at(i + 1));

    /// Print out output
    std::cerr << stages_.back().output() << std::endl;
  }

 private:
  /// All stages that are part of the pipeline
  std::vector<Stage<StageLogic>> stages_;
};

#endif  // PIPELINE_H_
