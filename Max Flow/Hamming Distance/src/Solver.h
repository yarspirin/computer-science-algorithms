//
// Created by whoami on 11/17/16.
//

#ifndef HAMMING_DISTANCE_SOLVER_H
#define HAMMING_DISTANCE_SOLVER_H

#include <vector>
#include <string>

struct Edge {
  Edge()
      : from(0),
        to(0),
        capacity(0),
        flow(0) { }

  Edge(int _from, int _to, int _capacity, int _flow)
      : from(_from),
        to(_to),
        capacity(_capacity),
        flow(_flow) { }

  int from, to;
  int capacity;
  int flow;
};

using EdgeList = std::vector<Edge>;
using AdjacentList = std::vector<int>;

// Does the whole work
class Solver {
 public:
  Solver(const std::string& origin, const std::string& pattern);

  void Init();

  // Calculate the maximum correlation for the given templates
  // Based on Dinic algorithm
  int FindMaxCorrelation();

  // Restore the given template strings
  std::pair<std::string, std::string> RetrieveTemplates();

 private:

  // Divide the graph into two parts
  void FindMinCut(int vertex, std::vector<bool>& cut);

  int QuestionMarksCounter(const std::string& str) const {
    return static_cast<int>(std::count(str.begin(), str.end(), '?'));
  }

  void AddEdge(int from, int to, int capacity, int flow);

  // Helper function, a part of Dinic algorithm
  bool RunInBreadth(std::vector<int>& distances);

  // Helper function, a part of Dinic algorithm
  int RunInDepth(int vertex, int min_capacity, const std::vector<int>& distances);

  bool is_valid;
  bool is_correlation_found;

  int source_, target_;
  int num_vertices_;

  int difference_;

  std::string origin_;
  std::string pattern_;

  int origin_question_marks_;
  int pattern_question_marks_;

  std::vector<AdjacentList> adjacent_lists_;
  EdgeList edge_list_;

  std::vector<int> auxiliary_;
};


#endif //HAMMING_DISTANCE_SOLVER_H
