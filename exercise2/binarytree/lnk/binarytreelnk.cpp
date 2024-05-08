
namespace lasd {

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk (const NodeLnk & that)
{
    this->elem = that.elem;

    if (that.HasLeftChild())
    {
        try 
        {
            this->Sx = new NodeLnk (that.Sx);
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
    }
    else 
    {
        this->Sx = nullptr;
    }

    if (that.HasRightChild())
    {
        try 
        {
            this->Dx = new NodeLnk (that.Dx);
        }
        catch (std::bad_alloc & exc)
        {
            throw;
        }
    }
    else 
    {
        this->Dx = nullptr;
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
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::LeftChild ()
{
    if (this->HasLeftChild())
    {
        return this->Sx;
    } 
    else 
    {
        throw std::out_of_range ("left child does not exist.");
    }
} 

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::RightChild ()
{
    if (this->HasRightChild())
    {
        return this->Dx;
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
    this->root = new NodeLnk (that.root);
}

//Copy assignment
template <typename Data>
BinaryTreeLnk<Data> BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk & that)
{
    this->root = new NodeLnk (that.root);
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
    return this->root->operator==(that.root);
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk & that)
{
    return this->root->operator!=(that.root);
}

template <typename Data>
const Data & BinaryTreeLnk<Data>::Root() const
{
    return this->root;
}

template <typename Data>
Data & BinaryTreeLnk<Data>::Root()
{
    return this->root;
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
