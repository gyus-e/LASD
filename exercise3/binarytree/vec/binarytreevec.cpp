
namespace lasd {

/* ************************************************************************** */
/*          NodeVec         */
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec (const Data & d) : elem (d), idx (0), tree (nullptr)
{}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec (Data && d) : elem (std::move(d)), idx (0), tree (nullptr)
{}
    
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec (const BinaryTreeVec<Data>::NodeVec & that) : elem(that.elem), idx(that.idx), tree(that.tree) 
{}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec (BinaryTreeVec<Data>::NodeVec && that) noexcept //: elem(std::move(that.elem))
{
    std::swap (this->elem, that.elem); 
    std::swap (this->idx, that.idx); 
    std::swap (this->tree, that.tree);
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator= (const BinaryTreeVec<Data>::NodeVec & that) 
{
    this->elem = that.elem;
    this->idx = that.idx;
    this->tree = that.tree; 
    return * this;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator= (BinaryTreeVec<Data>::NodeVec && that) 
{
    NodeVec toSwap (std::move(that)); 
    std::swap (*this, toSwap); 
    return * this;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::operator== (const BinaryTreeVec<Data>::NodeVec & that) const
{
    return (this->elem == that.elem) && (this->idx == that.idx);
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::operator!= (const BinaryTreeVec<Data>::NodeVec & that) const
{
    return !(this->operator==(that));
}

template <typename Data>
inline Data & BinaryTreeVec<Data>::NodeVec::Element () 
{
    return this->elem;
}

template <typename Data>
inline const Data & BinaryTreeVec<Data>::NodeVec::Element () const
{
    return this->elem;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept
{
    return !(this->HasLeftChild() || this->HasRightChild());
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept
{
    if (this->tree == nullptr)
    {
        return false;
    }
    return ((this->idx * 2) + 1) < this->tree->size;
}

template <typename Data>
inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept
{
    if (this->tree == nullptr)
    {
        return false;
    }
    return ((this->idx * 2) + 2) < this->tree->size;
}

template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeVec<Data>::NodeVec::LeftChild()
{
    if (!this->HasLeftChild())
    {
        throw std::out_of_range ("no left child");
    }
    return this->tree->vec[(this->idx * 2) + 1];
}

template <typename Data>
const typename BinaryTree<Data>::Node & BinaryTreeVec<Data>::NodeVec::LeftChild() const
{
    if (!this->HasLeftChild())
    {
        throw std::out_of_range ("no left child");
    }

    return this->tree->vec[(this->idx * 2) + 1];
}

template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeVec<Data>::NodeVec::RightChild()
{
    if (!this->HasRightChild())
    {
        throw std::out_of_range ("no right child");
    }

    return this->tree->vec[(this->idx * 2) + 2];
}

template <typename Data>
const typename BinaryTree<Data>::Node & BinaryTreeVec<Data>::NodeVec::RightChild() const
{
    if (!this->HasRightChild())
    {
        throw std::out_of_range ("no right child");
    }

    return this->tree->vec[(this->idx * 2) + 2];
}
/* ************************************************************************** */
/*          BinaryTreeVec         */

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec (const TraversableContainer<Data> & cont) : vec (cont.Size())
{
    this->vecSize = this->vec.Size();
    this->size = 0;

    if(!cont.Empty()) 
    {       
        unsigned long i = 0;
        cont.Traverse(
            [this, &i] (const Data & dat)
            {
                this->vec[i].elem = dat;
                this->vec[i].idx = i;
                this->vec[i].tree = this;
                this->size++;
                i++;
            }
        );
    }    
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec (MappableContainer<Data> && cont) : vec (cont.Size())
{
    this->vecSize = this->vec.Size();
    this->size = 0;

    if(!cont.Empty()) 
    {       
        unsigned long i = 0;
        cont.Map(
            [this, &i] (Data & dat)
            {
                this->vec[i].elem = std::move(dat);
                this->vec[i].idx = i;
                this->vec[i].tree = this;
                this->size++;
                i++;
            }
        );
    }    
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec & that)
{
    this->vec = that.vec;
    this->vecSize = this->vec.Size();
    this->size = that.size;
    
    if (!this->vec.Empty())
    {
        unsigned long i = 0;
        this->vec.PreOrderMap(
            [this, &i](NodeVec & node)
            {
                node.tree = this;
                node.idx = i++;
            }
        );
    }

}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec && that) noexcept //: vec (std::move(that.vec)), size (that.size), vecSize (that.vecSize)
{
    std::swap (this->vec, that.vec);
    std::swap (this->vecSize, that.vecSize);
    std::swap (this->size, that.size);
    if (!this->vec.Empty())
    {
        this->vec.Map(
            [this] (NodeVec & node)
            {
                node.tree = this;
            }
        );
    }
}

template <typename Data>
BinaryTreeVec<Data> & BinaryTreeVec<Data>::operator=(const BinaryTreeVec & that)
{
    if (*this != that)
    {
        if (!(this->Empty()))
        {
            this->Clear();
        }
    
        this->vec = that.vec;
        this->vecSize = this->vec.Size();
        this->size = that.size;
    
        if (!this->vec.Empty())
        {
            unsigned long i = 0;
            this->vec.PreOrderMap(
                [this, &i](NodeVec & node)
                {
                    node.tree = this;
                    node.idx = i++;
                }
            );
        }
    }
    return *this;
}

template <typename Data>
BinaryTreeVec<Data> & BinaryTreeVec<Data>::operator=(BinaryTreeVec && that)
{
    if (*this != that)
    {
        if (!(this->Empty()))
        {
            this->Clear();
        }

        std::swap (this->vec, that.vec);
        std::swap (this->vecSize, that.vecSize);
        std::swap (this->size, that.size);
        if (!this->vec.Empty())
        {
            this->vec.Map(
                [this] (NodeVec & node)
                {
                    node.tree = this;
                }
            );
        }
        }
    return *this;
}

template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec & that)
{
    if (this->Empty() || that.Empty())
    {
        return this->Empty() && that.Empty();
    }

    if (this->size != that.size) // || this->vecSize != that.vecSize 
    {
        return false;
    }
    
    for (unsigned int i = 0; i < this->size; i++)
    {
        if ((this->vec[i].elem) != (that.vec[i].elem))
        {
            return false;
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
    return this->vec[0];
}

template <typename Data>
inline typename MutableBinaryTree<Data>::MutableNode & BinaryTreeVec<Data>::Root()
{
    if (this->Empty())
    {
        throw std::length_error ("no root: BinaryTreeVec is empty");
    }
    return this->vec[0];
}

template <typename Data>
void BinaryTreeVec<Data>::Clear()
{   
    if (!this->Empty())
    {
        this->vec.Clear();
        this->size = 0;
        this->vecSize = this->vec.Size();
    }
}

template <typename Data>
inline bool BinaryTreeVec<Data>::Empty() const noexcept
{
    return this->vec.Empty() && this->size == 0;
}

template <typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun fun) const
{
    for (unsigned long i = 0; i < this->size; i++)
    {
        fun(this->vec[i].Element());
    }
}

template <typename Data>
void BinaryTreeVec<Data>::BreadthMap(MapFun fun)
{
    if (!this->vec.Empty())
    {
        for (unsigned long i = 0; i < this->size; i++)
        {
            fun(this->vec[i].Element());
        }
    }
}
/* ************************************************************************** */
}
