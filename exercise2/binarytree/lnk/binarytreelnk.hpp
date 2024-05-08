
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

  public:
    virtual ~NodeLnk () {if (this->HasLeftChild()) {delete this->Sx;} if (this->HasRightChild()) {delete this->Dx;}}

    inline Data & Element() override {return this->elem;} 

    inline bool IsLeaf() const noexcept override {return this->Sx == nullptr == this->Dx;} 
    inline bool HasLeftChild() const noexcept override {return this->Sx != nullptr;}
    inline bool HasRightChild() const noexcept override {return this->Dx != nullptr;} 

    NodeLnk & LeftChild() override // (concrete function must throw std::out_of_range when not existent)
    {
      if (this->HasLeftChild())
      {
        return this->Sx;
      } 
      else 
      {
        throw std::out_of_range ("left child does not exist.");
      }
    } 

    NodeLnk & RightChild() override // (concrete function must throw std::out_of_range when not existent)
    {
      if (this->HasRightChild())
      {
        return this->Dx;
      } 
      else 
      {
        throw std::out_of_range ("right child does not exist.");
      }
    } 

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
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

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
