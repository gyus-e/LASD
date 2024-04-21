
namespace lasd {

/* ************************************************************************** */

//specific constructors
template<typename Data>
Vector<Data>::Vector (unsigned long sz)
{
    this->setSize (sz);
    if (sz != 0)
    {
        try 
        {
            this->A = new Data [sz];
        }
        catch (std::bad_alloc & exc)
        {
            // std::cerr<<exc.what();
            throw;
        }
    }
}

// A vector obtained from a TraversableContainer
template<typename Data>
Vector<Data>::Vector (const TraversableContainer<Data> & cont)
{
    unsigned long sz = cont.Size();
    this->setSize (sz);
    if (sz != 0)
    {
        try 
        {
            this->A = new Data [sz];
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }

        unsigned long i = 0;
        cont.Traverse (
            [this, &i] (const Data & dat)
            {
                this->A[i] = dat;
                i++;
            }
        );
    }
}


// A vector obtained from a MappableContainer
template<typename Data>
Vector<Data>::Vector (MappableContainer<Data> && cont)
{
    unsigned long sz = cont.Size();
    this->setSize (sz);
    if (sz != 0)
    {
        try 
        {
            this->A = new Data [sz];
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }

        unsigned long i = 0;
        cont.Map (
            [this, &i] (Data & dat)
            {
                this->A[i] = std::move(dat);
                i++;
            }
        );
    }
}

//destructor
template<typename Data>
Vector<Data>::~Vector ()
{
    if (this->A != nullptr)
    {
        delete [] this->A;
        this->A = nullptr;
    }
}

//move constructor
template<typename Data>
Vector<Data>::Vector (Vector && that) noexcept
{
    this->A = that.A;
    this->size = std::move(that.size);
    that.A = nullptr;
    that.setSize(0);
}

//move operator
template<typename Data>
Vector<Data> Vector<Data>::operator=(Vector && that)
{
    this->A = that.A;
    this->size = std::move(that.size);
    that.A = nullptr;
    that.setSize(0);
    return *this;
}

//copy constructor
template<typename Data>
Vector<Data>::Vector (const Vector & that)
{
    this->setSize(that.Size());
    this->A = new Data [this->Size()];

    for (unsigned long i = 0; i < that.Size(); i++)
    {
        this->A[i] = that.A[i];
    }
}

//copy operator
template<typename Data>
Vector<Data> Vector<Data>::operator=(const Vector & that)
{
    if (this->Size() != that.Size())
    {
        this->Resize(that.Size());
    }

    for (unsigned long i = 0; i < that.Size(); i++)
    {
        this->A[i] = that.A[i];
    }
}

//linear operator
template<typename Data>
inline Data & Vector<Data>::operator[](unsigned long idx)
{
    if (idx >= this->Container::Size ())
    {
        throw std::out_of_range ("from vector::operator []");
    }
    return this->A[idx];
}

//linear operator (non-mutable)
template<typename Data>
inline const Data & Vector<Data>::operator[](unsigned long idx) const 
{
    if (idx >= this->Container::Size ())
    {
        throw std::out_of_range ("from vector::operator []");
    }
    return this->A[idx];
}

template <typename Data>
inline const Data & Vector<Data>::Front() const 
{
    if (this->Empty()) 
    {
        throw std::length_error (EMPTY_CONTAINER_MSG);
    } 
    else
    {
        return this->A[0];
    }
}

template <typename Data>
inline Data & Vector<Data>::Front() 
{
    if (this->Empty()) 
    {
        throw std::length_error (EMPTY_CONTAINER_MSG);
    } 
    else
    {
        return this->A[0];
    }
}

template <typename Data>
inline const Data & Vector<Data>::Back() const 
{
    if (this->Empty()) 
    {
        throw std::length_error (EMPTY_CONTAINER_MSG);
    } 
    else 
    {
        return this->A[this->Size()-1];
    }
}

template <typename Data>
inline Data & Vector<Data>::Back() 
{
    if (this->Empty()) 
    {
        throw std::length_error (EMPTY_CONTAINER_MSG);
    } 
    else 
    {
        return this->A[this->Size()-1];;
    }
}

template <typename Data>
bool Vector<Data>::operator==(const Vector<Data> & that) const noexcept
{
    if (this->Size() != that.Size())
    {
        return false;
    }
    for (unsigned long i = 0; i < this->Size(); i++)
    {
        if  (this->A[i] != that.A[i])
        {
            return false;
        }
    }
    return true;
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector<Data> & that) const noexcept
{
    if (this->Size() != that.Size())
    {
        return true;
    }
    for (unsigned long i = 0; i < this->Size(); i++)
    {
        if  (this->A[i] != that.A[i])
        {
            return true;
        }
    }
    return false;
}

template<typename Data>
void Vector<Data>::Resize(unsigned long newSize)
{
    Data * NewA = nullptr;

    if (newSize > 0)
    {
        try 
        {
            NewA = new Data [newSize];
        }
        catch (std::bad_alloc &exc)
        {
            throw;
        }
    }
    
    unsigned long minSize = this->Size();
    // bool bigger = true;
    if (this->Size() > newSize) 
    {
        // bigger = false;
        minSize = newSize;
    }

    

    //se il nuovo Array è piú grande, inizializza i valori rimanenti
    // if (bigger)
    // {
    //     while (i < newSize)
    //     {
    //         NewA [i] = 0;
    //     }
    // }


    if (this->A != nullptr)
    {
        //se minSize = 0, non copia niente
        unsigned long i = 0;
        while (i < minSize)
        {
            NewA [i] = this->A[i];
            i++;
        }
        delete [] this->A;
        this->A = nullptr;
    }

    this->A = NewA;
    this->setSize(newSize);
}

template <typename Data>
void Vector<Data>::Clear()
{
    if (this->A != nullptr)
    {
        delete [] this->A;
        this->A = nullptr;
    }
    this->setSize(0);
} 

/* ************************************************************************** */


//move operator
template<typename Data>
SortableVector<Data> SortableVector<Data>::operator=(SortableVector && that)
{
    this->A = that.A;
    this->size = std::move(that.size);
    that.A = nullptr;
    that.setSize(0);
    return *this;
}

//copy operator
template<typename Data>
SortableVector<Data> SortableVector<Data>::operator=(const SortableVector & that)
{
    if (this->Size() != that.Size())
    {
        this->Resize(that.Size());
    }

    for (unsigned long i = 0; i < that.Size(); i++)
    {
        this->A[i] = that.A[i];
    }
}

}
