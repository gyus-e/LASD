
namespace lasd {

/* ************************************************************************** */
/*          NodeVec         */

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept
{
    return ((this->idx * 2) + 1) < this->tree->dim;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept
{
    return ((this->idx * 2) + 2) < this->tree->dim;
}

template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeVec<Data>::NodeVec::LeftChild()
{
    if (!this->HasLeftChild())
    {
        throw std::out_of_range ("no left child");
    }

    return *(this->tree->vec->operator[]((this->idx * 2) + 1));
}

template <typename Data>
const typename BinaryTree<Data>::Node & BinaryTreeVec<Data>::NodeVec::LeftChild() const
{
    if (!this->HasLeftChild())
    {
        throw std::out_of_range ("no left child");
    }

    return *(this->tree->vec->operator[]((this->idx * 2) + 1));
}

template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeVec<Data>::NodeVec::RightChild()
{
    if (!this->HasRightChild())
    {
        throw std::out_of_range ("no right child");
    }

    return *(this->tree->vec->operator[]((this->idx * 2) + 2));
}

template <typename Data>
const typename BinaryTree<Data>::Node & BinaryTreeVec<Data>::NodeVec::RightChild() const
{
    if (!this->HasRightChild())
    {
        throw std::out_of_range ("no right child");
    }

    return *(this->tree->vec->operator[]((this->idx * 2) + 2));
}
/* ************************************************************************** */
/*          BinaryTreeVec         */

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec (const TraversableContainer<Data> & cont)
{
    this->size = cont.Size();

    if(this->size > 0) 
    {
        try
        {
            this->vec = new Vector<NodeVec*>(this->size);
        }
        catch(const std::bad_alloc & e)
        {
            throw;
        }
        
        
        unsigned long i = 0;
        cont.Traverse(
            [this, &i] (const Data & dat)
            {
                try
                {
                    NodeVec* node = new NodeVec(dat);
                    node->idx = i;
                    node->tree = this;
                    
                    this->vec->operator[](i) = node;
                }
                catch(const std::exception& e)
                {
                    throw;
                }

                i++;
            }
        );
    }    
    
    this->dim = this->size;
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec (MappableContainer<Data> && cont)
{
    this->size = cont.Size();

    if(this->size > 0) 
    {
        try
        {
            this->vec = new Vector<NodeVec*>(this->size);
        }
        catch(const std::bad_alloc & e)
        {
            throw;
        }
        
        unsigned long i = 0;
        cont.Traverse(
            [this, &i] (const Data & dat)
            {
                try
                {
                    NodeVec* node = new NodeVec(std::move(dat));
                    node->idx = i;
                    node->tree = this;
                    
                    this->vec->operator[](i) = node;
                }
                catch(const std::exception& e)
                {
                    throw;
                }
                

                i++;
            }
        );
    }    
    
    this->dim = this->size;
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec & that)
{
    if (that.size > 0)
    {
        try
        {
            this->vec = new Vector<NodeVec*>(that.size);
            
            for (unsigned long i = 0; i < that.size; i++)
            {
                if (i < that.dim)
                {
                    NodeVec * temp = that.vec->operator[](i);
                    NodeVec * curr = new NodeVec (*temp);
                    curr->tree = this;
                    this->vec->operator[](i) = curr;
                }
                else if (i < that.size)
                {
                    this->vec->operator[](i) = nullptr;
                }
            }
        }
        catch (std::exception & exc)
        {
            throw;
        }
    }    
    this->size = that.size;
    this->dim = that.dim;
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec && that) noexcept
{
    std::swap (this->vec, that.vec);
    std::swap (this->size, that.size);
    std::swap (this->dim, that.dim);
}

template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec()
{
    for (unsigned long i = 0; i < this->size; i++)
    {
        if (this->vec->operator[](i) != nullptr)
        {    
            delete this->vec->operator[](i);
        }
    }
    delete this->vec;
}

template <typename Data>
BinaryTreeVec<Data> BinaryTreeVec<Data>::operator=(const BinaryTreeVec & that)
{
    if (this->vec != nullptr)
    {
        this->Clear();
    }

    if (that.size > 0)
    {
        try
        {
            this->vec = new Vector<NodeVec*>(that.size);
            
            for (unsigned long i = 0; i < that.size; i++)
            {
                if (i < that.dim)
                {
                    NodeVec * temp = that.vec->operator[](i);
                    NodeVec * curr = new NodeVec (*temp);
                    curr->tree = this;
                    this->vec->operator[](i) = curr;
                }
                else if (i < that.size)
                {
                    this->vec->operator[](i) = nullptr;
                }
            }
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
    }    
    this->size = that.size;
    this->dim = that.dim;

    return *this;
}

template <typename Data>
BinaryTreeVec<Data> BinaryTreeVec<Data>::operator=(BinaryTreeVec && that)
{
    std::swap (this->vec, that.vec);
    std::swap (this->size, that.size);
    std::swap (this->dim, that.dim);

    return *this;
}

template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec & that)
{
    if (this->size != that.size || this->dim != that.dim)
    {
        return false;
    }
    else
    {
        for (unsigned int i = 0; i < this->size; i++)
        {
            if (*(this->vec->operator[](i)) != *(that.vec->operator[](i)))
            {
                return false;
            }   
        }
    }
    return true;
}

template <typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec & that)
{
    return !(this->operator==(that));
}

template <typename Data>
inline const typename BinaryTree<Data>::Node & BinaryTreeVec<Data>::Root() const
{
    if (this->Empty())
    {
        throw std::length_error ("no root: BinaryTreeVec is empty");
    }
    return *(this->vec->operator[](0));
}

template <typename Data>
inline typename MutableBinaryTree<Data>::MutableNode & BinaryTreeVec<Data>::Root()
{
    if (this->Empty())
    {
        throw std::length_error ("no root: BinaryTreeVec is empty");
    }
    return *(this->vec->operator[](0));
}

template <typename Data>
void BinaryTreeVec<Data>::Clear()
{   
    if (this->vec != nullptr)
    {
        for (unsigned long i = 0; i < this->size; i++)
        {
            if (this->vec->operator[](i) != nullptr)
            {    
                delete this->vec->operator[](i);
            }
        }
        delete this->vec;
        this->vec = nullptr;
    }
    this->dim = 0;
    this->size = 0;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::Empty() const noexcept
{
    return this->dim == 0 || this->vec == nullptr;
}

template <typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun fun) const
{
    for (unsigned long i = 0; i < this->dim; i++)
    {
        fun(this->vec->operator[](i)->Element());
    }
}

template <typename Data>
void BinaryTreeVec<Data>::BreadthMap(MapFun fun)
{
    for (unsigned long i = 0; i < this->dim; i++)
    {
        fun(this->vec->operator[](i)->Element());
    }
}
/* ************************************************************************** */
}
