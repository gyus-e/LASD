#include <iostream>

namespace lasd {

/* ************************************************************************** */
template <typename Data>
QueueVec<Data>::QueueVec() : Vector<Data> (INIT_SIZE), dim (0), head (0), tail (0) 
{
    this->size = INIT_SIZE;
}

// A queue obtained from a TraversableContainer
template <typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data> & cont) : 
    Vector<Data> (cont),
    dim(cont.Size()), 
    head (0), 
    tail (cont.Size()-1) 
{
    this->size = cont.Size();
    if (this->size < INIT_SIZE) 
    {
        this->Vector<Data>::Resize(INIT_SIZE);
        this->size = INIT_SIZE;
    }
}

// A queue obtained from a MappableContainer
template <typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data> && cont) : 
    Vector<Data> (std::move(cont)), 
    dim(cont.Size()),
    head (0), 
    tail (cont.Size()-1)
{
    this->size = cont.Size();
    if (this->size < INIT_SIZE) 
    {
        this->Vector<Data>::Resize(INIT_SIZE);
        this->size = INIT_SIZE;
    }
}

// Copy constructor
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec & that) : 
    Vector<Data> (that), 
    dim(that.dim), 
    head (that.head), 
    tail (that.tail) 
{
    this->size = that.size;
}

// Move constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec && that) noexcept : 
    Vector<Data> (std::move(that)), dim (0), head (0), tail (0)
{
    this->size = 0;
    std::swap (this->size, that.size);
    std::swap (this->dim, that.dim); 
    std::swap (this->head, that.head); 
    std::swap (this->tail, that.tail);
}


// Copy assignment
template <typename Data>
QueueVec<Data> & QueueVec<Data>::operator=(const QueueVec & that) 
{
    if (*this != that)
    {
        if (!this->Empty())
        {
            this->Clear();
        }

        this->Vector<Data>::operator= (that); 
        this->size = that.size;
        this->dim = that.dim; 
        this->head = that.head; 
        this->tail = that.tail; 
    }
    return *this;
}

// Move assignment
template <typename Data>
QueueVec<Data> & QueueVec<Data>::operator=(QueueVec && that) 
{
    if (*this != that)
    {
        this->Vector<Data>::operator=(std::move(that));
        std::swap (this->size, that.size);
        std::swap (this->dim, that.dim); 
        std::swap (this->head, that.head); 
        std::swap (this->tail, that.tail);
    }
    return *this;
}

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec & that) const
{
    if (this->dim != that.dim)// || this->head != that.head || this->tail != that.tail)
    {
        return false;
    }

    for (unsigned long i = 0; i < this->dim; i++)
    {
        if (this->operator[]((this->head + i) % this->size) != that[(that.head + i) % that.size])
        {
            // std::cout<<this->operator[]((this->head + i) % this->size)<<" != "<<that[(that.head + i) % that.size]<<std::endl;
            return false;
        }
    }
    return true;
}

template <typename Data>
bool QueueVec<Data>::operator!=(const QueueVec & that) const
{
    return !this->operator==(that);
}

template <typename Data>
inline const Data & QueueVec<Data>::Head() const 
{
    if (this->Empty ())
    {
        throw std::length_error ("no head");
    }
    return this->A[head];
}   

template <typename Data>
inline Data & QueueVec<Data>::Head() 
{
    if (this->Empty ())
    {
        throw std::length_error ("no head");
    }
    return this->A[head];
}   

template <typename Data>
inline void QueueVec<Data>::Dequeue() 
{
    if (this->Empty ())
    {
        throw std::length_error ("from dequeue");
    }
    
    this->head = (this->head + 1) % this->size; //successivo lungo coda circolare (se head era l'ultimo, ritorna al primo)
    this->dim--;

    // if ((this->dim < (this->size * REDUCE_THRESHOLD)))// && (this->size * REDUCE_THRESHOLD > INIT_SIZE))
    // {
    //     this->Resize(this->size * REDUCE_FACTOR);
    // }
}   

template <typename Data>
inline Data QueueVec<Data>::HeadNDequeue() 
{
    if (this->Empty ())
    {
        throw std::length_error ("from dequeue");
    }
    Data ret = this->Head();
    this->Dequeue();
    return ret;
}   

template <typename Data>
inline void QueueVec<Data>::Enqueue(const Data & dat) 
{
    if (this->dim >= this->size)
    {
        unsigned long newSize = this->size * INCREASE_FACTOR;
        this->Vector<Data>::Resize(newSize);
        this->size = newSize;
    }

    this->A[tail] = dat;
    this->tail = (this->tail + 1) % size;
    this->dim++;
}  

template <typename Data>
inline void QueueVec<Data>::Enqueue(Data && dat) 
{
    if (this->dim >= this->size)
    {
        unsigned long newSize = this->size * INCREASE_FACTOR;
        this->Vector<Data>::Resize(newSize);
        this->size = newSize;
    }

    this->A[tail] = std::move(dat);
    this->tail = (this->tail + 1) % size;
    this->dim++;
}  

template <typename Data>
inline void QueueVec<Data>::Clear()
{
    // this->Vector<Data>::Clear();
    this->Vector<Data>::Resize(INIT_SIZE);
    this->size = INIT_SIZE;
    this->dim = 0; 
    this->head = 0; 
    this->tail = 0;
}
/* ************************************************************************** */
}
