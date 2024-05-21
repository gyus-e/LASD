
namespace lasd {

/* ************************************************************************** */
/*          Node           */
//copy constructor
template <typename Data>
List<Data>::Node::Node(const Node & that)
{
    this->elem = that.elem;
    if (that.next != nullptr)
    {
        try
        {    
            this->next = new Node (*that.next);
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
    }
}

//move constructor
template <typename Data>
List<Data>::Node::Node(Node && that) noexcept
{
    std::swap (this->elem, that.elem);
    std::swap (this->next, that.next);
}

//destructor
template <typename Data>
List<Data>::Node::~Node()
{
    if (this->next != nullptr)
    {
        delete this->next;
    }
}

//Comparison operators
template <typename Data>
bool List<Data>::Node::operator==(const Node & that) const
{
    if (this->elem != that.elem)
    {
        return false;
    }
    else if (this->next == nullptr && that.next == nullptr)
    {
        return true;
    }
    else if (this->next == nullptr || that.next == nullptr)
    {
        return false;
    }
    else 
    {
        return *(this->next) == *(that.next);
    }
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node & that) const
{
    return !(this->operator==(that));
}

template <typename Data>
void List<Data>::Node::PreOrderTraverse (TraverseFun func) const
{
    func (this->elem);

    if (this->next != nullptr)
    {
    this->next->PreOrderTraverse (func);
    }
}

template <typename Data>
void List<Data>::Node::PostOrderTraverse (TraverseFun func) const
{
    if (this->next != nullptr)
    {
    this->next->PostOrderTraverse(func);
    }

    func (this->elem);
}

template <typename Data>
void List<Data>::Node::PreOrderMap (MapFun func)
{
    func (this->elem);

    if (this->next != nullptr)
    {
    this->next->PreOrderMap (func);
    }
}

template <typename Data>
void List<Data>::Node::PostOrderMap (MapFun func)
{
    if (this->next != nullptr)
    {
    this->next->PostOrderMap (func);
    }

    func (this->elem);
}

/* ************************************************************************** */
/*          List           */

// A list obtained from a TraversableContainer
template <typename Data>
List<Data>::List (const TraversableContainer<Data> & cont)
{
    if (!cont.Empty())
    {
        cont.Traverse(
            [this] (const Data & dat)
            {
                this->InsertAtBack(dat);
            }
        );
    }
}

// A list obtained from a MappableContainer
template <typename Data>
List<Data>::List (MappableContainer<Data> && cont)
{
    if (!cont.Empty())
    {
        cont.Traverse(
            [this] (const Data & dat)
            {
                this->InsertAtBack(std::move(dat));
            }
        );
    }
}

// Copy constructor
template <typename Data>
List<Data>::List (const List<Data> & that)
{
    try 
    {
        this->head = new Node (*that.head);
    }
    catch (std::bad_alloc & exc)
    {
        throw;
    }

    this->tail = this->head;
    while (this->tail->next != nullptr)
    {
        this->tail = this->tail->next;
    }

    this->size = that.size;
}

// Move constructor
template <typename Data>
List<Data>::List (List<Data> && that) noexcept
{
    std::swap (this->head, that.head);
    std::swap (this->tail, that.tail);
    std::swap (this->size, that.size);
}

// Destructor
template <typename Data>
List<Data>::~List()
{
    if (this->head != nullptr)
    {
        delete this->head;
    }
}

// Copy assignment
template <typename Data>
List<Data> List<Data>::operator= (const List<Data> & that)
{
    if (this->head != nullptr)
    {
        this->Clear();
    }

    try 
    {
        this->head = new Node (*that.head);
    }
    catch (std::bad_alloc & exc)
    {
        throw;
    }

    this->tail = this->head;
    while (this->tail->next != nullptr)
    {
        this->tail = this->tail->next;
    }

    this->size = that.size;

    return *this;
}

// Move assignment
template <typename Data>
List<Data> List<Data>::operator= (List<Data> && that)
{
    std::swap (this->head, that.head);
    std::swap (this->tail, that.tail);
    std::swap (this->size, that.size);

    return *this;
}

// Comparison operators
template <typename Data>
bool List<Data>::operator== (const List<Data> & that) const
{
    return this->size == that.size && this->head->operator==(*(that.head));
}

template <typename Data>
bool List<Data>::operator!= (const List<Data> & that) const
{
    return !this->operator==(that);
}

// Specific member functions

// Copy of the value
template <typename Data>
void List<Data>::InsertAtFront(const Data & d)
{
    try
    {
        Node * newHead = new Node (d);
        newHead->next = this->head;
        this->head = newHead;
        this->size++;
    }
    catch (std::bad_alloc & exc)
    {
        throw;
    }

    if (this->tail == nullptr)
    {
        this->tail = this->head;
    }
}

// Move of the value
template <typename Data>
void List<Data>::InsertAtFront(Data && d)
{
    try
    {
        Node * newHead = new Node (std::move(d));
        newHead->next = this->head;
        this->head = newHead;
        this->size++;
    }
    catch (std::bad_alloc & exc)
    {
        throw;
    }
    
    if (this->tail == nullptr)
    {
        this->tail = this->head;
    }
}

template <typename Data>
void List<Data>::RemoveFromFront()
{
    if (this->Empty())
    {
        throw std::length_error ("RemoveFromFront used on empty list");
    }

    if (this->tail == this->head)
    {
        this->tail = nullptr;
    }

    Node * temp = this->head;
    this->head = this->head->next;
    temp->next = nullptr;
    delete temp;

    this->size--;
}

template <typename Data>
inline Data List<Data>::FrontNRemove()
{
    if (this->Empty())
    {
        throw std::length_error ("FrontNRemove used on empty list");
    }

    if (this->tail == this->head)
    {
        this->tail = nullptr;
    }

    Node * temp = this->head;
    this->head = this->head->next;
    temp->next = nullptr;

    Data ret = temp->elem;

    delete temp;

    this->size--;

    return ret;
}


// Copy of the value
template <typename Data>
void List<Data>::InsertAtBack(const Data & d)
{
    try
    {
        Node * newTail = new Node (d);
        if (this->tail != nullptr)
        {
            this->tail->next = newTail;
        }
        this->tail = newTail;
        this->size++;
    }
    catch (std::bad_alloc & exc)
    {
        throw;
    }

    if (this->head == nullptr)
    {
        this->head = this->tail;
    }
}

// Move of the value
template <typename Data>
void List<Data>::InsertAtBack(Data && d)
{
    try
    {
        Node * newTail = new Node (std::move(d));
        if (this->tail != nullptr)
        {
            this->tail->next = newTail;
        }
        this->tail = newTail;
        this->size++;
    }
    catch (std::bad_alloc & exc)
    {
        throw;
    }

    if (this->head == nullptr)
    {
        this->head = this->tail;
    }
}

template <typename Data>
void List<Data>::Clear()
{
    if (this->head != nullptr)
    {
        delete this->head;
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template <typename Data>
bool List<Data>::Insert(const Data & dat)
{
    if (this->Exists (dat))
    {
        return false;
    }
    try
    {
        this->InsertAtBack(dat);
    }
    catch (std::exception & e)
    {
        return false;
    }
    return true;
}

template <typename Data>
bool List<Data>::Insert(Data && dat)
{
    if (this->Exists (std::move(dat)))
    {
        return false;
    }
    try
    {
        this->InsertAtBack(dat);
    }
    catch (std::exception & e)
    {
        return false;
    }
    return true;
}


template <typename Data>
bool List<Data>::Remove(const Data & toRemove)
{
    Node * pred = nullptr;
    Node * curr = this->head;
    
    while (curr != nullptr)
    {
        if (curr->elem != toRemove)
        {
            pred = curr;
            curr = curr->next;
        }

        else 
        {
            if (pred != nullptr)
            {
                pred->next = curr->next;
            }

            else //the node to be removed is the head
            {
                this->head = curr->next;
            }

            // the node to be removed is the tail
            if (curr == tail) 
            {    
                this->tail = pred;
            }
            
            curr->next = nullptr;
            delete curr; 
            this->size--;
            return true;    
        }
    }

    return false;
}

template <typename Data>
const Data & List<Data>::operator[](unsigned long idx) const
{
    if (idx >= this->size)
    {
        throw std::out_of_range("from operator []");
    }
    Node *ret = this->head;
    for (unsigned long i = 0; i < idx; i++)
    {
        ret = ret->next;
    }
    return ret->elem;
}

template <typename Data>
Data & List<Data>::operator[](unsigned long idx)
{
    if (idx >= this->size)
    {
        throw std::out_of_range("from operator []");
    }
    Node *ret = this->head;
    for (unsigned long i = 0; i < idx; i++)
    {
        ret = ret->next;
    }
    return ret->elem;
}
template <typename Data>
inline const Data & List<Data>::Front() const
{
    if (this->head == nullptr) 
    {
        throw std::length_error("from Front");
    } 
    return this->head->elem;
} 

template <typename Data>
inline Data & List<Data>::Front()
{
    if (this->head == nullptr) 
    {
        throw std::length_error("from Front");
    } 
    return this->head->elem;
} 

template <typename Data>
inline const Data & List<Data>::Back() const
{
    if (this->tail == nullptr) 
    {
        throw std::length_error("from Back");
    } 
    return this->tail->elem;
}

template <typename Data>
inline Data & List<Data>::Back()
{
    if (this->tail == nullptr) 
    {
        throw std::length_error("from Back");
    } 
    return this->tail->elem;
}
}
