
namespace lasd
{

    /* ************************************************************************** */
    
    //copy constructor
    template<typename Data>
    List<Data>::List (const List & that)
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;

        Node* curr = that.head;
        while (curr != nullptr) 
        {
            try 
            {
                this->InsertAtBack(curr->element);
            }
            catch (std::bad_alloc & exc)
            {
                throw;
            }
            curr = curr->next;
        }
        if (this->size != that.size)
        {
            throw std::runtime_error ("COPY CONSTRUCTOR SIZE ERROR");
        }
    }

    //copy operator
    template<typename Data>
    List<Data> List<Data>::operator= (const List & that)
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;

        Node* curr = that.head;
        while (curr != nullptr) 
        {
            try 
            {
                this->InsertAtBack(curr->element); 
            }
            catch (std::bad_alloc & exc)
            {
                throw;
            }
            curr = curr->next;
        }
        if (this->size != that.size)
        {
            throw std::runtime_error ("COPY OPERATOR SIZE ERROR");
        }
        
        return *this;
    }

    //move constructor
    template<typename Data>
    List<Data>::List (List && that) noexcept
    {
        std::swap(this->size, that.size);
        std::swap(this->head, that.head);
        std::swap(this->tail, that.tail);
    }

    //move operator
    template<typename Data>
    List<Data> List<Data>::operator= (List && that)
    {
        std::swap(this->size, that.size);
        std::swap(this->head, that.head);
        std::swap(this->tail, that.tail);
        return *this;
    }

    // A list obtained from a TraversableContainer
    template<typename Data>
    List<Data>::List (const TraversableContainer<Data> & cont)
    {
        if (cont.Size() != 0)
        {
            cont.Traverse (
                [this] (const Data & dat)
                {
                    this->Insert (dat);
                }
            );
        }
    }

    // A list obtained from a MappableContainer
    template<typename Data>
    List<Data>::List (MappableContainer<Data> && cont)
    {
        if (cont.Size() != 0)
        {
            cont.Map (
                [this] (Data & dat)
                {
                    this->Insert (std::move(dat));
                }
            );
        }
    }

    //destructor
    template <typename Data>
    List<Data>::~List ()
    {
        Node* curr = this->head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    template <typename Data>
    void List<Data>::Clear ()
    {
        Node* curr = this->head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;
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
        return ret->element;
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
        return ret->element;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(const Data &dat)
    {
        Node * newNode = nullptr;
        try 
        {
            newNode = new Node (dat);
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
        
        if (this->head == nullptr)
        {
            if (this->size != 0)
            {
                throw std::logic_error ("SIZE NOT 0 IN EMPTY LIST");
            }
            this->head = newNode;
        }
        if (this->tail == nullptr) 
        {
            this->tail = newNode;
        } 
        else 
        {
            this->tail->next = newNode;
            this->tail = this->tail->next;
        }
        this->size++;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data &&dat)
    {
       Node * newNode = nullptr;
        try 
        {
            newNode = new Node (std::move(dat));
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
        
        if (this->head == nullptr)
        {
            if (this->size != 0)
            {
                throw std::logic_error ("SIZE NOT 0 IN EMPTY LIST");
            }
            this->head = newNode;
        }
        if (this->tail == nullptr) 
        {
            this->tail = newNode;
        } 
        else 
        {
            this->tail->next = newNode;
            this->tail = this->tail->next;
        }
        this->size++;
    }

    // Copy of the value
    template <typename Data>
    void List<Data>::InsertAtFront(const Data & dat)
    {
        Node * newNode = nullptr;
        try 
        {
            newNode = new Node (dat);
        }
        catch (std::bad_alloc & exc)
        {
            delete newNode;
            throw;
        }

        newNode->next = this->head;
        this->head = newNode;
        this->size++;
        if (this->tail == nullptr)
        {
            this->tail = newNode;
        }
    }

    // Move of the value
    template <typename Data>
    void List<Data>::InsertAtFront(Data && dat)
    {
        Node * newNode = nullptr;
        try 
        {
            newNode = new Node (std::move(dat));
        }
        catch (std::bad_alloc & exc)
        {
            delete newNode;
            throw;
        }

        newNode->next = this->head;
        this->head = newNode;
        this->size++;
        if (this->tail == nullptr)
        {
            this->tail = newNode;
        }
    } 

    template <typename Data>
    bool List<Data>::Insert(const Data &dat)
    {
        if (this->Exists (dat))
        {
            return false;
        }
        try
        {
            this->InsertAtBack(dat);
        }
        catch (std::exception &e)
        {
            return false;
        }
        return true;
    }

    template <typename Data>
    bool List<Data>::Insert(Data &&dat)
    {
        if (this->Exists (dat))
        {
            return false;
        }
        try
        {
            this->InsertAtBack(std::move(dat));
        }
        catch (std::exception &e)
        {
            return false;
        }
        return true;
    }

    template <typename Data>
    bool List<Data>::Remove(const Data &toRemove)
    {
        Node *pred = nullptr;
        Node *curr = this->head;
        
        while (curr != nullptr)
        {
            if (curr->element != toRemove)
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
                    head = curr->next;
                }

                // the node to be removed is the tail
                if (curr == tail) 
                {    
                    tail = pred;
                }

                delete curr; 
                this->size--;
                return true;    
            }
        }

        return false;
    }

    template <typename Data>
    void List<Data>::RemoveFromFront() 
    {
        if (this->head == nullptr) 
        {
            throw std::length_error ("RemoveFromFront impossible: List empty.");
        } 
        Node * toDel = this->head; 
        this->head = this->head->next; 
        if (toDel == this->tail)
        {
            this->tail = nullptr;
        }
        delete toDel; 
        this->size--;
    }

    template <typename Data>
    inline Data List<Data>::FrontNRemove() 
    {
        Data ret;
        try 
        {
            ret = this->Front(); 
            this->RemoveFromFront();
        } 
        catch (std::length_error &exc) 
        {
            throw;
        }
        return ret;
    } 

    template <typename Data>
    bool List<Data>::operator==(const List & that) const
    {

        if (this->size != that.size)
        {
            return false;
        }

        Node * thisCurr = this->head;
        Node * thatCurr = that.head;

        while (thisCurr != nullptr) //&& thatCurr != nullptr scontato se hanno la stessa dimensione
        {
            if (thisCurr->element != thatCurr->element)
            {
                return false;
            }
            thisCurr = thisCurr->next;
            thatCurr = thatCurr->next;
        }

        return true;
    }

    template <typename Data>
    bool List<Data>::operator!=(const List & that) const
    {

        if (this->size != that.size)
        {
            return true;
        }

        Node * thisCurr = this->head;
        Node * thatCurr = that.head;

        while (thisCurr != nullptr) //&& thatCurr != nullptr scontato se hanno la stessa dimensione
        {
            if (thisCurr->element != thatCurr->element)
            {
                return true;
            }
            thisCurr = thisCurr->next;
            thatCurr = thatCurr->next;
        }

        return false;
    }



    /* ************************************************************************** */

}
