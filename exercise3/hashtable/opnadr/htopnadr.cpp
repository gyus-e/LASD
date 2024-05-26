
namespace lasd {

/* ************************************************************************** */
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr () : Table (INITIAL_SIZE), flag (INITIAL_SIZE)
{
    this->tableSize = this->Table.Size();
    InitFlag();

    acoeff2 = dista2(gen2);
    bcoeff2 = distb2(gen2);
}

// Specific constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long newSize) : 
    Table (std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE)), 
    flag (std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE)) 
{
    this->tableSize = this->Table.Size();
    InitFlag();

    acoeff2 = dista2(gen2);
    bcoeff2 = distb2(gen2);
}

// Constructor from TraversableContainer
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& container) : Table (INITIAL_SIZE), flag (INITIAL_SIZE)
{
    this->tableSize = this->Table.Size();
    InitFlag();
    
    acoeff2 = dista2(gen2);
    bcoeff2 = distb2(gen2);

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
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long newSize, const TraversableContainer<Data>& container) : 
    Table (std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE)), 
    flag (std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE)) 
{
    this->tableSize = this->Table.Size();
    InitFlag();
    
    acoeff2 = dista2(gen2);
    bcoeff2 = distb2(gen2);

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
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data> && container) : Table (INITIAL_SIZE), flag (INITIAL_SIZE)
{
    this->tableSize = this->Table.Size();
    InitFlag();
    
    acoeff2 = dista2(gen2);
    bcoeff2 = distb2(gen2);

    if (!container.Empty())
    {
        container.Map(
            [this](Data & elem) 
            {
                this->Insert(std::move(elem));
            }
        );
    }
}

// Constructor from MappableContainer with specified tableSize
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long newSize, MappableContainer<Data> && container) : 
    Table (std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE)), 
    flag (std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE)) 
{
    this->tableSize = this->Table.Size();
    InitFlag();
    
    acoeff2 = dista2(gen2);
    bcoeff2 = distb2(gen2);

    if (!container.Empty())
    {
        container.Map(
            [this](Data & elem) 
            {
                this->Insert(std::move(elem));
            }
        );
    }
}

// Copy constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data> & that) : HashTable<Data> (that), Table (that.Table), flag (that.flag)
{
    //non copio i coefficienti perché la nuova hashtable dovrá avenre di diversi
    // this->acoeff2 = that.acoeff2;
    // this->bcoeff2 = that.bcoeff2;
} 

// Move constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& that) noexcept : HashTable<Data> (std::move (that))
{
    std::swap ((this->Table), (that.Table));
    std::swap ((this->flag), (that.flag));

    std::swap (this->acoeff2, that.acoeff2);
    std::swap (this->bcoeff2, that.bcoeff2);
}

// Copy assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& that) 
{
    if (this != &that) 
    {
        this->HashTable<Data>::operator=(that);
        this->Table = that.Table;
        this->flag = that.flag;
        
        this->acoeff2 = that.acoeff2;
        this->bcoeff2 = that.bcoeff2;
    }
    return *this;
}

// Move assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& that) 
{
    if (this != &that) 
    {
        this->HashTable<Data>::operator=(std::move(that));        
        std::swap(this->Table, that.Table);
        std::swap(this->flag, that.flag);

        std::swap (this->acoeff2, that.acoeff2);
        std::swap (this->bcoeff2, that.bcoeff2);
    }
    return *this;
}

// Comparison operators
template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data> & that) const
{
    if (this->size != that.size || this->tableSize != that.tableSize) 
    {
        return false;
    }

    for (unsigned long i = 0; i < this->tableSize; i++) 
    {
        if (this->flag[i] == status::inserted) 
        {
            if (that.flag[i] != status::inserted || !(this->Table[i] == that.Table[i])) 
            {
                return false;
            }
        }
    }
    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr& that) const
{
    return !(this->operator==(that));
}

// Specific member functions (inherited from DictionaryContainer)

// Insert (copy)
template <typename Data>
bool HashTableOpnAdr<Data>::Insert (const Data & dat)
{
    if ((this->size + 1) >= (double)this->tableSize * LOAD_FACTOR_OPNADR) 
    {
        this->Resize(this->tableSize * 2);
    }

    bool replace = false;
    for (unsigned long i = 0; i < this->tableSize; i++)
    {
        unsigned long index = this->HashTableOpnAdr<Data>::HashKey(dat, i);

        if (this->flag[index] == status::inserted && this->Table[index] == dat) 
        {
            if (replace)
            {
                this->flag[index] = status::deleted;
                this->size--;
            }
            return false; // Giá presente, anche se è stato sostituito
        }

        else if (this->flag[index] == status::free)  
        {
            if (!replace)
            {
                this->Table[index] = dat;
                this->flag[index] = status::inserted;
                this->size++;
            }
            return true;
        }

        else if (this->flag[index] == status::deleted)
        {
            if (!replace)
            {
                this->Table[index] = dat;
                this->flag[index] = status::inserted;
                this->size++;

                //ma devo continuare col probing per vedere se era giá presente in sequenze successive
                replace = true;
            }
            else 
            {
                return true;
            }
        }
    }

    //error: table overflow
    throw (std::runtime_error ("Table overflow"));
}

