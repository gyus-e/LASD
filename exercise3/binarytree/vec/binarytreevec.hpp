
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : public virtual MutableBinaryTree<Data> {

protected:

  struct NodeVec : public virtual MutableBinaryTree<Data>::MutableNode
  {
  protected:
    Data elem {};
    unsigned long idx = 0;
    BinaryTreeVec<Data> * tree = nullptr;

  public:
    NodeVec () = default;

    NodeVec (const Data &);
    NodeVec (Data &&);
    
    NodeVec (const NodeVec &);
    NodeVec (NodeVec &&) noexcept;

    NodeVec & operator= (const NodeVec &);
    NodeVec & operator= (NodeVec &&);

    virtual ~NodeVec () = default;

    bool operator== (const NodeVec &) const;
    bool operator!= (const NodeVec &) const;
    
    inline Data & Element () override;
    inline const Data & Element () const override;
    
    inline bool IsLeaf() const noexcept override;
    
    inline bool HasLeftChild() const noexcept override;
    inline bool HasRightChild() const noexcept override;

    typename MutableBinaryTree<Data>::MutableNode & LeftChild() override; // (concrete function must throw std::out_of_range when not existent)
    const typename BinaryTree<Data>::Node & LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)

    typename MutableBinaryTree<Data>::MutableNode & RightChild() override; // (concrete function must throw std::out_of_range when not existent)    
    const typename BinaryTree<Data>::Node & RightChild() const override; // (concrete function must throw std::out_of_range when not existent)
  
    friend class BinaryTreeVec<Data>;
    friend class Vector<Data>;
  };
  
  using MutableBinaryTree<Data>::size; //amount of elements in the tree
  unsigned long vecSize = 0; //real size of the vector
  Vector<NodeVec> vec;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data> &); // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data> &&); // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec &);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec & operator=(const BinaryTreeVec &);

  // Move assignment
  BinaryTreeVec & operator=(BinaryTreeVec &&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec &);
  bool operator!=(const BinaryTreeVec &);

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  inline const typename BinaryTree<Data>::Node & Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  inline typename MutableBinaryTree<Data>::MutableNode & Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() override; // Override ClearableContainer member

  inline virtual bool Empty() const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  
  void BreadthTraverse(TraverseFun) const override; // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void BreadthMap(MapFun) override; // Override BreadthMappableContainer member
  
  friend class Vector<Data>;
};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
