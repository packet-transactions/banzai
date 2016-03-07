#include "packet.h"
#include "atom.h"
#include "pipeline.h"
extern "C" {
void update(const Packet & packet __attribute__((unused)), Atom::StateType & state) { state++; }
int initialize(const Packet & packet __attribute__((unused))) { return 0; }
PacketFieldSet test_fields({"arrival_time", "dport", "sport"});
Pipeline test_pipeline{{Atom(test_fields, update, initialize)}};
}
