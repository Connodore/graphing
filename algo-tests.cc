#include "catch.hpp"
#include "Floyd.hpp"
#include "Graph.hpp"

#include <algorithm>
#include <iostream>
using std::cerr;

template <class GraphIt>
void printg(GraphIt first, GraphIt last)
{
    std::for_each(first, last, [](auto &k) {
        cerr << "Node: " << k.first << std::endl;
        std::for_each(k.second.begin(), k.second.end(), [=](auto &i) {
            cerr << "    Adj: " << i.first << "    Cost: " << i.second << std::endl;
        });
    });
}

SCENARIO("Floyd is run")
{
    THEN("the resulting graph is structured properly")
    {
        Graph<int> g{};
        g.insert(0, {2, 7});
        g.insert(1, {{0, 6}, {2, 4}, {3, 1}, {6, 3}});
        g.insert(2, {{4, 4}, {6, 1}});
        g.insert(3, {5, 1});
        g.insert(4, {2, 3});
        g.insert(5, {1, 3});
        g.insert(6, {2, 8});
        g.insert(7, {{5, 1}, {6, 1}});

        floyd(g, g.begin(), g.end());

        printg(g.begin(), g.end());
    }
}