
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {
/* ************************************************************************** */

template <typename Data>
class LinearContainer : public virtual PreOrderMappableContainer<Data>, public virtual PostOrderMappableContainer<Data> {
  // Must extend PreOrderMappableContainer<Data>,
  //             PostOrderMappableContainer<Data>

private:

  // ...

protected:

  // ...
  LinearContainer () = default;
  void swap (const unsigned long, const unsigned long);

public:
  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer operator=(const LinearContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  LinearContainer operator=(LinearContainer &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer &) const noexcept; // Comparison of abstract types is possible.
  bool operator!=(const LinearContainer &) const noexcept; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data operator[](const unsigned long idx) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  virtual Data & operator[](const unsigned long idx) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  inline Data Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  inline Data Front(); // (mutable version; concrete function must throw std::length_error when empty)

  inline Data Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  inline Data Back(); // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  virtual void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  virtual void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  virtual void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  virtual void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer : public LinearContainer<Data>{
  // Must extend LinearContainer<Data>

private:

  // ...

protected:

  // ...
  SortableLinearContainer () = default;

public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer operator=(const SortableLinearContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  SortableLinearContainer operator=(SortableLinearContainer &&) = delete; // Move assignment of abstract types is not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SortableLinearContainer &) const noexcept; // Comparison of abstract types is possible.
  bool operator!=(const SortableLinearContainer &) const noexcept; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member function

  virtual void Sort();

protected:

  // Auxiliary member functions
  void heapSort ();
  void buildHeap (const unsigned long);
  void heapify (const unsigned long i, const unsigned long heapsize);

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
