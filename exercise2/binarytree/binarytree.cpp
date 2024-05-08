
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
        ret = that.LeftChild() == this->LeftChild(); //ricorsione Sx 
    }
    else if (this->HasLeftChild() != that.HasLeftChild()) //se this ha figlio sx e that no, o viceversa
    {
        return false;
    }
    
    if (this->HasRightChild() && that.HasRightChild())
    {
        ret = that.RightChild() == this->RightChild(); //ricorsione Dx
    }
    else if (this->HasRightChild() != that.HasRightChild()) //se this ha figlio dx e that no, o viceversa
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
    traverseFun(this->Element); //visita in preorder
    
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
    
    traverseFun(this->Element); //visita in postorder
}

template <typename Data>
void BinaryTree<Data>::Node::InOrderTraverse (TraverseFun traverseFun) const
{
    if (this->HasLeftChild())
    {
        this->LeftChild().InOrderTraverse(traverseFun); //chiamata a sinistra
    }    

    traverseFun(this->Element); //visita in order

    if (this->HasRightChild())
    {
        this->RightChild().InOrderTraverse(traverseFun); //chiamata a destra
    }
}

template <typename Data>
void BinaryTree<Data>::Node::BreadthTraverse (TraverseFun traverseFun) const
{
    Queue<Node> Q;
    Q.Enqueue(*this);
    while (!Q.Empty())
    {
        Node curr = Q.Head();

        //Accoda figlio sx
        if (curr.HasLeftChild())
        {
            Q.Enqueue(curr.LeftChild());
        }
        //Accoda figlio dx
        if (curr.HasRightChild())
        {
            Q.Enqueue(curr.RightChild());
        }
        //visita curr
        traverseFun(curr);

        Q.Dequeue();
    } 
}

/* ************************************************************************** */
/*  BinaryTree  */

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree & that) const
{
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
    this->Root().InOrderTraverse(traverseFun);
}

template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun traverseFun) const
{
    this->Root().PreOrderTraverse(traverseFun);
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun traverseFun) const
{
    this->Root().PostOrderTraverse(traverseFun);
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun traverseFun) const
{
    this->Root().InOrderTraverse(traverseFun);
}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun traverseFun) const
{
    this->Root().BreadthTraverse(traverseFun);
}

/* ************************************************************************** */

}
