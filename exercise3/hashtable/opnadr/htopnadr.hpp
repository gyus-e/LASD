
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"
#include "../../list/list.hpp"

#include "../../queue/lst/queuelst.hpp"
#include "../../queue/vec/queuevec.hpp"

#include "../../stack/lst/stacklst.hpp"
#include "../../stack/vec/stackvec.hpp"

#include "../../binarytree/lnk/binarytreelnk.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : public virtual HashTable<Data>
{

private:

protected:

  enum class status {absent, present, deleted};

  using HashTable<Data>::size;
  unsigned long dim = 0;
  Vector<Data> Table;
  Vector<status> flag; 

public:

  // Default constructor
  // HashTableOpnAdr() specifiers;

  /* ************************************************************************ */

  // Specific constructors
  // HashTableOpnAdr(argument) specifiers; // A hash table of a given size
  // HashTableOpnAdr(argument) specifiers; // A hash table obtained from a TraversableContainer
  // HashTableOpnAdr(argument) specifiers; // A hash table of a given size obtained from a TraversableContainer
  // HashTableOpnAdr(argument) specifiers; // A hash table obtained from a MappableContainer
  // HashTableOpnAdr(argument) specifiers; // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  // HashTableOpnAdr(argument) specifiers;

  // Move constructor
  // HashTableOpnAdr(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~HashTableOpnAdr() specifiers;

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

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override; // Override DictionaryContainer member (Copy of the value)
  // type Insert(argument) specifiers; // Override DictionaryContainer member (Move of the value)
  // type Remove(argument) specifiers; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  // type Exists(argument) specifiers; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  // type Resize(argument) specifiers; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  // type Clear() specifiers; // Override Container member

protected:

  // Auxiliary member functions

  // type HashKey(argument) specifiers;
  // type Find(argument) specifiers;
  // type FindEmpty(argument) specifiers;
  // type Remove(argument) specifiers;

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
