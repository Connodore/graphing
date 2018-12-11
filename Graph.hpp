#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <unordered_map>
#include <utility>

#include <iostream>
using std::cerr;

#include "Node.hpp"

// My graph library should be called Graph++

// If the user specifies a unique cost type they must have certain operators implemnted, I think + and +=?

// We are currently keeping double the space needed because both Graph's lookup table and the node hold the same value

// Type T better be hashable and copyable

// Could inherit from unordered_map? Could override functions I do not want to offer and hide/delete them

// REMEMBER! GRAPH VALUES MUST BE UNIQUE (for this version of the implementation)
// Data values still need to be unique!! For the meantime

// This id system needs to be kind of smart, if a key gets removed that value will probably have to be reused. Unless the floyd algorithm is written a different way or the operator[] is properly implemented to insert a node if one did not already exist, because the floyd algorithm relies on the idea that the keys are the same

// Should nest node class and Graph needs to keep track of an id counter that way an easier insert function not requiring an id

// A graph is really just a node with multiple 0 weight connections, I don't like wasting space to store 0...

// Ultimately, a graph should be able to be constructed from nothing and when a new adj node is used that wasn't in the graph it gets automatically added

//operator[] can be overloaded and uses {} in call
template<class T, class Cost = size_t>
class Graph
{
public:
    using key_type = T;
    using node_type = Node<T>;
    using size_type = size_t;
    using cost_type = Cost;
    // Probably should define a const too
    // Should probably have a more readable def than being an unordered map
    // Why typename?
    // using iterator = typename std::unordered_map<key_type, node_type*>::iterator;
    using iterator = typename node_type::iterator;
    using const_iterator = typename node_type::const_iterator;

    // Add init list constructor that just takes initial valuessc

    // The default value should be move constructed? for every node to save space?

    // A size constructor does not make much sense for a container that needs unique values
    Graph(/*size_type size = 0*/)
    {
        // for (size_type s = 0; s < size; ++s)
        //     insert();
    }

    // This does not actually make a copy
    // Graph(const Graph& other)
    // : Graph(other.begin(), other.end())
    // {}

    // This does not actually make a copy
    Graph(const Graph& other)
    : m_data(other.m_data), m_node(other.m_node)
    {}


    // NEXT UP!!! IMPLEMENT A WORKING RANGE CONSTRUCTOR AND HAVE THE COPY CONSTRUCTOR DELAGATE TO THAT



    // // This is hard to implement
    // Currently only supports graph iterators, ideally want to support generic iterators (probably InputIt?)
    // template<class GraphIt>
    // Graph(GraphIt first, GraphIt last)
    // {
    //     std::for_each(first, last, [&](const auto& other)
    //     {
    //         // cerr << "og"other.first->val << std::endl;
    //         auto it = insert(other.first->val);
    //     });
    // }

    ~Graph()
    {
        // delete nodes
    }

    // Change return type
    // Should be able to insert with at least a default val
    // void
    // // insert()
    // insert(T val)
    // {
    //     m_node.insert({m_curr_id++, std::pair{new node_type{val}, (cost_type) 0}});
    // }

    // Since the graph should be unqiue a default value is not a good idea
    // void
    // insert(T val = T{})
    // {
    //     m_node.insert({new node_type{val}, (cost_type) 0});
    // }

    // Is this the return type I want?
    // std::pair<iterator, bool>
    // insert(T val)
    // {
    //     return m_nodes.insert({val, new node_type{}});
    // }

    // This will insert repeats of the same val!! This is not unique, is that okay?

    iterator
    insert(T val)
    {
        m_data.insert({val, new node_type{val}});
        return m_node.insert({m_data[val], cost_type{}});
    }

    iterator
    insert(T val, std::pair<iterator, cost_type> adj)
    {
        return insert(val, {adj});
    }

    // This currently cannot handle adding links if the type T does not exist in m_data, this should probably be improved
    iterator
    insert(T val, std::pair<T, cost_type> adj)
    {
        return insert(val, {adj});
    }

    iterator
    insert(T val, std::initializer_list<std::pair<iterator, cost_type>> init)
    {
        return insert(insert(val), init);
    }

    // If a value in the adj list does not yet exist, this won't work, should it auto insert values that don't yet exist in the graph? I think maybe it should
    iterator
    insert(T val, std::initializer_list<std::pair<T, cost_type>> init)
    {
        auto it = insert(val);
        for (auto [adj_val, cost] : init)
            it->first->insert({find(adj_val)->first, cost});
        return it;
    }

    // I think the only combo of insert not implemented is an iterator pos with a pair or init list of type T and cost


    iterator
    insert(iterator pos, std::pair<iterator, cost_type> adj)
    {
        return insert(pos, {adj});
    }

    // At the moment there is no way to make connections to non-existing node, which would then create additional new nodes (it might be good not to include this feature)
    // What if this val already exists?
    // cost_type than iterator or vice versa?


    iterator
    insert(iterator pos, std::initializer_list<std::pair<iterator, cost_type>> init)
    {
        for (auto [adj_it, cost] : init)
            pos->first->insert({adj_it->first, cost});

        return pos;
    }

    // Normal find is not currently supported because we use node iterators, ideally the graph should be able to use type T as a hash for the unordered_map while pointers are used to nodes where needed, but for the meantime we will need a linear find algorithm
    // iterator
    // find(const key_type& key)
    // {
    //     return m_node.find(key);
    // }


    // This is quite inefficient (O(N)), ideally we should hash type T and get constant time find but that requires a combined implemntation to use type T and to use pointers to nodes
    // iterator
    // find(const T& val)
    // {
    //     return std::find_if(begin(), end(), [&](const auto& n)
    //     {
    //         return n.first->val == val;
    //     });
    // }

    iterator
    find(const T& val)
    {
        return m_node.find(m_data[val]);
    }

    const_iterator
    find(const T& val) const
    {
        return m_node.find(m_data[val]);
    }


    // This is literally taking node addresses, this is not the best way to do this but is a reasonable workaround for the moment
    // Ideally this should take a type T
    iterator
    find(node_type* key)
    {
        return m_node.find(key);
    }

    const_iterator
    find(node_type* key) const
    {
        return m_node.find(key);
    }


    iterator
    find(const T& from, const T& to)
    {
        return find(find(from), find(to));
    }

    const_iterator
    find(const T& from, const T& to) const
    {
        return find(find(from), find(to));
    }


    // Find an edge between two nodes
    iterator
    find(iterator from, iterator to)
    {
        if (auto it = from->first->find(to->first); it != to->first->end())
            return it;
        else
            return end();
    }

    const_iterator
    find(const_iterator from, const_iterator to) const
    {
        if (auto it = from->first->find(to->first); it != to->first->end())
            return it;
        else
            return end();
    }

    // If node does not exist a new one will be created, I think
    // Should probs add a const version

    // GAH have this return cost as well and have it insert if it does not already exist, that way I can do g[#][#].second type stuff
    // node_type&
    // operator[](size_type key)
    // {
    //     return m_node[key];
    // }

    iterator
    begin()
    {
        return m_node.begin();
    }

    const_iterator
    begin() const
    {
        return m_node.begin();
    }

    iterator
    end()
    {
        return m_node.end();
    }

    const_iterator
    end() const
    {
        return m_node.end();
    }

    size_type
    size() const
    {
        return m_node.size();
    }

private:
    // std::unordered_map<size_type, node_type> m_data{};

    // size_t m_curr_id = 0;

    // std::unordered_map<key_type, node_type*> m_nodes{};

    std::unordered_map<key_type, node_type*> m_data{};
    node_type m_node{};
    // size_t m_size{};
};


#endif