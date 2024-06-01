
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */
#define INIT_SIZE 16 
#define REDUCE_THRESHOLD 0.2
#define INCREASE_FACTOR 2
#define REDUCE_FACTOR 0.5

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : public virtual Stack<Data>, protected virtual Vector<Data>
{
protected:

  using Vector<Data>::size;
  unsigned long top = 0;

public:

  // Default constructor
  StackVec();

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const TraversableContainer<Data> &);
  StackVec(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec<Data> &);

  // Move constructor
  StackVec(StackVec<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec & operator=(const StackVec<Data> & that);
  // Move assignment
  StackVec & operator=(StackVec<Data> && that);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec<Data> & that) const; 
  bool operator!=(const StackVec<Data> & that) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data & Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  Data & Top() override; // Override Stack member (mutable version; must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data &) override; // Override Stack member (copy of the value)
  void Push(Data &&) override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline virtual bool Empty() const noexcept override {return (this->top == 0);} // Override Container member

  inline unsigned long Size() const noexcept override {return this->top;} // Override Container member



  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline virtual void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
