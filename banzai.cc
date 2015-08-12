#include "packet.h"
#include "pipeline.h"
#include "atom.h"
#include "stage.h"
#include "dynamic_linking_loader.h"

#include <exception>
#include <vector>
#include <iostream>

int main(const int argc __attribute__ ((unused)), const char ** argv __attribute__((unused))) {
  try {
    // Initialize field map to contain the right fields
    const Packet exemplar_packet(std::map<std::string, uint32_t>({{"a", 0}, {"b", 0}, {"c", 0}}), 1);

    // Construct shared library loader
    DynamicLinkingLoader("/lib/x86_64-linux-gnu/libc.so.6");

    // Construct pipeline
    Pipeline pipeline({{Atom([](const Packet & p, State & s __attribute__((unused)))
                             { auto ret = p; ret.write("a", ret.read("a") + 1); return ret; }, FieldContainer())}});

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
