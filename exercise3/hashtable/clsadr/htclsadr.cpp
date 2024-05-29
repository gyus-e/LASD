#include <stdexcept>
#include <iostream>

namespace lasd {

/* ************************************************************************** */

// Default constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() : Table (INITIAL_SIZE)
{
    this->tableSize = this->Table.Size();
}

// Specific constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long newSize) : Table (std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE))
{
    this->tableSize = this->Table.Size();
}

// Constructor from TraversableContainer
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& container) : Table (INITIAL_SIZE)
{
    this->tableSize = this->Table.Size();

    if (!container.Empty())
    {
        container.Traverse(
            [this](const Data& elem) 
            {
                this->Insert(elem);
            }
        );
    }
}

// Constructor from TraversableContainer with specified tableSize
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long newSize, const TraversableContainer<Data>& container) : Table ((std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE)))
{
    this->tableSize = this->Table.Size();

    if (!container.Empty())
    {
        container.Traverse(
            [this](const Data& elem) 
            {
                this->Insert(elem);
            }
        );
    }
}

// Constructor from MappableContainer
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& container) : Table (INITIAL_SIZE)
{
    this->tableSize = this->Table.Size();

    if (!container.Empty())
    {
        container.Map(
            [this](Data&& elem) 
            {
                this->Insert(std::move(elem));
            }
        );
    }
}

// Constructor from MappableContainer with specified tableSize
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long newSize, MappableContainer<Data>&& container) : Table ((std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE)))
{
    this->tableSize = this->Table.Size();

    if (!container.Empty())
    {
        container.Map(
            [this](Data&& elem) 
            {
                this->Insert(std::move(elem));
            }
        );
    }
}

// Copy constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> & that) : Table (INITIAL_SIZE)
{
    this->tableSize = this->Table.Size();
    this->size = 0;

    if (!that.Empty())
    {
        that.Table.Traverse(
            [this](const Bucket & bucket)
            {
                if (!bucket.Empty())
                {
                    bucket.Traverse(
                        [this](const Data & dat)
                        {
                            this->Insert(dat);
                        }
                    );
                }
            }
        );
    }

}

// Move constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& that) noexcept : HashTable<Data> (std::move (that))
{
    std::swap ((this->Table), (that.Table));
}

// Copy assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& that) 
{
    if (this != &that) 
    {
        HashTableClsAdr<Data> copy (that);
        std::swap (*this, copy);
    }
    return *this;
}

// Move assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& that) noexcept 
{
    if (this != &that) 
    {
        this->HashTable<Data>::operator=(std::move(that));        
        std::swap(this->Table, that.Table);
    }
    return *this;
}

// Comparison operators
template <typename Data>
inline bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& that) const
{
    if (this->size != that.size)
    {
        return false;
    }

    bool ret = true;

    this->Table.Traverse(
        [&that, &ret] (const Bucket & bucket)
        {
            if (!bucket.Empty())
            {
                bucket.Traverse(
                    [&that, &ret] (const Data & dat)
                    {
                         ret &= that.Exists(dat);
                    }
                );
            }
        }
    );
    return ret;
}

template <typename Data>
inline bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& that) const
{
    return !(this->operator==(that));
}

// Insert (copy)
template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& data) 
{
    if (Table[this->HashKey(data)].Insert(data)) 
    {
        this->size++;
        if (this->size > (this->tableSize * LOAD_FACTOR_CLSADR)) 
        {
            this->Resize(this->tableSize * 2);
        }

        return true;
    }
    return false;
}

// Insert (move)
template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& data) 
{
    if (Table[this->HashKey(data)].Insert(std::move(data)))
    {
        this->size++;

        if (this->size > (this->tableSize * LOAD_FACTOR_CLSADR))
        {
            this->Resize(this->tableSize * 2);
        }

        return true;
    }
    return false;
}

// Remove
template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& data) 
{
    if (this->Table[this->HashKey(data)].Remove(data)) 
    {
        this->size--;
        if ((this->size < (this->tableSize * REDUCE_LOAD_FACTOR_CLSADR)) && ((this->tableSize / 2) > INITIAL_SIZE)) 
        {
            this->Resize(this->tableSize / 2);
        }
        return true;
    }
    return false;
}

// Exists
template <typename Data>
inline bool HashTableClsAdr<Data>::Exists(const Data& data) const noexcept 
{
    return Table[this->HashKey(data)].Exists(data);
}

// Resize
template <typename Data>
void HashTableClsAdr<Data>::Resize(unsigned long newSize) 
{   
    //se la resize è a 0, fa una clear
    if (newSize == 0)
    {
        this->Clear();
        return;
    }

    //Arrotonda newSize alla prossima potenza di 2
    unsigned long exp = ceil(log2(newSize));
    newSize = pow(2, exp);
    //Verifica che la dimensione minima sia rispettata
    newSize = std::max(newSize, INITIAL_SIZE);
    //Verifica che la dimensione massima sia rispettata
    newSize = std::min(newSize, MAX_SIZE);
    
    //Verifica che la resize vada effettuata davvero
    if (newSize == this->tableSize)
    {
        return;
    }

    //serve una nuova HashTable perché vogliamo anche una nuova funzione HashKey
    HashTableClsAdr<Data> newTable(newSize); 
    
    this->Table.Map (
        [&newTable] (Bucket & cont)
        {
            if (!cont.Empty())
            {
                cont.Map(
                    [&newTable] (Data & data)
                    {
                        if (newTable.Table[newTable.HashKey(data)].Insert(std::move(data)))
                        {
                            newTable.size++;
                        }
                    }
                );
            }
        }
    );

    std::swap (*this, newTable);
}

// Clear
template <typename Data>
void HashTableClsAdr<Data>::Clear() 
{
    unsigned long count = 0;
    Table.Map(
        [&count](Bucket & cont)
        {
            if (!cont.Empty())
            {    
                cont.Clear();
            }
        }
    );
    this->size = 0;
    Table.Resize(INITIAL_SIZE);
}

/* ************************************************************************** */

}
