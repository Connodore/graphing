#include <cstdlib>
#include <iostream>

//#include "AdjMatrix.hpp"

#include "Floyd.hpp"
#include "Graph.hpp"

#include <algorithm>
#include <unordered_map>

using std::cerr;

template <class GraphIt>
void printg(GraphIt first, GraphIt last);

int main()
{
    // m.insert({1, std::unordered_map<const T *, Cost>{}});
    // m.insert({2, std::unordered_map<const T *, Cost>{}});
    // m.insert({3, std::unordered_map<const T *, Cost>{}});

    // m[1].insert({&m.find(2)->first, 55});

    // for (auto &[key, adj] : m)
    // {
    //     cerr << "from: " << key << "    ";

    //     adj.insert({&m.find(3)->first, 10});
    //     for (auto &[val, cost] : adj)
    //     {
    //         cost = 101;
    //         cerr << "to: " << *val << "    "
    //              << "for: " << cost << std::endl;
    //     }
    //     cerr << std::endl;
    // }

    Graph<int> g{};

    // auto [n0, _0] = g.insert(0);
    // auto [n1, _1] = g.insert(1);
    // auto [n2, _2] = g.insert(2);
    // auto [n3, _3] = g.insert(3);
    // auto [n4, _4] = g.insert(4);
    // auto [n5, _5] = g.insert(5);
    // auto [n6, _6] = g.insert(6);
    // auto [n7, _7] = g.insert(7);

    // g.insert(n0, {8, 3});
    // g.insert(n1, {{9, 7}, {10, 3}});

    g.insert(0, {{3, 9}, {4, 6}});
    g.insert(1, {{5, 9}, {6, 4}});
    g.insert(2, {{1, 3}, {5, 2}, {6, 6}});
    g.insert(3, {{1, 7}, {7, 1}});
    g.insert(4, {6, 9});
    g.insert(5, {{1, 4}, {7, 2}});
    g.insert(6, {7, 2});
    g.insert(7);

    // g.insert(n0, {n1, 7});
    // g.insert(n1, {n2, 9});
    // g.insert(n2, {{n0, 8}, {n4, 7}, {n6, 6}});
    // g.insert(3, {{n1, 1}, {n5, 3}, {n7, 4}});
    // g.insert(n4, {n2, 8});
    // g.insert(n5, {n3, 9});
    // g.insert(n6, {{n2, 7}, {n4, 7}, {n5, 2}});
    // g.insert(7, {n6, 3});

    cerr << "Before Floyd\n"
         << std::endl;
    printg(g.begin(), g.end());
    cerr << std::endl;

    floyd(g, g.begin(), g.end());

    cerr << "After Floyd\n"
         << std::endl;
    printg(g.begin(), g.end());

    return EXIT_SUCCESS;
}

// TODO remove reliance on adj list, even though this is accessible now it won't be after custom iterators are implemented
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

// It would be cool with floyd and the graph class if you could do
// begin(n1) and end(n8) and traverse the best path