
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : public virtual Queue<Data>, protected virtual List<Data> {
  // Must extend Queue<Data>,
  //             List<Data>

private:

  // ...

protected:

  //using List<Data>::size;

  // ...

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const TraversableContainer<Data> & cont) : List<Data> (cont) {} // A stack obtained from a TraversableContainer
  QueueLst(MappableContainer<Data> && cont) : List<Data> (cont) {}; // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst & that) : List<Data> (that) {}

  // Move constructor
  QueueLst (QueueLst && that) : List<Data> (std::move(that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline QueueLst & operator=(const QueueLst & that) {this->List<Data>::operator=((List<Data>)(that)); return *this;}

  // Move assignment
  inline QueueLst & operator=(QueueLst && that) {this->List<Data>::operator=(std::move((List<Data>)(that))); return *this;}

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const QueueLst & that) const {return (List<Data>)(*this) == (List<Data>)(that);}
  inline bool operator!=(const QueueLst & that) const {return (List<Data>)(*this) != (List<Data>)(that);}

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  inline const Data & Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data & Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  inline void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline void Enqueue(const Data &) override; // Override Queue member (copy of the value)
  inline void Enqueue(Data &&) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
