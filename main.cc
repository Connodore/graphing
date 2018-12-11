#include <cstdlib>
#include <iostream>

//#include "AdjMatrix.hpp"

#include "Floyd.hpp"
#include "Graph.hpp"

#include <algorithm>
#include <unordered_map>

using std::cerr;

template<class GraphIt>
void
printg(GraphIt first, GraphIt last);

int
main()
{
    Graph<int> g{};

    auto n0 = g.insert(0);
    auto n1 = g.insert(1);
    auto n2 = g.insert(2);
    auto n3 = g.insert(3);
    auto n4 = g.insert(4);
    auto n5 = g.insert(5);
    auto n6 = g.insert(6);
    auto n7 = g.insert(7);

    g.insert(n0, {{n2, 2}, {n3, 5}});
    g.insert(n1, {{n2, 9}});
    g.insert(n2, {{n1, 5}, {n5, 2}, {n6, 7}});
    g.insert(n3, {{n7, 9}});
    g.insert(n4, {{n6, 4}});
    g.insert(n5, {{n6, 3}});
    g.insert(n6, {{n5, 3}});

    cerr << "Before Floyd\n" << std::endl;
    printg(g.begin(), g.end());
    cerr << std::endl;

    auto it1 = g.find(n1->first);
    auto it2 = g.find(n2->first);
    auto it = g.find(it1, it2);

    cerr << it->first->val << std::endl;

    auto fg = floyd(g);
    // auto fg = floyd(g.begin(), g.end());

    cerr << "After Floyd\n" << std::endl;
    printg(fg.begin(), fg.end());

    printg(g.begin(), g.end());

    return EXIT_SUCCESS;
}

template<class GraphIt>
void
printg(GraphIt first, GraphIt last)
{
    std::for_each(first, last, [](auto& k)
    {
        cerr << "Node: " << k.first->val << "    " << k.first << std::endl;
        std::for_each(k.first->begin(), k.first->end(), [=](auto& i)
        {
            cerr << "    Adj: " << i.first->val << "    Cost: " << i.second << "    " << i.first << std::endl;
        });
    });
}

// It would be cool with floyd and the graph class if you could do
// begin(n1) and end(n8) and traverse the best path