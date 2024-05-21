
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

/* ************************************************************************** */
/*  BTPreOrderIterator  */

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator (const BinaryTree<Data> & binTree)
{
    if (binTree.Size() != 0)
    {
        this->root = &binTree.Root();
        this->curr = this->root;
    }
}

// Copy assignment
template <typename Data>
BTPreOrderIterator<Data> BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data> & that)
{
    this->root = that.root;
    this->curr = that.curr;
    this->stk = that.stk;

    return *this;
}

// Move assignment
template <typename Data>
BTPreOrderIterator<Data> BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> && that) noexcept
{
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);

    return *this;
}

// Comparison operators
template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> & that) const
{
    return (this->root == that.root) && (this->curr == that.curr) && (this->stk == that.stk);
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator & that) const
{
    return !(this->operator==(that));
}

template <typename Data>
const Data & BTPreOrderIterator<Data>::operator*() const // (throw std::out_of_range when terminated)
{
    if (this->Terminated())
    {
        throw std::out_of_range("from operator *");
    }
    return this->curr->Element();   
}

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept // (should not throw exceptions)
{
    return (this->curr==nullptr);
}

template <typename Data>
BTPreOrderIterator<Data> & BTPreOrderIterator<Data>::operator++() // (throw std::out_of_range when terminated)
{
    if (this->Terminated())
    {
        throw std::out_of_range("from operator++");
    }

    //curr inizia dalla radice

    //prima spingo il figlio destro
    if (this->curr->HasRightChild())
    {
        this->stk.Push(&(this->curr->RightChild()));
    }
    //poi spingo il figlio sinistro in cima allo stack
    if (this->curr->HasLeftChild())
    {
        this->stk.Push(&(this->curr->LeftChild()));
    } 
    //se lo stack è vuoto, non ci sono altri nodi da visitare
    if (this->stk.Empty())
    {
        this->curr = nullptr;
    }
    //altrimenti, curr passa al nodo in cima allo stack
    else 
    {
        this->curr = this->stk.Top();
        this->stk.Pop();
    }
    return *this;
}

template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept // (should not throw exceptions)
{
    this->stk.Clear();
    this->curr = this->root;
}

/* ************************************************************************** */
/*  BTPreOrderMutableIterator  */

// Copy assignment
template <typename Data>
BTPreOrderMutableIterator<Data>  BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator & that)
{
    this->BTPreOrderIterator<Data>::operator=(that);
}

// Move assignment
template <typename Data>
BTPreOrderMutableIterator<Data> BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator && that)
{
    this->BTPreOrderIterator<Data>::operator=(std::move(that));
}

// Comparison operators
template <typename Data>
bool BTPreOrderMutableIterator<Data>::operator==(const BTPreOrderMutableIterator & that) const
{
    return this->BTPreOrderIterator<Data>::operator==((const BTPreOrderIterator<Data> &) that);
}

template <typename Data>
bool BTPreOrderMutableIterator<Data>::operator!=(const BTPreOrderMutableIterator & that) const
{
    return this->BTPreOrderIterator<Data>::operator!=((const BTPreOrderIterator<Data> &) that);
}

template <typename Data>
Data & BTPreOrderMutableIterator<Data>::operator*()  // (throw std::out_of_range when terminated)
{
    if (this->Terminated())
    {
        throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
}

/* ************************************************************************** */
/*  BTPostOrderIterator  */

template <typename Data>
void BTPostOrderIterator<Data>::toLeftMostLeaf()
{
    if (this->curr == nullptr)
    {
        return;
        // throw std::out_of_range("from toLeftMostLeaf");
    }

    while (!this->curr->IsLeaf())
    {
        //scendo a sinistra, se possibile
        if (this->curr->HasLeftChild())
        {
        this->stk.Push(this->curr);
        this->curr = & this->curr->LeftChild();
        }
        //altrimenti scendo a destra
        else if (this->curr->HasRightChild())
        {
        this->stk.Push(this->curr);
        this->curr = & this->curr->RightChild();
        }      
    }
}

// Specific constructors
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator (const BinaryTree<Data> & binTree) // An iterator over a given binary tree
{
    if (binTree.Size() != 0)
    {
        this->root = &binTree.Root();
        this->curr = this->root;
        this->toLeftMostLeaf();
    }
}

// Copy assignment
template <typename Data>
BTPostOrderIterator<Data> BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data> & that)
{
    this->root = that.root;
    this->curr = that.curr;
    this->stk = that.stk;

    return *this;
}

// Move assignment
template <typename Data>
BTPostOrderIterator<Data> BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data> && that) noexcept
{
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);

    return *this;
}

// Comparison operators
template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data> & that) const
{
    return ((this->root == that.root) && (this->curr == that.curr) && (this->stk == that.stk));
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data> & that) const
{
    return !(this->operator==(that));
}

// Specific member functions (inherited from Iterator)

