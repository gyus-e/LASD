
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : public virtual Stack<Data>, protected virtual List<Data> {
  // Must extend Stack<Data>,
  //             List<Data>

private:

  // ...

protected:

  using List<Data>::size;

  // ...

public:

  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst (const TraversableContainer<Data> & cont) : List<Data> (cont) {} // A stack obtained from a TraversableContainer
  StackLst (MappableContainer<Data> && cont) : List<Data> (std::move(cont)) {} // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst & that) : List<Data> ((List<Data>)that) {}

  // Move constructor
  StackLst(StackLst && that) noexcept : List<Data> (std::move((List<Data>)that)) {}

  /* ************************************************************************ */

  // Destructor
  ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline StackLst operator=(const StackLst & that) {(List<Data>)(*this) = (List<Data>)(that); return *this;}

  // Move assignment
  inline StackLst operator=(StackLst && that) {(List<Data>)(*this) = std::move((List<Data>)(that)); return *this;}

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const StackLst & that) const {return (List<Data>)(*this) == (List<Data>)(that);}
  inline bool operator!=(const StackLst & that) const {return (List<Data>)(*this) != (List<Data>)(that);}

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  inline const Data & Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  inline Data & Top() override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  inline Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data &) override; // Override Stack member (copy of the value)
  void Push(Data &&) override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() override {((List<Data>)(*this)).Clear();}

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
