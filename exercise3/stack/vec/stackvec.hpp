
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */
#define INIT_SIZE 16 
#define REDUCE_THRESHOLD 4
#define INCREASE_FACTOR 2
#define REDUCE_FACTOR 2

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : public virtual Stack<Data>, protected virtual Vector<Data>{
  // Must extend Stack<Data>,
  //             Vector<Data>

private:

  // ...

protected:

  using Vector<Data>::size;
  unsigned long top = 0;

public:

  // Default constructor
  StackVec() : Vector<Data> (INIT_SIZE), top (0) {}

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const TraversableContainer<Data> & cont) : Vector<Data> (cont), top(cont.Size()) {if (this->size < INIT_SIZE) {this->Resize(INIT_SIZE);}} // A stack obtained from a TraversableContainer
  StackVec(MappableContainer<Data> && cont) : Vector<Data> (std::move(cont)), top(cont.Size()) {if (this->size < INIT_SIZE) {this->Resize(INIT_SIZE);}} // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec & that) : Vector<Data> ((Vector<Data>) that), top (that.top) {}

  // Move constructor
  StackVec(StackVec && that) noexcept : Vector<Data> (std::move((Vector<Data>) that)), top (that.top) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec & operator=(const StackVec & that) {this->Vector<Data>::operator=((Vector<Data>)(that)); this->top = that.top; return *this;}

  // Move assignment
  StackVec & operator=(StackVec && that) {this->Vector<Data>::operator= (std::move((Vector<Data>)(that))); std::swap(this->top, that.top); return *this;}

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec & that) const; //{return (Vector<Data>)(*this) == (Vector<Data>)(that) && this->top == that.top;}
  bool operator!=(const StackVec & that) const; //{return (Vector<Data>)(*this) != (Vector<Data>)(that) || this->top != that.top;}

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

  inline bool Empty() const noexcept override {return (this->top == 0);} // Override Container member

  inline unsigned long Size() const noexcept override {return this->top;} // Override Container member



  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline virtual void Clear() override {((Vector<Data>)(* this)).Clear(); this->top = 0;} // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
