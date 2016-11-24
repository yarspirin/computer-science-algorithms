//
// Created by whoami on 11/17/16.
//

#include <cassert>
#include <queue>

#include "Solver.h"

void Solver::FindMinCut(int vertex, std::vector<bool> &cut) {
  cut[vertex] = true;
  for (auto& current : adjacent_lists_[vertex]) {
    int next = edge_list_[current].to;
    if (!cut[next] && edge_list_[current].capacity > edge_list_[current].flow) {
      FindMinCut(next, cut);
    }
  }
}

std::pair<std::string, std::string> Solver::RetrieveTemplates() {
  assert(is_correlation_found);

  std::string retrieved_origin = "";
  std::string retrieved_pattern = "";

  // Building minumum cut
  std::vector<int> min_cut;
  std::vector<bool> cut(static_cast<size_t>(num_vertices_), false);

  FindMinCut(source_, cut);

  for (int i = 0; i < num_vertices_; ++i) {
    if (i != source_ && cut[i]) {
      min_cut.push_back(i);
    }
  }

  // Retrieving
  int shift = 0;
  int current = 0;

  for (int i = 0; i < origin_.length(); ++i) {
    if (origin_[i] != '?') {
      retrieved_origin.push_back(origin_[i]);
      continue;
    }

    if (shift < min_cut.size() && min_cut[shift] == current) {
      retrieved_origin.push_back('0');
      shift += 1;
    } else {
      retrieved_origin.push_back('1');
    }
    current += 1;
  }

  current = 0;

  for (int i = 0; i < pattern_.length(); ++i) {
    if (pattern_[i] != '?') {
      retrieved_pattern.push_back(pattern_[i]);
      continue;
    }

    if (shift < min_cut.size() && min_cut[shift] == current + origin_question_marks_) {
      retrieved_pattern.push_back('0');
      shift += 1;
    } else {
      retrieved_pattern.push_back('1');
    }
    current += 1;
  }

  return std::make_pair(retrieved_origin, retrieved_pattern);
}

int Solver::FindMaxCorrelation() {
  assert(is_valid);

  int flow = 0;
  std::vector<int> distances;

  while (RunInBreadth(distances)) {
    auxiliary_.assign(static_cast<size_t>(num_vertices_), 0);
    int current_flow = RunInDepth(source_, std::numeric_limits<int>::max() / 2, distances);

    while (current_flow) {
      flow += current_flow;
      current_flow = RunInDepth(source_, std::numeric_limits<int>::max() / 2, distances);
    }
  }

  is_correlation_found = true;
  return flow + difference_;
}

bool Solver::RunInBreadth(std::vector<int>& distances) {
  distances.assign(static_cast<size_t>(num_vertices_), -1);
  distances[source_] = 0;

  std::queue<int> queue;
  queue.push(source_);
  while (!queue.empty()) {
    int top = queue.front();
    queue.pop();

    if (distances[target_] != -1) {
      break;
    }

    for (auto& vertex : adjacent_lists_[top]) {
      int next = edge_list_[vertex].to;
      if (distances[next] == -1 &&
          edge_list_[vertex].flow < edge_list_[vertex].capacity) {
        queue.push(next);
        distances[next] = distances[top] + 1;
      }
    }
  }

  return distances[target_] != -1;
}

int Solver::RunInDepth(int vertex, int min_capacity, const std::vector<int>& distances) {
  if (vertex == target_ || min_capacity == 0) {
    return min_capacity;
  }

  while (auxiliary_[vertex] < adjacent_lists_[vertex].size()) {
    int from = adjacent_lists_[vertex][auxiliary_[vertex]];
    int to = edge_list_[from].to;

    if (distances[to] == distances[vertex] + 1) {
      int top = RunInDepth(to,
                           std::min(min_capacity, edge_list_[from].capacity - edge_list_[from].flow),
                           distances);
      if (top != 0) {
        edge_list_[from].flow += top;
        edge_list_[from ^ 1].flow -= top;
        return top;
      }
    }

    auxiliary_[vertex] += 1;
  }

  return 0;
}

Solver::Solver(const std::string &origin, const std::string &pattern)
    : is_correlation_found(false),
      is_valid(false),
      origin_(origin),
      pattern_(pattern),
      difference_(0) {

  origin_question_marks_ = QuestionMarksCounter(origin_);
  pattern_question_marks_ = QuestionMarksCounter(pattern_);

  source_ = origin_question_marks_+ pattern_question_marks_;
  target_ = origin_question_marks_ + pattern_question_marks_ + 1;
  num_vertices_ = origin_question_marks_ + pattern_question_marks_ + 2;
}


void Solver::Init() {
  int pos = 0;

  adjacent_lists_.resize(static_cast<size_t>(num_vertices_));

  for (int i = 0; i < origin_.length() - pattern_.length() + 1; ++i) {
    int u = pos;
    int v = 0;

    for (int j = 0; j < pattern_.length(); ++j) {
      if (origin_[i + j] == '0') {
        if (pattern_[j] == '0') {
          continue;
        } else if (pattern_[j] == '1') {
          difference_ += 1;
        } else if (pattern_[j] == '?') {
          AddEdge(origin_question_marks_+ pattern_question_marks_,
                  origin_question_marks_ + v,
                  1, 0);
        } else {
          assert(true);
        }
      } else if (origin_[i + j] == '1') {
        if (pattern_[j] == '0') {
          difference_ += 1;
        } else if (pattern_[j] == '1') {
          continue;
        } else if (pattern_[j] == '?') {
          AddEdge(origin_question_marks_ + v,
                  origin_question_marks_ + pattern_question_marks_ + 1,
                  1, 0);
        } else {
          assert(true);
        }
      } else if (origin_[i + j] == '?') {
        if (pattern_[j] == '0') {
          AddEdge(origin_question_marks_ + pattern_question_marks_,
                  u,
                  1, 0);
        } else if (pattern_[j] == '1') {
          AddEdge(u,
                  origin_question_marks_ + pattern_question_marks_ + 1,
                  1, 0);
        } else if (pattern_[j] == '?') {
          AddEdge(u, origin_question_marks_ + v, 1, 0);
          AddEdge(origin_question_marks_ + v, u, 1, 0);
        } else {
          assert(true);
        }
      } else {
        assert(true);
      }

      if (origin_[i + j] == '?') {
        u += 1;
      }

      if (pattern_[j] == '?') {
        v += 1;
      }
    }

    if (origin_[i] == '?') {
      pos += 1;
    }
  }

  is_valid = true;
}

void Solver::AddEdge(int from, int to, int capacity, int flow) {
  Edge direct_edge(from, to, capacity, flow);
  Edge reversed_edge(to, from, 0, flow);

  adjacent_lists_[from].push_back(static_cast<int>(edge_list_.size()));
  edge_list_.push_back(direct_edge);

  adjacent_lists_[to].push_back(static_cast<int>(edge_list_.size()));
  edge_list_.push_back(reversed_edge);
}