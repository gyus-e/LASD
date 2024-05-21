
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

private:

  // ...

protected:

  // ...

  struct NodeVec : public virtual MutableBinaryTree<Data>::MutableNode
  {

  private:

    // ...

  protected:

    Data elem;
    unsigned long idx = 0;
    BinaryTreeVec * tree = nullptr;

  public:

    friend class BinaryTreeVec<Data>;
    
    NodeVec () = default;
    NodeVec (const Data & d) : elem (d) {}
    NodeVec (Data && d) {this->elem = std::move(d);}
    NodeVec (const NodeVec & that) : elem(that.elem), idx(that.idx), tree(that.tree) {}
    NodeVec (NodeVec && that) noexcept {std::swap (this->elem, that.elem); std::swap (this->idx, that.idx); std::swap (this->tree, that.tree);}
    
    virtual ~NodeVec () = default;
    
    inline Data & Element () override {return this->elem;}
    inline const Data & Element () const override {return this->elem;}
    
    inline bool IsLeaf() const noexcept override {return !(this->HasLeftChild() || this->HasRightChild());} 
    
    inline bool HasLeftChild() const noexcept override;
    inline bool HasRightChild() const noexcept override;

    typename MutableBinaryTree<Data>::MutableNode & LeftChild() override; // (concrete function must throw std::out_of_range when not existent)
    const typename BinaryTree<Data>::Node & LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)

    typename MutableBinaryTree<Data>::MutableNode & RightChild() override; // (concrete function must throw std::out_of_range when not existent)    
    const typename BinaryTree<Data>::Node & RightChild() const override; // (concrete function must throw std::out_of_range when not existent)
  };
  
  using MutableBinaryTree<Data>::size; //real size of the vector
  unsigned long dim = 0; //amount of nodes in the tree
  Vector<NodeVec *> * vec = nullptr;

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
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec operator=(const BinaryTreeVec &);

  // Move assignment
  BinaryTreeVec operator=(BinaryTreeVec &&);

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

  void Clear() override; // Override ClearableContainer member

  inline bool Empty() const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;
  
  void BreadthTraverse(TraverseFun) const override; // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  using typename MappableContainer<Data>::MapFun;


  void BreadthMap(MapFun) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
