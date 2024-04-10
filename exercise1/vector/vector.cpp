
namespace lasd {

/* ************************************************************************** */

//specific constructor
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

//destructor
template<typename Data>
Vector<Data>::~Vector ()
{
    if (this->A != nullptr)
    {
        delete [] A;
        A = nullptr;
    }
}

//move constructor
template<typename Data>
Vector<Data>::Vector (Vector && that) noexcept
{
    this->A = std::move (that.A);
    this->setSize(that.Size());
    that.A = nullptr;
    that.setSize(0);
}

//move operator
template<typename Data>
Vector<Data> Vector<Data>::operator=(Vector && that)
{
    this->A = std::move(that.A);
    this->setSize(that.Size());
    that.A = nullptr;
    that.setSize(0);
}

//copy constructor
template<typename Data>
Vector<Data>::Vector (const Vector & vec)
{
    this->setSize(vec.Size());
    A = new Data [this->Size()];

    for (unsigned long i = 0; i < vec.Size(); i++)
    {
        this->A[i] = vec.A[i];
    }
}

//copy operator
template<typename Data>
Vector<Data> Vector<Data>::operator=(const Vector & vec)
{
    if (this->Size() != vec.Size())
    {
        this->Resize(vec.Size());
    }

    for (unsigned long i = 0; i < vec.Size(); i++)
    {
        this->A[i] = vec.A[i];
    }
}

//linear operator
template<typename Data>
inline Data & Vector<Data>::operator[](unsigned long idx)
{
    if (idx >= this->Container::Size ())
    {
        throw std::out_of_range ("");
    }
    return this->A[idx];
}

//linear operator (non-mutable)
template<typename Data>
inline const Data & Vector<Data>::operator[](unsigned long idx) const 
{
    if (idx >= this->Container::Size ())
    {
        throw std::out_of_range ("");
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

template<typename Data>
void Vector<Data>::Resize(unsigned long newSize)
{
    Data * NewA = nullptr;
    try 
    {
        NewA = new Data [newSize];
    }
    catch (std::bad_alloc &exc)
    {
        throw;
    }
    
    unsigned long minSize = this->Size();
    // bool bigger = true;
    if (this->Size() > newSize) 
    {
        // bigger = false;
        minSize = newSize;
    }

    //se minSize = 0, non copia niente
    unsigned long i = 0;
    while (i < minSize)
    {
        NewA [i] = this->A[i];
        i++;
    }

    //se il nuovo Array è piú grande, inizializza i valori rimanenti
    // if (bigger)
    // {
    //     while (i < newSize)
    //     {
    //         NewA [i] = 0;
    //     }
    // }


    if (A != nullptr)
    {
        delete [] this->A;
        this->A = nullptr;
    }

    this->A = NewA;
    this->setSize(newSize);
}

/* ************************************************************************** */

}
