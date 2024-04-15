
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

  using typename TraversableContainer<Data>::TraverseFun;
  using typename MappableContainer<Data>::MapFun;

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

    void PreOrderTraverse (TraverseFun func) const
    {
      func (this->element);

      if (this->next != nullptr)
      {
        this->next->PreOrderTraverse (func);
      }
    }

    void PostOrderTraverse (TraverseFun func) const
    {
      if (this->next != nullptr)
      {
        this->next->PostOrderTraverse(func);
      }

      func (this->element);
    }

    void PreOrderMap (MapFun func)
    {
      func (this->element);

      if (this->next != nullptr)
      {
        this->next->PreOrderTraverse (func);
      }
    }

    void PostOrderMap (MapFun func)
    {
      if (this->next != nullptr)
      {
        this->next->PostOrderMap (func);
      }

      func (this->element);
    }

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
  bool operator==(const List &) const;
  bool operator!=(const List &) const;

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


  inline void Traverse(TraverseFun func) const override {this->PreOrderTraverse(func);} // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun func) const override {this->head->PreOrderTraverse(func);} // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun func) const override {this->head->PostOrderTraverse(func);} // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  inline void Map(MapFun func) override {this->PreOrderMap(func);} // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline void PreOrderMap(MapFun func) override {this->head->PreOrderMap(func);} // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline void PostOrderMap(MapFun func) override {this->head->PostOrderMap(func);} // Override PostOrderMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
