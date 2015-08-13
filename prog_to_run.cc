#include "packet.h"
#include "atom.h"
#include "pipeline.h"

extern "C" {
  Packet plus10(const Packet & p, State & s __attribute__((unused))) {
    auto ret = p;
    ret.write("a", ret.read("a") + 10);
    return ret;
  }
  Packet test_packet(std::map<std::string, uint32_t>({{"a", 0}, {"b", 0}, {"c", 0}}), 1);

  Pipeline test_pipeline({{Atom(plus10, FieldContainer())}, {Atom(plus10, FieldContainer())}});
}
