
namespace lasd {

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk () 
{
    if (this->Sx != nullptr) 
    {
        delete this->Sx;
    } 
    if (this->Dx != nullptr) 
    {
        delete this->Dx;
    }

    // delete this;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk (const NodeLnk & that)
{
    this->elem = that.elem;

    if (that.HasLeftChild())
    {
        try 
        {
            this->Sx = new NodeLnk (*that.Sx);
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
    }

    if (that.HasRightChild())
    {
        try 
        {
            this->Dx = new NodeLnk (*that.Dx);
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
    }
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk (NodeLnk && that) noexcept
{
    std::swap (this->elem, that.elem);
    std::swap (this->Sx, that.Sx);
    std::swap (this->Dx, that.Dx);
}

template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::NodeLnk::LeftChild() 
{
    if (this->HasLeftChild())
    {
        return *(this->Sx);
    } 
    else 
    {
        throw std::out_of_range ("left child does not exist.");
    }
} 

template <typename Data>
const typename BinaryTree<Data>::Node & BinaryTreeLnk<Data>::NodeLnk::LeftChild () const
{
    if (this->HasLeftChild())
    {
        return *(this->Sx);
    } 
    else 
    {
        throw std::out_of_range ("left child does not exist.");
    }
} 

template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::NodeLnk::RightChild ()
{
    if (this->HasRightChild())
    {
        return *(this->Dx);
    } 
    else 
    {
        throw std::out_of_range ("right child does not exist.");
    }
} 

template <typename Data>
const typename BinaryTree<Data>::Node & BinaryTreeLnk<Data>::NodeLnk::RightChild () const
{
    if (this->HasRightChild())
    {
        return *(this->Dx);
    } 
    else 
    {
        throw std::out_of_range ("right child does not exist.");
    }
} 

/* ************************************************************************** */

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk()
{
    if (this->root != nullptr)
    {
        delete this->root;
        this->root = nullptr;
    }
}

// A binary tree obtained from a TraversableContainer
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk (const TraversableContainer<Data> & con)
{
    this->size = con.Size();
  
    if (this->size > 0)
    {
        QueueLst<NodeLnk **> Q;
        Q.Enqueue (&(this->root));

        con.Traverse (
            [&Q] (const Data & d)
            {
                NodeLnk ** temp = (Q.HeadNDequeue());

                *temp = new NodeLnk (d);

                Q.Enqueue (&((*temp)->Sx));
                Q.Enqueue (&((*temp)->Dx));
            }
        );
    }
}


// A binary tree obtained from a MappableContainer
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk (MappableContainer<Data> & con)
{
    this->size = con.Size();
  
    if (this->size > 0)
    {
        QueueLst<NodeLnk **> Q;
        Q.Enqueue (&(this->root));

        con.Map (
            [&Q] (Data & d)
            {
                NodeLnk ** temp = (Q.HeadNDequeue());

                *temp = new NodeLnk (std::move(d));

                Q.Enqueue (&((*temp)->Sx));
                Q.Enqueue (&((*temp)->Dx));
            }
        );
    }
}

//Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk & that)
{
    this->root = new NodeLnk (*that.root);
    this->size = that.size;
}

//Copy assignment
template <typename Data>
BinaryTreeLnk<Data> BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk & that)
{
    this->root = new NodeLnk (*that.root);
    this->size = that.size;
    return *this;
}

//Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk (BinaryTreeLnk && that) noexcept
{
    std::swap (this->root, that.root);
    std::swap (this->size, that.size);
}

//Move assignment
template <typename Data>
BinaryTreeLnk<Data> BinaryTreeLnk<Data>::operator=(BinaryTreeLnk && that)
{
    std::swap (this->root, that.root);
    std::swap (this->size, that.size);
    return *this;
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk & that)
{
    return (*(this->root) == *(that.root));
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk & that)
{
    return (*(this->root) != *(that.root));
}

template <typename Data>
inline const typename BinaryTree<Data>::Node & BinaryTreeLnk<Data>::Root() const
{
    if (this->root == nullptr)
    {
        throw std::length_error ("no root: BinaryTreeLnk is empty");
    }    
    return *(this->root);
}

template <typename Data>
inline typename MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::Root()
{
    if (this->root == nullptr)
    {
        throw std::length_error ("no root: BinaryTreeLnk is empty");
    }  
    return *(this->root);
}

template <typename Data>
void BinaryTreeLnk<Data>::Clear()
{
    if (this->root != nullptr)
    {
        delete this->root;
        this->root = nullptr;
    }
    this->size = 0;
}

template <typename Data>
inline bool BinaryTreeLnk<Data>::Empty() const noexcept
{
    return this->root == nullptr;
}
/* ************************************************************************** */

}
