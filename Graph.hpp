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

// My graph library should be called Graph++
// Type T better be hashable and copyable

// IMPORTANT: What if we do not make the adj list const, what if instead, if the user wants to add links that's okay as long as they use the type we require (<std::reference_wrapper<const T>, Cost>)? This would allow us to add links in with just using iterators and not needing the whole graph object, additionally this kind of follows how the u_map interface already words since users need to insert a pair type. It might be possible that the type can be deduced by the compiler as well which would make the syntax cleaner. Summary: Let's try keeping the adj list non-const

// TODO Make sure formatting is similar across all files
// TODO setup nonconst versions of methods to rely on const ones, or vice versa (whichever is the proper way, it is outlined in my Effective C++ book)
// TODO Remember to make it very clear that this graph requires unique values (at least for this implementation)

// No decision has been made on const_iterator being the only iterator
// Could write a custom iterator class that extends our u_map iterator and adds an implicit cast to const from non-const

// TODO Pickup after "insert" in the adjacency interface, after that interface is done only the ctor, dtor, and op= need to have skeleton code added

// Take away the default cost type?
template <class T, class Cost = unsigned long long>
class Graph
{
public:
  // Should probably have a more readable def than being an unordered map
  // Why typename?

private:
  // using adjacency_type = std::unordered_map<const T *, Cost>;
  using adjacency_type = std::unordered_map<std::reference_wrapper<const T>, Cost, std::hash<T>>;
  using graph_type = std::unordered_map<T, adjacency_type>;

public:
  using key_type = T;
  using value_type = const T;
  using adjacency_value_type = std::pair<const key_type, Cost>;

  using size_type = typename graph_type::size_type;
  using adjacency_size_type = typename adjacency_type::size_type;

  using hasher = typename graph_type::hasher;
  using key_equal = typename graph_type::key_equal;

  using reference = typename graph_type::reference;
  using const_reference = typename graph_type::const_reference;
  using iterator = typename graph_type::iterator;
  using const_iterator = typename graph_type::const_iterator;
  using adjacency_iterator = typename adjacency_type::iterator;
  using const_adjacency_iterator = typename adjacency_type::const_iterator;

public:
  // Add init list constructor that just takes initial values

  // The default value should be move constructed? for every node to save space?

  /************************************/
  // Constructors

  Graph() {}

  template <class InputIt>
  Graph(InputIt first, InputIt last)
  {
  }

  Graph(const Graph &other)
  {
    for (const auto &[val, adj] : other.m_nodes)
    {
      this->insert(val);
      for (const auto &[node, cost] : adj)
        this->insert(val, {node, cost});
    }
  }

  Graph(Graph &&other)
  {
  }

  Graph(std::initializer_list<value_type> init)
  {
  }

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

  // Constructors
  /************************************/
  // Iterators

  iterator
  begin()
  {
    return m_nodes.begin();
  }

  const_iterator
  begin() const
  {
    return m_nodes.begin();
  }

  const_iterator
  cbegin() const
  {
    return begin();
  }

  iterator
  end()
  {
    return m_nodes.end();
  }

  const_iterator
  end() const
  {
    return m_nodes.end();
  }

  const_iterator
  cend() const
  {
    return end();
  }

  // Iterators
  /************************************/
  // Capacity

  bool
  empty() const
  {
    return m_nodes.empty();
  }

  size_type
  size() const
  {
    return m_nodes.size();
  }

  // Capacity
  /************************************/
  // Modifiers

  /****************/
  // Clear

  // TODO write tests for
  void
  clear()
  {
    m_nodes.clear();
  }

  // Clear
  /****************/
  // Insert

  std::pair<iterator, bool>
  insert(const value_type &value)
  {
    return m_nodes.emplace(value, adjacency_type{});
  }

  // TODO
  // Currently commented out because a test case was trying to call this and it was not defined
  // std::pair<iterator, bool>
  // insert(value_type &&value);

  // TODO
  // Remember, it's a list of value_types
  template <class InputIt>
  void
  insert(InputIt first, InputIt last);

