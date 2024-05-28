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

    //genero nuovi coefficienti
    gen  = std::default_random_engine (std::random_device{}());
    dista = std::uniform_int_distribution <unsigned long> (1, prime - 1);
    distb = std::uniform_int_distribution <unsigned long> (0, prime - 1);

    this->acoeff = dista(gen);
    this->bcoeff = distb(gen);
}

// Move constructor
template <typename Data>
HashTable<Data>::HashTable(HashTable<Data> && that) noexcept
{
    std::swap(this->tableSize, that.tableSize);
    std::swap(this->size, that.size);
    std::swap(this->acoeff, that.acoeff);
    std::swap(this->bcoeff, that.bcoeff);
    std::swap(this->gen, that.gen);
    std::swap (this->dista, that.dista);
    std::swap (this->distb, that.distb);
}

// Copy assignment
template <typename Data>
HashTable<Data> & HashTable<Data>::operator=(const HashTable<Data> & that)
{
    this->tableSize = that.tableSize;

    //genero nuovi coefficienti
    this->acoeff = dista(gen);
    this->bcoeff = distb(gen);
    
    this->size = that.size;
    return *this;
}

// Move assignment
template <typename Data>
HashTable<Data> & HashTable<Data>::operator=(HashTable<Data> && that) noexcept
{
    std::swap(this->tableSize, that.tableSize);
    std::swap(this->acoeff, that.acoeff);
    std::swap(this->bcoeff, that.bcoeff);
    std::swap(this->size, that.size);
    return *this;
}

template <typename Data>
inline unsigned long HashTable<Data>::HashKey(const Data & dat) const noexcept
{
    // sfruttando le proprietá: 
    // (A + B) % C == (A % C + B % C) % C
    // (A * B) % C == (A % C * B % C) % C
    return ( ( ( ( (this->acoeff % this->prime) * (this->enchash(dat) % this->prime) ) % this->prime ) + ( this->bcoeff % this->prime ) ) % this->prime ) % this->tableSize;
}

/* ************************************************************************** */

}
