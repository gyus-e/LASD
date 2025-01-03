
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
        ret &= (this->LeftChild() == that.LeftChild()) ; 
    }
    else if (this->HasLeftChild() || that.HasLeftChild()) 
    {
        return false;
    }
    
    if (this->HasRightChild() && that.HasRightChild())
    {
        ret &= (this->RightChild() == that.RightChild()); 
    }
    else if (this->HasRightChild() || that.HasRightChild()) 
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
    traverseFun(this->Element());
    
    if (this->HasLeftChild())
    {
        this->LeftChild().PreOrderTraverse(traverseFun); 
    }    
    if (this->HasRightChild())
    {
        this->RightChild().PreOrderTraverse(traverseFun); 
    }
}

template <typename Data>
void BinaryTree<Data>::Node::PostOrderTraverse (TraverseFun traverseFun) const
{
    if (this->HasLeftChild())
    {
        this->LeftChild().PostOrderTraverse(traverseFun);
    }    
    if (this->HasRightChild())
    {
        this->RightChild().PostOrderTraverse(traverseFun);
    }
    
    traverseFun(this->Element());
}

template <typename Data>
void BinaryTree<Data>::Node::InOrderTraverse (TraverseFun traverseFun) const
{
    if (this->HasLeftChild())
    {
        this->LeftChild().InOrderTraverse(traverseFun); 
    }    

    traverseFun(this->Element()); 

    if (this->HasRightChild())
    {
        this->RightChild().InOrderTraverse(traverseFun);
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

        if (curr->HasLeftChild())
        {
            Q.Enqueue(& (curr->LeftChild()));
        }
        if (curr->HasRightChild())
        {
            Q.Enqueue(& (curr->RightChild()));
        }
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

    if (this->size != that.size)
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
    if (!this->Empty())
    {    
        this->BreadthTraverse(traverseFun);
    }
}

template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun traverseFun) const
{
    if (!this->Empty())
    {
        this->Root().PreOrderTraverse(traverseFun);
    }
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun traverseFun) const
{
    if (!this->Empty())
    {
        this->Root().PostOrderTraverse(traverseFun);
    }
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun traverseFun) const
{
    if (!this->Empty())
    {
        this->Root().InOrderTraverse(traverseFun);
    }
}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun traverseFun) const
{
    if (!this->Empty())
    {
        this->Root().BreadthTraverse(traverseFun);
    }
}

/* ************************************************************************** */
/*  Mutable Node  */

template <typename Data>
void MutableBinaryTree<Data>::MutableNode::PreOrderMap (MapFun mapFun)
{
    mapFun(this->Element()); 
    
    if (this->HasLeftChild())
    {
        this->LeftChild().PreOrderMap(mapFun); 
    }    
    if (this->HasRightChild())
    {
        this->RightChild().PreOrderMap(mapFun); 
    }
}

template <typename Data>
void MutableBinaryTree<Data>::MutableNode::PostOrderMap (MapFun mapFun)
{
    if (this->HasLeftChild())
    {
        this->LeftChild().PostOrderMap(mapFun); 
    }    
    if (this->HasRightChild())
    {
        this->RightChild().PostOrderMap(mapFun); 
    }
    
    mapFun(this->Element()); 
}

template <typename Data>
void MutableBinaryTree<Data>::MutableNode::InOrderMap (MapFun mapFun)
{
    if (this->HasLeftChild())
    {
        this->LeftChild().InOrderMap(mapFun); 
    }    

    mapFun(this->Element()); 

    if (this->HasRightChild())
    {
        this->RightChild().InOrderMap(mapFun);
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

        if (curr->HasLeftChild())
        {
            Q.Enqueue(&(curr->LeftChild()));
        }
        if (curr->HasRightChild())
        {
            Q.Enqueue(&(curr->RightChild()));
        }
        mapFun(curr->Element ());

        Q.Dequeue();
    } 
} 

/* ************************************************************************** */
/*  Mutable BinaryTree  */