// Insert (move)
template <typename Data>
bool HashTableOpnAdr<Data>::Insert (Data && dat)
{
    if ((this->size + 1) >= (double)this->tableSize * LOAD_FACTOR_OPNADR) 
    {
        this->Resize(this->tableSize * 2);
    }
    
    bool replace = false;
    for (unsigned long i = 0; i < this->tableSize; i++)
    {
        unsigned long index = this->HashTableOpnAdr<Data>::HashKey(dat, i);

        if (this->flag[index] == status::inserted && this->Table[index] == dat) 
        {
            if (replace)
            {
                this->flag[index] = status::deleted;
                this->size--;
            }
            return false; // Giá presente, anche se è stato sostituito
        }

        else if (this->flag[index] == status::free)  
        {
            if (!replace)
            {
                this->Table[index] = dat;
                this->flag[index] = status::inserted;
                this->size++;
            }
            return true;
        }

        else if (this->flag[index] == status::deleted)
        {
            if (! replace)
            {
                this->Table[index] = std::move(dat);
                this->flag[index] = status::inserted;
                this->size++;

                //ma devo continuare col probing per vedere se era giá presente in sequenze successive
                replace = true;
            }
            else 
            {
                return true;
            }
        }
    }
    //error: table overflow
    throw (std::runtime_error("Table overflow"));
}

//Remove
template <typename Data>
bool HashTableOpnAdr<Data>::Remove (const Data & dat)
{
    for (unsigned long i = 0; i < this->tableSize; i++)
    {
        unsigned long index = this->HashTableOpnAdr<Data>::HashKey(dat, i);

        if (this->flag[index] == status::inserted && this->Table[index] == dat) 
        {
            this->flag[index] = status::deleted;
            this->size--;
            this->GarbageCollect();
            return true;
        }

        else if (this->flag[index] == status::free)
        {
            return false;
        }

        // else if (this->flag[index] == status::deleted) 
        // {
        //         continue;
        // }
    }

    return false;
}

//Exists
template <typename Data>
bool HashTableOpnAdr<Data>::Exists (const Data & dat) const noexcept
{
    for (unsigned long i = 0; i < this->tableSize; i++)
    {
        unsigned long index = this->HashTableOpnAdr<Data>::HashKey(dat, i);

        if (this->flag[index] != status::inserted) //se siamo in una casella vuota o cancellata, vuol dire che il valore non è stato inserito
        {
            return false;
        }

        else if (this->Table[index] == dat) //&& this->flag[index] == status::inserted
        {
            return true;
        }
    } 
    return false;
} 

// Resize
template <typename Data>
void HashTableOpnAdr<Data>::Resize(unsigned long newSize) 
{    
    //Arrotonda newSize alla prossima potenza di 2
    unsigned long exp = ceil(log2(newSize));
    newSize = pow(2, exp);
    //Verifica che la dimensione minima sia rispettata
    newSize = std::max(newSize, INITIAL_SIZE);

    //Verifica che la resize vada effettuata davvero
    if (newSize == this->tableSize)
    {
        return;
    }

    //Evita che la resize venga fatta a una dimensione non valida (vogliamo che il numero di elementi sia sempre inferiore a tableSize * LOAD_FACTOR)
    if (this->size >= newSize * LOAD_FACTOR_OPNADR) 
    {
        //lanciare eccezione?
        return;
    }

    //serve una nuova HashTable perché vogliamo anche una nuova funzione HashKey
    HashTableOpnAdr<Data> newTable(newSize); 
    
    for (unsigned long i = 0; i < this->tableSize; i++)
    {
        if (this->flag[i] == status::inserted)
        {
            Data dat = this->Table[i];
            
            for (unsigned long k = 0; k < newTable.tableSize; k++)
            {
                unsigned long idx = newTable.HashKey(dat, k);
                if (newTable.flag[idx] != status::inserted)
                {
                    newTable.Table[idx] = dat;
                    newTable.flag[idx] = status::inserted;
                    break;
                }
            }
        }
    }
    std::swap (*this, newTable);
}

//Clear
template <typename Data>
void HashTableOpnAdr<Data>::Clear()
{
    this->Table.Clear();
    this->InitFlag();
    this->size = 0;
} 

/* ************************************************************************** */
// Private methods

template <typename Data>
unsigned long HashTableOpnAdr<Data>::HashKey(const Data & dat, const unsigned long i) const
{
        // return HashKey(dat) + (i*i); //probing quadratico, conviene se si usano numeri primi per tablesize
        
        return (this->HashTable<Data>::HashKey(dat) + i*(this->HashKey2(dat))) % this->tableSize; //doppio hashing
}

//Deve produrre sempre numeri dispari (coprimi con tableSize)
template <typename Data>
unsigned long HashTableOpnAdr<Data>::HashKey2(const Data & dat) const
{
    return (((acoeff2 * this->HashTable<Data>::enchash(dat) + bcoeff2) % prime2) * 2) + 1;
}

template <typename Data>
void HashTableOpnAdr<Data>::GarbageCollect ()
{
    if ((this->size) <= (double)this->tableSize * REDUCE_LOAD_FACTOR_OPNADR) 
    {
        this->Resize(this->tableSize / 2); //la resize va a inserire nella nuova tabella solo gli elementi con status inserted
    }
}

template <typename Data>
void HashTableOpnAdr<Data>::InitFlag ()
{
    this->flag.Map(
        [](status & s)
        {
            s = status::free;
        }
    );
}
/* ************************************************************************** */

}
