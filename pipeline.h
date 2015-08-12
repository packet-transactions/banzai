#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <iostream>
#include <algorithm>
#include <vector>

#include "packet_latches.h"
#include "stage.h"

/// A Pipeline class that repesents a switch pipeline made up of several
/// stages that pass data from one stage to the next.
class Pipeline {
 public:
  /// Pipeline constructor
  Pipeline(const std::vector<Stage> & t_stages)
    : stages_(t_stages),
      packet_latches_(std::vector<PacketLatches>(stages_.size() -1)) {}

  /// Tick the pipeline synchronously with input from the outside
  Packet tick(const Packet & packet) {
    /// Feed input to the first stage of the pipeline
    packet_latches_.front().write_half() = stages_.front().tick(packet);

    /// Execute stages 1 through n - 2
    for (uint32_t i = 1; i < stages_.size() - 1; i++) packet_latches_.at(i).write_half() = stages_.at(i).tick(packet_latches_.at(i - 1).read_half());

    /// Execute last stage
    auto ret = stages_.back().tick(packet_latches_.back().read_half());

    /// Swap read and write halves of packet latches akin to double buffering
    for (auto & packet_latch : packet_latches_) packet_latch.swap();

    return ret;
  }

 private:
  /// All stages that are part of the pipeline
  std::vector<Stage> stages_;

  /// All latches that are part of the pipeline
  std::vector<PacketLatches> packet_latches_;
};

#endif  // PIPELINE_H_
