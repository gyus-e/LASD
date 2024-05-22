#include <string>

namespace lasd {
/* ************************************************************************** */
/*          Hashable           */

template<>
class Hashable<int>
{
public:
    unsigned long operator()(const int & dat) const noexcept 
    {
        return dat*dat;
    }
};

template<>
class Hashable<double>
{
public:
    unsigned long operator()(const double & dat) const noexcept 
    {
        long intgpart = floor(dat);
        long fracpart = pow(2, 24) * (dat - intgpart);
        return (intgpart * fracpart);
    }
};

template<>
class Hashable<std::string>
{
public:
    unsigned long operator()(const std::string & dat) const noexcept 
    {
        unsigned long hash = 5381; //numero primo
        for (unsigned long i = 0; i < dat.length(); i++)
        {
            hash = (hash << 5) + dat[i]; 
            //hash = (hash/(2^5)) + dat[i]
        }
        return hash;
    }
};


/* ************************************************************************** */
/*          HashTable           */

// Default constructor
template <typename Data>
HashTable<Data>::HashTable()
{
    this->acoeff = dista(gen);
    this->bcoeff = distb(gen);
}

// Copy constructor
template <typename Data>
HashTable<Data>::HashTable(const HashTable<Data> & that)
{
    this->size = that.size;
    this->acoeff = that.acoeff;
    this->bcoeff = that.bcoeff;
    this->tableSize = that.tableSize;
}

// Move constructor
template <typename Data>
HashTable<Data>::HashTable(HashTable<Data> && that) noexcept
{
    std::swap(this->size, that.size);
    std::swap(this->acoeff, that.acoeff);
    std::swap(this->bcoeff, that.bcoeff);
    std::swap(this->tableSize, that.tableSize);
}

// Copy assignment
template <typename Data>
HashTable<Data> & HashTable<Data>::operator=(const HashTable<Data> & that)
{
    this->size = that.size;
    this->acoeff = that.acoeff;
    this->bcoeff = that.bcoeff;
    this->tableSize = that.tableSize;
    return *this;
}

// Move assignment
template <typename Data>
HashTable<Data> & HashTable<Data>::operator=(HashTable<Data> && that) noexcept
{
    std::swap(this->size, that.size);
    std::swap(this->acoeff, that.acoeff);
    std::swap(this->bcoeff, that.bcoeff);
    std::swap(this->tableSize, that.tableSize);
    return *this;
}

template <typename Data>
inline unsigned long HashTable<Data>::HashKey(const Data & dat) const noexcept
{
    return HashKey(enchash(dat));
}

template <typename Data>
inline unsigned long HashTable<Data>::HashKey(unsigned long key) const noexcept
{
    return ((acoeff * key + bcoeff) % prime) % tableSize;
}

/* ************************************************************************** */

}
