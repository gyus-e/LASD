
namespace lasd {

/* ************************************************************************** */
// Default constructor
template <typename Data>
StackVec<Data>::StackVec() : Vector<Data> (INIT_SIZE), top (0) 
{
    this->size = INIT_SIZE;
}

// Specific constructor

// A stack obtained from a TraversableContainer
template <typename Data>
StackVec<Data>::StackVec(const TraversableContainer<Data> & cont) : Vector<Data> (cont), top(cont.Size())
{
    this->size = cont.Size();
    if (this->size < INIT_SIZE) 
    {
        this->Resize(INIT_SIZE);
        this->size = INIT_SIZE;
    }
} 

// A stack obtained from a MappableContainer
template <typename Data>
StackVec<Data>::StackVec(MappableContainer<Data> && cont) : Vector<Data> (std::move(cont)), top(cont.Size()) 
{
    this->size = cont.Size();
    if (this->size < INIT_SIZE) 
    {
        this->Resize(INIT_SIZE);
        this->size = INIT_SIZE;
    }
} 

// Copy constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data> & that) : Vector<Data> ((Vector<Data>) that), top (that.top) 
{
    this->size = that.size;
}

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data> && that) noexcept : Vector<Data> (std::move((Vector<Data>) that)), top (std::move(that.top))
{
    that.top = 0;
}

// Copy assignment
template <typename Data>
StackVec<Data> & StackVec<Data>::operator=(const StackVec<Data> & that)
{
    if (this != &that)
    {
        this->Vector<Data>::operator=((Vector<Data>)(that)); 
        this->top = that.top; 
        this->size = that.size;
    }
    return *this;
}

// Move assignment
template <typename Data>
StackVec<Data> & StackVec<Data>::operator=(StackVec<Data> && that) 
{
    if (this != &that)
    {
        this->Vector<Data>::operator= (std::move((Vector<Data>)(that))); 
        std::swap(this->top, that.top); 
        that.top = 0;
    }
    return *this;
}


template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data> & that) const
{
    if (this->top != that.top) 
    {
      return false;
    }

    //non riutilizzo l'operatore di uguaglianza di Vec perché interessano solo i valori inseriti nello stack
    for (unsigned long i = 0; i < this->top; i++)
    {
      if (this->operator[](i) != that[i]) 
      {
        return false;
      }
    }

    return true;
}

template <typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data> & that) const
{
    return !this->operator==(that);
}

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
    if (this->top < (this->size * REDUCE_THRESHOLD) && (this->size * REDUCE_THRESHOLD > INIT_SIZE))
    {
        this->Resize(this->size * REDUCE_FACTOR);
        this->size = this->Vector<Data>::Size();
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
void StackVec<Data>::Push(const Data & dat) 
{
    if (this->top == this->size)
    {
        this->Resize(this->size * INCREASE_FACTOR);
        this->size = this->Vector<Data>::Size();
    }
    this->A[top] = dat;
    this->top++;
}

template <typename Data> 
void StackVec<Data>::Push(Data && dat) 
{
    if (this->top == this->size)
    {
        this->Resize(this->size * INCREASE_FACTOR);
        this->size = this->Vector<Data>::Size();
    }
    this->A[top] = std::move(dat);
    this->top++;
}

template <typename Data> 
inline void StackVec<Data>::Clear() 
{
    this->Vector<Data>::Clear(); 
    this->Vector<Data>::Resize(INIT_SIZE);
    this->top = 0;
}

/* ************************************************************************** */

}
