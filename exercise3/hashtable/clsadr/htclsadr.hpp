
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"

#include "../../vector/vector.hpp"
#include "../../list/list.hpp"

#include "../../queue/lst/queuelst.hpp"
// #include "../../queue/vec/queuevec.hpp"

#include "../../stack/lst/stacklst.hpp"
// #include "../../stack/vec/stackvec.hpp"

#include "../../binarytree/lnk/binarytreelnk.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : public virtual HashTable<Data>
{
private:
  
protected:
  #define LOAD_FACTOR_CLSADR 0.8
  #define REDUCE_LOAD_FACTOR_CLSADR 0.2

  typedef BST<Data> BUCKET;
  // typedef List<Data> BUCKET;

  using HashTable<Data>::tableSize; //size of the Table
  using HashTable<Data>::size; //number of elements
  Vector <BUCKET> Table;

public:

  // Default constructor
  HashTableClsAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(unsigned long); // A hash table of a given size
  HashTableClsAdr(const TraversableContainer<Data> &); // A hash table obtained from a TraversableContainer
  HashTableClsAdr(unsigned long, const TraversableContainer<Data> &); // A hash table of a given size obtained from a TraversableContainer
  HashTableClsAdr(MappableContainer<Data> &&); // A hash table obtained from a MappableContainer
  HashTableClsAdr(unsigned long, MappableContainer<Data> &&); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr<Data>  &);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableClsAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr<Data> & operator=(const HashTableClsAdr<Data> &);

  // Move assignment
  HashTableClsAdr<Data> & operator=(HashTableClsAdr<Data> &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const HashTableClsAdr &) const;
  inline bool operator!=(const HashTableClsAdr &) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data &&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data &) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  inline bool Exists(const Data &) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(unsigned long); // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
