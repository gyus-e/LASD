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
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long newSize) : Table (pow(2, ceil(log2(newSize))))
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
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long newSize, const TraversableContainer<Data>& container) : Table (pow(2, ceil(log2(newSize))))
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
HashTableClsAdr<Data>::HashTableClsAdr(unsigned long newSize, MappableContainer<Data>&& container) : Table (pow(2, ceil(log2(newSize))))
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
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> & that) : HashTable<Data> (that) //, Table (that.Table)
{
    this->Table = that.Table;
    // this->size = that.size;
    // this->tableSize = that.tableSize;
}

// Move constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& that) noexcept //: HashTable<Data> (std::move (that)) //, Table (std::move (that.Table))
{
    std::cout<<"attempting swap"<<std::endl;
    //deadly signal

    // std::swap(this->Table, that.Table); 
    // this->Table.operator=(std::move(that.Table));
    
    // std::swap(this->size, that.size);
    // std::swap(this->tableSize, that.tableSize);
}

// Copy assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr& that) 
{
    if (this != &that) 
    {
        this->Table = that.Table;
        this->size = that.size;
        this->tableSize = that.tableSize;
    }
    return *this;
}

// Move assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr&& that) noexcept 
{
    if (this != &that) 
    {
        std::swap(this->Table, that.Table);
        std::swap(this->size, that.size);
        std::swap(this->tableSize, that.tableSize);
    }
    return *this;
}

// Comparison operators
template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& that) 
{
    return (this->Table == that.Table) && (this->size == that.size) && (this->tableSize == that.tableSize);
}

template <typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& that) 
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
        if (this->size > (this->tableSize * LOAD_FACTOR)) 
        {
            // this->Resize(this->tableSize * 2);
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

        if (this->size > (this->tableSize * LOAD_FACTOR))
        {
            // this->Resize(this->tableSize * 2);
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
        if ((this->size < (this->tableSize * REDUCE_LOAD_FACTOR)) && ((this->tableSize / 2) > INITIAL_SIZE)) 
        {
            this->Resize(this->tableSize / 2);
        }
        return true;
    }
    return false;
}

// Exists
template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& data) const noexcept 
{
    return Table[this->HashKey(data)].Exists(data);
}

// Resize
template <typename Data>
void HashTableClsAdr<Data>::Resize(unsigned long newSize) 
{    
    //Arrotonda newSize alla prossima potenza di 2 
    unsigned long exp = ceil(log2(newSize));
    newSize = pow(2, exp);
    
    if (newSize == this->tableSize)
    {
        return;
    }

    //serve una nuova HashTable perché vogliamo anche una nuova funzione HashKey
    HashTableClsAdr<Data> newTable(newSize); 
    
    this->Table.Map (
        [&newTable] (BUCKET & cont)
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
    
    //ERRORE SOTTO!
    //rivedere move constructor

    // this->Table = newTable.Table;
    // std::swap (this->Table, newTable.Table);
    // this->Table = std::move(newTable.Table); //rivedere move constructor?
    // this->tableSize = newTable.tableSize;

    // std::swap (*this, newTable);
    // std::swap (this, &newTable);

    std::cout<<"Resized to "<<this->tableSize<<std::endl;
}

// Clear
template <typename Data>
void HashTableClsAdr<Data>::Clear() 
{
    Table.Map(
        [](BUCKET & cont)
        {
            cont.Clear();
        }
    );
    this->size = 0;
    Table.Resize(INITIAL_SIZE);
}

/* ************************************************************************** */

}
