
namespace lasd {

/* ************************************************************************** */
/*  Node  */

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node & that) const
{
    if (this->Element() != that.Element())
    {
        return false;
    }
    
    bool ret = true;

    if (this->HasLeftChild() && that.HasLeftChild())
    {
        ret &= this->LeftChild().operator==(that.LeftChild()) ; //ricorsione Sx 
    }
    else if (this->HasLeftChild() || that.HasLeftChild()) //se this ha figlio sx e that no, o viceversa
    {
        return false;
    }
    
    if (this->HasRightChild() && that.HasRightChild())
    {
        ret &= this->RightChild().operator==(that.RightChild()); //ricorsione Dx
    }
    else if (this->HasRightChild() || that.HasRightChild()) //se this ha figlio dx e that no, o viceversa
    {
        return false;
    }

    return ret;
}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node & that) const
{
    return !(this->operator==(that));
}

template <typename Data>
void BinaryTree<Data>::Node::PreOrderTraverse (TraverseFun traverseFun) const
{
    traverseFun(this->Element()); //visita in preorder
    
    if (this->HasLeftChild())
    {
        this->LeftChild().PreOrderTraverse(traverseFun); //chiamata a sinistra
    }    
    if (this->HasRightChild())
    {
        this->RightChild().PreOrderTraverse(traverseFun); //chiamata a destra
    }
}

template <typename Data>
void BinaryTree<Data>::Node::PostOrderTraverse (TraverseFun traverseFun) const
{
    if (this->HasLeftChild())
    {
        this->LeftChild().PostOrderTraverse(traverseFun); //chiamata a sinistra
    }    
    if (this->HasRightChild())
    {
        this->RightChild().PostOrderTraverse(traverseFun); //chiamata a destra
    }
    
    traverseFun(this->Element()); //visita in postorder
}

template <typename Data>
void BinaryTree<Data>::Node::InOrderTraverse (TraverseFun traverseFun) const
{
    if (this->HasLeftChild())
    {
        this->LeftChild().InOrderTraverse(traverseFun); //chiamata a sinistra
    }    

    traverseFun(this->Element()); //visita in order

    if (this->HasRightChild())
    {
        this->RightChild().InOrderTraverse(traverseFun); //chiamata a destra
    }
}

template <typename Data>
void BinaryTree<Data>::Node::BreadthTraverse (TraverseFun traverseFun) const
{
    QueueLst<const Node *> Q;
    Q.Enqueue(this);
    while (!Q.Empty())
    {
        const Node * curr = Q.Head();

        //Accoda figlio sx
        if (curr->HasLeftChild())
        {
            Q.Enqueue(& (curr->LeftChild()));
        }
        //Accoda figlio dx
        if (curr->HasRightChild())
        {
            Q.Enqueue(& (curr->RightChild()));
        }
        //visita curr
        traverseFun(curr->Element ());

        Q.Dequeue();
    } 
}

/* ************************************************************************** */
/*  BinaryTree  */

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree & that) const
{
    if (this->Empty() && that.Empty ())
    {
        return true;
    }
    else if (this->Empty() || that.Empty())
    {
        return false;
    }

    return this->Root() == that.Root();
}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree & that) const
{
    return !(this->operator==(that));
}

template <typename Data>
void BinaryTree<Data>::Traverse(TraverseFun traverseFun) const
{
    this->BreadthTraverse(traverseFun);
}

template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun traverseFun) const
{
    const Node * root = &(this->Root());
    if (root != nullptr)
        root->PreOrderTraverse(traverseFun);
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun traverseFun) const
{
    const Node * root = &(this->Root());
    if (root != nullptr)
        root->PostOrderTraverse(traverseFun);
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun traverseFun) const
{
    const Node * root = &(this->Root());
    if (root != nullptr)
        root->InOrderTraverse(traverseFun);
}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun traverseFun) const
{
    const Node * root = &(this->Root());
    if (root != nullptr)
        root->BreadthTraverse(traverseFun);
}

/* ************************************************************************** */
/*  Mutable Node  */

template <typename Data>
void MutableBinaryTree<Data>::MutableNode::PreOrderMap (MapFun mapFun)
{
    mapFun(this->Element()); //visita in preorder
    
    if (this->HasLeftChild())
    {
        this->LeftChild().PreOrderMap(mapFun); //chiamata a sinistra
    }    
    if (this->HasRightChild())
    {
        this->RightChild().PreOrderMap(mapFun); //chiamata a destra
    }
}

template <typename Data>
void MutableBinaryTree<Data>::MutableNode::PostOrderMap (MapFun mapFun)
{
    if (this->HasLeftChild())
    {
        this->LeftChild().PostOrderMap(mapFun); //chiamata a sinistra
    }    
    if (this->HasRightChild())
    {
        this->RightChild().PostOrderMap(mapFun); //chiamata a destra
    }
    
    mapFun(this->Element()); //visita in postorder
}

template <typename Data>
void MutableBinaryTree<Data>::MutableNode::InOrderMap (MapFun mapFun)
{
    if (this->HasLeftChild())
    {
        this->LeftChild().InOrderMap(mapFun); //chiamata a sinistra
    }    

    mapFun(this->Element()); //visita in order

    if (this->HasRightChild())
    {
        this->RightChild().InOrderMap(mapFun); //chiamata a destra
    }
}

template <typename Data>
void MutableBinaryTree<Data>::MutableNode::BreadthMap (MapFun mapFun)
{
    QueueLst<MutableNode *> Q;
    Q.Enqueue(this);
    while (!Q.Empty())
    {
        MutableNode * curr = Q.Head();

        //Accoda figlio sx
        if (curr->HasLeftChild())
        {
            Q.Enqueue(&(curr->LeftChild()));
        }
        //Accoda figlio dx
        if (curr->HasRightChild())
        {
            Q.Enqueue(&(curr->RightChild()));
        }
        //visita curr
        mapFun(curr->Element ());

        Q.Dequeue();
    } 
} 

/* ************************************************************************** */
/*  Mutable BinaryTree  */

template <typename Data>
void MutableBinaryTree<Data>::Map(MapFun mapFun)
{
    this->Root().BreadthMap(mapFun);
}

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun mapFun)
{
    this->Root().PreOrderMap(mapFun);
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun mapFun) 
{
    this->Root().PostOrderMap(mapFun);
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun mapFun) 
{
    this->Root().InOrderMap(mapFun);
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun mapFun) 
{
    this->Root().BreadthMap(mapFun);
}

}

/* ************************************************************************** */
/*  BTPreOrderIterator  */

// Copy assignment
// template <typename Data>
// BTPreOrderIterator<Data> BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data> & that)
// {
// this->root = that.root;
// this->curr = that.curr;
// this->stk = that.stk;

// return *this;
// }

// Move assignment
// template <typename Data>
// BTPreOrderIterator<Data> BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> && that) noexcept
// {
// std::swap (this->root, that.root);
// std::swap (this->curr, that.curr);
// std::swap (this->stk, that.stk);

// return *this;
// }


// Comparison operators
// template <typename Data>
// bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> & that) const
// {
// return (this->root == that.root) && (this->curr == that.curr) && (this->stk == that.stk);
// }

// template <typename Data>
// bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator & that) const
// {
// return !(this->operator==(that));
// }