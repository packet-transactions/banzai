#include "dynamic_match_action_table.h"

#include <cassert>
#include "field_container.h"

DynamicMatchActionTable::DynamicMatchActionTable(const PacketFieldSet & t_field_names,
                                                 const Updater & t_updater,
                                                 const Initializer & t_initializer)
    : storage_(),
      field_names_(t_field_names),
      updater_(t_updater),
      initializer_(t_initializer) {}

DynamicMatchActionTable::StateType DynamicMatchActionTable::update(const Packet & packet) {
  FieldContainer<int> sliced_packet;
  for (const auto & field : field_names_) {
    sliced_packet(field) = packet(field);
  }

  if (storage_.find(sliced_packet) != storage_.end()) {
    updater_(packet, storage_.at(sliced_packet));
  } else {
    storage_[sliced_packet] = initializer_(packet);
  }

  return storage_.at(sliced_packet);
} 

DynamicMatchActionTable::StateType DynamicMatchActionTable::erase(const Packet & packet) {
  FieldContainer<int> sliced_packet;
  for (const auto & field : field_names_) {
    sliced_packet(field) = packet(field);
  }

  assert(storage_.find(sliced_packet) != storage_.end());
  const auto ret = storage_.at(sliced_packet);

  storage_.erase(sliced_packet);
  return ret;
}
