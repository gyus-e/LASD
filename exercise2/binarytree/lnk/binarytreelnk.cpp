
namespace lasd {

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk () 
{
    if (this->HasLeftChild()) 
    {
        delete this->Sx;
    } 
    if (this->HasRightChild()) 
    {
        delete this->Dx;
    }
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
MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::NodeLnk::LeftChild() 
{
    if (this->HasLeftChild())
    {
        return *Sx;
    } 
    else 
    {
        throw std::out_of_range ("left child does not exist.");
    }
} 

template <typename Data>
const BinaryTree<Data>::Node & BinaryTreeLnk<Data>::NodeLnk::LeftChild () const
{
    if (this->HasLeftChild())
    {
        return *Sx;
    } 
    else 
    {
        throw std::out_of_range ("left child does not exist.");
    }
} 

template <typename Data>
MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::NodeLnk::RightChild ()
{
    if (this->HasRightChild())
    {
        return *Dx;
    } 
    else 
    {
        throw std::out_of_range ("right child does not exist.");
    }
} 

template <typename Data>
const BinaryTree<Data>::Node & BinaryTreeLnk<Data>::NodeLnk::RightChild () const
{
    if (this->HasRightChild())
    {
        return *Dx;
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

//Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk & that)
{
    this->root = new NodeLnk (*that.root);
}

//Copy assignment
template <typename Data>
BinaryTreeLnk<Data> BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk & that)
{
    this->root = new NodeLnk (*that.root);
    return *this;
}

//Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk (BinaryTreeLnk && that) noexcept
{
    std::swap (this->root, that.root);
}

//Move assignment
template <typename Data>
BinaryTreeLnk<Data> BinaryTreeLnk<Data>::operator=(BinaryTreeLnk && that)
{
    std::swap (this->root, that.root);
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
const BinaryTree<Data>::Node & BinaryTreeLnk<Data>::Root() const
{
    return *root;
}

template <typename Data>
MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::Root()
{
    return *root;
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

/* ************************************************************************** */

}
