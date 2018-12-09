#ifndef ADJMATRIX_HPP
#define ADJMATRIX_HPP

#include <initializer_list>
#include <vector>

template<class T>
class AdjMatrix
{
public:
  using cost_type = size_t; // could be defined 

  AdjMatrix(std::initializer_list<std::initializer_list<T>> init)
  : m_matrix(init)
  {}

private:
  using node_id_type = size_t;

  std::unordered_set<std::pair<T, cost_type>> m_matrix;
};

#endif