
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
class Vector : public virtual ResizableContainer, public virtual LinearContainer<Data> {
  // Must extend ResizableContainer,
  //             LinearContainer<Data>

private:

  // ...

protected:

  using Container::size;
  
  Data * A = nullptr;

  // ...

public:

  // Default constructor
  Vector () = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector (unsigned long); // A vector with a given initial dimension
  Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data> &&); // A vector obtained from a MappableContainer

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

  using Container::size;
  using Vector<Data>::A;

  // ...

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(unsigned long sz) : Vector<Data> (sz) {} // A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data> & con) : Vector<Data> (con) {} // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data> && con) : Vector<Data> (std::move(con)) {} // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector<Data> & vec) : Vector<Data> ((const Vector<Data>) vec) {}

  // Move constructor
  SortableVector(SortableVector<Data> && vec) noexcept : Vector<Data> (std::move(vec)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;// {if (this->A != nullptr) {delete [] this->A}; this->A = nullptr;}

  /* ************************************************************************ */

  // Copy assignment
  SortableVector operator=(const SortableVector & that) {(Vector<Data>) (*this) = (const Vector<Data>) that; return *this;}

  // Move assignment
  SortableVector operator=(SortableVector && that) {(Vector<Data>) (*this) = std::move ((Vector<Data>) that); return *this;}

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
