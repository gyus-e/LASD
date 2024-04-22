
namespace lasd {

/* ************************************************************************** */
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

    if (this->dim == this->size / REDUCE_THRESHOLD)
    {
        unsigned long newSize = this->size / REDUCE_FACTOR;
        this->Resize(newSize);
    }
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
    if (this->dim == this->size)
    {
        unsigned long newSize = size * INCREASE_FACTOR;
        this->Resize(newSize);
    }

    this->A[tail] = dat;
    this->tail = (this->tail + 1) % size;
    dim++;
}  

template <typename Data>
inline void QueueVec<Data>::Enqueue(Data && dat) 
{
    if (this->dim == this->size)
    {
        unsigned long newSize = size * INCREASE_FACTOR;
        this->Resize(newSize);
    }

    this->A[tail] = std::move(dat);
    this->tail = (this->tail + 1) % size;
    dim++;
}  

/* ************************************************************************** */

}
