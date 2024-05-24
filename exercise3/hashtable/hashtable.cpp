namespace lasd {
/* ************************************************************************** */
/*          Hashable           */

//Hash per interi
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
class Hashable<long>
{
public:
    unsigned long operator()(const long & dat) const noexcept 
    {
        return dat*dat;
    }
};

template<>
class Hashable<char>
{
public:
    unsigned long operator()(const char & dat) const noexcept 
    {
        return ((long)dat)*((long)dat);
    }
};

//Hash per reali
template<>
class Hashable<float>
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

//Hash per stringhe
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
    this->tableSize = that.tableSize;
    this->size = that.size;
    this->acoeff = that.acoeff;
    this->bcoeff = that.bcoeff;
    // this->gen = that.gen;
    // this->dista = that.dista;
    // this->distb = that.distb;
    // this->enchash = that.enchash;
}

// Move constructor
template <typename Data>
HashTable<Data>::HashTable(HashTable<Data> && that) noexcept
{
    std::swap(this->tableSize, that.tableSize);
    std::swap(this->size, that.size);
    std::swap(this->acoeff, that.acoeff);
    std::swap(this->bcoeff, that.bcoeff);
    // std::swap(this->gen, that.gen);
    // std::swap (this->dista, that.dista);
    // std::swap (this->distb, that.distb);
    // std::swap (this->enchash, that.enchash);
}

// Copy assignment
template <typename Data>
HashTable<Data> & HashTable<Data>::operator=(const HashTable<Data> & that)
{
    this->tableSize = that.tableSize;
    this->acoeff = that.acoeff;
    this->bcoeff = that.bcoeff;
    this->tableSize = that.tableSize;
    return *this;
}

// Move assignment
template <typename Data>
HashTable<Data> & HashTable<Data>::operator=(HashTable<Data> && that) noexcept
{
    std::swap(this->tableSize, that.tableSize);
    std::swap(this->acoeff, that.acoeff);
    std::swap(this->bcoeff, that.bcoeff);
    std::swap(this->tableSize, that.tableSize);
    return *this;
}

template <typename Data>
inline unsigned long HashTable<Data>::HashKey(const Data & dat) const noexcept
{
    // return HashKey(enchash(dat));
    return ((acoeff * enchash(dat) + bcoeff) % prime) % tableSize;
}

// template <typename Data>
// inline unsigned long HashTable<Data>::HashKey(unsigned long key) const noexcept
// {
//     return ((acoeff * key + bcoeff) % prime) % tableSize;
// }

/* ************************************************************************** */

}
