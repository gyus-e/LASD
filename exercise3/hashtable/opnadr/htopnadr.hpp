
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"
// #include "../../list/list.hpp"

// #include "../../queue/lst/queuelst.hpp"
// #include "../../queue/vec/queuevec.hpp"

// #include "../../stack/lst/stacklst.hpp"
// #include "../../stack/vec/stackvec.hpp"

// #include "../../binarytree/lnk/binarytreelnk.hpp"
// #include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : public virtual HashTable<Data>
{

private:

protected:
  #define LOAD_FACTOR_OPNADR 0.5
  #define REDUCE_LOAD_FACTOR_OPNADR 0.2

  enum class status {free, inserted, deleted};

  using HashTable<Data>::tableSize; //size of the Table
  using HashTable<Data>::size; //number of elements
  Vector<Data> Table;
  Vector<status> flag; 


  //per doppio hashing
  // unsigned long acoeff2 = 1;
  // unsigned long bcoeff2 = 0;
  // static const unsigned long prime2 = 2184872057;
  // std::default_random_engine gen2  = std::default_random_engine (std::random_device{}());
  // std::uniform_int_distribution <unsigned long> dista2 = std::uniform_int_distribution <unsigned long> (1, prime2 - 1);
  // std::uniform_int_distribution <unsigned long> distb2 = std::uniform_int_distribution <unsigned long> (0, prime2 - 1);

public:

  // Default constructor
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(unsigned long); // A hash table of a given size
  HashTableOpnAdr(const TraversableContainer<Data> &); // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(unsigned long, const TraversableContainer<Data> &); // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(MappableContainer<Data> &&); // A hash table obtained from a MappableContainer
  HashTableOpnAdr(unsigned long, MappableContainer<Data> &&); // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr<Data> &);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data> &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr<Data> & operator=(const HashTableOpnAdr<Data> &);

  // Move assignment
  HashTableOpnAdr<Data> & operator=(HashTableOpnAdr<Data> &&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr<Data> &) const;
  bool operator!=(const HashTableOpnAdr<Data> &) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data &) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data &&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data &) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data &) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(unsigned long); // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions
  using HashTable<Data>::enchash;
  using HashTable<Data>::HashKey;
  unsigned long HashKey (const Data &, const unsigned long) const;
  unsigned long coprimeF (const Data & dat) const;
  // unsigned long HashKey2 (const Data &) const;

  // type Find(argument) specifiers;
  // type FindEmpty(argument) specifiers;
  // type Remove(argument) specifiers;
  void GarbageCollect ();
  void InitFlag ();
  // void InitCoeffs ();
};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
