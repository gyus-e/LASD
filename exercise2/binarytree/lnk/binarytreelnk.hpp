
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : public virtual MutableBinaryTree<Data>{
  // Must extend MutableBinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  // ...

  struct NodeLnk : public virtual MutableBinaryTree<Data>::MutableNode { // Must extend MutableNode

  private:

    Data elem;
    NodeLnk * Sx = nullptr;
    NodeLnk * Dx = nullptr;

  protected:

    NodeLnk () = default;
    NodeLnk (const NodeLnk &); //Copy constructor
    NodeLnk (NodeLnk &&) noexcept; //Move constructor

  public:
    virtual ~NodeLnk () {if (this->HasLeftChild()) {delete this->Sx;} if (this->HasRightChild()) {delete this->Dx;}}

    inline Data & Element() override {return this->elem;} 

    inline bool IsLeaf() const noexcept override {return this->Sx == nullptr == this->Dx;} 
    inline bool HasLeftChild() const noexcept override {return this->Sx != nullptr;}
    inline bool HasRightChild() const noexcept override {return this->Dx != nullptr;} 

    NodeLnk & LeftChild() override; // (concrete function must throw std::out_of_range when not existent)
    NodeLnk & RightChild() override; // (concrete function must throw std::out_of_range when not existent)

  };


  NodeLnk * root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  // BinaryTreeLnk(argument) specifiers; // A binary tree obtained from a TraversableContainer
  // BinaryTreeLnk(argument) specifiers; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // BinaryTreeLnk(argument) specifiers;

  // Move constructor
  // BinaryTreeLnk(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk operator=(const BinaryTreeLnk &);

  // Move assignment
  BinaryTreeLnk operator=(BinaryTreeLnk &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk &);
  bool operator!=(const BinaryTreeLnk &);

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  const Data & Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  Data & Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
