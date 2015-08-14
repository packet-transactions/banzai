#include "packet.h"
#include "atom.h"
#include "pipeline.h"

extern "C" {
  void atom0(Packet & packet, State & state __attribute__((unused))) {
      packet("new_hop") = (packet("sport") * packet("dport")) % 10;
      if (packet("arrival_time") - state("last_time") > 5) {
        state("next_hop") = packet("new_hop");
      };
      state("last_time") = packet("arrival_time");
      packet("next_hop") = state("next_hop");
  }

  void plus20(Packet & p, State & s __attribute__((unused))) {
    p("a") = p("a") + 20;
  }
  void plus10(Packet & p, State & s __attribute__((unused))) {
    p("a") = p("a") + 10;
  }
  Packet test_packet(std::map<std::string, uint32_t>({{"new_hop", 0}, {"next_hop", 0}, {"sport", 0}, {"dport", 0}}), 1);

  Pipeline test_pipeline({{Atom(atom0, FieldContainer())}, {Atom(plus20, FieldContainer())}});
}
