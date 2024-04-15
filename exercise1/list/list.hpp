
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
class List : public virtual ClearableContainer, public virtual LinearContainer<Data>, public virtual DictionaryContainer<Data> {
  // Must extend ClearableContainer,
  //             LinearContainer<Data>,
  //             DictionaryContainer<Data>

private:

  // ...

protected:

  using Container::size;

  struct Node {

    Data element;
    Node * next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    Node () = default;
    Node (const Data & dat) : element (dat) {}
    Node (Data && dat) : element (std::move (dat)) {}

    /* ********************************************************************** */

    // Copy constructor
    Node (const Node & N) {this->element = N.element; if (N.next != nullptr) {this->next = new Node (N.next);}} 

    // Move constructor
    Node (Node && N) noexcept {this->element = std::move(N.element); this->next = N.next;}

    /* ********************************************************************** */

    // Destructor
    virtual ~Node () = default;

    /* ********************************************************************** */

    // Comparison operators
    // ...

    /* ********************************************************************** */

    // Specific member functions

  };

  Node * head = nullptr;
  Node * tail = nullptr;

public:

  // Default constructor
  List () = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data> &); // A list obtained from a TraversableContainer
  List(const MappableContainer<Data> &); // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List &);

  // Move constructor
  List(List &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();
  /* ************************************************************************ */

  // Copy assignment
  List operator=(const List &);

  // Move assignment
  List operator=(List &&);

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions

  void InsertAtFront(const Data &); // Copy of the value
  void InsertAtFront(Data &&); // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  inline Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data & dat); // Copy of the value
  void InsertAtBack(Data && dat); // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  inline bool Insert(const Data & dat) override; // Copy of the value
  inline bool Insert(Data && dat) override; // Move of the value
  bool Remove(const Data &);

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator[](unsigned long idx) const override;  // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data & operator[](unsigned long idx) override; // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  inline const Data & Front() const override {if (this->head == nullptr) {throw std::length_error("from Front");} return this->head->element;} // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data & Front() override {if (this->head == nullptr) {throw std::length_error("from Front");} return this->head->element;} // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  inline const Data & Back() const override {if (this->tail == nullptr) {throw std::length_error("from Back");} return this->tail->element;} // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  inline Data & Back() override {if (this->tail == nullptr) {throw std::length_error("from Back");} return this->tail->element;} // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  // using typename TraversableContainer<Data>::TraverseFun;

  // type Traverse(arguments) specifiers; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // type PreOrderTraverse(arguments) specifiers; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // type PostOrderTraverse(arguments) specifiers; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  // using typename MappableContainer<Data>::MapFun;

  // type Map(argument) specifiers; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // type PreOrderMap(argument) specifiers; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // type PostOrderMap(argument) specifiers; // Override PostOrderMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
