#include "packet.h"
#include "atom.h"
#include "pipeline.h"
extern "C" {
void update(const Packet & packet __attribute__((unused)), Atom::StateType & state) { state++; }
int initialize(const Packet & packet __attribute__((unused))) { return 0; }
PacketFieldSet match_fields({"dport", "sport"});
Pipeline test_pipeline{{Atom(match_fields, update, initialize)}};
}
