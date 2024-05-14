
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../queue/vec/queuevec.hpp"
#include "../../queue/lst/queuelst.hpp"

#include <iostream>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : public virtual MutableBinaryTree<Data>
{

private:

  // ...

protected:

  struct NodeLnk : public virtual MutableBinaryTree<Data>::MutableNode 
  {

  protected:

    Data elem;
    NodeLnk * Sx = nullptr;
    NodeLnk * Dx = nullptr;

    void CreateTree(const TraversableContainer<Data> &);

  public:
    friend class BinaryTreeLnk<Data>;

    NodeLnk () = default;
    NodeLnk (const Data & d) : elem (d) {}
    NodeLnk (Data && d) noexcept : elem (std::move(d)) {}
    NodeLnk (const NodeLnk &); //Copy constructor
    NodeLnk (NodeLnk &&) noexcept; //Move constructor

    virtual ~NodeLnk ();

    inline Data & Element() override {return this->elem;} 
    inline const Data & Element() const override {return this->elem;} 

    inline bool IsLeaf() const noexcept override {return (this->Sx == nullptr) && (this->Dx == nullptr);} 
    inline bool HasLeftChild() const noexcept override {return this->Sx != nullptr;}
    inline bool HasRightChild() const noexcept override {return this->Dx != nullptr;} 

    typename MutableBinaryTree<Data>::MutableNode & LeftChild() override; // (concrete function must throw std::out_of_range when not existent)
    const typename BinaryTree<Data>::Node & LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)

    typename MutableBinaryTree<Data>::MutableNode & RightChild() override; // (concrete function must throw std::out_of_range when not existent)    
    const typename BinaryTree<Data>::Node & RightChild() const override; // (concrete function must throw std::out_of_range when not existent)

  };

  using BinaryTree<Data>::size;
  NodeLnk * root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data> &); // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data> &); // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk &);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk operator=(const BinaryTreeLnk &);

  // Move assignment
  BinaryTreeLnk operator=(BinaryTreeLnk &&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk &);
  bool operator!=(const BinaryTreeLnk &);

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  inline const typename BinaryTree<Data>::Node & Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  inline typename MutableBinaryTree<Data>::MutableNode & Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

  inline bool Empty() const noexcept override;

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
