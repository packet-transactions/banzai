#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <ostream>

#include "field_container.h"

/// Wrapper around FieldContainer representing a Packet
/// including a Boolean denoting whether it's initialized or not.
class Packet {
 public:
  typedef std::string FieldName;

  /// Packet constructor
  Packet(const FieldContainer & t_field_container)
    : bubble_(false),
      packet_(t_field_container) {}
  Packet() {}

  /// Check if we have a bubble, to bypass packet processing
  bool is_bubble() const { return bubble_; }

  /// Write method
  void write(const FieldName & field_name, const uint32_t & val) {
    assert(not bubble_);
    packet_.write(field_name, val);
  }

  /// Read method
  uint32_t read(const FieldName & field_name) const {
    assert(not bubble_);
    return packet_.read(field_name);
  }

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
    return Packet(packet_.generate_random_field_map());
  }

  /// Print to stream
  friend std::ostream & operator<< (std::ostream & out, const Packet & t_packet) {
    if (t_packet.bubble_) out << "Bubble \n";
    else out << t_packet.packet_ << "\n";
    return out;
  }

 private:
  bool bubble_ = true;
  FieldContainer packet_ = FieldContainer();
};

#endif  // TYPEDEFS_H_
