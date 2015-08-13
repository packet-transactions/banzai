#ifndef FIELD_CONTAINER_H_
#define FIELD_CONTAINER_H_

#include <cassert>

#include <vector>
#include <ostream>
#include <map>

/// FieldContainer: a map from the field name as a string
/// to the field value as an integer.
/// Two FieldContainers, can be added (unioned) together,
/// so long as they don't have the same fields
///  in them, in which case it isn't clear which
/// value should take precedence.
/// FieldContainers can be used to represent both packets with named fields
/// and state with named fields as part of that state.
class FieldContainer {
 public:
  /// Typedef for string as field name
  typedef std::string FieldName;

  /// Constructor from map
  FieldContainer(const std::map<FieldName, uint32_t> & t_field_map = {}) : field_map_(t_field_map) {}

  /// Write field
  void write(const FieldName & field_name, const uint32_t & val) { field_map_[field_name] = val; }

  /// Read field
  uint32_t read(const FieldName & field_name) const {
    if (field_map_.find(field_name) == field_map_.end()) throw std::logic_error("Could not find " + field_name + " in FieldContainer \n" + str());
    return field_map_.at(field_name);
  }

  /// Overload += operator to merge a FieldContainer into this
  /// as long as they have no fields in common
  FieldContainer & operator+=(const FieldContainer & fc) {
    // Check that none of fc's keys are in this ...
    for (const auto & key_pair : fc.field_map_) {
      if(this->field_map_.find(key_pair.first) != this->field_map_.end()) {
        throw std::logic_error("Can't perform FieldContainer union here: " + key_pair.first + " belongs in both " + this->str() + " and " + fc.str());
      }
    }

    // ... and vice versa.
    for (const auto & key_pair : this->field_map_) {
      if(fc.field_map_.find(key_pair.first) != fc.field_map_.end()) {
        throw std::logic_error("Can't perform FieldContainer union here: " + key_pair.first + " belongs in both " + this->str() + " and " + fc.str());
      }
    }

    // Collapse the fc key set
    for (const auto & key_pair : fc.field_map_) write(key_pair.first, key_pair.second);

    return *this;
  }

  /// String representation of object
  std::string str() const {
    std::string ret = "\n";
    for (const auto & key_pair : field_map_) ret += key_pair.first + " : " + std::to_string(key_pair.second) + "\n";
    return ret;
  }

  /// Print to stream
  friend std::ostream & operator<< (std::ostream & out, const FieldContainer & field_container) {
    out << field_container.str();
    return out;
  }

  /// Get list of all fields
  std::vector<FieldName> field_list() const {
    std::vector<FieldName> ret;
    for (const auto & key_pair : field_map_) ret.emplace_back(key_pair.first);
    return ret;
  }

 private:
  /// Map from FieldName to field value.
  std::map<FieldName, uint32_t> field_map_ = {};
};

#endif  // FIELD_CONTAINER_H_