  // FIXME can call the range insertor using ilist.begin() and end()
  void
  insert(std::initializer_list<value_type> ilist)
  {
    for (const auto &val : ilist)
      insert(val);
  }

  // Insert
  /****************/
  // Emplace

  // TODO
  template <class... Args>
  std::pair<iterator, bool>
  emplace(Args &&... args);

  // Emplace
  /****************/
  // Erase

  // I am not exactly sure how this functionality is going to work yet, since edges have references to a value that needs to be erased

  // TODO
  iterator
  erase(const value_type &value);

  // TODO
  iterator
  erase(const_iterator pos);

  // TODO
  iterator
  erase(const_iterator first, const_iterator last);

  // Erase
  /****************/
  // Swap

  // TODO
  void
  swap(Graph &other);

  /****************/

  // Might need an extract and merge, I am not exactly sure how to implement those though

  // Modifiers
  /************************************/
  // Lookup

  // TODO
  reference
  at(const value_type &value);

  // TODO
  const_reference
  at(const value_type &value) const;

  iterator
  find(const value_type &value)
  {
    return m_nodes.find(value);
  }

  const_iterator
  find(const value_type &value) const
  {
    return m_nodes.find(value);
  }

  // TODO Perform tests
  bool
  contains(const value_type &value) const
  {
    return find(value) != end();
  }

  // Lookup
  /************************************/
  // Adjacency list interface

  /****************/
  // Adj. iterators

  /******/
  // Adj. begin

  adjacency_iterator
  begin(const key_type &key)
  {
    return find(key)->second.begin();
  }

  const_adjacency_iterator
  begin(const key_type &key) const
  {
    return find(key)->second.begin();
  }

  const_adjacency_iterator
  cbegin(const key_type &key) const
  {
    return begin(key);
  }

  adjacency_iterator
  begin(iterator pos)
  {
    return pos->second.begin();
  }

  const_adjacency_iterator
  begin(iterator pos) const
  {
    return pos->second.begin();
  }

  const_adjacency_iterator
  cbegin(iterator pos) const
  {
    return begin(pos);
  }

  // Adj. begin
  /******/
  // Adj. end

  adjacency_iterator
  end(const key_type &key)
  {
    return find(key)->second.end();
  }

  const_adjacency_iterator
  end(const key_type &key) const
  {
    return find(key)->second.end();
  }

  const_adjacency_iterator
  cend(const key_type &key) const
  {
    return end(key);
  }

  adjacency_iterator
  end(iterator pos)
  {
    return pos->second.end();
  }

  const_adjacency_iterator
  end(iterator pos) const
  {
    return pos->second.end();
  }

  const_adjacency_iterator
  cend(iterator pos) const
  {
    return end(pos);
  }

  // Adj. end
  /******/

  // Adj. iterators
  /****************/
  // Adj. capacity

  bool
  empty(const key_type &key) const
  {
    return find(key)->second.empty();
  }

  bool
  empty(iterator pos) const
  {
    return pos->second.empty();
  }

  adjacency_size_type
  size(const key_type &key) const
  {
    return find(key)->second.size();
  }

  adjacency_size_type
  size(iterator pos) const
  {
    return pos->second.size();
  }

  // Adj. capacity
  /****************/
  // Adj. modifiers

  /******/
  // Adj. clear

  // TODO
  void
  clear(const key_type &key);

  // TODO
  void
  clear(iterator pos);

  // Adj. clear
  /******/
  // Adj. insert

  // If node does not exist a new one will be created, I think
  // Should probs add a const version

  // Does this overwrite connection costs? Should it?

  std::pair<adjacency_iterator, bool>
  insert(const key_type &key, const adjacency_value_type &adj_value)
  {
    auto [it, _0] = insert(key);
    auto [adj_it, _1] = insert(adj_value.first);

    return insert(it, {adj_it, adj_value.second});
  }

  // TODO
  // Currently commented out because a test is trying to call this and it is not defined
  // std::pair<adjacency_iterator, bool>
  // insert(const key_type &key, adjacency_value_type &&adj_value);

  std::pair<adjacency_iterator, bool>
  insert(const key_type &key, const std::pair<iterator, Cost> &adj)
  {
    auto [it, _] = insert(key);

    return insert(it, {adj.first, adj.second});
  }

