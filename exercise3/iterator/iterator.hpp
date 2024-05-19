
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

  // ...

protected:

  // ...
  Iterator () = default;

public:

  // Destructor
  virtual ~Iterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  Iterator operator=(const Iterator &) = delete; // Copy assignment of abstract is not possible.

  // Move assignment
  Iterator operator=(Iterator &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Iterator &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const Iterator &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & operator*() const = 0; // (non-mutable version; concrete function must throw std::out_of_range when terminated)

  virtual bool Terminated() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class MutableIterator : public virtual Iterator<Data> {
  // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...
  MutableIterator () = default;

public:

  // Destructor
  virtual ~MutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableIterator operator=(const MutableIterator &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableIterator operator=(MutableIterator &&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MutableIterator &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const MutableIterator &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data & operator*() = 0; // (mutable version; concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator : public virtual Iterator<Data> {
  // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...
  ForwardIterator () = default;
  

public:

  // Destructor
  virtual ~ForwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ForwardIterator operator=(const ForwardIterator &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ForwardIterator operator=(ForwardIterator &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ForwardIterator &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(ForwardIterator &&) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual ForwardIterator & operator++() = 0; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class ResettableIterator : public virtual Iterator<Data> {
  // Must extend Iterator<Data>

private:

  // ...

protected:

  // ...
  ResettableIterator () = default;

public:

  // Destructor
  virtual ~ResettableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResettableIterator operator=(const ResettableIterator &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ResettableIterator operator=(ResettableIterator &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ResettableIterator &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const ResettableIterator &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Reset() noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif
