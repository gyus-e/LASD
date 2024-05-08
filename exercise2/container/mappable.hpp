
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer : public virtual TraversableContainer<Data> {
  // Must extend TraversableContainer<Data>

private:

  // ...

protected:

  // ...
  MappableContainer () = default;

public:

  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer operator=(const MappableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MappableContainer operator=(MappableContainer &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const MappableContainer &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const MappableContainer &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using MapFun = std::function<void(Data &)>;

  virtual void Map(MapFun) = 0;

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : public virtual MappableContainer<Data>, public virtual PreOrderTraversableContainer<Data> {
  // Must extend MappableContainer<Data>,
  //             PreOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...
  PreOrderMappableContainer () = default;

public:

  // Destructor
  virtual ~PreOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderMappableContainer operator=(const PreOrderMappableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PreOrderMappableContainer operator=(PreOrderMappableContainer &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderMappableContainer &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const PreOrderMappableContainer &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PreOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun mapFun) override {this->PreOrderMap(mapFun);} // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer : public virtual MappableContainer<Data>, public virtual PostOrderTraversableContainer<Data> {
  // Must extend MappableContainer<Data>,
  //             PostOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...
  PostOrderMappableContainer () = default;

public:

  // Destructor
  virtual ~PostOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderMappableContainer operator=(const PostOrderMappableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PostOrderMappableContainer operator=(PostOrderMappableContainer &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderMappableContainer &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const PostOrderMappableContainer &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PostOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun mapFun) override {this->PostOrderMap(mapFun);} // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class InOrderMappableContainer : public virtual MappableContainer<Data>, public virtual InOrderTraversableContainer<Data> {
  // Must extend MappableContainer<Data>,
  //             InOrderTraversableContainer<Data>

private:

  // ...

protected:

  // ...
  InOrderMappableContainer() = default;

public:

  // Destructor
  virtual ~InOrderMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  InOrderMappableContainer operator=(const InOrderMappableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  InOrderMappableContainer operator=(InOrderMappableContainer &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderMappableContainer &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const InOrderMappableContainer &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void InOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun mapFun) override {this->InOrderMap(mapFun);} // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer : public virtual MappableContainer<Data>, public virtual BreadthTraversableContainer<Data> {
  // Must extend MappableContainer<Data>,
  //             BreadthTraversableContainer<Data>

private:

  // ...

protected:

  // ...
  BreadthMappableContainer () = default;

public:

  // Destructor
  virtual ~BreadthMappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthMappableContainer operator=(const BreadthMappableContainer &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BreadthMappableContainer operator=(BreadthMappableContainer &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthMappableContainer &) = delete; // Comparison of abstract types is not possible.
  bool operator!=(const BreadthMappableContainer &) = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void BreadthMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun mapFun) override {this->BreadthMap(mapFun);} // Override MappableContainer member

};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif
