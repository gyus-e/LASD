
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"
//memory leak usando le varianti lst, testare!
#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : public virtual PreOrderTraversableContainer<Data>,
                   public virtual PostOrderTraversableContainer<Data>,
                   public virtual InOrderTraversableContainer<Data>,
                   public virtual BreadthTraversableContainer<Data>
{

private:

  // ...

protected:

  // ...
  using Container::size;

public:

  using typename TraversableContainer<Data>::TraverseFun;

  struct Node { //classe astratta, verrá implementata in binarytreelnk e binarytreevec
  protected:
    
    // Comparison operators
    bool operator==(const Node &) const; // Comparison of abstract types is possible, but is not visible.
    bool operator!=(const Node &) const; // Comparison of abstract types is possible, but is not visible.

    //Auxiliary functions
    void PreOrderTraverse (TraverseFun) const;
    void PostOrderTraverse (TraverseFun) const;
    void InOrderTraverse (TraverseFun) const;
    void BreadthTraverse (TraverseFun) const;

  public:
    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node operator=(const Node &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    Node operator=(Node &&) = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual const Data & Element() const = 0; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual const Node & LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual const Node & RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree operator=(const BinaryTree &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BinaryTree operator=(BinaryTree &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree &) const; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree &) const; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Node & Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  void InOrderTraverse(TraverseFun) const override; // Override InOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  void BreadthTraverse(TraverseFun) const override; // Override BreadthTraversableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : public virtual ClearableContainer,
                          public virtual BinaryTree<Data>,
                          public virtual PreOrderMappableContainer<Data>,
                          public virtual PostOrderMappableContainer<Data>,
                          public virtual InOrderMappableContainer<Data>,
                          public virtual BreadthMappableContainer<Data>
{
private:

  // ...

protected:
  using Container::size;
  using typename BinaryTree<Data>::Node;
  MutableBinaryTree() = default;

public:
  
  using typename MappableContainer<Data>::MapFun;

  struct MutableNode : public virtual BinaryTree<Data>::Node {
  public:
    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode operator=(const MutableNode &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    MutableNode operator=(MutableNode &&) noexcept = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual Data & Element() = 0; // Mutable access to the element (concrete function should not throw exceptions)

    virtual MutableNode & LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual MutableNode & RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)
  
  protected:
    MutableNode() = default;
    // Auxiliary functions
    void PreOrderMap (MapFun);
    void PostOrderMap (MapFun);
    void InOrderMap (MapFun);
    void BreadthMap (MapFun);
  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableNode operator=(const MutableNode &) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableNode operator=(MutableNode &&) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual MutableNode & Root() = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  void InOrderMap(MapFun) override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  void BreadthMap(MapFun) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator :  public virtual ForwardIterator<Data>,
                            public virtual ResettableIterator<Data>
{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stk;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data> & binTree) // An iterator over a given binary tree
  {
    if (binTree.Size() != 0)
    {
        this->root = &binTree.Root();
        this->curr = this->root;
    }
  }
  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator<Data> & that) : root (that.root), curr (that.curr), stk (that.stk) {}

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator<Data> && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator operator=(const BTPreOrderIterator<Data> & that)
  {
    this->root = that.root;
    this->curr = that.curr;
    this->stk = that.stk;

    return *this;
  }

  // Move assignment
  BTPreOrderIterator operator=(BTPreOrderIterator<Data> && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);

    return *this;
  }


  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator<Data> & that) const
  {
    return (this->root == that.root) && (this->curr == that.curr) && (this->stk == that.stk);
  }

  bool operator!=(const BTPreOrderIterator<Data> & that) const
  {
    return !(this->operator==(that));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
  }

  bool Terminated() const noexcept override // (should not throw exceptions)
  {
    return (this->curr==nullptr);
  }
  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPreOrderIterator & operator++() override // (throw std::out_of_range when terminated)
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
  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override // (should not throw exceptions)
  {
    this->stk.Clear();
    this->curr = this->root;
  }
};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : public virtual MutableIterator<Data>,
                                  public virtual BTPreOrderIterator<Data>
{

private:

  // ...

protected:

  using BTPreOrderIterator<Data>::curr;
  using BTPreOrderIterator<Data>::root;
  using BTPreOrderIterator<Data>::stk;

public:

  // Specific constructors
  BTPreOrderMutableIterator(const MutableBinaryTree<Data> & bTree) : BTPreOrderIterator<Data>(bTree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator & that) : BTPreOrderIterator<Data> ((const BTPreOrderIterator<Data> &) that) {}

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator && that) noexcept : BTPreOrderIterator<Data> (std::move((const BTPreOrderIterator<Data> &) that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator operator=(const BTPreOrderMutableIterator & that)
  {
    this->BTPreOrderIterator<Data>::operator=(that);
  }

  // Move assignment
  BTPreOrderMutableIterator operator=(BTPreOrderMutableIterator && that)
  {
    this->BTPreOrderIterator<Data>::operator=(std::move(that));
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderMutableIterator & that) const
  {
    return this->BTPreOrderIterator<Data>::operator==((const BTPreOrderIterator<Data> &) that);
  }

  bool operator!=(const BTPreOrderMutableIterator & that) const
  {
    return this->BTPreOrderIterator<Data>::operator!=((const BTPreOrderIterator<Data> &) that);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
  }
};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : public virtual ForwardIterator<Data>,
                            public virtual ResettableIterator<Data>
{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stk;

  void toLeftMostLeaf()
  //Scendo preferibilmente a sinistra fino a trovare una foglia
  //Aggiungo allo stack i nodi attraversati ma non visitati
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

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data> & binTree) // An iterator over a given binary tree
  {
    if (binTree.Size() != 0)
    {
      this->root = &binTree.Root();
      this->curr = this->root;
      this->toLeftMostLeaf();
    }
  }
  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator & that) : curr(that.curr), stk(that.stk) {}

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator operator=(const BTPostOrderIterator & that)
  {
    this->root = that.root;
    this->curr = that.curr;
    this->stk = that.stk;

    return *this;
  }

  // Move assignment
  BTPostOrderIterator operator=(BTPostOrderIterator && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);
    
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  
  bool operator==(const BTPostOrderIterator & that) const
  {
    return ((this->root == that.root) && (this->curr == that.curr) && (this->stk == that.stk));
  }

  bool operator!=(const BTPostOrderIterator & that) const
  {
    return !(this->operator==(that));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
  }

  bool Terminated() const noexcept override // (should not throw exceptions)
  {
    return (this->curr==nullptr);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPostOrderIterator & operator++() override // (throw std::out_of_range when terminated)
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
  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override // (should not throw exceptions)
  {
    this->stk.Clear();
    this->curr = this->root;
    this->toLeftMostLeaf();
  }
};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : public virtual MutableIterator<Data>,
                                   public virtual BTPostOrderIterator<Data>
{

private:

  // ...

protected:

  using BTPostOrderIterator<Data>::curr;
  using BTPostOrderIterator<Data>::root;
  using BTPostOrderIterator<Data>::stk;

public:

  // Specific constructors
  BTPostOrderMutableIterator(const MutableBinaryTree<Data> & bTree) : BTPostOrderIterator<Data>(bTree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator & that) : BTPostOrderIterator<Data> ((const BTPostOrderIterator<Data> &) that) {}

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator && that) noexcept : BTPostOrderIterator<Data> (std::move((const BTPostOrderIterator<Data> &) that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator operator=(const BTPostOrderMutableIterator & that)
  {
    this->BTPostOrderIterator<Data>::operator=(that);
  }

  // Move assignment
  BTPostOrderMutableIterator operator=(BTPostOrderMutableIterator && that)
  {
    this->BTPostOrderIterator<Data>::operator=(std::move(that));
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderMutableIterator & that) const
  {
    return this->BTPostOrderIterator<Data>::operator==((const BTPostOrderIterator<Data> &) that);
  }

  bool operator!=(const BTPostOrderMutableIterator & that) const
  {
    return this->BTPostOrderIterator<Data>::operator!=((const BTPostOrderIterator<Data> &) that);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
  }

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : public virtual ForwardIterator<Data>,
                          public virtual ResettableIterator<Data>
{

private:

  // ...

protected:
  
  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stk;

  void toLeftMostNode ()
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
public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data> & binTree) // An iterator over a given binary tree
  {
    if (binTree.Size() != 0)
    {
      this->root = &binTree.Root();
      this->curr = this->root;
      this->toLeftMostNode();
    }
  }
  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator & that) : curr(that.curr), stk(that.stk) {}

  // Move constructor
  BTInOrderIterator(BTInOrderIterator && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator operator=(const BTInOrderIterator & that)
  {
    this->root = that.root;
    this->curr = that.curr;
    this->stk = that.stk;

    return *this;
  }

  // Move assignment
  BTInOrderIterator operator=(BTInOrderIterator && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->stk, that.stk);
    
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  
  bool operator==(const BTInOrderIterator & that) const
  {
    return ((this->root == that.root) && (this->curr == that.curr) && (this->stk == that.stk));
  }

  bool operator!=(const BTInOrderIterator & that) const
  {
    return !(this->operator==(that));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
  }

  bool Terminated() const noexcept override // (should not throw exceptions)
  {
    return (this->curr==nullptr);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator & operator++() override // (throw std::out_of_range when terminated)
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
  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override // (should not throw exceptions)
  {
    this->stk.Clear();
    this->curr = this->root;
    this->toLeftMostNode();
  }
};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator :  public virtual MutableIterator<Data>,
                                  public virtual BTInOrderIterator<Data>
{

private:

  // ...

protected:

  using BTInOrderIterator<Data>::curr;
  using BTInOrderIterator<Data>::root;
  using BTInOrderIterator<Data>::stk;

public:
  
  // Specific constructors
  BTInOrderMutableIterator(const MutableBinaryTree<Data> & bTree) : BTInOrderIterator<Data>(bTree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator & that) : BTInOrderIterator<Data> ((const BTInOrderIterator<Data> &) that) {}

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator && that) noexcept : BTInOrderIterator<Data> (std::move((const BTInOrderIterator<Data> &) that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator operator=(const BTInOrderMutableIterator & that)
  {
    this->BTInOrderIterator<Data>::operator=(that);
  }

  // Move assignment
  BTInOrderMutableIterator operator=(BTInOrderMutableIterator && that)
  {
    this->BTInOrderIterator<Data>::operator=(std::move(that));
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderMutableIterator & that) const
  {
    return this->BTInOrderIterator<Data>::operator==((const BTInOrderIterator<Data> &) that);
  }

  bool operator!=(const BTInOrderMutableIterator & that) const
  {
    return this->BTInOrderIterator<Data>::operator!=((const BTInOrderIterator<Data> &) that);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
  }

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : public virtual ForwardIterator<Data>,
                          public virtual ResettableIterator<Data>
{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * curr = nullptr;
  QueueVec<const typename BinaryTree<Data>::Node *> que;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data> & binTree) // An iterator over a given binary tree
  {
    if (binTree.Size() != 0)
    {
        this->root = &binTree.Root();
        this->curr = this->root;
    }
  }
  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator& that) : root(that.root), curr(that.root), que(that.que) {}

  // Move constructor
  BTBreadthIterator(BTBreadthIterator&& that) noexcept 
  {
    std::swap(root, that.root);
    std::swap(curr, that.curr);
    std::swap(que, that.que);
  }

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator operator=(const BTBreadthIterator & that)
  {
    this->root = that.root;
    this->curr = that.curr;
    this->que = that.que;

    return *this;
  }

  // Move assignment
  BTBreadthIterator operator=(BTBreadthIterator && that) noexcept
  {
    std::swap (this->root, that.root);
    std::swap (this->curr, that.curr);
    std::swap (this->que, that.que);
    
    return *this;
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator & that) const
  {
    return ((this->root == that.root) && (this->curr == that.curr) && (this->que == that.que));
  }

  bool operator!=(const BTBreadthIterator & that) const
  {
    return !(this->operator==(that));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
  }

  bool Terminated() const noexcept override // (should not throw exceptions)
  {
    return (this->curr == nullptr);
  }
  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTBreadthIterator & operator++() override // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator++");
    }
    //accoda figlio sinistro
    if (this->curr->HasLeftChild())
    {
      this->que.Enqueue(&(this->curr->LeftChild()));
    }
    //accoda figlio destro
    if (this->curr->HasRightChild())
    {
      this->que.Enqueue(&(this->curr->RightChild()));
    }

    //visita testa della coda
    if (!this->que.Empty())
    {
      this->curr = this->que.HeadNDequeue();
    }
    //se la coda è vuota l'iteratore è terminato
    else 
    {
      this->curr = nullptr; 
    }

    return *this;
  }
  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override // (should not throw exceptions)
  {
    this->que.Clear();
    this->curr = this->root;
  }

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : public virtual MutableIterator<Data>,
                                 public virtual BTBreadthIterator<Data> 
{

private:

  // ...

protected:

  using BTBreadthIterator<Data>::curr;
  using BTBreadthIterator<Data>::root;
  using BTBreadthIterator<Data>::que;

public:
  
  // Specific constructors
  BTBreadthMutableIterator(const MutableBinaryTree<Data> & bTree) : BTBreadthIterator<Data>(bTree) {}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator & that) : BTBreadthIterator<Data> ((const BTBreadthIterator<Data> &) that) {}

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator && that) noexcept : BTBreadthIterator<Data> (std::move((const BTBreadthIterator<Data> &) that)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator operator=(const BTBreadthMutableIterator & that)
  {
    this->BTBreadthIterator<Data>::operator=(that);
  }

  // Move assignment
  BTBreadthMutableIterator operator=(BTBreadthMutableIterator && that)
  {
    this->BTBreadthIterator<Data>::operator=(std::move(that));
  }

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthMutableIterator & that) const
  {
    return this->BTInOrderIterator<Data>::operator==((const BTInOrderIterator<Data> &) that);
  }

  bool operator!=(const BTBreadthMutableIterator & that) const
  {
    return this->BTInOrderIterator<Data>::operator!=((const BTInOrderIterator<Data> &) that);
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override // (throw std::out_of_range when terminated)
  {
    if (this->Terminated())
    {
      throw std::out_of_range("from operator *");
    }
    return this->curr->Element();
  }
};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
