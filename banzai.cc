#include "packet.h"
#include "pipeline.h"
#include "atom.h"
#include "dynamic_linking_loader.h"

#include <exception>
#include <vector>
#include <iostream>
#include <regex>

/// Split string based on another string used as delimiter
/// using C++11's regex_token_iterator
/// Based on http://en.cppreference.com/w/cpp/regex/regex_token_iterator
/// and http://stackoverflow.com/a/9437426/1152801
std::vector<std::string> split(const std::string & input, const std::string & regex_str) {
  std::regex regex_object(regex_str);
  std::sregex_token_iterator first{input.begin(), input.end(), regex_object, -1}, last;
  return {first, last};
}

int main(const int argc __attribute__ ((unused)), const char ** argv __attribute__((unused))) {
  try {
    if (argc < 4) {
      std::cerr << "Usage: " << argv[0] << " prog_to_run_as_library seed comma_separated_test_field_list" << std::endl;
      return EXIT_SUCCESS;
    }

    // Get cmdline args
    const auto prog_to_run(argv[1]);
    const uint32_t seed = static_cast<uint32_t>(std::atoi(argv[2]));
    const std::vector<std::string> field_vector = split(std::string(argv[3]), ",");
    const PacketFieldSet packet_field_set(field_vector.begin(), field_vector.end());

    /// PRNG to generate random packet fields,
    std::default_random_engine prng = std::default_random_engine(seed);

    /// Uniform distribution over ints to generate random packet fields
    std::uniform_int_distribution<uint32_t> packet_field_dist = std::uniform_int_distribution<uint32_t>(0, std::numeric_limits<uint32_t>::max());

    // Construct shared library loader for prog_to_run
    DynamicLinkingLoader dynamic_linking_loader(prog_to_run);
    Pipeline  pipeline = dynamic_linking_loader.get_object<Pipeline>("test_pipeline");

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
