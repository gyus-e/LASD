
namespace lasd {

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
