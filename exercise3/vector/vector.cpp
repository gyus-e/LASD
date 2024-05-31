
namespace lasd {

/* ************************************************************************** */

//specific constructors
template<typename Data>
Vector<Data>::Vector (unsigned long sz) : Vector<Data> ()
{
    if (sz != 0)
    {
        try 
        {
            this->A = new Data [sz] {};
            this->size = sz;
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
Vector<Data>::Vector (const TraversableContainer<Data> & cont) : Vector<Data> (cont.Size())
{
    if (!cont.Empty())       
    {
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
Vector<Data>::Vector (MappableContainer<Data> && cont) : Vector<Data> (cont.Size())
{
    if (!cont.Empty())       
    {
        unsigned long i = 0;
        cont.Map (
            [this, &i] (Data & dat)
            {
                this->A[i] = std::move(dat);
                // std::swap (this->A[i], dat);
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
Vector<Data>::Vector (Vector<Data> && that) noexcept
{
    std::swap(this->A, that.A);
    std::swap(this->size, that.size);
    that.Clear();
}

//move operator
template<typename Data>
Vector<Data> & Vector<Data>::operator=(Vector && that)
{
    if (*this != that)
    {
        if (!this->Empty())
        {
            this->Clear();
        }
        std::swap (this->A, that.A);
        std::swap (this->size, that.size);
        that.Clear();
    }
    return *this;
}

//copy constructor
template<typename Data>
Vector<Data>::Vector (const Vector<Data> & that)
{
    if (!that.Empty())
    {
        try 
        {
            this->A = new Data [that.size];
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
        this->size = that.size;
        
        for (unsigned long i = 0; i < this->size; i++) 
        {
            this->A[i] = that.A[i];
        }
    }
}

//copy operator
template<typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> & that)
{
    if (*this != that)
    {
        if (!this->Empty())
        {
            this->Clear();
        }

        if (!that.Empty())
        {
            try 
            {
                this->A = new Data [that.size];
            }
            catch (std::bad_alloc & exc)
            {
                throw;
            }
            this->size = that.size;
            for (unsigned long i = 0; i < this->size; i++) 
            {
                this->A[i] = that.A[i];
            }        
        }
    }
    return *this;
}

//linear operator
template<typename Data>
inline Data & Vector<Data>::operator[](unsigned long idx)
{
    if (this->Empty() || idx >= this->size)
    {
        throw std::out_of_range ("from vector::operator []");
    }
    return this->A[idx];
}

//linear operator (non-mutable)
template<typename Data>
inline const Data & Vector<Data>::operator[](unsigned long idx) const 
{
    if (this->Empty() || idx >= this->size)
    {
        throw std::out_of_range ("from vector::operator []");
    }
    return (const Data &) this->A[idx];
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
    if (that.Empty() || this->Empty())
    {
        return this->Empty() && that.Empty();
    }

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
    return !this->operator==(that);
}

template<typename Data>
void Vector<Data>::Resize(unsigned long newSize)
{
    if (newSize == this->size)
    {
        return;
    }

    if (newSize == 0)
    {
        this->Clear();
        return;
    }

    Data * NewA = nullptr;

    try 
    {
        NewA = new Data [newSize] {};
    }
    catch (std::bad_alloc & exc)
    {
        throw;
    }

    unsigned long minSize = std::min (this->size, newSize);

    if (this->A != nullptr)
    {
        for (unsigned long i = 0; i < minSize; i++)
        {
            NewA [i] = this->A[i];
        }

        delete [] this->A;
        this->A = nullptr;
    }

    this->A = NewA;
    this->size = newSize;
}

template <typename Data>
void Vector<Data>::Clear()
{
    if (this->A != nullptr)
    {
        delete [] this->A;
        this->A = nullptr;
    }
    this->size = 0;
} 

/* ************************************************************************** */

/*
//move operator
template<typename Data>
SortableVector<Data> SortableVector<Data>::operator=(SortableVector && that)
{
    
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
*/
}
