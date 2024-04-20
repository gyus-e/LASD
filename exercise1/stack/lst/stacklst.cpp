
namespace lasd {

/* ************************************************************************** */

// ...
template <typename Data>
const Data & StackLst<Data>::Top() const 
{
    if (this->Empty()) 
    {
        throw std::length_error("");
    } 
    return this->head;
}

template <typename Data>
Data & StackLst<Data>::Top() 
{
    if (this->Empty()) 
    {
        throw std::length_error("");
    } 
    return this->head;
}

template <typename Data>
void StackLst<Data>::Pop() 
{
    if (this->Empty() || this->head == nullptr) 
    {
        throw std::length_error("");
    }
    this->RemoveFromFront();
}

template <typename Data>
Data & StackLst<Data>::TopNPop() 
{
    Data ret = this->Front();
    try 
    {
        this->RemoveFromFront();

    } catch (std::length_error & exc) 
    {
        throw;
    } 
    return ret;
}

template <typename Data>
void StackLst<Data>::Push(const Data & dat)
{
    try
    {
        this->InsertAtFront(dat); 
    }
    catch(const std::bad_alloc& e)
    {
        throw;
    }
}

template <typename Data>
void StackLst<Data>::Push(Data && dat)
{
    try
    {
        this->InsertAtFront(std::move(dat)); 
    }
    catch(const std::bad_alloc& e)
    {
        throw;
    }
} 
/* ************************************************************************** */

}
