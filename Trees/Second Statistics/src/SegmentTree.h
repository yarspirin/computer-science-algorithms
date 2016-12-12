//
// Created by whoami on 12/11/16.
//

#ifndef SECOND_STATISTICS_SEGMENTTREE_H
#define SECOND_STATISTICS_SEGMENTTREE_H

#include <vector>
#include <climits>

struct TreeNode {
  TreeNode(int _id = -1,
           int _first_statistics = std::numeric_limits<int>::max(),
           int _second_statistics = std::numeric_limits<int>::max())
      : id(_id),
        first_statistics(_first_statistics),
        second_statistics(_second_statistics) { }

  static TreeNode MakeFictiveNode(const TreeNode& left, const TreeNode& right);

  // Choose two lowest elements from the corresponding segments
  void ApplySegments(const TreeNode& left, const TreeNode& right);

  int id;
  int first_statistics;
  int second_statistics;
};

class SegmentTree {
 public:
  SegmentTree()
      : is_valid_(false) { }

  void BuildTree(const std::vector<int>& array);
  int GetSecondStatistics(int query_left, int query_right) const;

 private:
  void BuildOnSegment(const std::vector<int>& array, int node_id, int left, int right);
  TreeNode GetSecondStatisticsOnSegment(int node_id, int left, int right, int query_left, int query_right) const;

  bool is_valid_;
  std::vector<TreeNode> buffer_;
};


#endif //SECOND_STATISTICS_SEGMENTTREE_H
