#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <unordered_map>
#include <utility>

#include <functional>
#include <iostream>
using std::cerr;

#include "Node.hpp"

// TODO setup nonconst versions of methods to rely on const ones, or vice versa (whichever is the proper way, it is outlined in my Effective C++ book)

// Remember to make it very clear that this graph requires unique values

// My graph library should be called Graph++

// If the user specifies a unique cost type they must have certain operators implemnted, I think + and +=?

// Type T better be hashable and copyable

// REMEMBER! GRAPH VALUES MUST BE UNIQUE (for this version of the implementation)

// FIXME if we are allow the u_map to be accessible it needs to be const, that cannot just be modified whenever. Parts of my current implementation do rely on this functionality so they will need to be updated (I think it should be pretty easy to convert over though). This needs to be const in the iterator but cannot be const within the class

template <class T, class Cost = size_t>
class Graph
{
public:
  using size_type = size_t;
  // Probably should define a const too
  // Should probably have a more readable def than being an unordered map
  // Why typename?
  // using iterator = typename std::unordered_map<key_type, node_type*>::iterator;
  // using iterator = typename node_type::iterator;
  // using const_iterator = typename node_type::const_iterator;

private:
  // using adj_type = std::unordered_map<const T *, Cost>;
  using adj_type = std::unordered_map<std::reference_wrapper<const T>, Cost, std::hash<T>>;
  using graph_type = std::unordered_map<T, adj_type>;

public:
  using iterator = typename graph_type::iterator;
  using local_iterator = typename adj_type::iterator;

public:
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
  // Graph(const Graph &other)
  //     : m_data(other.m_data), m_node(other.m_node)
  // {
  // }

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

  /******************************/

  std::pair<iterator, bool>
  insert(T val)
  {
    return m_nodes.emplace(val, adj_type{});
  }

  std::pair<local_iterator, bool>
  insert(T val, const std::pair<T, Cost> &adj)
  {
    auto [it, _0] = insert(val);
    auto [adj_it, _1] = insert(adj.first);

    return insert(it, {adj_it, adj.second});
  }

  std::pair<local_iterator, bool>
  insert(T val, const std::pair<iterator, Cost> &adj)
  {
    auto [it, _] = insert(val);

    return insert(it, {adj.first, adj.second});
  }

  void
  insert(T val, std::initializer_list<std::pair<T, Cost>> ilist)
  {
    for (const auto &adj : ilist)
      insert(val, adj);
  }

  void
  insert(T val, std::initializer_list<std::pair<iterator, Cost>> ilist)
  {
    for (const auto &adj : ilist)
      insert(val, adj);
  }

  std::pair<local_iterator, bool>
  insert(iterator pos, std::pair<T, Cost> adj)
  {
    auto [adj_it, _] = insert(adj.first);

    return insert(pos, {adj_it, adj.second});
  }

  std::pair<local_iterator, bool>
  insert(iterator pos, const std::pair<iterator, Cost> &adj)
  {
    return pos->second.emplace(adj.first->first, adj.second);
  }

  void
  insert(iterator pos, std::initializer_list<std::pair<T, Cost>> ilist)
  {
    for (const auto &adj : ilist)
      insert(pos, adj);
  }

  // This return type follows what insert does for an u_map
  void
  insert(iterator pos, std::initializer_list<std::pair<iterator, Cost>> ilist)
  {
    for (const auto &adj : ilist)
      insert(pos, adj);
  }

  /******************************/

  iterator
  find(const T &val)
  {
    return m_nodes.find(val);
  }

  // const_iterator
  // find(const T &val) const
  // {
  //     return m_node.find(m_data[val]);
  // }

  // FIXME if the T does not exist this seg faults, it should return the end of the local iterator
  local_iterator
  find(const T &from, const T &to)
  {
    return find(find(from), find(to));
  }

  // const_iterator
  // find(const T &from, const T &to) const
  // {
  //     return find(find(from), find(to));
  // }

  // Find an edge between two nodes
  local_iterator
  find(iterator from, iterator to)
  {
    return from->second.find(to->first);
  }

  // const_iterator
  // find(const_iterator from, const_iterator to) const
  // {
  //     if (auto it = from->first->find(to->first); it != to->first->end())
  //         return it;
  //     else
  //         return end();
  // }

  // If node does not exist a new one will be created, I think
  // Should probs add a const version

  iterator
  begin()
  {
    return m_nodes.begin();
  }

  // const_iterator
  // begin() const
  // {
  //     return m_node.begin();
  // }

  // Begin of adj of a node
  local_iterator
  begin(const T &val)
  {
    return find(val)->second.begin();
  }

  // // Begin of adj of a node
  // const_iterator
  // begin(const T &val) const
  // {
  //     return find(val)->first->begin();
  // }

  // Begin of adj of a node
  local_iterator
  begin(iterator pos)
  {
    return pos->second.begin();
  }

  // // Begin of adj of a node
  // const_iterator
  // begin(const_iterator pos) const
  // {
  //     return find(pos)->first->begin();
  // }

  iterator
  end()
  {
    return m_nodes.end();
  }

  // const_iterator
  // end() const
  // {
  //     return m_node.end();
  // }

  // End of adj of a node
  local_iterator
  end(const T &val)
  {
    return find(val)->second.end();
  }

  // // End of adj of a node
  // const_iterator
  // end(const T &val) const
  // {
  //     return find(val)->first->end();
  // }

  // End of adj of a node
  local_iterator
  end(iterator pos)
  {
    return pos->second.end();
  }

  // // End of adj of a node
  // const_iterator
  // end(const_iterator pos) const
  // {
  //     return find(pos)->first->end();
  // }

  size_type
  size() const
  {
    return m_nodes.size();
  }

private:
  graph_type m_nodes{};
};

// template <class T, class Cost>
// bool operator==(Graph<T, Cost> &lhs, Graph<T, Cost> &rhs)
// {
//     for (auto &n : lhs)
//         for (auto &adj : *(n.first))
//             if (auto edge = rhs.find(n.first->val, adj.first->val); edge != rhs.end())
//             {
//                 if (adj.second != edge->second)
//                     return false;
//             }
//             else
//                 return false;

//     return true;
// }

#endif