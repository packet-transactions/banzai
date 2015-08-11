#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <iostream>
#include <algorithm>
#include <vector>

#include "stage.h"

class Pipeline {
 public:
  /// Pipeline constructor
  Pipeline(const std::vector<Stage> & stages) : stages_(stages) {}

  /// Tick the pipeline synchronously
  void tick() {
    /// Initialize field map to contain the right fields TODO
    /// Initialize the state to the right value.

    /// Feed input to the first stage of the pipeline
    stages_.front().read_incoming(FieldContainer().generate_random_field_map());

    /// Execute all stages
    std::for_each(stages_.begin(), stages_.end(), [] (auto & x) { x.tick(); });
    /// Move outputs of one stage into inputs of the next
    for (uint32_t i = 0; i < stages_.size() - 1; i++)
      stages_.at(i).move_output(stages_.at(i + 1));

    /// Print out output
    std::cerr << stages_.back().output() << std::endl;
  }

 private:
  /// All stages that are part of the pipeline
  std::vector<Stage> stages_;
};

#endif  // PIPELINE_H_
