#include "packet.h"
#include "pipeline.h"
#include "atom.h"
#include "stage.h"

#include <vector>
#include <iostream>

int main(const int argc __attribute__ ((unused)), const char ** argv __attribute__((unused))) {
  /// Initialize field map to contain the right fields TODO
  std::cerr << "Hello world" << std::endl;
  Pipeline pipeline({{Atom([](const Packet & p, State & s __attribute__((unused))) { return p; }, FieldContainer())}});
  pipeline.tick(Packet());
}
