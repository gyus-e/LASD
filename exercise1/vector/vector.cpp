
namespace lasd {

/* ************************************************************************** */

// ...
template<typename Data>
Vector<Data>::Vector (unsigned long sz)
{
    this->Container::setSize (sz);
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

template<typename Data>
Vector<Data>::~Vector ()
{
    if (this->A != nullptr)
    {
        delete [] A;
        A = nullptr;
    }
}

template<typename Data>
inline Data & Vector<Data>::operator[](unsigned long idx)
{
    if (idx >= this->Container::Size ())
    {
        std::__throw_out_of_range ("");
    }
    return this->A[idx];
}

template<typename Data>
inline Data Vector<Data>::operator[](unsigned long idx) const 
{
    if (idx >= this->Container::Size ())
    {
        std::__throw_out_of_range ("");
    }
    return this->A[idx];
}

template<typename Data>
void Vector<Data>::Resize(unsigned long newSize)
{
    Data * NewA = new Data [newSize];
    
    unsigned long minSize = this->Size();
    // bool bigger = true;
    if (this->Size() > newSize) 
    {
        // bigger = false;
        minSize = newSize;
    }

    unsigned long i = 0;
    while (i < minSize)
    {
        NewA [i] = this->A[i];
        i++;
    }

    // if (bigger)
    // {
    //     while (i < newSize)
    //     {
    //         NewA [i] = 0;
    //     }
    // }

    delete [] this->A;
    this->A = NewA;
}

/* ************************************************************************** */

}
