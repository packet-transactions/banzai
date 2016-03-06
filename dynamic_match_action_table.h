#ifndef DYNAMIC_MATCH_ACTION_TABLE_H_
#define DYNAMIC_MATCH_ACTION_TABLE_H_

#include <map>
#include <vector>
#include <string>
#include <functional>

#include "packet.h"

/// A match-action table supporting data-plane inserts and deletes of match keys.
/// For now, the action for each match entry involves
/// updating some state on the same programmable basis
/// across all match entries. This isn't a fundamental restriction.
/// Different match entries can have different computations/actions attached to them.
/// Also, for now, the match is an exact match on a specific set of packet fields.
class DynamicMatchActionTable {
 public:
  typedef int StateType;
  typedef std::function<void(const Packet &, StateType &)> Updater;
  typedef std::function<int(const Packet &)> Initializer;

  /// Constructor takes in vector of strings
  /// denoting the exact match fields
  DynamicMatchActionTable(const std::vector<std::string> & t_field_names,
                          const Updater & t_updater,
                          const Initializer & t_initializer);

  /// Update entry:
  /// 1. Create a new entry if it doesn't exist.
  /// 2. Update the existing entry if it does exist.
  /// In both cases, return updated StateType value
  StateType update(const Packet & packet);

  /// Erase entry, making sure that it actually exists
  /// Return the erased entry
  StateType erase(const Packet & packet);

 private:
  /// Underlying storage
  /// Key is a FieldContainer, i.e., a wrapper for a map from field names to values
  /// An incoming packet is "sliced" to the appropriate fields and then matched against storage_ 
  std::map<FieldContainer<int>, StateType> storage_ = {};

  /// Field names to match against
  /// Simulates exact match on a set of field names
  std::vector<std::string> field_names_ = {};

  /// Update function when updating match-action table
  Updater updater_ = {};

  /// Initialize function when initializing match-action table
  Initializer initializer_ = {};
};

#endif  // DYNAMIC_MATCH_ACTION_TABLE_H_
