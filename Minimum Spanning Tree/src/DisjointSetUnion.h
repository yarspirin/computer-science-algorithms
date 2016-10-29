//
// Created by whoami on 10/24/16.
//

#ifndef MST_DISJOINTSETUNION_H
#define MST_DISJOINTSETUNION_H

#include <vector>

// Efficient data structure to make operations with disjoint sets of elements
class DisjointSetUnion {
 public:

  // Allocate disjoint set of num_elements size
  void InitDSU(int num_elements);

  // Make atomic sets
  void CreateElementarySet(int element_id);

  // Find the leader of a group
  int GetRepresentativeOfSet(int element_id);

  // Merge two sets
  void UniteSets(int first_element_id, int second_element_id);

  // Get size of leader's subset which contains element_id
  int GetLeaderSubsetSize(int element_id) const;

 private:

  // Get values of heuristics
  int GetLeader(int element_id) const;
  int GetRank(int element_id) const;
  int GetSubsetSize(int element_id) const;

  // Set values of heuristics
  void SetLeader(int element_id, int new_leader);
  void SetRank(int element_id, int new_rank);
  void SetSubsetSize(int element_id, int new_size);

  int num_elements_;

  std::vector<int> rank_;
  std::vector<int> leader_;
  std::vector<int> size_;
};


#endif //MST_DISJOINTSETUNION_H
