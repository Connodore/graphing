#ifndef FLOYD_HPP
#define FLOYD_HPP

// Remove later
#include <algorithm>
#include <iostream>
#include <iterator>

using std::cerr;

#include "Graph.hpp"

// Use pseudo code from wikipedia in powerpoint

// Negative weights are NOT supported, looping back to yourself is a valid path (allows for graphs with self loops to be used)

// Will the first, last, pair be useful or should I send the whole graph container
// Make recursive

// Links from ij need to be added to make this algo work. Start off with the version that only calculates distances, not the path itself

// Currently, returns a Graph, ultimately I would like the graph to be written to an iterator
// This really needs to be done or the arguments to the function need to change because the function call requires template parameters because type deduction cannot happen

// I AM RELYING ON THE VALUE OF A NODE TO ALWAYS BE THE KEY TYPE FOR THE GRAPH, THIS WILL RARELY EVER BE THE CASE

// The new graph we are creating must have the initial connections or I have to rework part of my algorithm

// What would it mean for a graph to be passed with iterators that excluded nodes that were on the adj list of some of the nodes in the range?

// Need to remove the auto return type, ideally we should accept an out_iterator as an argument just like the STL algorithms do

// template<class T, class GraphIt>
// template<class T>
// Graph<T>
// floyd(GraphIt first, GraphIt last)
// If this sig is kept we will want const
// floyd(Graph<T>& g)
// floyd(GraphIt first, GraphIt last, GraphIt d_first)

// Not using range algorithm because the range constructor is hard to implement, should switch back to range algo once it's implemented
// template<class GraphIt>
// auto
// floyd(GraphIt first, GraphIt last)

// To use a signature that takes 3 iterators, first, last, and d_first, I need to have custom iterators for the graph implemented, because they are not, to allow partitioning of the graph I will take iterators that are the range of the graph passed in that should be gone over. THIS SHOULD NOT BE IN THE ACTUAL API

// Currently modifies g (yes, I know it says its const)
template<class T, class GraphIt>
void
// Graph<T>
// floyd(const Graph<T> &g)
floyd(Graph<T> &g, GraphIt first, GraphIt last)
{
    // Remember this graph type is hardcoded at the moment!
    // Graph<int> g{first, last};

    // Graph<T> g{g};

    std::for_each(first, last, [&](auto &k)
    {
        std::for_each(first, last, [&](auto &i)
        {
            std::for_each(first, last, [&](auto &j)
            {
                if (auto ik = g.find(i.first->val, k.first->val); ik != g.end())
                    if (auto kj = g.find(k.first->val, j.first->val); kj != g.end())
                    {
                        // Ideally I want to use the Graph's cost_type here
                        size_t cost = ik->second + kj->second;
                        if (auto ij = g.find(i.first->val, j.first->val); ij != g.end())
                        {
                            if (ij != g.end() && ij->second > cost)
                                ij->second = cost;
                        }
                        else
                            g.insert(i.first->val, {j.first->val, cost});
                    }
            });
        });

    });

    // return g;
}

#endif