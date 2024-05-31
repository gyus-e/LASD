
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */
#define INIT_SIZE 16 
#define REDUCE_THRESHOLD 4
#define INCREASE_FACTOR 2
#define REDUCE_FACTOR 2

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : public virtual Queue<Data>, protected virtual Vector<Data> {
  // Must extend Queue<Data>,
  //             Vector<Data>

private:

  // ...

protected:

  using Vector<Data>::size;
  unsigned long dim = 0;
  unsigned long head = 0;
  unsigned long tail = 0;

public:

  // Default constructor
  QueueVec() : Vector<Data> (INIT_SIZE), dim (0), head (0), tail (0) {}

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const TraversableContainer<Data> & cont) : Vector<Data> (cont), dim(cont.Size()), head (0), tail (cont.Size()-1) {if (this->size < INIT_SIZE) {this->Resize(INIT_SIZE);}} // A queue obtained from a TraversableContainer
  QueueVec(MappableContainer<Data> && cont) : Vector<Data> (std::move(cont)), dim(cont.Size()), head (0), tail (cont.Size()-1) {if (this->size < INIT_SIZE) {this->Resize(INIT_SIZE);}} // A queue obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec & that) : Vector<Data> ((Vector<Data>) that), dim(that.dim), head (that.head), tail (that.tail) {}

  // Move constructor
  QueueVec(QueueVec && that) noexcept : Vector<Data> (std::move((Vector<Data>) (that))) {std::swap (this->dim, that.dim); std::swap (this->head, that.head); std::swap (this->tail, that.tail);}

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec & operator=(const QueueVec & that) {this->Vector<Data>::operator= ((Vector<Data>)(that)); this->dim = that.dim; this->head = that.head; this->tail = that.tail; return *this;}

  // Move assignment
  QueueVec & operator=(QueueVec && that) {this->Vector<Data>::operator= (std::move((Vector<Data>)(that))); std::swap (this->dim, that.dim); std::swap (this->head, that.head); std::swap (this->tail, that.tail); return *this;}

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

  inline virtual void Clear() override {((Vector<Data>)(* this)).Clear(); this->dim = 0; this->head = 0; this->tail = 0;} // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
