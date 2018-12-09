#ifndef NODE_HPP
#define NODE_HPP

#include <unordered_map>
#include <utility>


// Remove later
#include <iostream>


// Change adj to unordered_map and give a operator[]

// Need an iterator class that when dereferenced just gives the node and not the cost?


// TAKE AWAY AND THE PAIR AND MAKE IT A STRUCT with a .node and .cost

template<class T, class Cost = size_t>
struct Node
{
  using key_type = size_t;
  using node_type = Node<T>;

  //using node_ptr = node<T, Cost>*;
  using cost_type = Cost;

  // Wrap this pair into a more useable struct?
  using mapped_type = std::pair<node_type*, cost_type>;

  using value_type = std::pair<key_type, mapped_type>;

  // custom iterator type should be implemented
  using iterator = typename std::unordered_map<key_type, mapped_type>::iterator;

  T val;
  //Cost cost; // This was a temp variable, used only be algorithms

  std::unordered_map<key_type, mapped_type> adj;

  // Probably very unsafe, probably should default construct val but I don't want to waste space
  Node()
  : val(T{})
  {}

  Node(T val)
  : val(val)
  {}

  Node(const Node<T>& other)
  : val(other.val), adj(other.adj)
  {}

  // should probably be set to return mapped_type... but it is way more convenient with it just being node_type
  node_type&
  operator[](key_type key)
  {
    // I think it might be because the pair cannot be default constructed if the key does not exist?
    // return adj[key].first WHY IN THE WORLD WILL THIS NOT WORK PROPERLY

    // return *(adj.find(key)->second.first);
    return *(adj[key].first);
  }

  // Change return type to iterator and follow std:: template
  void
  insert(const value_type& value)
  {
    adj.insert(value);
  }

  iterator
  find(key_type key)
  {
    return adj.find(key);
  }

  iterator
  begin()
  {
      return adj.begin();
  }

  iterator
  end()
  {
      return adj.end();
  }

  //std::vector<std::pair<node_ptr, Cost>> adj;

  /*static
  std::vector<std::pair<node_ptr, Cost>>
  succ (node_ptr n)
  {
    return n->adj;
  }*/

  /*static
  bool
  less (const node<T, Cost>* lhs, const node<T, Cost>* rhs)
  {
    return lhs->cost < rhs->cost;
  }*/
};

// Make an edge class?

// No negaive cycles for Floyd Warshall

#endif