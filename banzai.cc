#include "packet.h"
#include "pipeline.h"
#include "atom.h"
#include "dynamic_linking_loader.h"

#include <exception>
#include <vector>
#include <iostream>

int main(const int argc __attribute__ ((unused)), const char ** argv __attribute__((unused))) {
  try {
    // Construct shared library loader
    DynamicLinkingLoader dynamic_linking_loader(".libs/libprogtorun.so.0.0.0");

    // Construct pipeline and exemplar packet from shared library.
    Pipeline  pipeline = dynamic_linking_loader.get_object<Pipeline>("test_pipeline");
    const Packet exemplar_packet = dynamic_linking_loader.get_object<Packet>("test_packet");

    // Run for 100 ticks
    for (uint32_t i = 0; i < 100; i++) {
      // Generate packets using this exemplar
      const auto input_packet = exemplar_packet.generate_random_packet();
      std::cerr << "input_packet is \n" << input_packet << "\n";
      std::cerr << "output_packet is \n" << pipeline.tick(input_packet);
    }
  } catch (const std::exception & e) {
    std::cerr << "Caught exception in main " << e.what() << std::endl;
  }
}
