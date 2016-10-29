//
// Created by whoami on 10/24/16.
//

#include <algorithm>

#include "DisjointSetUnion.h"

const int kInitialRank = 0;
const int kInitialSize = 1;

void DisjointSetUnion::InitDSU(int num_elements) {
  num_elements_ = num_elements;

  leader_.resize(static_cast<size_t>(num_elements_), -1);
  rank_.resize(static_cast<size_t>(num_elements_), -1);
  size_.resize(static_cast<size_t>(num_elements_), -1);
}

void DisjointSetUnion::CreateElementarySet(int element_id) {
  SetLeader(element_id, element_id);
  SetRank(element_id, kInitialRank);
  SetSubsetSize(element_id, kInitialSize);
}

int DisjointSetUnion::GetRepresentativeOfSet(int element_id) {
  if (element_id == leader_[element_id]) {
    return element_id;
  }

  int leader_id = GetLeader(element_id);
  SetLeader(element_id, GetRepresentativeOfSet(leader_id));

  return GetLeader(element_id);
}

void DisjointSetUnion::UniteSets(int first_element_id, int second_element_id) {
  first_element_id = GetRepresentativeOfSet(first_element_id);
  second_element_id = GetRepresentativeOfSet(second_element_id);

  if (first_element_id == second_element_id) {
    return;
  }

  if (GetRank(first_element_id) < GetRank(second_element_id)) {
    std::swap(first_element_id, second_element_id);
  }

  SetLeader(second_element_id, first_element_id);
  SetSubsetSize(first_element_id, GetSubsetSize(first_element_id) + GetSubsetSize(second_element_id));

  if (GetRank(first_element_id) == GetRank(second_element_id)) {
    rank_[first_element_id] += 1;
  }
}

int DisjointSetUnion::GetLeader(int element_id) const {
  return leader_[element_id];
}

int DisjointSetUnion::GetRank(int element_id) const {
  return rank_[element_id];
}

int DisjointSetUnion::GetSubsetSize(int element_id) const {
  return size_[element_id];
}

int DisjointSetUnion::GetLeaderSubsetSize(int element_id) const {
  return size_[GetLeader(element_id)];
}

void DisjointSetUnion::SetLeader(int element_id, int new_parent) {
  leader_[element_id] = new_parent;
}

void DisjointSetUnion::SetRank(int element_id, int new_rank) {
  rank_[element_id] = new_rank;
}

void DisjointSetUnion::SetSubsetSize(int element_id, int new_size) {
  size_[element_id] = new_size;
}