#include "packet.h"
#include "atom.h"
#include "pipeline.h"
extern "C" {
void atom0(Packet &packet, StateScalar & state_scalar __attribute__((unused)), StateArray & state_array __attribute__((unused))) {
  packet("new_hop") = (packet("sport") * packet("dport")) % 10;
  if (packet("arrival_time") - state_scalar("last_time") > 5) {
    state_scalar("next_hop") = packet("new_hop");
  };
  state_scalar("last_time") = packet("arrival_time");
  packet("next_hop") = state_scalar("next_hop");
}
PacketFieldSet test_fields({"arrival_time", "dport", "new_hop", "next_hop",
                            "sport"});
Pipeline test_pipeline{
    {Atom(atom0, StateScalar(std::map<std::string, int>{{"last_time", 0}, {"next_hop", 0}})
               , StateArray(std::map<std::string, std::vector<int>>{}))}};
}