template <typename Data>
void MutableBinaryTree<Data>::Map(MapFun mapFun)
{
    if (!this->Empty())
    {
        this->BreadthMap(mapFun);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun mapFun)
{
    if (!this->Empty())
    {
        this->Root().PreOrderMap(mapFun);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun mapFun) 
{
    if (!this->Empty())
    {
        this->Root().PostOrderMap(mapFun);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun mapFun) 
{
    if (!this->Empty())
    {    
        this->Root().InOrderMap(mapFun);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun mapFun) 
{
    if (!this->Empty())
    {    
        this->Root().BreadthMap(mapFun);
    }
}

/* ************************************************************************** */
/*  BTPreOrderIterator  */

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator (const BinaryTree<Data> & binTree)
{
    if (!binTree.Empty())
    {
        this->root = &binTree.Root();
        this->curr = this->root;
    }
}

// Copy assignment
template <typename Data>
BTPreOrderIterator<Data> & BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data> & that)
{
    this->root = that.root;
    this->curr = that.curr;
    this->stk = that.stk;

    return *this;
}

// Move assignment
template <typename Data>
BTPreOrderIterator<Data> & BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> && that) noexcept
{
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);

    that.root = nullptr;
    that.curr = nullptr;
    that.stk.Clear();

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
    return this->stk.Empty() && (this->curr==nullptr);
}

template <typename Data>
BTPreOrderIterator<Data> & BTPreOrderIterator<Data>::operator++() // (throw std::out_of_range when terminated)
{
    if (this->Terminated())
    {
        throw std::out_of_range("from operator++");
    }

    if (this->curr->HasRightChild())
    {
        this->stk.Push(&(this->curr->RightChild()));
    }
    if (this->curr->HasLeftChild())
    {
        this->stk.Push(&(this->curr->LeftChild()));
    } 
    if (this->stk.Empty())
    {
        this->curr = nullptr;
    }
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
BTPreOrderMutableIterator<Data>  & BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator & that)
{
    this->BTPreOrderIterator<Data>::operator=(that);
}

// Move assignment
template <typename Data>
BTPreOrderMutableIterator<Data> & BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator && that)
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
    return const_cast<Data&> (this->curr->Element());
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
        if (this->curr->HasLeftChild())
        {
            this->stk.Push(this->curr);
            this->curr = & this->curr->LeftChild();
        }
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
BTPostOrderIterator<Data> & BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data> & that)
{
    this->root = that.root;
    this->curr = that.curr;
    this->stk = that.stk;

    return *this;
}

// Move assignment
template <typename Data>
BTPostOrderIterator<Data> & BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data> && that) noexcept
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

    if (!stk.Empty())
    {
        const typename BinaryTree<Data>::Node* top = this->stk.Top();

        if (top->HasRightChild() && this->curr != &(top->RightChild()))
        {
            this->curr = & (top->RightChild());
            this->toLeftMostLeaf();
        }

        else 
        {
            this->curr = top;
            this->stk.Pop();
        }
    }
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
BTPostOrderMutableIterator<Data> & BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator & that)
{
    this->BTPostOrderIterator<Data>::operator=(that);
}

// Move assignment
template <typename Data>
BTPostOrderMutableIterator<Data> & BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator && that)
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
    return const_cast<Data&> (this->curr->Element());
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

    while (this->curr->HasLeftChild())
    {
        this->stk.Push(this->curr);
        this->curr = &(this->curr->LeftChild());
        // throw std::logic_error("from toLeftMostNode: curr has no left child");        
    }
    return;
}

// Specific constructors
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> & binTree) // An iterator over a given binary tree
{
    if (!binTree.Empty())
    {
        this->root = &(binTree.Root());
        this->curr = this->root;
        this->toLeftMostNode();
    }
}

// Copy assignment
template <typename Data>
BTInOrderIterator<Data> & BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data> & that)
{
    this->root = that.root;
    this->curr = that.curr;
    this->stk = that.stk;

    return *this;
}

