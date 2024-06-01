
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>
#include <string>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  virtual unsigned long operator()(const Data &) const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : public virtual ResizableContainer,
                  public virtual DictionaryContainer<Data>
{

private:

protected:
  #define INITIAL_SIZE 128UL
  // #define MAX_SIZE 2147483648UL //2^31

  using DictionaryContainer<Data>::size;
  unsigned long acoeff = 1;
  unsigned long bcoeff = 0;
  // static const unsigned long prime = 2147483647; //numero primo ((2^31) - 1)
  static const unsigned long prime = 4294967291; //largest prime number in unsigned long int


  std::default_random_engine gen  = std::default_random_engine (std::random_device{}());
  std::uniform_int_distribution <unsigned long> dista = std::uniform_int_distribution <unsigned long> (1, prime - 1);
  std::uniform_int_distribution <unsigned long> distb = std::uniform_int_distribution <unsigned long> (0, prime - 1);

  static const Hashable<Data> enchash;

  unsigned long tableSize = INITIAL_SIZE;


  // Default constructor
  HashTable();

  // Copy constructor
  HashTable(const HashTable &);

  // Move constructor
  HashTable(HashTable &&) noexcept;

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */
protected:

  // Copy assignment
  HashTable<Data> & operator=(const HashTable<Data> &); // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable<Data> & operator=(HashTable<Data> &&) noexcept; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

public:
  // Comparison operators
  bool operator==(const HashTable &) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  bool operator!=(const HashTable &) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.

protected:

  // Auxiliary member functions

  virtual inline unsigned long HashKey(const Data & dat) const noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
