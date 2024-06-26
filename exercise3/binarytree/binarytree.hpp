
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

// #define Stck StackVec
#define Stck StackLst
// #define Que QueueVec
#define Que QueueLst

/* ************************************************************************** */

template <typename Data>
class BinaryTree : public virtual PreOrderTraversableContainer<Data>,
                   public virtual PostOrderTraversableContainer<Data>,
                   public virtual InOrderTraversableContainer<Data>,
                   public virtual BreadthTraversableContainer<Data>
{
protected:
  using Container::size;

public:
  using typename TraversableContainer<Data>::TraverseFun;

  struct Node {
  protected:
    
    // // Comparison operators
    bool operator==(const Node &) const; // Comparison of abstract types is possible, but is not visible.
    bool operator!=(const Node &) const; // Comparison of abstract types is possible, but is not visible.

    //Auxiliary functions
    void PreOrderTraverse (TraverseFun) const;
    void PostOrderTraverse (TraverseFun) const;
    void InOrderTraverse (TraverseFun) const;
    void BreadthTraverse (TraverseFun) const;

  public:
    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node & operator=(const Node &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    Node & operator=(Node &&) = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual const Data & Element() const = 0; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual const Node & LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual const Node & RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
  };

  /* ************************************************************************ */
  BinaryTree() = default;

public:
  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree & operator=(const BinaryTree &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BinaryTree & operator=(BinaryTree &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree &) const; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree &) const; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual const Node & Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  void InOrderTraverse(TraverseFun) const override; // Override InOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  virtual void BreadthTraverse(TraverseFun) const override; // Override BreadthTraversableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : public virtual ClearableContainer,
                          public virtual BinaryTree<Data>,
                          public virtual PreOrderMappableContainer<Data>,
                          public virtual PostOrderMappableContainer<Data>,
                          public virtual InOrderMappableContainer<Data>,
                          public virtual BreadthMappableContainer<Data>
{
protected:
  using BinaryTree<Data>::size;
  using typename BinaryTree<Data>::Node;
  MutableBinaryTree() = default;

public:

  using typename MappableContainer<Data>::MapFun;

  struct MutableNode : public virtual BinaryTree<Data>::Node {
  protected:
  
    MutableNode() = default;
  
    // Auxiliary functions
    void PreOrderMap (MapFun);
    void PostOrderMap (MapFun);
    void InOrderMap (MapFun);
    void BreadthMap (MapFun);

  public:
    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode & operator=(const MutableNode &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    MutableNode & operator=(MutableNode &&) noexcept = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    using BinaryTree<Data>::Node::Element;
    virtual Data & Element() = 0; // Mutable access to the element (concrete function should not throw exceptions)

    using BinaryTree<Data>::Node::LeftChild;
    virtual MutableNode & LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)

    using BinaryTree<Data>::Node::RightChild;
    virtual MutableNode & RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)    
  };

  /* ************************************************************************ */
public:

  // Destructor
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableNode & operator=(const MutableNode &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableNode & operator=(MutableNode &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions
  
  using BinaryTree<Data>::Root;
  virtual MutableNode & Root() = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  void InOrderMap(MapFun) override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  virtual void BreadthMap(MapFun) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator :  public virtual ForwardIterator<Data>,
                            public virtual ResettableIterator<Data>
{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  Stck<const typename BinaryTree<Data>::Node*> stk;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data> & binTree); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator<Data> & that) : root (that.root), curr (that.curr), stk (that.stk) {}

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator<Data> && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);

    that.root = nullptr;
    that.curr = nullptr;
    that.stk.Clear();
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator & operator=(const BTPreOrderIterator<Data> & that);

  // Move assignment
  BTPreOrderIterator & operator=(BTPreOrderIterator<Data> && that) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator<Data> & that) const;
  bool operator!=(const BTPreOrderIterator<Data> & that) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPreOrderIterator & operator++() override; // (throw std::out_of_range when terminated)
  
  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)
};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : public virtual MutableIterator<Data>,
                                  public virtual BTPreOrderIterator<Data>
{

private:

  // ...

protected:

  // typename MutableBinaryTree<Data>::MutableNode * mRoot = nullptr;
  // typename MutableBinaryTree<Data>::MutableNode * mCurr = nullptr;
  using BTPreOrderIterator<Data>::curr;
  using BTPreOrderIterator<Data>::root;
  using BTPreOrderIterator<Data>::stk;

public:

  // Specific constructors
  BTPreOrderMutableIterator(const MutableBinaryTree<Data> & bTree) : BTPreOrderIterator<Data>(bTree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator & that) : BTPreOrderIterator<Data> ((const BTPreOrderIterator<Data> &) that) {}

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator && that) noexcept : BTPreOrderIterator<Data> (std::move((const BTPreOrderIterator<Data> &) that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator & operator=(const BTPreOrderMutableIterator & that);

  // Move assignment
  BTPreOrderMutableIterator & operator=(BTPreOrderMutableIterator && that);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderMutableIterator & that) const;
  bool operator!=(const BTPreOrderMutableIterator & that) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  using BTPreOrderIterator<Data>::operator*;
  Data & operator*() override; // (throw std::out_of_range when terminated)
};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : public virtual ForwardIterator<Data>,
                            public virtual ResettableIterator<Data>
{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  Stck<const typename BinaryTree<Data>::Node*> stk;

  void toLeftMostLeaf();

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data> & binTree); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator & that) : curr(that.curr), stk(that.stk) {}

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);

    that.root = nullptr;
    that.curr = nullptr;
    that.stk.Clear();
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator & operator=(const BTPostOrderIterator & that);

  // Move assignment
  BTPostOrderIterator & operator=(BTPostOrderIterator && that) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  
  bool operator==(const BTPostOrderIterator & that) const;
  bool operator!=(const BTPostOrderIterator & that) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPostOrderIterator & operator++() override; // (throw std::out_of_range when terminated)
  
  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : public virtual MutableIterator<Data>,
                                   public virtual BTPostOrderIterator<Data>
{

private:

  // ...

protected:

  using BTPostOrderIterator<Data>::curr;
  using BTPostOrderIterator<Data>::root;
  using BTPostOrderIterator<Data>::stk;

public:

  // Specific constructors
  BTPostOrderMutableIterator(const MutableBinaryTree<Data> & bTree) : BTPostOrderIterator<Data>(bTree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator & that) : BTPostOrderIterator<Data> ((const BTPostOrderIterator<Data> &) that) {}

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator && that) noexcept : BTPostOrderIterator<Data> (std::move((const BTPostOrderIterator<Data> &) that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator & operator=(const BTPostOrderMutableIterator & that);

  // Move assignment
  BTPostOrderMutableIterator & operator=(BTPostOrderMutableIterator && that);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderMutableIterator & that) const;

  bool operator!=(const BTPostOrderMutableIterator & that) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  using BTPostOrderIterator<Data>::operator*;
  Data & operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : public virtual ForwardIterator<Data>,
                          public virtual ResettableIterator<Data>
{

private:

  // ...

protected:
  
  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  Stck<const typename BinaryTree<Data>::Node*> stk;

  void toLeftMostNode ();

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data> & binTree); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator & that) : curr(that.curr), stk(that.stk) {}

  // Move constructor
  BTInOrderIterator(BTInOrderIterator && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);

    that.root = nullptr;
    that.curr = nullptr;
    that.stk.Clear();
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator & operator=(const BTInOrderIterator & that);

  // Move assignment
  BTInOrderIterator & operator=(BTInOrderIterator && that) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  
  bool operator==(const BTInOrderIterator<Data> & that) const;
  bool operator!=(const BTInOrderIterator<Data> & that) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator & operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)
};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator :  public virtual MutableIterator<Data>,
                                  public virtual BTInOrderIterator<Data>
{

private:

  // ...

protected:

  using BTInOrderIterator<Data>::curr;
  using BTInOrderIterator<Data>::root;
  using BTInOrderIterator<Data>::stk;

public:
  
  // Specific constructors
  BTInOrderMutableIterator(const MutableBinaryTree<Data> & bTree) : BTInOrderIterator<Data>(bTree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator & that) : BTInOrderIterator<Data> ((const BTInOrderIterator<Data> &) that) {}

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator && that) noexcept : BTInOrderIterator<Data> (std::move((const BTInOrderIterator<Data> &) that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator & operator=(const BTInOrderMutableIterator & that);

  // Move assignment
  BTInOrderMutableIterator & operator=(BTInOrderMutableIterator && that);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderMutableIterator & that) const;

  bool operator!=(const BTInOrderMutableIterator & that) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  using BTInOrderIterator<Data>::operator*;
  Data & operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : public virtual ForwardIterator<Data>,
                          public virtual ResettableIterator<Data>
{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  Que<const typename BinaryTree<Data>::Node *> que;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data> & binTree); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator& that) : root(that.root), curr(that.root), que(that.que) {}

  // Move constructor
  BTBreadthIterator(BTBreadthIterator&& that) noexcept 
  {
    std::swap(root, that.root);
    std::swap(curr, that.curr);
    std::swap(que, that.que);

    that.root = nullptr;
    that.curr = nullptr;
    that.que.Clear();
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator & operator=(const BTBreadthIterator & that);

  // Move assignment
  BTBreadthIterator & operator=(BTBreadthIterator && that) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator & that) const;

  bool operator!=(const BTBreadthIterator & that) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTBreadthIterator & operator++() override; // (throw std::out_of_range when terminated)
 
  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : public virtual MutableIterator<Data>,
                                 public virtual BTBreadthIterator<Data> 
{

private:

  // ...

protected:

  using BTBreadthIterator<Data>::curr;
  using BTBreadthIterator<Data>::root;
  using BTBreadthIterator<Data>::que;

public:
  
  // Specific constructors
  BTBreadthMutableIterator(const MutableBinaryTree<Data> & bTree) : BTBreadthIterator<Data>(bTree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator & that) : BTBreadthIterator<Data> ((const BTBreadthIterator<Data> &) that) {}

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator && that) noexcept : BTBreadthIterator<Data> (std::move((const BTBreadthIterator<Data> &) that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator & operator=(const BTBreadthMutableIterator & that);

  // Move assignment
  BTBreadthMutableIterator & operator=(BTBreadthMutableIterator && that);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthMutableIterator & that) const;

  bool operator!=(const BTBreadthMutableIterator & that) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  using BTBreadthIterator<Data>::operator*;
  Data & operator*() override; // (throw std::out_of_range when terminated)
};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
