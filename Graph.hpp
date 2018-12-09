#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <utility>

#include "Node.hpp"

// This id system needs to be kind of smart, if a key gets removed that value will probably have to be reused. Unless the floyd algorithm is written a different way or the operator[] is properly implemented to insert a node if one did not already exist, because the floyd algorithm relies on the idea that the keys are the same

// Should nest node class and Graph needs to keep track of an id counter that way an easier insert function not requiring an id

// A graph is really just a node with multiple 0 weight connections, I don't like wasting space to store 0...

// Ultimately, a graph should be able to be constructed from nothing and when a new adj node is used that wasn't in the graph it gets automatically added

//operator[] can be overloaded and uses {} in call
template<class T, class Cost = size_t>
class Graph
{
public:
    using node_type = Node<T>;
    using size_type = size_t;
    using cost_type = Cost;
    // Probably should define a const too
    // Should probably have a more readable def than being an unordered map
    // Why typename?
    using iterator = typename node_type::iterator;

    // Add init list constructor that just takes initial valuessc

    // The default value should be move constructed? for every node to save space?
    Graph(size_type size = 0)
    {
        // Is this cast okay? Should I use static_cast? (probably should if possible)
        // std::generate_n(std::inserter(m_node.adj, m_node.adj.end()), size, [key = (size_type) 0]() mutable
        // {
        //     return std::pair{key++, std::pair{node_type{}, (cost_type) 0}};
        // });
        std::generate_n(std::inserter(m_node.adj, m_node.adj.end()), size, [this]()
        {
            return std::pair{m_curr_id++, std::pair{new node_type{}, (cost_type) 0}};
        });
    }

    // This does not actually make a copy
    Graph(const Graph& other)
    {
        this->m_curr_id = other.m_curr_id;
        this->m_node = other.m_node;
    }

    ~Graph()
    {
        // delete nodes
    }

    // Change return type
    // Should be able to insert with at least a default val
    void
    // insert()
    insert(T val)
    {
        m_node.insert({m_curr_id++, std::pair{new node_type{val}, (cost_type) 0}});
    }

    // If node does not exist a new one will be created, I think
    // Should probs add a const version

    // GAH have this return cost as well and have it insert if it does not already exist, that way I can do g[#][#].second type stuff
    node_type&
    operator[](size_type key)
    {
        return m_node[key];
    }

    iterator
    begin()
    {
        return m_node.adj.begin();
    }

    iterator
    end()
    {
        return m_node.adj.end();
    }

    size_type
    size() const
    {
        return m_node.adj.size();
    }

private:
    // std::unordered_map<size_type, node_type> m_data{};

    size_t m_curr_id = 0;

    node_type m_node{};
};


#endif