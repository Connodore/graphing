#include <cstdlib>
#include <iostream>

//#include "AdjMatrix.hpp"

#include "Floyd.hpp"
#include "Graph.hpp"


using std::cerr;
using std::cout;

template<class GraphIt>
void
printg(GraphIt first, GraphIt last);

int
main()
{
    Graph<int> g{8};

    g[0].val = 0;
    g[1].val = 1;
    g[2].val = 2;
    g[3].val = 3;
    g[4].val = 4;
    g[5].val = 5;
    g[6].val = 6;
    g[7].val = 7;


    for (auto &[id, node] : g)
        cout << node.first->val << std::endl;

    /*
        | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7
    ---------------------------------
    0 |
    ---------------------------------
    1 |
    ---------------------------------
    2 |
    ---------------------------------

    ---------------------------------

    ---------------------------------
    */


    g[0].adj = {{2, {&g[2], 2}}, {3, {&g[3], 5}}};
    g[1].adj = {{2, {&g[2], 9}}};
    g[2].adj = {{1, {&g[1], 5}}, {5, {&g[5], 2}}, {6, {&g[6], 7}}};
    g[3].adj = {{7, {&g[7], 9}}};
    g[4].adj = {{6, {&g[6], 4}}};
    g[5].adj = {{6, {&g[6], 3}}};
    g[6].adj = {{5, {&g[5], 3}}};
    g[7].adj = {};


    //   g[7].insert({4, {&g[4], 3}});

    // for (auto [key, p] : g[0].adj)
    //   cout << p.second << std::endl;

    // for (auto &[id, node] : g)
    //   cout << node.val << std::endl;

    // cout << "hi" << g[0][3][0][3].val << std::endl;

    // g[0][3].val = 33;
    // cout << "Real: " << g[3].val << std::endl;
    // cout << "Ref : " << g[0][3].val << std::endl;

    cout << "Before Floyd\n" << std::endl;
    printg(g.begin(), g.end());
    cout << std::endl;

    // auto fg = floyd<int>(g.begin(), g.end());
    auto fg = floyd(g);

    cout << "After Floyd\n" << std::endl;
    printg(fg.begin(), fg.end());

    return EXIT_SUCCESS;
}

template<class GraphIt>
void
printg(GraphIt first, GraphIt last)
{
    std::for_each(first, last, [](auto& k)
    {
        cerr << "Node: " << k.second.first->val << std::endl;
        std::for_each(k.second.first->begin(), k.second.first->end(), [=](auto& i)
        {
            cerr << "    Adj: " << i.second.first->val << "    Cost: " << i.second.second << std::endl;
        });
    });
}

// It would be cool with floyd and the graph class if you could do
// begin(n1) and end(n8) and traverse the best path