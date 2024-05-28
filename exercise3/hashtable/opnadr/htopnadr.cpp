
namespace lasd {

/* ************************************************************************** */
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr () : Table (INITIAL_SIZE), flag (INITIAL_SIZE)
{
    this->tableSize = this->Table.Size();
    InitFlag();
}

// Specific constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long newSize) : 
    Table (std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE)), 
    flag (std::max ((unsigned long) pow(2, ceil(log2(newSize))), INITIAL_SIZE)) 
{
    this->tableSize = this->Table.Size();
    InitFlag();
}

// Constructor from TraversableContainer
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& container) : Table (INITIAL_SIZE), flag (INITIAL_SIZE)
{
    this->tableSize = this->Table.Size();
    InitFlag();

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
} 

// Move constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& that) noexcept : HashTable<Data> (std::move (that))
{
    std::swap ((this->Table), (that.Table));
    std::swap ((this->flag), (that.flag));
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
    if (this->Exists(dat))
    {
        return false;
    }

    if ((this->size + 1) >= (double)this->tableSize * LOAD_FACTOR_OPNADR) 
    {
        this->Resize(this->tableSize * 2);
        // std::cout<<"Resized to "<<this->tableSize<<std::endl;
    }

    unsigned long i = 0;
    do
    {
        unsigned long idx = this->HashKey(dat, i);
        if (this->flag[idx] != status::inserted)
        {
            this->Table[idx] = dat;
            this->flag[idx] = status::inserted;
            this->size++;
            return true;
        }
        else 
        {
            i++;
        }
    } while (i < this->tableSize);

    return false;
}

// Insert (move)
template <typename Data>
bool HashTableOpnAdr<Data>::Insert (Data && dat)
{
    if (this->Exists(dat))
    {
        return false;
    }

    if ((this->size + 1) >= (double)this->tableSize * LOAD_FACTOR_OPNADR) 
    {
        this->Resize(this->tableSize * 2);
        // std::cout<<"Resized to "<<this->tableSize<<std::endl;
    }

    unsigned long i = 0;
    do
    {
        unsigned long idx = this->HashKey(dat, i);
        if (this->flag[idx] != status::inserted)
        {
            this->Table[idx] = std::move(dat);
            this->flag[idx] = status::inserted;
            this->size++;
            return true;
        }
        else 
        {
            i++;
        }
    } while (i < this->tableSize);

    return false;
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

        // else if (this->flag[index] == status::free)
        // {
        //     return false;
        // }

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

        if (this->flag[index] == status::inserted && this->Table[index] == dat)
        {
            return true;
        }
        
        // else if (this->flag[index] == status::free) //se siamo in una casella vuota, vuol dire che il valore non è stato inserito
        // {
        //     return false;
        // }
    } 
    return false;
} 

// Resize
template <typename Data>
void HashTableOpnAdr<Data>::Resize(unsigned long newSize) 
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
    //(NB: ma potrei voler usare resize solo per fare rehashing)
    if (newSize == this->tableSize)
    {
        return;
    }

    //Evita che la resize venga fatta a una dimensione non valida (vogliamo che il numero di elementi sia sempre inferiore a tableSize * LOAD_FACTOR)
    if (this->size >= newSize * LOAD_FACTOR_OPNADR) 
    {
        //Non bisogna lanciare eccezione
        return;
    }

    //serve una nuova HashTable perché vogliamo anche una nuova funzione HashKey
    HashTableOpnAdr<Data> newTable(newSize); 
    for (unsigned long j = 0; j < this->tableSize; j++)
    {
        if (this->flag[j] == status::inserted)
        {
            Data dat = this->Table[j];
            
            for (unsigned long i = 0; i < newTable.tableSize; i++)
            {
                unsigned long idx = newTable.HashKey(dat, i);
                if (newTable.flag[idx] == status::free)
                {
                    newTable.Table[idx] = dat;
                    newTable.flag[idx] = status::inserted;
                    newTable.size++;
                    break;
                }
                else if (newTable.flag[idx] == status::inserted && dat == newTable.Table[idx])
                {
                    //ho fatto il giro?
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
    //modo semplice: allocare una nuova hashtable a initial size e fare lo swap
    HashTableOpnAdr<Data> clearTable (INITIAL_SIZE);
    std::swap (*this, clearTable);

    //modo vecchio:

    // this->Table.Clear();
    // this->Table.Resize(INITIAL_SIZE);
    // this->tableSize = this->Table.Size();

    // this->flag.Resize(INITIAL_SIZE);
    // this->InitFlag();

    // this->size = 0;
} 

/* ************************************************************************** */
// Private methods

template <typename Data>
unsigned long HashTableOpnAdr<Data>::HashKey(const Data & dat, const unsigned long i) const
{
    return (this->HashKey(dat) + ((i * this->coprimeFun(dat)) % this->tableSize)) % this->tableSize;
}

//Deve produrre sempre numeri dispari (coprimi con tableSize, che è una potenza di 2)
template <typename Data>
unsigned long HashTableOpnAdr<Data>::coprimeFun (const Data & dat) const 
{
    return ((this->enchash(dat) % this->prime) * 2 + 1) % this->tableSize;
}

template <typename Data>
inline void HashTableOpnAdr<Data>::GarbageCollect ()
{
    if ((this->size) < (double)this->tableSize * REDUCE_LOAD_FACTOR_OPNADR) 
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
