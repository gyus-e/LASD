
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */
#define INIT_SIZE 16 
#define REDUCE_THRESHOLD 0.2
#define INCREASE_FACTOR 2
#define REDUCE_FACTOR 0.5

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : public virtual Queue<Data>, protected virtual Vector<Data> {
protected:

  using Vector<Data>::size;
  unsigned long dim = 0;
  unsigned long head = 0;
  unsigned long tail = 0;

public:

  // Default constructor
  QueueVec();

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const TraversableContainer<Data> & cont);
  QueueVec(MappableContainer<Data> && cont);

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec & that);

  // Move constructor  
  QueueVec(QueueVec && that) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec & operator=(const QueueVec & that);

  // Move assignment
  QueueVec & operator=(QueueVec && that);
  
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec & that) const; //{return (Vector<Data>)(*this) == (Vector<Data>)(that) && this->dim == that.dim && this->head == that.head && this->tail == that.tail;}
  bool operator!=(const QueueVec & that) const; //{return (Vector<Data>)(*this) != (Vector<Data>)(that) || this->dim != that.dim || this->head != that.head || this->tail != that.tail;}

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  inline const Data & Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data & Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  inline void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  inline void Enqueue(const Data &) override; // Override Queue member (copy of the value)
  inline void Enqueue(Data &&) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline virtual bool Empty() const noexcept override {return (this->dim == 0);}

  inline unsigned long Size() const noexcept override {return this->dim;}

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline virtual void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
