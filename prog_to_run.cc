#include "packet.h"
#include "atom.h"
#include "pipeline.h"
extern "C" {
void atom0(Packet &packet, State &state __attribute__((unused))) {
  packet("new_hop") = (packet("sport") * packet("dport")) % 10;
  if (packet("arrival_time") - state("last_time") > 5) {
    state("next_hop") = packet("new_hop");
  };
  state("last_time") = packet("arrival_time");
  packet("next_hop") = state("next_hop");
}
PacketFieldSet test_fields({"arrival_time", "dport", "new_hop", "next_hop",
                            "sport"});
Pipeline test_pipeline{
    {Atom(atom0, FieldContainer(std::map<FieldContainer::FieldName, FieldContainer::FieldType>{
                     {"last_time", 0}, {"next_hop", 0}}))}};
}
