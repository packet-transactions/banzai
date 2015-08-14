#include "packet.h"
#include "pipeline.h"
#include "atom.h"
#include "dynamic_linking_loader.h"

#include <exception>
#include <vector>
#include <iostream>

int main(const int argc __attribute__ ((unused)), const char ** argv __attribute__((unused))) {
  try {
    if (argc < 3) {
      std::cerr << "Usage: " << argv[0] << " prog_to_run_as_library seed" << std::endl;
      return EXIT_SUCCESS;
    }
    // Get cmdline args
    const auto prog_to_run(argv[1]);
    const uint32_t seed = static_cast<uint32_t>(std::atoi(argv[2]));

    /// PRNG to generate random packet fields,
    std::default_random_engine prng = std::default_random_engine(seed);

    /// Uniform distribution over ints to generate random packet fields
    std::uniform_int_distribution<uint32_t> packet_field_dist = std::uniform_int_distribution<uint32_t>(0, std::numeric_limits<uint32_t>::max());

    // Construct shared library loader for prog_to_run
    DynamicLinkingLoader dynamic_linking_loader(prog_to_run);
    Pipeline  pipeline = dynamic_linking_loader.get_object<Pipeline>("test_pipeline");
    const PacketFieldSet packet_field_set = dynamic_linking_loader.get_object<PacketFieldSet>("test_fields");

    // Run for 100 ticks
    for (uint32_t i = 0; i < 100; i++) {
      // Generate random test packets using packet_field_set
      // Construct Packet using an empty FieldContainer to signal that this isn't
      // a default-constructed packet, which is treated as a bubble.
      Packet test_packet = Packet(FieldContainer());
      for (const auto & field_name : packet_field_set) test_packet(field_name) = packet_field_dist(prng);

      std::cerr << "input_packet is \n" << test_packet << "\n";
      std::cerr << "output_packet is \n" << pipeline.tick(test_packet);
    }
  } catch (const std::exception & e) {
    std::cerr << "Caught exception in main " << std::endl << e.what() << std::endl;
  }
}
