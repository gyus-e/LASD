
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : public virtual ClearableContainer,
            public virtual DictionaryContainer<Data>,
            public virtual BinaryTree<Data>,
            public virtual BinaryTreeLnk<Data>
{
private:

  // ...

protected:

  using typename BinaryTreeLnk<Data>::NodeLnk;

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const TraversableContainer<Data> & con) : BinaryTreeLnk<Data>(con) {} // A bst obtained from a TraversableContainer
  BST(MappableContainer<Data> & con) : BinaryTreeLnk<Data>(std::move(con)) {} // A bst obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST<Data> & that) : BinaryTreeLnk<Data>(that) {}

  // Move constructor
  BST(BST<Data> && that) noexcept : BinaryTreeLnk<Data> (std::move(that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST operator=(const BST<Data> &);

  // Move assignment
  BST operator=(BST<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST<Data> &) const;
  bool operator!=(const BST<Data> &) const;

  /* ************************************************************************ */

  // Specific member functions

  const Data & Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin(); // (concrete function must throw std::length_error when empty)

  const Data & Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data & Predecessor(const Data &) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data &); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data &); // (concrete function must throw std::length_error when not found)

  const Data & Successor(const Data &) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data &); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data &); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  inline const typename BinaryTree<Data>::Node & Root() const override; // Override BinaryTree member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data &&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data &) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data &) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

protected:
  // Auxiliary functions, if necessary!

  // Data DataNDelete(NodeLnk *);

  typename BinaryTreeLnk<Data>::NodeLnk * Detach(typename BinaryTreeLnk<Data>::NodeLnk **);
  // void Detach(typename BinaryTreeLnk<Data>::NodeLnk **);

  typename BinaryTreeLnk<Data>::NodeLnk * DetachMin(typename BinaryTreeLnk<Data>::NodeLnk *, typename BinaryTreeLnk<Data>::NodeLnk *);
  typename BinaryTreeLnk<Data>::NodeLnk * DetachMax(typename BinaryTreeLnk<Data>::NodeLnk *, typename BinaryTreeLnk<Data>::NodeLnk *);

  // typename BinaryTreeLnk<Data>::NodeLnk * Skip2Left(typename BinaryTreeLnk<Data>::NodeLnk **);
  // typename BinaryTreeLnk<Data>::NodeLnk * Skip2Right(typename BinaryTreeLnk<Data>::NodeLnk **);

  typename BinaryTreeLnk<Data>::NodeLnk * FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk *); //mutable version
  const typename BinaryTreeLnk<Data>::NodeLnk * FindPointerToMin(const typename BinaryTreeLnk<Data>::NodeLnk *) const; //unmutable version

  typename BinaryTreeLnk<Data>::NodeLnk * FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk *); //mutable version
  const typename BinaryTreeLnk<Data>::NodeLnk * FindPointerToMax(const typename BinaryTreeLnk<Data>::NodeLnk *) const; //unmutable version

  typename BinaryTreeLnk<Data>::NodeLnk * FindPointerTo(const Data &, typename BinaryTreeLnk<Data>::NodeLnk *); //mutable version
  const typename BinaryTreeLnk<Data>::NodeLnk * FindPointerTo(const Data &, const typename BinaryTreeLnk<Data>::NodeLnk *) const; //unmutable version

  typename BinaryTreeLnk<Data>::NodeLnk ** FindPointerToPredecessor(const Data &, typename BinaryTreeLnk<Data>::NodeLnk **); //mutable version
  const typename BinaryTreeLnk<Data>::NodeLnk * const * FindPointerToPredecessor(const Data &, const typename BinaryTreeLnk<Data>::NodeLnk * const *) const; //unmutable version

  typename BinaryTreeLnk<Data>::NodeLnk ** FindPointerToSuccessor(const Data &, typename BinaryTreeLnk<Data>::NodeLnk **); //mutable version
  const typename BinaryTreeLnk<Data>::NodeLnk * const * FindPointerToSuccessor(const Data &, const typename BinaryTreeLnk<Data>::NodeLnk * const *) const; //unmutable version
  
  //...

  bool Insert(const Data &, typename BinaryTreeLnk<Data>::NodeLnk **); //copy
  bool Insert(Data &&, typename BinaryTreeLnk<Data>::NodeLnk **); //move
  bool Remove (const Data &, typename BinaryTreeLnk<Data>::NodeLnk **);
};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
