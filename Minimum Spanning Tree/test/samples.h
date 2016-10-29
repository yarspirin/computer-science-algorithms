//
// Created by whoami on 10/29/16.
//

#ifndef MST_SAMPLES_H
#define MST_SAMPLES_H

const EdgeList<int> kSampleEdgeList = {{0, 1, 1},
                                       {1, 0, 1},
                                       {1, 2, 2},
                                       {2, 1, 2},
                                       {2, 3, 5},
                                       {3, 2, 5},
                                       {3, 0, 4},
                                       {0, 3, 4}};

const EdgeList<int16_t> kShortEdgeList = {{0, 1, 1},
                                          {1, 0, 1},
                                          {1, 2, 2},
                                          {2, 1, 2},
                                          {2, 3, 5},
                                          {3, 2, 5},
                                          {3, 0, 4},
                                          {0, 3, 4}};

const EdgeList<int64_t> kLongEdgeList = {{0, 1, 1000000000},
                                         {1, 0, 1000000000},
                                         {1, 2, 2000000000},
                                         {2, 1, 2000000000},
                                         {2, 3, 5000000000},
                                         {3, 2, 5000000000},
                                         {3, 0, 4000000000},
                                         {0, 3, 4000000000}};

const EdgeList<float> kFloatEdgeList = {{0, 1, 1.0},
                                        {1, 0, 1.0},
                                        {1, 2, 2.0},
                                        {2, 1, 2.0},
                                        {2, 3, 5.0},
                                        {3, 2, 5.0},
                                        {3, 0, 4.0},
                                        {0, 3, 4.0}};

const EdgeList<double> kDoubleEdgeList = {{0, 1, 100.0},
                                          {1, 0, 100.0},
                                          {1, 2, 200.0},
                                          {2, 1, 200.0},
                                          {2, 3, 500.0},
                                          {3, 2, 500.0},
                                          {3, 0, 400.0},
                                          {0, 3, 400.0}};


#endif //MST_SAMPLES_H