// Move assignment
template <typename Data>
BTInOrderIterator<Data> & BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data> && that) noexcept
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

    if (this->curr->HasRightChild())
    {
        this->curr = & (this->curr->RightChild());
        this->toLeftMostNode();
    }
    else 
    {
        if (!stk.Empty())
        {
            this->curr = this->stk.Top();
            this->stk.Pop();
        }
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

  // Copy assignment
  template <typename Data>
  BTInOrderMutableIterator<Data> & BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator & that)
  {
    this->BTInOrderIterator<Data>::operator=(that);
  }

  // Move assignment
  template <typename Data>
  BTInOrderMutableIterator<Data> & BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator<Data> && that)
  {
    this->BTInOrderIterator<Data>::operator=(std::move(that));
  }

  // Comparison operators
  template <typename Data>
  bool BTInOrderMutableIterator<Data>::operator==(const BTInOrderMutableIterator<Data> & that) const
  {
    return this->BTInOrderIterator<Data>::operator==((const BTInOrderIterator<Data> &) that);
  }

  template <typename Data>
  bool BTInOrderMutableIterator<Data>::operator!=(const BTInOrderMutableIterator<Data> & that) const
  {
    return this->BTInOrderIterator<Data>::operator!=((const BTInOrderIterator<Data> &) that);
  }

  // Specific member functions (inherited from MutableIterator)

  template <typename Data>
  Data & BTInOrderMutableIterator<Data>::operator*() // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return const_cast<Data&> (this->curr->Element());
  }

/* ************************************************************************** */
/*  BTBreadthIterator  */
  template <typename Data>
  BTBreadthIterator<Data>::BTBreadthIterator (const BinaryTree<Data> & binTree) // An iterator over a given binary tree
  {
    if (binTree.Size() != 0)
    {
        this->root = &binTree.Root();
        this->curr = this->root;
    }
  }

  // Copy assignment
  template <typename Data>
  BTBreadthIterator<Data> & BTBreadthIterator<Data>::operator=(const BTBreadthIterator & that)
  {
    this->root = that.root;
    this->curr = that.curr;
    this->que = that.que;

    return *this;
  }

  // Move assignment
  template <typename Data>
  BTBreadthIterator<Data> & BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data> && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->que, that.que);
    
    return *this;
  }

  // Comparison operators
  template <typename Data>
  bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator & that) const
  {
    return ((this->root == that.root) && (this->curr == that.curr) && (this->que == that.que));
  }
  
  template <typename Data>
  bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator & that) const
  {
    return !(this->operator==(that));
  }

  // Specific member functions (inherited from Iterator)
  template <typename Data>
  const Data & BTBreadthIterator<Data>::operator*() const // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
  }

  template <typename Data>
  bool BTBreadthIterator<Data>::Terminated() const noexcept // (should not throw exceptions)
  {
    return (this->curr == nullptr);
  }

  // Specific member functions (inherited from ForwardIterator)
  template <typename Data>
  BTBreadthIterator<Data> & BTBreadthIterator<Data>::operator++() // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator++");
    }
    if (this->curr->HasLeftChild())
    {
      this->que.Enqueue(&(this->curr->LeftChild()));
    }
    if (this->curr->HasRightChild())
    {
      this->que.Enqueue(&(this->curr->RightChild()));
    }

    if (!this->que.Empty())
    {
      this->curr = this->que.HeadNDequeue();
    }
    else 
    {
      this->curr = nullptr; 
    }

    return *this;
  }
  
  template <typename Data>
  void BTBreadthIterator<Data>::Reset() noexcept // (should not throw exceptions)
  {
    this->que.Clear();
    this->curr = this->root;
  }

/* ************************************************************************** */
/*  BTBreadthMutableIterator  */

  // Copy assignment
  template <typename Data>
  BTBreadthMutableIterator<Data> & BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator<Data> & that)
  {
    this->BTBreadthIterator<Data>::operator=(that);
  }

  // Move assignment
  template <typename Data>
  BTBreadthMutableIterator<Data> & BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator<Data> && that)
  {
    this->BTBreadthIterator<Data>::operator=(std::move(that));
  }

  // Comparison operators
  template <typename Data>
  bool BTBreadthMutableIterator<Data>::operator==(const BTBreadthMutableIterator<Data> & that) const
  {
    return this->BTInOrderIterator<Data>::operator==((const BTInOrderIterator<Data> &) that);
  }

  template <typename Data>
  bool BTBreadthMutableIterator<Data>::operator!=(const BTBreadthMutableIterator<Data> & that) const
  {
    return this->BTInOrderIterator<Data>::operator!=((const BTInOrderIterator<Data> &) that);
  }

  // Specific member functions (inherited from MutableIterator)
  template <typename Data>
  Data & BTBreadthMutableIterator<Data>::operator*() // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return const_cast<Data&> (this->curr->Element());
  }
}