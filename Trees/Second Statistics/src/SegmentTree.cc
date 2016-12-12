//
// Created by whoami on 12/11/16.
//

#include <cassert>

#include "SegmentTree.h"

TreeNode TreeNode::MakeFictiveNode(const TreeNode &left, const TreeNode &right) {
  TreeNode result;
  result.ApplySegments(left, right);
  return result;
}

void TreeNode::ApplySegments(const TreeNode &left, const TreeNode &right) {
  if (left.second_statistics < right.first_statistics) {
    first_statistics = left.first_statistics;
    second_statistics = left.second_statistics;
    id = left.id;
  } else if (left.first_statistics > right.second_statistics) {
    first_statistics = right.first_statistics;
    second_statistics = right.second_statistics;
    id = right.id;
  } else {
    if (left.first_statistics < right.first_statistics) {
      first_statistics = left.first_statistics;
      second_statistics = right.first_statistics;
      id = right.id;
    } else {
      first_statistics = right.first_statistics;
      second_statistics = left.first_statistics;
      id = left.id;
    }
  }
}

void SegmentTree::BuildTree(const std::vector<int> &array) {
  buffer_.assign(4 * array.size(), 0);
  BuildOnSegment(array, 1, 0, static_cast<int>(array.size() - 1));
  is_valid_ = true;
}

int SegmentTree::GetSecondStatistics(int query_left, int query_right) const {
  assert(query_right - query_left > 0 && is_valid_);
  TreeNode fictive_node = GetSecondStatisticsOnSegment(1, 0, static_cast<int>(buffer_.size()) / 4 - 1,
                                                       query_left, query_right);
  return fictive_node.second_statistics;
}

void SegmentTree::BuildOnSegment(const std::vector<int> &array, int node_id, int left, int right) {
  if (left == right) {
    buffer_[node_id] = TreeNode(left, array[left]);
    return;
  }

  int left_end = (left + right) / 2;
  int right_begin = (left + right) / 2 + 1;

  BuildOnSegment(array, node_id * 2, left, left_end);
  BuildOnSegment(array, node_id * 2 + 1, right_begin, right);

  buffer_[node_id].ApplySegments(buffer_[node_id * 2], buffer_[node_id * 2 + 1]);
}

TreeNode SegmentTree::
GetSecondStatisticsOnSegment(int node_id, int left, int right, int query_left, int query_right) const {
  if (left == query_left && right == query_right) {
    return buffer_[node_id];
  }

  int left_end = (left + right) / 2;
  int right_begin = (left + right) / 2 + 1;

  if (left <= query_left && query_right <= left_end) {
    return GetSecondStatisticsOnSegment(node_id * 2, left, left_end, query_left, query_right);
  }

  if (right_begin <= query_left && query_right <= right) {
    return GetSecondStatisticsOnSegment(node_id * 2 + 1, right_begin, right, query_left, query_right);
  }

  return TreeNode::
  MakeFictiveNode(GetSecondStatisticsOnSegment(node_id * 2, left, left_end, query_left, left_end),
                  GetSecondStatisticsOnSegment(node_id * 2 + 1, right_begin, right, right_begin, query_right));
}