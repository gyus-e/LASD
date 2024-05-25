
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"

#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : public virtual ClearableContainer,
             public virtual LinearContainer<Data>,
             public virtual DictionaryContainer<Data>

{

public:

  using typename TraversableContainer<Data>::TraverseFun;
  using typename MappableContainer<Data>::MapFun;

protected:

  using Container::size;

  struct Node {

    Data elem;
    Node * next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    Node () = default;
    Node (const Data & d) : elem (d), next (nullptr) {}
    Node (Data && d) : elem (std::move(d)), next (nullptr) {}

    /* ********************************************************************** */

    // Copy constructor
    Node (const Node &);

    // Move constructor
    Node (Node &&) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node ();

    /* ********************************************************************** */

    // Comparison operators
    bool operator== (const Node &) const;
    bool operator!= (const Node &) const;

    /* ********************************************************************** */

    // Specific member functions

    void PreOrderTraverse (TraverseFun) const;
    void PostOrderTraverse (TraverseFun) const;

    void PreOrderMap (MapFun);
    void PostOrderMap (MapFun);
  };

  Node * head = nullptr;
  Node * tail = nullptr;

public:

  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data> &); // A list obtained from a TraversableContainer
  List(MappableContainer<Data> &&); // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List<Data> &);

  // Move constructor
  List(List<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List & operator=(const List<Data> &);

  // Move assignment
  List & operator=(List<Data> &&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List<Data> &) const;
  bool operator!=(const List<Data> &) const;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data &); // Copy of the value
  void InsertAtFront(Data &&); // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  inline Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data &); // Copy of the value
  void InsertAtBack(Data &&); // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &); // Copy of the value
  bool Insert(Data &&); // Move of the value
  bool Remove(const Data &);

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](unsigned long) const override;  // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data & operator[](unsigned long) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  inline const Data & Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data & Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  inline const Data & Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data & Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  inline void Traverse(TraverseFun func) const override {this->PreOrderTraverse(func);} // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun func) const override {if (this->head != nullptr) {this->head->PreOrderTraverse(func);}} // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun func) const override {if (this->head != nullptr) {this->head->PostOrderTraverse(func);}} // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun func) override {this->PreOrderMap(func);} // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun func) override {if (this->head != nullptr) {this->head->PreOrderMap(func);}} // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun func) override {if (this->head != nullptr) {this->head->PostOrderMap(func);}} // Override PostOrderMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
