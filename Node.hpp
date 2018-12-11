#ifndef NODE_HPP
#define NODE_HPP

#include <unordered_map>
#include <utility>


// Remove later
#include <iostream>

// Change this file to 4 tabs

// Change adj to unordered_map and give a operator[]

// Need an iterator class that when dereferenced just gives the node and not the cost?

// To access data from an iterator the call is it->first->val, ideally the map iterator would be wrapped and we could do *(it->first) and this would get us the val, or something like that



// TAKE AWAY AND THE PAIR AND MAKE IT A STRUCT with a .node and .cost

template<class T, class Cost = size_t>
struct Node
{
  using size_type = size_t;
  // using key_type = size_t;
  using node_type = Node<T>;
  using key_type = node_type*;

  //using node_ptr = node<T, Cost>*;
  using cost_type = Cost;

  // struct Edge
  // {
  //   node_type *toNode;
  //   cost_type cost;
  // };

  // Wrap this pair into a more useable struct?
  // using mapped_type = std::pair<node_type*, cost_type>;
  // using mapped_type = Edge;
  using mapped_type = cost_type;

  using value_type = std::pair<key_type, mapped_type>;

  // custom iterator type should be implemented
  using iterator = typename std::unordered_map<key_type, mapped_type>::iterator;
  using const_iterator = typename std::unordered_map<key_type, mapped_type>::const_iterator;



  // Header node stores a default T, kind of wasted space and hopefully it has a default value
  T val{};
  std::unordered_map<key_type, mapped_type> adj{};

  // Probably very unsafe, probably should default construct val but I don't want to waste space
  Node()
  {}

  Node(T val)
  : val(val)
  {}

  // I don't think actually does a deep copy
  Node(const Node<T>& other)
  : val(other.val), adj(other.adj)
  {}

  // should probably be set to return mapped_type... but it is way more convenient with it just being node_type
  // node_type&
  // operator[](key_type key)
  // {
  //   // I think it might be because the pair cannot be default constructed if the key does not exist?
  //   // return adj[key].first WHY IN THE WORLD WILL THIS NOT WORK PROPERLY

  //   // return *(adj.find(key)->second.first);
  //   return *(adj[key].toNode);
  // }

  // Change return type to iterator and follow std:: template
  // std::pair<iterator, bool>
  iterator
  insert(const value_type& value)
  {
    return adj.insert(value).first;
  }



  iterator
  find(key_type key)
  {
    return adj.find(key);
  }

  const_iterator
  find(key_type key) const
  {
    return adj.find(key);
  }

  iterator
  begin()
  {
      return adj.begin();
  }

  const_iterator
  begin() const
  {
    return adj.begin();
  }

  iterator
  end()
  {
      return adj.end();
  }

  // Could setup const versions to rely on nonconst ones implementations (I think in my C++ programming book they do this)
  const_iterator
  end() const
  {
    return adj.end();
  }

  size_type
  size() const
  {
    return adj.size();
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




// template<class T, class Cost = size_t>
// struct GraphIterator
// {
//   using node = Node<T>;
//   using self = GraphIterator<T>;

//   using reference = std::pair<T, Cost>&;
//   using pointer = std::pair<T, Cost>*;

//   explicit
//   GraphIterator(node* nodeptr)
//   : m_nodeptr(nodeptr)
//   {}

//   reference
//   operator*() const
//   {
//     return m_nodeptr->val;
//   }

//   pointer
//   operator->() const
//   {
//     return &m_nodeptr->val;
//   }

//   // pre
//   // Self&
//   // operator++()
//   // {
//   //   m_nodeptr =
//   // }

//   node* m_nodeptr;
// };

// Make an edge class?

// No negaive cycles for Floyd Warshall

#endif