template <typename Data>
const Data & BTPostOrderIterator<Data>::operator*() const // (throw std::out_of_range when terminated)
{
    if (this->Terminated())
    {
        throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept // (should not throw exceptions)
{
    return (this->curr==nullptr);
}

// Specific member functions (inherited from ForwardIterator)

template <typename Data>
BTPostOrderIterator<Data> & BTPostOrderIterator<Data>::operator++() // (throw std::out_of_range when terminated)
{
    if (this->Terminated())
    {
        throw std::out_of_range("from operator++");
    }

    //curr inizia dalla foglia piú a sinistra (NB! non dal nodo piú a sinistra)

    if (!stk.Empty())
    {
        //il top dello stack è il fratello sinistro di curr, oppure il padre
        const typename BinaryTree<Data>::Node* top = this->stk.Top();

        //se top è il fratello sinistro di curr
        if (top->HasRightChild() && this->curr != &(top->RightChild()))
        {
            //curr si sposta sul fratello sinistro
            this->curr = & (top->RightChild());
            //e poi sulla foglia piú a sinistra del sottoablero radicato in curr, aggiungendo allo stack i nodi attraversati
            this->toLeftMostLeaf();
        }

        //altrimenti, se top è il padre di curr, basta visitarlo
        else 
        {
            this->curr = top;
            this->stk.Pop();
        }
    }
    //se lo stack è vuoto, l'iteratore è terminato
    else 
    {
        this->curr = nullptr;
    }
    return *this;
}

// Specific member functions (inherited from ResettableIterator)

template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept // (should not throw exceptions)
{
    this->stk.Clear();
    this->curr = this->root;
    this->toLeftMostLeaf();
}

/* ************************************************************************** */
/*  BTPostOrderMutableIterator  */

// Copy assignment
template <typename Data>
BTPostOrderMutableIterator<Data>  BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator & that)
{
    this->BTPostOrderIterator<Data>::operator=(that);
}

// Move assignment
template <typename Data>
BTPostOrderMutableIterator<Data> BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator && that)
{
    this->BTPostOrderIterator<Data>::operator=(std::move(that));
}

// Comparison operators
template <typename Data>
bool BTPostOrderMutableIterator<Data>::operator==(const BTPostOrderMutableIterator & that) const
{
    return this->BTPostOrderIterator<Data>::operator==((const BTPostOrderIterator<Data> &) that);
}

template <typename Data>
bool BTPostOrderMutableIterator<Data>::operator!=(const BTPostOrderMutableIterator & that) const
{
    return this->BTPostOrderIterator<Data>::operator!=((const BTPostOrderIterator<Data> &) that);
}

template <typename Data>
Data & BTPostOrderMutableIterator<Data>::operator*()  // (throw std::out_of_range when terminated)
{
    if (this->Terminated())
    {
        throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
}

/* ************************************************************************** */
/*  BTInOrderIterator  */

template <typename Data>
void BTInOrderIterator<Data>::toLeftMostNode ()
{
    if (this->curr == nullptr)
    {
        return;
        // throw std::out_of_range("from toLeftMostNode: curr is nullptr");
    }

    //scendo sempre a sinistra finché possibile
    while (this->curr->HasLeftChild())
    {
        if (this->curr->HasLeftChild())
        {
        this->stk.Push(this->curr);
        this->curr = & this->curr->LeftChild();
        // throw std::logic_error("from toLeftMostNode: curr has no left child");
        }
        
    }

    return;
}

// Specific constructors
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> & binTree) // An iterator over a given binary tree
{
    if (binTree.Size() != 0)
    {
        this->root = &binTree.Root();
        this->curr = this->root;
        this->toLeftMostNode();
    }
}

// Copy assignment
template <typename Data>
BTInOrderIterator<Data> BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data> & that)
{
    this->root = that.root;
    this->curr = that.curr;
    this->stk = that.stk;

    return *this;
}

// Move assignment
template <typename Data>
BTInOrderIterator<Data> BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data> && that) noexcept
{
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);

    return *this;
}

// Comparison operators

template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data> & that) const
{
    return ((this->root == that.root) && (this->curr == that.curr) && (this->stk == that.stk));
}

template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data> & that) const
{
    return !(this->operator==(that));
}

template <typename Data>
const Data & BTInOrderIterator<Data>::operator*() const // (throw std::out_of_range when terminated)
{
    if (this->Terminated())
    {
        throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept // (should not throw exceptions)
{
    return (this->curr==nullptr);
}

template <typename Data>
BTInOrderIterator<Data> & BTInOrderIterator<Data>::operator++() // (throw std::out_of_range when terminated)
{
    if (this->Terminated())
    {
        throw std::out_of_range("from operator++");
    }

    //curr inizia dal nodo piú a sinistra (minimo)

    //se puó scendere a destra, lo fa partendo dal minimo del sottoalbero destro
    if (this->curr->HasRightChild())
    {
        this->curr = & (this->curr->RightChild());
        this->toLeftMostNode();
    }
    else 
    {
        //recupera il padre dallo stack, se presente
        if (!stk.Empty())
        {
            this->curr = this->stk.Top();
            this->stk.Pop();
        }
        //altrimenti l'iteratore è terminato
        else 
        {
            this->curr = nullptr;
        }
    }
    return *this;
}

template <typename Data>
void BTInOrderIterator<Data>::Reset() noexcept // (should not throw exceptions)
{
    this->stk.Clear();
    this->curr = this->root;
    this->toLeftMostNode();
}

/* ************************************************************************** */
/*  BTInOrderMutableIterator  */


/* ************************************************************************** */
/*  BTBreadthIterator  */


/* ************************************************************************** */
/*  BTBreadthMutableIterator  */


}