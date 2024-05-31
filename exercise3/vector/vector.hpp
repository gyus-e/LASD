
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
class Vector : public virtual ResizableContainer, public virtual LinearContainer<Data> 
{
protected:

  using Container::size;
  Data * A = nullptr;

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
  Vector(const Vector<Data> & that);

  // Move constructor
  Vector(Vector<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector& operator=(const Vector &);

  // Move assignment
  Vector& operator=(Vector &&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector &) const noexcept;
  bool operator!=(const Vector &) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() override; // Override ClearableContainer member

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

  inline virtual bool Empty () const noexcept override {return this->A == nullptr || this->size == 0;}
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
  SortableVector(const SortableVector<Data> & that) : Vector<Data> ((const Vector<Data>) that) {}

  // Move constructor
  SortableVector(SortableVector<Data> && that) noexcept : Vector<Data> (std::move((Vector<Data>) that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector operator=(const SortableVector & that) {(Vector<Data>) (*this) = (const Vector<Data>) that; return *this;}

  // Move assignment
  SortableVector operator=(SortableVector && that) {Vector<Data>::operator=(std::move(that)); return *this;}

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
