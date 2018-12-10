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

// template<class T, class GraphIt>
template<class T>
Graph<T>
// floyd(GraphIt first, GraphIt last)
// If this sig is kept we will want const
floyd(Graph<T>& g)
// floyd(GraphIt first, GraphIt last, GraphIt d_first)
{
    auto first = g.begin(), last = g.end();
    Graph<int> copy_g{g};

    std::for_each(first, last, [=, &copy_g](auto &k)
    {
        std::for_each(first, last, [=, &copy_g](auto &i)
        {
            std::for_each(first, last, [=, &copy_g](auto &j)
            {
                auto i_val = i.second.toNode->val, j_val = j.second.toNode->val, k_val = k.second.toNode->val;

                if (auto it_ik = i.second.toNode->find(k_val); it_ik != i.second.toNode->end())
                    if (auto it_kj = k.second.toNode->find(j_val); it_kj != k.second.toNode->end())
                    {
                        size_t  cost = it_ik->second.cost + it_kj->second.cost;
                        if (i.second.toNode->find(j_val) != i.second.toNode->end())
                        {
                            if (auto it_ij = copy_g[i_val].find(j_val); it_ij != copy_g[i_val].end() && it_ij->second.cost > cost)
                                it_ij->second.cost = cost;
                        }
                        else
                        {
                            copy_g[i_val].insert({j_val, {j.second.toNode, cost}});
                        }
                    }
            });
        });

    });

    return copy_g;
}

#endif