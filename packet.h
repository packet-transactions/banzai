#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <ostream>
#include <random>

#include "field_container.h"

/// Wrapper around FieldContainer representing a Packet
/// including a Boolean denoting whether it's initialized or not.
class Packet {
 public:
  typedef std::string FieldName;

  /// Packet constructor
  Packet(const FieldContainer & t_field_container, const uint32_t & seed)
    : bubble_(false),
      packet_(t_field_container),
      prng_(seed) {}
  Packet() {}

  /// Check if we have a bubble, to bypass packet processing
  bool is_bubble() const { return bubble_; }

  /// Reference to underlying field
  uint32_t & operator() (const FieldName & field_name) { return packet_(field_name); }

  /// Overload += operator
  Packet & operator+=(const Packet & t_packet) {
    assert(not t_packet.is_bubble());
    if (this->bubble_) {
      this->bubble_ = false;
      this->packet_ = t_packet.packet_;
      return *this;
    } else {
      assert(not t_packet.bubble_ and not this->bubble_);
      this->packet_ += t_packet.packet_;
      return *this;
    }
  }

  /// Generate random Packet with the same fields
  /// as the current one, but with all fields init. to random values.
  auto generate_random_packet() const {
    // Copy over all fields as such from this
    Packet ret(*this);

    const auto field_list = ret.packet_.field_list();
    for (const auto & field_name : field_list) ret(field_name) = packet_field_dist_(prng_);
    return ret;
  }

  /// Print to stream
  friend std::ostream & operator<< (std::ostream & out, const Packet & t_packet) {
    if (t_packet.bubble_) out << "Bubble \n";
    else out << t_packet.packet_ << "\n";
    return out;
  }

 private:
  /// Is this a bubble? i.e. no packet
  bool bubble_ = true;

  /// Underlying FieldContainer managed by Packet
  FieldContainer packet_ = FieldContainer();

  /// PRNG to generate random packet fields,
  /// This is mutable to allow us to generate random packets from a
  /// const exemplar packet used to determine the field list
  mutable std::default_random_engine prng_ = std::default_random_engine(std::random_device()());

  /// Uniform distribution over ints to generate random packet fields
  /// This is mutable to allow us to generate random packets from a
  /// const exemplar packet used to determine the field list
  mutable std::uniform_int_distribution<uint32_t> packet_field_dist_ = std::uniform_int_distribution<uint32_t>(0, std::numeric_limits<uint32_t>::max());
};

#endif  // TYPEDEFS_H_
