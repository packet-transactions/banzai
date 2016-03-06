#ifndef DYNAMIC_MATCH_ACTION_TABLE_H_
#define DYNAMIC_MATCH_ACTION_TABLE_H_

#include <map>
#include <vector>
#include <string>

/// A match-action table supporting data-plane inserts and deletes of match keys.
/// For now, the action for each match entry involves
/// updating some state on the same programmable basis
/// across all match entries. This isn't a fundamental restriction.
/// Different match entries can have different computations/actions attached to them.
/// Also, for now, the match is an exact match on a specific set of packet fields.
class DynamicMatchActionTable {
 public:
  typedef int StateType;
  typedef std::function<void(Packet &, StateType &)> UpdateFunction;

  /// Lookup entry:
  /// 1. Create a new entry if it doesn't exist.
  /// 2. Update the existing entry if it does exist.
  /// TODO: Complete implementation
  void lookup(Packet & p);

  /// Erase entry, making sure that it actually exists
  /// Return the erased entry
  /// TODO: Complete implementation
  StateType erase(Packet & p);

 private:
  /// Underlying storage
  /// Key is a FieldContainer, i.e., a wrapper for a map from field names to values
  /// An incoming packet is "sliced" to the appropriate fields and then matched against storage_ 
  std::map<FieldContainer, StateType> storage_;

  /// Field names to match against
  /// Simulates exact match on a set of field names
  std::vector<std::string> field_names_;

  /// Update function when updating the match-action table on lookup
  UpdateFunction update_function_;
 
};

#endif  // DYNAMIC_MATCH_ACTION_TABLE_H_
