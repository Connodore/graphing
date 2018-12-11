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

// Currently modifies g (yes, I know it says its const)
template<class T>
Graph<T>
floyd(const Graph<T> &g)
{
    // auto first = g.begin(), last = g.end();

    // Remember this graph type is hardcoded at the moment!
    // Graph<int> fg{first, last};

    Graph<T> fg{g};

    std::for_each(fg.begin(), fg.end(), [&](auto &k)
    {
        std::for_each(fg.begin(), fg.end(), [&](auto &i)
        {
            std::for_each(fg.begin(), fg.end(), [&](auto &j)
            {
                // auto i_val = i.first->val, j_val = j.first->val, k_val = k.first->val;

                // if (auto ik = i.first->find(k_val); ik != i.first->end())
                //     if (auto kj = k.first->find(j_val); kj != k.first->end())
                //     {
                //         size_t cost = ik->second + kj->second;
                //         if (i.first->find(j_val) != i.first->end())
                //         {
                //             if (auto it_ij = copy_g[i_val].find(j_val); it_ij != copy_g[i_val].end() && it_ij->second.cost > cost)
                //                 it_ij->second.cost = cost;
                //         }
                //         else
                //         {
                //             copy_g[i_val].insert({j_val, {j.second.toNode, cost}});
                //         }
                //     }



                if (auto ik = fg.find(fg.find(i.first), fg.find(k.first)); ik != fg.end())
                    if (auto kj = fg.find(fg.find(k.first), fg.find(j.first)); kj != fg.end())
                    {
                        // Ideally I want to use the Graph's cost_type here
                        size_t cost = ik->second + kj->second;
                        if (fg.find(fg.find(i.first), fg.find(j.first)) != fg.end())
                        {
                            if (auto ij = fg.find(fg.find(i.first), fg.find(j.first)); ij != fg.end() && ij->second > cost)
                                ij->second = cost;
                        }
                        else
                            fg.insert(fg.find(i.first), {fg.find(j.first), cost});
                    }
            });
        });

    });

    return fg;
}

#endif