  // TODO
  std::pair<adjacency_iterator, bool>
  insert(const key_type &key, std::pair<iterator, Cost> &&adj);

  // TODO
  // Remember this is a range containing adjacency_value_type or std::pair<iterator, Cost>
  template <class InputIt>
  void
  insert(const key_type &key, InputIt first, InputIt last);

  void
  insert(const key_type &key, std::initializer_list<adjacency_value_type> ilist)
  {
    for (const auto &adj : ilist)
      insert(key, adj);
  }

  void
  insert(const key_type &key, std::initializer_list<std::pair<iterator, Cost>> ilist)
  {
    for (const auto &adj : ilist)
      insert(key, adj);
  }

  std::pair<adjacency_iterator, bool>
  insert(iterator pos, const adjacency_value_type &adj_value)
  {
    auto [adj_it, _] = insert(adj_value.first);

    return insert(pos, {adj_it, adj_value.second});
  }

  // TODO
  std::pair<adjacency_iterator, bool>
  insert(iterator pos, adjacency_value_type &&adj_value);

  std::pair<adjacency_iterator, bool>
  insert(iterator pos, const std::pair<iterator, Cost> &adj)
  {
    return pos->second.emplace(adj.first->first, adj.second);
  }

  // TODO
  // Currently commented out because a test case is trying to call it
  // std::pair<adjacency_iterator, bool>
  // insert(iterator pos, std::pair<iterator, Cost> &&adj);

  // TODO
  // Remember this range will container adjacency_value_type or std::pair<iterator, bool>
  template <class InputIt>
  void
  insert(iterator pos, InputIt first, InputIt last);

  void
  insert(iterator pos, std::initializer_list<adjacency_value_type> ilist)
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

  // Adj. insert
  /******/

  // Adj. modifiers
  /****************/
  // Adj. lookup

  // FIXME if the T does not exist this seg faults, it should return the end of the local iterator
  adjacency_iterator
  find(const T &from, const T &to)
  {
    return find(find(from), find(to));
  }

  const_adjacency_iterator
  find(const T &from, const T &to) const
  {
    return find(find(from), find(to));
  }

  adjacency_iterator
  find(iterator from, iterator to)
  {
    return from->second.find(to->first);
  }

  const_adjacency_iterator
  find(iterator from, iterator to) const
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

  // Adj. lookup
  /****************/

  // Adjacency list interface
  /************************************/
  // Hash policy

  // TODO test
  void
  rehash(size_type count)
  {
    m_nodes.rehash(count);
  }

  // TODO test
  void
  reserve(size_type count)
  {
    m_nodes.reserve(count);
  }

  // Hash policy
  /************************************/
  // Observers

  // TODO test
  hasher
  hash_function() const
  {
    return m_nodes.hash_function();
  }

  // TODO test
  key_equal
  key_eq() const
  {
    return m_nodes.key_eq();
  }

  // Observers
  /************************************/

private:
  graph_type m_nodes{};
};

// Member functions
/******************************************************************************/
// Non-member functions

// TODO I am sure there is an STL algorithm this could be written with
// FIXME this is causing problems because there is no find that takes 2 const iterators
// template <class T, class Cost>
// bool operator==(const Graph<T, Cost> &lhs, const Graph<T, Cost> &rhs)
// {
//   for (auto &[val, adj] : lhs)
//     for (auto [adj_val, cost] : adj)
//       if (auto edge = rhs.find(val, adj_val); edge != rhs.end(val))
//       {
//         if (cost != edge->second)
//           return false;
//       }
//       else
//         return false;
//   return true;
// }

// TODO
template <class T, class Cost>
bool operator!=(const Graph<T, Cost> &lhs, const Graph<T, Cost> &rhs);

// TODO
template <class T, class Cost>
void swap(Graph<T, Cost> &lhs, Graph<T, Cost> &rhs);

// TODO
template <class T, class Cost, class Pred>
void erase_if(Graph<T, Cost> &c, Pred pred);

// Non-member functions
/******************************************************************************/

#endif