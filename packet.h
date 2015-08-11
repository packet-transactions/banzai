#ifndef PACKET_H_
#define PACKET_H_

struct Packet {
 int a;
 int b;
 int c;
};

auto generate_random_packet() { return Packet{1, 2, 3}; }

#endif  // PACKET_H_
