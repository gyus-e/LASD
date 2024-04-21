
namespace lasd {

/* ************************************************************************** */

// ...
template <typename Data>
const Data & StackVec<Data>::Top() const
{
    if (this->Empty()) 
    {
        throw std::length_error("");
    }
    unsigned long idx = this->top - 1;
    return this->A[idx];
}

template <typename Data>
Data & StackVec<Data>::Top() 
{
    if (this->Empty()) 
    {
        throw std::length_error("");
    } 
    unsigned long idx = this->top - 1;
    return this->A[idx];
}


template <typename Data>
void StackVec<Data>::Pop() 
{
    if (this->Empty()) 
    {
        throw std::length_error("");
    }
    
    this->top--;
    if (this->top < (this->size / REDUCE_THRESHOLD))
    {
        unsigned long newSize = (this->size / REDUCE_FACTOR);
        this->Resize(newSize);
    }
}

template <typename Data>
Data StackVec<Data>::TopNPop() 
{
    Data ret;
    try
    {
        ret = this->Top();
        this->Pop();
    }
    catch (std::length_error & exc)
    {
        throw;
    }
    return ret;
}

template <typename Data> 
void StackVec<Data>::Push(const Data & dat) {
    if (this->top == this->size)
    {
        unsigned long newSize = this->size * INCREASE_FACTOR;
        this->Resize(newSize);
    }
    this->A[top] = dat;
    top++;
}

template <typename Data> 
void StackVec<Data>::Push(Data && dat) {
    if (this->top == this->size)
    {
        unsigned long newSize = this->size * INCREASE_FACTOR;
        this->Resize(newSize);
    }
    this->A[top] = std::move(dat);
    top++;
}

/* ************************************************************************** */

}
