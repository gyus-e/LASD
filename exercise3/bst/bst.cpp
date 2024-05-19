#include <iostream>
#include <stdexcept>

namespace lasd {

/* ************************************************************************** */
//Specific constructor
template <typename Data>
BST<Data>::BST (const TraversableContainer<Data> & con)
{
    con.Traverse(
        [this](const Data & d)
        {
            this->Insert(d);
        }
    );
}

template <typename Data>
BST<Data>::BST (MappableContainer<Data> & con)
{
    con.Map(
        [this](const Data & d)
        {
            this->Insert(std::move(d));
        }
    );
}

// Copy assignment
template <typename Data>
BST<Data> BST<Data>::operator=(const BST<Data> & that) 
{
    this->BinaryTreeLnk<Data>::operator=(that);
    return *this;
}

// Move assignment
template <typename Data>
BST<Data> BST<Data>::operator=(BST<Data> && that) noexcept
{
    this->BinaryTreeLnk<Data>::operator=(std::move(that));
    return *this;
}

// Comparison operators
template <typename Data>
bool BST<Data>::operator==(const BST<Data> & that) const
{
    // return ((BinaryTreeLnk<Data> *) this)->BinaryTreeLnk<Data>::operator==((BinaryTreeLnk<Data>)that);
    if (this->Size() != that.Size())
    {
        return false;
    }
    
    QueueLst<Data> Q;
    this->InOrderTraverse(
        [&Q](const Data & d)
        {
            Q.Enqueue(d);
        }
    );

    bool ret = true;

    that.InOrderTraverse(
        [&Q, &ret](const Data & d)
        {
            ret = ret && (d == Q.HeadNDequeue());
        }
    );

    return ret;
}

template <typename Data>
bool BST<Data>::operator!=(const BST<Data> & that) const
{
    return !(this->operator==(that));
}

// Specific member functions

template <typename Data>
const Data & BST<Data>::Min() const // (concrete function must throw std::length_error when empty)
{
    if (this->Empty())
    {
        throw std::length_error ("no min: BST is empty.");
    }

    return FindPointerToMin(this->root)->Element();
}

template <typename Data>
Data BST<Data>::MinNRemove() // (concrete function must throw std::length_error when empty)
{
    Data ret;
    try 
    {
        ret = this->Min();
        this->RemoveMin();
    }
    catch (std::exception & e)
    {
        throw;
    }
    return ret;
}

template <typename Data>
void BST<Data>::RemoveMin() // (concrete function must throw std::length_error when empty)
{
    if (this->Empty())
    {
        throw std::length_error ("cannot remove min: BST is empty.");
    }

    NodeLnk * min = DetachMin(this->root, nullptr); //restituisce puntatore al minimo dopo averlo staccato dall'albero
    delete min;
    
    this->size--;
}

template <typename Data>
const Data & BST<Data>::Max() const // (concrete function must throw std::length_error when empty)
{
    if (this->Empty())
    {
        throw std::length_error ("no max: BST is empty.");
    }
    return this->FindPointerToMax(this->root)->Element();   
}

template <typename Data>
Data BST<Data>::MaxNRemove() // (concrete function must throw std::length_error when empty)
{
    Data ret;
    try
    {
        ret = this->Max();
        this->RemoveMax();
    }
    catch (std::length_error & exc)
    {
        throw;
    }
    return ret;
}

template <typename Data>
void BST<Data>::RemoveMax() // (concrete function must throw std::length_error when empty)
{
    if (this->Empty())
    {
        throw std::length_error ("cannot remove max: BST is empty.");
    }

    NodeLnk * max = DetachMax(this->root, nullptr);
    delete max;

    this->size--;
}

template <typename Data>
const Data & BST<Data>::Predecessor (const Data & d) const // (concrete function must throw std::length_error when not found)
{
    const typename BinaryTreeLnk<Data>::NodeLnk * const * ret = FindPointerToPredecessor(d, &(root));
    if (*ret == nullptr)
    {
        throw std::length_error("Predecessor not found.");
    }
    return (*ret)->Element();
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data & d) // (concrete function must throw std::length_error when not found)
{
    Data ret;
    try 
    {
        ret = this->Predecessor(d);
        this->RemovePredecessor(d);
    }
    catch (std::exception & exc)
    {
        std::cerr<<exc.what();
        throw std::length_error("from PredecessorNRemove: predecessor not found");
    }
    return ret;
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data & d) // (concrete function must throw std::length_error when not found)
{
    try 
    {
        typename BinaryTreeLnk<Data>::NodeLnk ** predecessor = FindPointerToPredecessor(d, &(root));
        // delete 
        *predecessor = Detach(predecessor);
        this->size--;
    }
    catch (std::exception & exc)
    {
        std::cerr<<exc.what();
        throw std::length_error("from RemovePredecessor: predecessor not found");
    }
}

template <typename Data>
const Data & BST<Data>::Successor(const Data & d) const// (concrete function must throw std::length_error when not found)
{
    const typename BinaryTreeLnk<Data>::NodeLnk * const * ret = this->FindPointerToSuccessor (d, &root);
    if (*ret == nullptr)
    {
        throw std::length_error("Successor not found.");
    }
    return (*ret)->Element();
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data & d) // (concrete function must throw std::length_error when not found)
{
    Data ret;
    try 
    {
        ret = this->Successor(d);
        this->RemoveSuccessor(d);
    }
    catch (std::exception & exc)
    {
        std::cerr<<exc.what();
        throw std::length_error("from SuccessorNRemove: predecessor not found");
    }
    return ret;
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data & d) // (concrete function must throw std::length_error when not found)
{
    try 
    {
        typename BinaryTreeLnk<Data>::NodeLnk ** successor = FindPointerToSuccessor(d, &root);
        // delete 
        *successor = Detach(successor);
        this->size--;
    }
    catch (std::exception & exc)
    {
        std::cerr<<exc.what();
        throw std::length_error("from RemoveSuccessor: predecessor not found");
    }
}

template <typename Data>
inline const typename BinaryTree<Data>::Node & BST<Data>::Root() const
{
    if (this->root == nullptr)
    {
        throw std::length_error ("no root: BST is empty");
    }    
    return *(this->root);
}

template <typename Data>
bool BST<Data>::Insert(const Data & d)
{
    bool ret = false;
    try
    {
        ret = this->Insert (d, &(this->root));
        if (ret)
        {
            this->size++;
        }
    }
    catch (std::exception & e)
    {
        throw;
    }
    return ret;
}

template <typename Data>
bool BST<Data>::Insert(Data && d)
{
    bool ret = false;
    try
    {
        ret = this->Insert (std::move(d), &(this->root));
        if (ret)
        {
            this->size++;
        }
    }
    catch (std::exception & e)
    {
        throw;
    }
    return ret;
}

template <typename Data>
bool BST<Data>::Remove(const Data & d) 
{
    bool ret = false;
    try 
    {
        ret = Remove (d, &(this->root));
        if (ret)
        {
            this->size--;
        }
    }
    catch (std::exception & e)
    {
        throw;
    }
    return ret;     
}

template <typename Data>
bool BST<Data>::Exists(const Data & d) const noexcept
{
    return (this->FindPointerTo(d, this->root) != nullptr);
}

template <typename Data>
void BST<Data>::Clear() 
{
    this->BinaryTreeLnk<Data>::Clear();
}

/* ************************************************************************** */
/*  Auxiliary functions    */

// template <typename Data>
// Data BST<Data>::DataNDelete(NodeLnk* curr) 
// {
//     
// }

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::Detach(typename BinaryTreeLnk<Data>::NodeLnk ** curr)
{
    if (curr == nullptr)
    {
        throw std::logic_error("detach called on nullptr");
    }

    NodeLnk *ret = nullptr; 

    if ((*curr) != nullptr)
    {
        if (!((*curr)->HasLeftChild()))
        {
            ret = (*curr)->Dx;
        }
        else if (!((*curr)->HasRightChild()))
        {
            ret = (*curr)->Sx;
        }
        else 
        {
            NodeLnk * min = DetachMin((*curr)->Dx, (*curr)); 
            (*curr)->elem = min->elem; 
        }
        
        (*curr)->Sx = nullptr;
        (*curr)->Dx = nullptr;
        delete (*curr);
        *curr = nullptr;
    }
    return ret;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::DetachMin(typename BinaryTreeLnk<Data>::NodeLnk * curr, typename BinaryTreeLnk<Data>::NodeLnk * pred)
{
    if (curr != nullptr)
    {
        if (curr->HasLeftChild())
        {
            return DetachMin (curr->Sx, curr);
        }
        else 
        {
            NodeLnk * min = curr;

            if (pred != nullptr)
            {   
                if (curr == (pred->Sx))
                {
                    pred->Sx = curr->Dx;
                }
                else
                {
                    pred->Dx = curr->Dx;
                }
            }
            min->Dx = nullptr;
            return min;
        }
    }
    else 
    {
        throw std::length_error ("from DetachMin: curr is nullptr");
    }
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::DetachMax(typename BinaryTreeLnk<Data>::NodeLnk * curr, typename BinaryTreeLnk<Data>::NodeLnk * pred)
{
    if (curr != nullptr)
    {
        if (curr->HasRightChild())
        {
            return DetachMax (curr->Dx, curr);
        }
        else 
        {
            NodeLnk * max = curr;

            if (pred != nullptr)
            {   
                if (curr == (pred->Sx))
                {
                    pred->Sx = curr->Sx;
                }
                else 
                {
                    pred->Dx = curr->Sx;
                }
            }
            max->Sx = nullptr;
            return max;
        }
    }
    else 
    {
        throw std::length_error ("from DetachMax: curr is nullptr");
    }
}

// template <typename Data>
// typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::Skip2Left(typename BinaryTreeLnk<Data>::NodeLnk ** curr)
// {
//     NodeLnk* temp = nullptr;
//     if(curr != nullptr) {
//         std::swap(temp, *((*curr)->SX()));
//         std::swap(temp, *curr);
//     }
//     return temp;
// }

// template <typename Data>
// typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::Skip2Right(typename BinaryTreeLnk<Data>::NodeLnk ** curr)
// {
//     NodeLnk* temp = nullptr;
//     if(curr != nullptr) {
//         std::swap(temp, *((*curr)->DX()));
//         std::swap(temp, *curr);
//     }
//     return temp;
// }

//mutable version
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerToMin (typename BinaryTreeLnk<Data>::NodeLnk * curr)
{
    if (curr->HasLeftChild())
    {
        return FindPointerToMin(&(curr->LeftChild()));
    }
    else 
    {
        return curr;
    }
}

//unmutable version
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerToMin (const typename BinaryTreeLnk<Data>::NodeLnk * curr) const
{
    if (curr->HasLeftChild())
    {
        return FindPointerToMin(&(curr->LeftChild()));
    }
    else 
    {
        return curr;
    }
}

//mutable version
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerToMax (typename BinaryTreeLnk<Data>::NodeLnk * curr)
{
    if (curr->HasRightChild())
    {
        return FindPointerToMax(&(curr->RightChild()));
    }
    else 
    {
        return curr;
    }
}

//unmutable version
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerToMax (const typename BinaryTreeLnk<Data>::NodeLnk * curr) const
{
    if (curr->HasRightChild())
    {
        return FindPointerToMax(&(curr->RightChild()));
    }
    else 
    {
        return curr;
    }
}

//mutable version
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerTo(const Data & d, typename BinaryTreeLnk<Data>::NodeLnk * curr)
{
    if (curr != nullptr)
    {
        if (curr->Element() == d)
        {
            return curr;
        }

        else if (curr->HasLeftChild() && curr->Element() > d)
        {
            return this->FindPointerTo(d, curr->Sx);
        }

        else if (curr->HasRightChild() && curr->Element() < d)
        {
            return this->FindPointerTo(d, curr->Dx);
        }

        else 
        {
            return nullptr;
        }
    }
    return nullptr;
}

//unmutable version
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerTo(const Data & d, const typename BinaryTreeLnk<Data>::NodeLnk * curr) const 
{
    if (curr != nullptr)
    {
        if (curr->Element() == d)
        {
            return curr;
        }

        else if (curr->HasLeftChild() && curr->Element() > d)
        {
            return this->FindPointerTo(d, curr->Sx);
        }

        else if (curr->HasRightChild() && curr->Element() < d)
        {
            return this->FindPointerTo(d, curr->Dx);
        }

        else 
        {
            return nullptr;
        }
    }
    return nullptr;
}

//mutable version
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk ** BST<Data>::FindPointerToPredecessor(const Data & d, typename BinaryTreeLnk<Data>::NodeLnk ** curr)
{
    if ((*curr) != nullptr)
    {
        if ((*curr)->Element() >= d)
        {
            return FindPointerToPredecessor(d, (*curr)->SX());
        }
        else 
        {
            NodeLnk ** ret = FindPointerToPredecessor(d, (*curr)->DX());
            if (ret == nullptr)
            {
                return curr;
            }
            else 
            {
                return ret;
            }
        }
    }
    else 
    {
        return nullptr;
    }
}

//unmutable version
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk * const * BST<Data>::FindPointerToPredecessor(const Data & d, const typename BinaryTreeLnk<Data>::NodeLnk * const * curr) const
{
    if ((*curr) != nullptr)
    {
        if ((*curr)->Element() >= d)
        {
            return FindPointerToPredecessor(d, (*curr)->SX());
        }
        else 
        {
            const NodeLnk * const * ret = FindPointerToPredecessor(d, (*curr)->DX());
            if (ret == nullptr)
            {
                return curr;
            }
            else 
            {
                return ret;
            }
        }
    }
    else 
    {
        return nullptr;
    }
}

//mutable version
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk ** BST<Data>::FindPointerToSuccessor(const Data & d, typename BinaryTreeLnk<Data>::NodeLnk ** curr)
{
    if ((*curr) != nullptr)
    {
        if ((*curr)->Element() <= d)
        {
            return FindPointerToSuccessor(d, (*curr)->DX());
        }
        else 
        {
            NodeLnk ** ret = FindPointerToSuccessor(d, (*curr)->SX());
            if (ret == nullptr)
            {
                return curr;
            }
            else 
            {
                return ret;
            }
        }
    }
    else 
    {
        return nullptr;
    }
}

//unmutable version
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk * const * BST<Data>::FindPointerToSuccessor(const Data & d, const typename BinaryTreeLnk<Data>::NodeLnk * const * curr) const
{
    if ((*curr) != nullptr)
    {
        if ((*curr)->Element() <= d)
        {
            return FindPointerToSuccessor(d, (*curr)->DX());
        }
        else 
        {
            const NodeLnk * const * ret = FindPointerToSuccessor(d, (*curr)->SX());
            if (ret == nullptr)
            {
                return curr;
            }
            else 
            {
                return ret;
            }
        }
    }
    else 
    {
        return nullptr;
    }
}

//copy
template <typename Data>
bool BST<Data>::Insert(const Data & d, typename BinaryTreeLnk<Data>::NodeLnk ** curr)
{
    if (*curr == nullptr)
    {
        try
        {
            *curr = new NodeLnk (d);
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
        return true;
    }
    
    else if ((*curr)->Element() > d)
    {
        return Insert (d, (*curr)->SX());
    }
    else if ((*curr)->Element() < d)
    {
        return Insert (d, (*curr)->DX());
    }
    else //if ((*curr)->Element() == d)
    {
        return false;
    }
}

//move
template <typename Data>
bool BST<Data>::Insert(Data && d, typename BinaryTreeLnk<Data>::NodeLnk ** curr)
{
    if (*curr == nullptr)
    {
        try
        {
            *curr = new NodeLnk (std::move(d));
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
        return true;
    }
    
    else if ((*curr)->Element() > d)
    {
        return Insert (d, (*curr)->SX());
    }
    else if ((*curr)->Element() < d)
    {
        return Insert (d, (*curr)->DX());
    }
    else //if ((*curr)->Element() == d)
    {
        return false;
    }
}


template <typename Data>
bool BST<Data>::Remove(const Data & d, typename BinaryTreeLnk<Data>::NodeLnk ** curr)
{
    if ((*curr) != nullptr)
    {
        if ((*curr)->Element() < d)
        {
            return Remove (d, &((*curr)->Dx));
        }
        else if ((*curr)->Element() > d)
        {
            return Remove (d, &((*curr)->Sx));
        }
        else //curr->Element() == d
        {
            try  
            {
                // void * temp = *curr;
                
                *curr = Detach(curr); 

                // std::cout<<std::endl<<"removed node at address "<<temp<<std::endl<<"now pointing to address: "<<*curr<<std::endl;
            }
            catch (std::exception & exc)
            {
                std::cerr<<exc.what();
                return false;
            }
            return true;;
        }
    }
    else 
    {
        return false;
    } 
}
}