#include <stdexcept>

namespace lasd {

/* ************************************************************************** */
    /* LinearContainer  */
template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data> & that) const noexcept
{
    if (this->Size() != that.Size())
    {
        return false;
    }
    for (unsigned long i = 0; i < this->Size(); i++)
    {
        if  ((*this) [i] != that [i])
        {
            return false;
        }
    }
    return true;
}

template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer<Data> & that) const noexcept
{
    if (this->Size() != that.Size())
    {
        return true;
    }
    for (unsigned long i = 0; i < this->Size(); i++)
    {
        if  ((*this) [i] != that [i])
        {
            return true;
        }
    }
    return false;
}

template <typename Data>
inline const Data & LinearContainer<Data>::Front() const 
{
    if (this->Empty()) 
    {
        throw std::length_error (EMPTY_CONTAINER_MSG);
            //Errore del compilatore: 
            //‘length_error’ is not a member of ‘std’
        // std::__throw_length_error (EMPTY_CONTAINER_MSG);
    } 
    else
    {
        return (*this) [0];
    }
}

template <typename Data>
inline Data & LinearContainer<Data>::Front() 
{
    if (this->Empty()) 
    {
        throw std::length_error (EMPTY_CONTAINER_MSG);
    } 
    else
    {
        return (*this) [0];
    }
}

template <typename Data>
inline const Data & LinearContainer<Data>::Back() const 
{
    if (this->Empty()) 
    {
        throw std::length_error (EMPTY_CONTAINER_MSG);
    } 
    else 
    {
        return (*this) [this->Size()-1];
    }
}

template <typename Data>
inline Data & LinearContainer<Data>::Back() 
{
    if (this->Empty()) 
    {
        throw std::length_error (EMPTY_CONTAINER_MSG);
    } 
    else 
    {
        return (*this) [this->Size()-1];
    }
}

template <typename Data>
inline void LinearContainer<Data>::Traverse(TraverseFun traverseFun) const
{
    this->PreOrderTraverse(traverseFun);
}

template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun traverseFun) const
{
    for (unsigned long i = 0; i < this->Size(); i++)
    {
        traverseFun (this->operator[](i));
    }
}

template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun traverseFun) const
{
    for (unsigned long i = (this->Size() - 1); i >= 0; i--)
    {
        if ((long) i < 0)
        {
            return;
        }
        traverseFun (this->operator[](i));
    }
}

template <typename Data>
inline void LinearContainer<Data>::Map(MapFun mapFun) 
{
    this->PreOrderMap(mapFun);
}

template <typename Data>
void LinearContainer<Data>::PreOrderMap(MapFun mapFun) 
{
    for (unsigned long i = 0; i < this->Size(); i++)
    {
        mapFun ((*this)[i]);
    }
}

template <typename Data>
void LinearContainer<Data>::PostOrderMap(MapFun mapFun) 
{
    for (unsigned long i = this->Size() - 1; i >= 0; i--)
    {
        if ((long) i < 0)
        {
            return;
        }
        mapFun ((*this)[i]);
    }
}


template <typename Data>
void LinearContainer<Data>::swap(const unsigned long a, const unsigned long b)
{
    const unsigned long SZ = this->Size();
    if (a < SZ && b < SZ)
    {
        Data temp = (*this) [a];
        (*this)[a] = (*this) [b];
        (*this)[b] = temp;
    }
    else
    {
        throw std::length_error ("cannot swap");
    }
}

/* ************************************************************************** */
    /*  SortableLinearContainer */
template <typename Data>
bool SortableLinearContainer<Data>::operator==(const SortableLinearContainer<Data> & that) const noexcept
{
    if (this->Size() != that.Size())
    {
        return false;
    }
    for (unsigned long i = 0; i < this->Size(); i++)
    {
        if  ((*this) [i] != that [i])
        {
            return false;
        }
    }
    return true;
}

template <typename Data>
bool SortableLinearContainer<Data>::operator!=(const SortableLinearContainer<Data> & that) const noexcept
{
    if (this->Size() != that.Size())
    {
        return true;
    }
    for (unsigned long i = 0; i < this->Size(); i++)
    {
        if  ((*this) [i] != that [i])
        {
            return true;
        }
    }
    return false;
}

template <typename Data>
void SortableLinearContainer<Data>::Sort ()
{
    if (! this->Empty())
    {    
        this->heapSort ();
    }
}

template <typename Data>
void SortableLinearContainer<Data>::heapSort()
{
    const unsigned long SZ = this->Size();
    unsigned long heapsize = SZ;
    buildHeap(SZ);
    for (unsigned long i = SZ-1; i > 0; i--)
    {
        this->swap(i, 0);
        heapsize--;
        this->heapify(0, heapsize);
    }
}

template <typename Data>
void SortableLinearContainer<Data>::buildHeap(const unsigned long heapsize)
{
    for (unsigned long i = parent(heapsize); i >= 0; i--) 
    //per qualche motivo, i viene decrementato ulteriormente una volta raggiunto 0
    {
        if ((long) i < 0)
        {
            return;
        }
        this->heapify(i, heapsize);
    }
}

template <typename Data>
void SortableLinearContainer<Data>::heapify(const unsigned long i, const unsigned long heapsize)
{
    const unsigned long Sx = (2 * i) + 1;
    const unsigned long Dx = (2 * i) + 2;
    unsigned long max = i;

    if (Sx < heapsize && (*this)[Sx] > (*this)[max])
    {
        max = Sx;
    }
    if (Dx < heapsize && (*this)[Dx] > (*this)[max])
    {
        max = Dx;
    }
    if (max != i)
    {
        this->swap(i, max);
        this->heapify(max, heapsize);
    }
}

}
