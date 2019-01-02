#include <algorithm>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_set>

// Located in Github repository "CC-Utilities"
#include "CC-Utilities/line.hpp"

#include "catch.hpp"
#include "Graph.hpp"

// Remove later
#include <iostream>
using std::cerr;

// FIXME I will need to put multiple adjs into an unordered_set as well when I do checks

/**************************/
// I am sure these helper functions could be written better

// for (auto s : gtous(g))
//     cerr << s << std::endl;
// cerr << std::endl;
// for (auto s : ftous("tests/small-connected"))
//     cerr << s << std::endl;
// cerr << std::endl;

// Should take a const arg once the const begin and end are implemented
template <class T>
std::unordered_set<std::string>
gtous(Graph<T> &g)
{
    std::unordered_set<std::string> us{};
    std::for_each(g.begin(), g.end(), [&](const auto &n) {
        std::stringstream ss{};

        ss << n.first << "|";
        std::for_each(g.begin(n.first), g.end(n.first), [&](const auto &adj) {
            ss << " "
               << "{" << adj.first << "," << adj.second << "}";
        });
        us.insert(ss.str());
    });
    return us;
}

std::unordered_set<std::string>
ftous(const std::string &filename)
{
    std::ifstream in{filename};
    return std::unordered_set<std::string>{std::istream_iterator<line>{in}, {}};
}

template <class T>
bool g_is_correct(Graph<T> &g, const std::string &filename)
{
    return gtous(g) == ftous(filename);
}

/**************************/

SCENARIO("Default construct a graph")
{
    Graph<int> g{};

    THEN("the size is 0")
    {
        REQUIRE(g.size() == 0);
    }
}

// TODO have a testing scenario that only checks return values?
SCENARIO("Insertions can be done")
{
    GIVEN("an empty graph")
    {
        Graph<int> g{};

        REQUIRE(g.size() == 0);

        WHEN("single values are inserted")
        {
            g.insert(0);
            g.insert(1);
            g.insert(2);
            g.insert(3);
            g.insert(4);

            THEN("the size is 5")
            {
                REQUIRE(g.size() == 5);
            }
            THEN("the graph is structured properly")
            {
                REQUIRE(g_is_correct(g, "tests/t1"));
            }
        }

        WHEN("an initializer list of values is used")
        {
            g.insert({0, 1, 2, 3, 4});

            THEN("the size is 5")
            {
                REQUIRE(g.size() == 5);
            }
            THEN("the graph is structured properly")
            {
                REQUIRE(g_is_correct(g, "tests/t1"));
            }
        }

        WHEN("a value is inserted and contains an edge")
        {
            WHEN("the initial value does not exist")
            {
                WHEN("the edge is to a value")
                {
                    WHEN("the edge value exists")
                    {
                        g.insert(0);
                        g.insert(1, {0, 7});
                        g.insert(2, {0, 3});
                        g.insert(3, {2, 2});
                        g.insert(4, {0, 4});
                        g.insert(5, {4, 1});

                        THEN("the size is 6")
                        {
                            REQUIRE(g.size() == 6);
                        }
                        THEN("the graph is structured properly")
                        {
                            REQUIRE(g_is_correct(g, "tests/t2"));
                        }
                    }

                    WHEN("the edge value does not exist")
                    {
                        g.insert(1, {0, 7});
                        g.insert(3, {2, 8});
                        g.insert(4, {5, 1});

                        THEN("the size is 6")
                        {
                            REQUIRE(g.size() == 6);
                        }
                        THEN("the graph is structured properly")
                        {
                            REQUIRE(g_is_correct(g, "tests/t3"));
                        }
                    }
                }
                WHEN("the edge is to an iterator")
                {
                }
            }

            WHEN("the initial value exists")
            {
            }
        }
    }
}

/******************************/
// Capacity

SCENARIO("Capacity is correct")
{
    GIVEN("an empty graph")
    {
        Graph<int> g{};

        THEN("the graph is empty")
        {
            REQUIRE(g.empty());
            REQUIRE(g.size() == 0);
        }
    }

    GIVEN("A non-connected graph")
    {
        Graph<int> g{};
        g.insert({0, 1, 2, 3, 4, 5, 6, 7});

        THEN("the graph is not empty")
        {
            REQUIRE(!g.empty());
            REQUIRE(g.size() != 0);
        }
        THEN("the adjacency lists are empty")
        {
            WHEN("the value functions are used")
            {
                for (const auto &[val, _] : g)
                {
                    REQUIRE(g.empty(val));
                    REQUIRE(g.size(val) == 0);
                }
            }
            WHEN("the iterator functions are used")
            {
                for (auto it = g.begin(); it != g.end(); ++it)
                {
                    REQUIRE(g.empty(it));
                    REQUIRE(g.size(it) == 0);
                }
            }
        }
    }

    GIVEN("a connected graph")
    {
        Graph<int> g{};
        g.insert(0, {{1, 5}, {2, 1}, {4, 3}});
        g.insert(1, {3, 2});
        g.insert(2, {{0, 9}, {1, 7}, {4, 2}});
        g.insert(3, {1, 8});
        g.insert(4, {{2, 4}, {6, 9}});
        g.insert(5, {{1, 7}, {3, 9}, {7, 3}});
        g.insert(6, {{4, 5}, {5, 1}, {7, 1}});
        g.insert(7, {0, 2});

        THEN("the graph is not empty")
        {
            REQUIRE(!g.empty());
            REQUIRE(g.size() != 0);
        }
        THEN("the adjacency lists are not empty")
        {
            WHEN("the value functions are used")
            {
                for (const auto &[val, _] : g)
                {
                    REQUIRE(!g.empty(val));
                    REQUIRE(g.size(val) != 0);
                }
            }
            WHEN("the iterator functions are used")
            {

                for (auto it = g.begin(); it != g.end(); ++it)
                {
                    REQUIRE(!g.empty(it));
                    REQUIRE(g.size(it) != 0);
                }
            }
        }
    }
}

// Capacity
/******************************/