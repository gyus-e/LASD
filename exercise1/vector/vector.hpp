
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : public ResizableContainer, public virtual LinearContainer<Data> {
  // Must extend ResizableContainer,
  //             LinearContainer<Data>

private:

  // ...
  Data * A = nullptr;

protected:

  // using Container::Size;

  // ...

public:

  // Default constructor
  Vector () = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector (unsigned long); // A vector with a given initial dimension
  Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  Vector(const MappableContainer<Data> &); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector &);

  // Move constructor
  Vector(Vector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector operator=(const Vector &);

  // Move assignment
  Vector operator=(Vector &&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector &) const noexcept;
  bool operator!=(const Vector &) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(unsigned long); // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  inline const Data & operator[](unsigned long idx) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  inline Data & operator[](unsigned long idx) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  inline const Data & Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data & Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  inline const Data & Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data & Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : public Vector<Data>, public SortableLinearContainer<Data> {
  // Must extend Vector<Data>,
  //             SortableLinearContainer<Data>

private:

  // ...

protected:

  // using Container::???;

  // ...

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(unsigned long sz) : Vector<Data> (sz) {} // A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data> & con) : Vector<Data> (con) {} // A vector obtained from a TraversableContainer
  SortableVector(const MappableContainer<Data> & con) : Vector<Data> (con) {} // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // SortableVector(const SortableVector &);

  // Move constructor
  // SortableVector(SortableVector &&);

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  // SortableVector operator=(const SortableVector &);

  // Move assignment
  // SortableVector operator=(const SortableVector &);

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
