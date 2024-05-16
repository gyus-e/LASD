#include <iostream>
#include <stdexcept>

namespace lasd {

/* ************************************************************************** */
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
    return ((BinaryTreeLnk<Data> *) this)->BinaryTreeLnk<Data>::operator==((BinaryTreeLnk<Data>)that);
}

template <typename Data>
bool BST<Data>::operator!=(const BST<Data> & that) const
{
    return ((BinaryTreeLnk<Data> *) this)->BinaryTreeLnk<Data>::operator!=((BinaryTreeLnk<Data>)that);
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

    delete (DetachMin(this->root, nullptr));
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
        throw std::length_error ("cannot remove min: BST is empty.");
    }

    delete (DetachMax(this->root, nullptr));
    this->size--;
}

template <typename Data>
const Data & BST<Data>::Predecessor (const Data & d) const // (concrete function must throw std::length_error when not found)
{
    const typename BinaryTreeLnk<Data>::NodeLnk * ret = this->FindPointerToPredecessor(d, this->root, nullptr);
    if (ret == nullptr)
    {
        throw std::length_error("Predecessor not found.");
    }
    return ret->Element();
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data & d) // (concrete function must throw std::length_error when not found)
{
    Data ret;
    try 
    {
        typename BinaryTreeLnk<Data>::NodeLnk * predecessor = FindPointerToPredecessor(d, this->root, nullptr);
        typename BinaryTreeLnk<Data>::NodeLnk * toDel = Detach(&predecessor);
        ret = toDel->Element();
        delete toDel;
    }
    catch (std::exception & exc)
    {
        std::cerr<<exc.what();
        throw std::length_error("from RemovePredecessor: predecessor not found");
    }
    return ret;
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data & d) // (concrete function must throw std::length_error when not found)
{
    try 
    {
        typename BinaryTreeLnk<Data>::NodeLnk * predecessor = FindPointerToPredecessor(d, this->root, nullptr);
        typename BinaryTreeLnk<Data>::NodeLnk * toDel = Detach(&predecessor);
        delete toDel;
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
    const typename BinaryTreeLnk<Data>::NodeLnk * ret = this->FindPointerToSuccessor (d, this->root, nullptr);
    if (ret == nullptr)
    {
        throw std::length_error("Successor not found.");
    }
    return ret->Element();
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data & d) // (concrete function must throw std::length_error when not found)
{
    Data ret;
    try 
    {
        typename BinaryTreeLnk<Data>::NodeLnk * successor = FindPointerToSuccessor(d, this->root, nullptr);
        typename BinaryTreeLnk<Data>::NodeLnk * toDel = Detach(&successor);
        ret = toDel->Element();
        delete toDel;
    }
    catch (std::exception & exc)
    {
        std::cerr<<exc.what();
        throw std::length_error("from PredecessorNRemove: predecessor not found");
    }
    return ret;
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data & d) // (concrete function must throw std::length_error when not found)
{
    try 
    {
        typename BinaryTreeLnk<Data>::NodeLnk ** successor = & FindPointerToSuccessor(d, this->root, nullptr);
        typename BinaryTreeLnk<Data>::NodeLnk * toDel = Detach(successor);
        delete toDel;
    }
    catch (std::exception & exc)
    {
        std::cerr<<exc.what();
        throw std::length_error("from PredecessorNRemove: predecessor not found");
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
        this->size++;
        ret = this->Insert (d, &(this->root));
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
        this->size++;
        ret = this->Insert (std::move(d), &(this->root));
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
        this->size--;
        ret = Remove (d, &(this->root));
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
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::Detach(typename BinaryTreeLnk<Data>::NodeLnk ** curr)
{
    typename BinaryTreeLnk<Data>::NodeLnk * ret = (*curr);
    if (! (*curr)->HasLeftChild())
    {
        *curr = &((*curr)->LeftChild());
    }
    else if (! (*curr)->HasRightChild())
    {
        *curr = &((*curr)->RightChild());
    }
    else 
    {
        ret = DetachMin(&((*curr)->RightChild()), *curr);
        (*curr)->Element() = ret->Element();
    }

    return ret;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::DetachMin(typename BinaryTreeLnk<Data>::NodeLnk * curr, typename BinaryTreeLnk<Data>::NodeLnk * pred)
{
    if (curr == nullptr)
    {
        throw std::logic_error("from DetachMin: curr is nullptr");
    }

    if (curr->HasLeftChild())
    {
        return DetachMin(&(curr->LeftChild()), curr);
    }

    else //curr is min
    {
        if (curr->HasRightChild())
        {
            if (pred == nullptr) //curr is root
            {
                this->root = &(curr->RightChild());
            }
            else
            {
                if (pred->HasRightChild() && curr == &(pred->RightChild()))
                {
                    pred->RightChild() = curr->RightChild();
                }
                else if (pred->HasLeftChild() && curr == &(pred->LeftChild()))
                {
                    pred->LeftChild() = curr->RightChild();
                }
                else 
                {
                    throw std::logic_error("from DetachMin: something went wrong");
                }
            }
        }    
        return curr;
    }
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::DetachMax(typename BinaryTreeLnk<Data>::NodeLnk * curr, typename BinaryTreeLnk<Data>::NodeLnk * pred)
{
    if (curr->HasRightChild())
    {
        return DetachMax(&(curr->LeftChild()), curr);
    }

    //curr is max
    if (curr->HasLeftChild())
    {
        if (pred == nullptr) //max is root
        {
            this->root = &(curr->LeftChild());
        }
        else
        {
            if (pred->HasRightChild() && curr == &(pred->RightChild()))
            {
                pred->RightChild() = curr->LeftChild();
            }
            else if (pred->HasLeftChild() && curr == &(pred->LeftChild()))
            {
                pred->LeftChild() = curr->LeftChild();
            }
            else 
            {
                throw std::logic_error("from DetachMax: something went wrong");
            }
        }
    }    
    return curr;
}

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
    if (curr->Element() == d)
    {
        return curr;
    }

    else if (curr->HasLeftChild() && curr->Element() > d)
    {
        return this->FindPointerTo(d, curr->LeftChild());
    }

    else if (curr->HasRightChild() && curr->Element() < d)
    {
        return this->FindPointerTo(d, curr->RightChild());
    }

    else 
    {
        return nullptr;
    }
}

//unmutable version
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerTo(const Data & d, typename BinaryTreeLnk<Data>::NodeLnk * curr) const 
{
    if (curr->Element() == d)
    {
        return curr;
    }

    else if (curr->HasLeftChild() && curr->Element() > d)
    {
        return this->FindPointerTo(d, &(curr->LeftChild()));
    }

    else if (curr->HasRightChild() && curr->Element() < d)
    {
        return this->FindPointerTo(d, &(curr->RightChild()));
    }

    else 
    {
        return nullptr;
    }
}

//mutable version
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerToPredecessor(const Data & d, typename BinaryTreeLnk<Data>::NodeLnk * curr, typename BinaryTreeLnk<Data>::NodeLnk * pred)
{
    if (curr->Element() == d)
	{
		if (curr->HasLeftChild())
		{	
            return FindPointerToMax (&(curr->LeftChild()));
        }
		else if ((pred != nullptr) && (pred->HasRightChild()) && (curr == &(pred->RightChild())))
		{
        	return pred;
        }
		else 
		{
        	return nullptr;
        }
    }
	
	else if ((curr->Element() < d) && (curr->HasRightChild()))
	{
		typename BinaryTreeLnk<Data>::NodeLnk * ret = FindPointerToPredecessor (d, &(curr->RightChild()), curr);

		if (ret != nullptr)
		{	
            return ret;
        }
		else 
		{
        	return curr;
        }
    }
	
	else if ((curr->Element() > d) && (curr->HasLeftChild()))
	{	
        return FindPointerToPredecessor (d, &(curr->LeftChild()), curr);
    }
	else 
    {
		return nullptr;
    }
}

//unmutable version
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerToPredecessor(const Data & d, const typename BinaryTreeLnk<Data>::NodeLnk * curr, const typename BinaryTreeLnk<Data>::NodeLnk * pred) const
{
    if (curr->Element() == d)
	{
		if (curr->HasLeftChild())
		{	
            return FindPointerToMax (&(curr->LeftChild()));
        }
		else if ((pred != nullptr) && (pred->HasRightChild()) && (curr == &(pred->RightChild())))
		{
        	return pred;
        }
		else 
		{
        	return nullptr;
        }
    }
	
	else if ((curr->Element() < d) && (curr->HasRightChild()))
	{
		const typename BinaryTreeLnk<Data>::NodeLnk * ret = FindPointerToPredecessor (d, &(curr->RightChild()), curr);

		if (ret != nullptr)
        {
			return ret;
        }
		else 
        {
			return curr;
        }
	}
	
	else if ((curr->Element() > d) && (curr->HasLeftChild()))
	{	
        return FindPointerToPredecessor (d, &(curr->LeftChild()), curr);
    }
	else 
	{
    	return nullptr;
    }
}

//mutable version
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerToSuccessor(const Data & d, typename BinaryTreeLnk<Data>::NodeLnk * curr, typename BinaryTreeLnk<Data>::NodeLnk * pred)
{
    if (curr->Element() == d)
	{
		if (curr->HasRightChild())
		{	
            return FindPointerToMin (&(curr->RightChild()));
        }
		else if ((pred != nullptr) && (pred->HasLeftChild()) && (curr == &(pred->LeftChild())))
		{
        	return pred;
        }
		else 
		{
        	return nullptr;
        }
    }
	
	else if ((curr->Element() > d) && (curr->HasLeftChild()))
	{
		typename BinaryTreeLnk<Data>::NodeLnk * ret = FindPointerToSuccessor (d, &(curr->LeftChild()), curr);

		if (ret != nullptr)
        {
			return ret;
        }
		else 
		{
        	return curr;
        }
    }
	
	else if ((curr->Element() < d) && (curr->HasRightChild()))
	{
    	return FindPointerToSuccessor (d, &(curr->RightChild()), curr);
    }
	else 
    {
		return nullptr;
    }
}

//unmutable version
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::FindPointerToSuccessor(const Data & d, const typename BinaryTreeLnk<Data>::NodeLnk * curr, const typename BinaryTreeLnk<Data>::NodeLnk * pred) const
{
    if (curr->Element() == d)
	{
		if (curr->HasRightChild())
		{	
            return FindPointerToMin (&(curr->RightChild()));
        }
		else if ((pred != nullptr) && (pred->HasLeftChild()) && (curr == &(pred->LeftChild())))
		{
        	return pred;
        }
		else 
		{
        	return nullptr;
        }
    }
	
	else if ((curr->Element() > d) && (curr->HasLeftChild()))
	{
		const typename BinaryTreeLnk<Data>::NodeLnk * ret = FindPointerToSuccessor (d, &(curr->LeftChild()), curr);

		if (ret != nullptr)
        {
			return ret;
        }
		else 
		{
        	return curr;
        }
    }
	
	else if ((curr->Element() < d) && (curr->HasRightChild()))
	{
    	return FindPointerToSuccessor (d, &(curr->RightChild()), curr);
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
    if ((*curr)->Element() == d)
    {
        typename BinaryTreeLnk<Data>::NodeLnk * toDel = Detach(curr);
        delete toDel;
        return true;
    }

    else if ((*curr)->Element() > d && (*curr)->HasLeftChild())
    {
        return Remove(d, (*curr)->SX());
    }

    else if ((*curr)->Element() < d && (*curr)->HasRightChild())
    {
        return Remove(d, (*curr)->DX());
    }

    else 
    {
        return false;
    }
}
}
