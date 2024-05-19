
namespace lasd {

/* ************************************************************************** */

// ...
template <typename Data>
inline const Data & QueueLst<Data>::Head() const 
{
    if (this->Empty ())
    {
        throw std::length_error ("no head");
    }
    return this->Front();
}   

template <typename Data>
inline Data & QueueLst<Data>::Head() 
{
    if (this->Empty ())
    {
        throw std::length_error ("no head");
    }
    return this->Front();
}   

template <typename Data>
inline void QueueLst<Data>::Dequeue() 
{
    if (this->Empty ())
    {
        throw std::length_error ("from dequeue");
    }
    this->RemoveFromFront();
}   

template <typename Data>
inline Data QueueLst<Data>::HeadNDequeue() 
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
inline void QueueLst<Data>::Enqueue(const Data & dat) 
{
    this->InsertAtBack(dat);
}  

template <typename Data>
inline void QueueLst<Data>::Enqueue(Data && dat) 
{
    this->InsertAtBack(std::move(dat));
}  
/* ************************************************************************** */

}
