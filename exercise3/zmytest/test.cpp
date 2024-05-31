#include "test.hpp"

#include <iostream>
#include <random>
#include <functional>
#include <string>
#include <cmath>

//1A
#include "../container/container.hpp"
#include "../container/traversable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"

//1B
#include "../queue/queue.hpp"
#include "../stack/stack.hpp"

//2A
#include "../iterator/iterator.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/vec/binarytreevec.hpp"

//2B
#include "../bst/bst.hpp"

//3
#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

// #include "../zlasdtest/exercise1a/test.hpp"
// #include "../zlasdtest/exercise1b/test.hpp"
// #include "../zlasdtest/exercise2a/test.hpp"
// #include "../zlasdtest/exercise2b/test.hpp"

/* ************************************************************************** */

typedef int T;

namespace mytst
{
  #define DIM 50
  #define TABLE_SIZE 400
  using std::cout;
  using std::endl;

  template <typename Data>
  void printdata (const Data & d)
  {
    std::cout<<d<<" ";
  }

  template <typename Data>
  void setdata (Data & d)
  {
    d = 0;
  }

  template <typename Data>
  void print (const lasd::TraversableContainer<Data> & cont)
  {
    cont.Traverse(
      [](const Data & d)
      {
        std::cout<<d<<" ";
      }
    );
    std::cout<<std::endl;
  }

  template <typename Data>
  void printInOrder (const lasd::InOrderTraversableContainer<Data> & cont)
  {
    cont.InOrderTraverse(
      [](const Data & d)
      {
        std::cout<<d<<" ";
      }
    );
    std::cout<<std::endl;
  }

  template <typename Data>
  void printPostOrder (const lasd::PostOrderTraversableContainer<Data> & cont)
  {
    cont.PostOrderTraverse(
      [](const Data & d)
      {
        std::cout<<d<<" ";
      }
    );
    std::cout<<std::endl;
  }

  template <typename Data>
  void printBreadth (const lasd::BreadthTraversableContainer<Data> & cont)
  {
    cont.BreadthTraverse(
      [](const Data & d)
      {
        std::cout<<d<<" ";
      }
    );
    std::cout<<std::endl;
  }

  template <typename Data>
  void printPreOrder (const lasd::PreOrderTraversableContainer<Data> & cont)
  {
    cont.PreOrderTraverse(
      [](const Data & d)
      {
        std::cout<<d<<" ";
      }
    );
    std::cout<<std::endl;
  }

  template <typename Data>
  void randInitReal (lasd::MappableContainer<Data> & cont)
  {
    std::default_random_engine gen (std::random_device{}());
    std::uniform_real_distribution <Data> dist (0, 999);

    cont.Map (
      [&gen, &dist] (Data & d)
      {
        d = dist(gen);
      }
    );
  }

  template <typename Data>
  void randInitInt (lasd::MappableContainer<Data> & cont)
  {
    std::default_random_engine gen (std::random_device{}());
    std::uniform_int_distribution <Data> dist (0, 999);

    cont.Map (
      [&gen, &dist] (Data & d)
      {
        d = dist(gen);
      }
    );
  }

  template <typename Data>
  void randInit (lasd::MappableContainer<Data> & cont)
  {
    randInitInt(cont);
    // randInitReal(cont);
  }

  template <typename Data>
  void testInsert (lasd::DictionaryContainer<Data> & cont)
  {
    std::default_random_engine gen (std::random_device{}());
    std::uniform_int_distribution <T> dist (0, 100);

    for (int i = 0; i < DIM; i++)
    {
      T d = dist(gen);
      if (cont.Insert(d))
      {
        // print(cont);    
        std::cout<<"size: "<<cont.Size()<<std::endl;
      }
    }
  }

  template <typename Data>
  void testRemove (lasd::DictionaryContainer<Data> & cont)
  {
      // for (int j = 0; j <= 100; j++)
      for (int j = 100; j >= 0; j--)
      {
        if (!cont.Empty())
        {
          if (cont.Remove(j))
          {
            if (!cont.Empty())
            {
              // print(cont);
            }
            std::cout<<"size: "<<cont.Size()<<std::endl;
          }
        }
        else 
        {
          break;
        }
      }
  }

  template <typename Data>
  void testInsertAll (lasd::DictionaryContainer<Data> & cont, const lasd::TraversableContainer<Data> & V)
  {
    std::cout<<"Inserted "<<(cont.InsertAll(V) ? "all" : "some or none")<<std::endl;
    // print(cont);
    std::cout<<"size: "<<cont.Size()<<std::endl;
    
    if (cont.InsertSome(V))
    {
      std::cout<<"Error: inserted some again"<<std::endl;
    }
  }

  template <typename Data>
  void testRemoveSome (lasd::DictionaryContainer<Data> & cont, const lasd::TraversableContainer<Data> & V)
  {
    std::cout<<"Removed "<<(cont.RemoveSome(V) ? "some or all" : "none")<<std::endl;
    // print(cont);
    std::cout<<"size: "<<cont.Size()<<std::endl;

    if (cont.RemoveAll(V))
    {
      std::cout<<"Error: removed all again"<<std::endl;
    }
  }

  template <typename BT>
  void TestBinaryTree ()
  {
    try 
    {
      std::cout<<"Starting vector: ";
      lasd::SortableVector<T> V (DIM);
      randInit(V);
      print<T> (V);

      std::cout<<std::endl;

      std::cout<<"Tree from copying vector: ";
      BT bt (V);
      print<T> (bt);
      std::cout<<std::endl;
      std::cout<<"root: "<<bt.Root().Element();

      std::cout<<std::endl;

      std::cout<<"clearing tree"<<std::endl;
      bt.Clear();
      std::cout<<(bt.Empty() ? "" : "error: not empty\n");

      try 
      {
        std::cout<<"root? "<<bt.Root().Element();
        std::cout<<"error\n"<<std::endl;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" (correct).\n";
      }

      std::cout<<"Tree from moving vector: ";
      bt = std::move(V);
      print<T> (bt);
      std::cout<<(bt.Empty() ? "error: empty\n" : "");

      T root = bt.Root().Element();

      std::cout<<"Tree from copy constructor: ";
      BT btcop (bt);
      print<T> (btcop);
      std::cout<<(bt == btcop ? "" : "copy error\n");

      std::cout<<"Tree from move constructor: ";
      BT btmov (std::move(bt));
      print<T> (btmov);
      std::cout<<(bt == btcop ? "move error\n" : "");

      std::cout<<(bt.Empty() ? "" : "move or empty error\n");

      btcop.Clear();
      std::cout<<(bt == btcop ? "" : "move error\n");

      std::cout<<(root == btmov.Root().Element() ? "" : "error\n");

      std::cout<<"testing map"<<std::endl;

      randInit(btmov); //map
      randInit(bt); //map empty

      std::cout<<"testing traverse"<<std::endl;

      print(btmov); //traverse
      print(bt); //traverse empty

      //TESTING ITERATORS

      std::default_random_engine gen (std::random_device{}());
      std::uniform_int_distribution <T> dist (0, 999);

      std::cout<<"TESTING ITERATORS:\n";

      std::cout<<"Inorder:\n";
      T k {};
      lasd::BTInOrderMutableIterator itr (btmov);
      while (!itr.Terminated())
      {
        k = dist(gen);
        *itr = k;
        std::cout<<*itr<<" ";
        ++itr;
      }
      try 
      {
        ++itr;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }
      std::cout<<std::endl;
      printInOrder(btmov);

      lasd::BTInOrderMutableIterator itrcopy (itr);
      std::cout<<(itrcopy.Terminated() ? "" : "error in copy\n");
      
      itr.Reset();
      lasd::BTInOrderMutableIterator itrmov (std::move(itr));
      std::cout<<*itr<<std::endl;
      std::cout<<(itr.Terminated() ? "" : "error in move\n");

      std::cout<<"left most node = "<<*itrmov<<std::endl;

      std::cout<<"Postorder:\n";
      lasd::BTPostOrderMutableIterator itr2 (btmov);
      while (!itr2.Terminated())
      {
        k = dist(gen);
        *itr2 = k;
        std::cout<<*itr2<<" ";
        ++itr2;
      }
      try 
      {
        ++itr2;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }
      std::cout<<std::endl;
      printPostOrder(btmov);

      lasd::BTPostOrderMutableIterator itr2copy (itr2);
      std::cout<<(itr2copy.Terminated() ? "" : "error in copy\n");
      
      itr2.Reset();
      lasd::BTPostOrderMutableIterator itr2mov (std::move(itr2));
      std::cout<<(itr2.Terminated() ? "" : "error in move\n");

      std::cout<<"left most leaf = "<<*itr2mov<<std::endl;

      std::cout<<"Preorder:\n";
      lasd::BTPreOrderMutableIterator itr3 (btmov);
      while (!itr3.Terminated())
      {
        k = dist(gen);
        *itr3 = k;
        std::cout<<*itr3<<" ";
        ++itr3;
      }
      try 
      {
        ++itr3;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }
      std::cout<<std::endl;
      printPreOrder(btmov);
      
      lasd::BTPreOrderMutableIterator itr3copy (itr3);
      std::cout<<(itr3copy.Terminated() ? "" : "error in copy\n");
      
      itr3.Reset();
      lasd::BTPreOrderMutableIterator itr3mov (std::move(itr3));
      std::cout<<(itr3.Terminated() ? "" : "error in move\n");

      if (*itr3mov != btmov.Root().Element())
      {
        std::cout<<"iterator error\n";
      }
      std::cout<<"root = "<<*itr3mov<<std::endl;

      std::cout<<"Breadth:\n";
      lasd::BTBreadthMutableIterator itr4 (btmov);
      while (!itr4.Terminated())
      {
        k = dist(gen);
        *itr4 = k;
        std::cout<<*itr4<<" ";
        ++itr4;
      }
      try 
      {
        ++itr4;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }
      std::cout<<std::endl;
      printBreadth(btmov);
      lasd::BTBreadthMutableIterator itr4copy (itr4);
      std::cout<<(itr4copy.Terminated() ? "" : "error in copy\n");
      
      itr.Reset();
      lasd::BTBreadthMutableIterator itr4mov (std::move(itr4));
      std::cout<<(itr4.Terminated() ? "" : "error in move\n");
      if (*itr4mov != *itr3mov)
      {
        std::cout<<"iterator error\n";
      }
      
      std::cout<<"root = "<<*itr4mov<<std::endl;

      btmov.Clear();

      lasd::BTInOrderMutableIterator empitr (btmov);
      if (!empitr.Terminated())
      {
        std::cout<<"error: iterator on empty tree\n";
      }
      try
      {
        *empitr;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }
      try
      {
        ++empitr;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }

      lasd::BTPostOrderMutableIterator empitr2 (btmov);
      if (!empitr2.Terminated())
      {
        std::cout<<"error: iterator on empty tree\n";
      }
      try
      {
        *empitr2;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }
      try
      {
        ++empitr2;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }

      lasd::BTPreOrderMutableIterator empitr3 (btmov);
      if (!empitr3.Terminated())
      {
        std::cout<<"error: iterator on empty tree\n";
      }
      try
      {
        *empitr3;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }
      try
      {
        ++empitr3;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }

      lasd::BTBreadthMutableIterator empitr4 (btmov);      
      if (!empitr4.Terminated())
      {
        std::cout<<"error: iterator on empty tree\n";
      }
      try
      {
        *empitr4;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }
      try
      {
        ++empitr4;
      }
      catch (std::exception & e)
      {
        std::cout<<e.what()<<" correct.\n";
      }
    }
    catch (std::exception & e)
    {
      std::cerr<<e.what()<<std::endl;
    }
  }

  void Test1A ()
  {
    try 
    {
      lasd::Vector<T> vec (127);
      randInit(vec);
      print(vec);

      std::cout<<std::endl;
      
      lasd::Vector<T> movVec (std::move(vec));
      print(movVec);
      std::cout<<(movVec == vec ? "error" : "correct")<<std::endl;

      std::cout<<std::endl;

      lasd::Vector<T> copVec (movVec);
      print(copVec);
      std::cout<<(movVec != copVec ? "error" : "correct")<<std::endl;

      std::cout<<std::endl;

      lasd::Vector<T> movVec2 = std::move(copVec);
      print(movVec2);
      std::cout<<(movVec != movVec2 ? "error" : "correct")<<std::endl;
      std::cout<<(copVec == movVec2 ? "error" : "correct")<<std::endl;

      std::cout<<std::endl;

      lasd::Vector<T> copVec2 = movVec2;
      print(copVec2);
      std::cout<<(copVec2 != movVec2 ? "error" : "correct")<<std::endl;
      std::cout<<(copVec2 == movVec ? "correct" : "error")<<std::endl;

      std::cout<<std::endl;

      lasd::Vector<T> vec2 (450);
      randInit(vec2);
      print(vec2);
      std::cout<<std::endl;
      copVec2 = std::move(vec2);
      print(copVec2);
      std::cout<<std::endl;

      lasd::Vector<T> vec3 (std::move(copVec2));
      print(vec3);
      std::cout<<std::endl;

    }
    catch (std::exception & exc)
    {
      std::cerr<<exc.what()<<std::endl;
    }
  }

  void Test2A ()
  {
    mytst::TestBinaryTree<lasd::BinaryTreeLnk<T>>();
    std::cout<<std::endl;
    mytst::TestBinaryTree<lasd::BinaryTreeVec<T>>();
    std::cout<<std::endl;

    lasd::BinaryTreeLnk<T> btLnk;
    randInit(btLnk);

    lasd::BinaryTreeVec<T> btVec = btLnk;

    std::cout<<(btVec.lasd::BinaryTree<T>::operator==(btLnk) ? "" : "error: not equals\n");
    
    btLnk.Clear();

    std::cout<<(btVec.lasd::BinaryTree<T>::operator!=(btLnk) ? "" : "error: equals after clear\n");

    btLnk = btVec;

    std::cout<<(btLnk.lasd::BinaryTree<T>::operator==(btVec) ? "" : "error: not equals\n");

    btVec.Clear();

    btVec = std::move(btLnk);
    std::cout<<(btLnk.Empty() ? "" : "error: not empty after move\n");
    std::cout<<(btLnk.lasd::BinaryTree<T>::operator!=(btVec) ? "" : "error: equals\n");

    btLnk = std::move(btVec);
    std::cout<<(btVec.Empty() ? "" : "error: not empty after move\n");
    std::cout<<(btLnk.lasd::BinaryTree<T>::operator!=(btVec) ? "" : "error: equals\n");

  }

  void Test2B ()
  {
    try 
    {
      lasd::BST<T> bst;
      
      testInsert(bst);

      //SUCCESSOR AND PREDECESSOR
      std::default_random_engine gen (std::random_device{}());
      std::uniform_int_distribution <T> dist (0, 100);
      for (int i = 0; i < 99; i++)
      {
        T x = dist(gen);
        std::cout<<bst.Predecessor(x)<<" "<<x<<" "<<bst.Successor(x)<<std::endl;
        if (i % 23 == 0)
        {
          bst.RemovePredecessor(x);
        }
        if (i % 29 == 0)
        {
          bst.RemoveSuccessor(x);
        }
      }

      //COPY AND MOVE TEST
      std::cout<<std::endl;
      std::cout<<"copy: "<<std::endl;
      lasd::BST<T> bstcop = bst;
      printInOrder(bstcop);    

      std::cout<<"move: "<<std::endl;
      lasd::BST<T> bstmov = std::move(bstcop);
      printInOrder(bstmov);
      std::cout<<std::endl;

      testRemove(bst);

      lasd::Vector<T> V (DIM);
      randInit(V);
      print(V);

      testInsertAll(bst, V);

      //COMPARISON OPERATOR
      lasd::BST<T> bstvec (V);
      print(bstvec);
      std::cout<<(bstvec == bst ? "equals" : "error: not equals")<<std::endl;

      //MAX AND MIN
      for (int i = 0; i < 10; i++)
      {
        std::cout<<bst.MaxNRemove()<<std::endl;
        std::cout<<bst.MinNRemove()<<std::endl;
      }

      //REMOVEALL AND REMOVESOME
      V.Resize(DIM-10);

      testRemoveSome(bst, V);
    }

    catch (std::exception & e)
    {
      std::cerr<<e.what()<<std::endl;
    }
  }

  template <typename HTable>
  void Test3 ()
  //Resize viene chiamata giá negli Insert
  //Size viene testato giá dai comparison operator
  //Costruttore e operatore di copia sono analoghi
  //Costruttore e operatore di spostamento sono analoghi
  {
    std::default_random_engine gen (std::random_device{}());
    std::uniform_int_distribution <T> dist (0, 9999);
    unsigned int errors = 0;

    try
    {
      HTable testingTable;
      testInsert<T>(testingTable);
      testRemove<T>(testingTable);

      testingTable.Clear();
      
      lasd::Vector<T> V (450);
      randInit(V);
      testInsertAll<T>(testingTable, V);
      testRemoveSome<T>(testingTable, V);


      HTable Table (TABLE_SIZE); //costruttore
      lasd::List<T> Lst;

      for (unsigned long i = 0; i < 999; i++)
      {
        bool inserted = false;
        T dat = dist(gen);

        if (!(inserted = Table.Insert(dat) == Lst.Insert(dat))) //Insert
        {
          std::cout<<"Error in Insert"<<std::endl;
        }

        if (inserted && !Table.Exists(dat)) //Exists
        {
          errors++;
          std::cout<<"Error in Exists"<<std::endl;
        }
      }

      HTable Table2 (Lst); //costruttore da TraversableContainer
      
      if (Table != Table2) //Comparison
      {
        errors++;
        std::cout<<"error in comparison"<<std::endl;
      }
      
      lasd::List<T> tmpLst (Lst);
      HTable Table3 (std::move(tmpLst)); //costruttore da MappableContainer

      if (Table3 != Table2) //Comparison
      {
        errors++;
        std::cout<<"error in comparison"<<std::endl;
      }

      if (Table3.Size() != Table2.Size())
      {
        errors++;
        std::cout<<"error in Size"<<std::endl;
      }

      if (Table3.InsertSome(Lst)) //InsertSome
      {
        errors++;
        std::cout<<"error in InsertSome"<<std::endl;
      }

      if (!Table2.RemoveAll(Lst)) //RemoveAll
      {
        errors++;
        std::cout<<"error in RemoveAll"<<std::endl;
      }

      if (Table2.RemoveSome(Lst)) //RemoveSome
      {
        errors++;
        std::cout<<"error in RemoveSome"<<std::endl;
      }
      
      if (Table3 == Table2) //Comparison
      {
        errors++;
        std::cout<<"error in comparison"<<std::endl;
      }

      if (!Table2.Empty()) //Empty
      {
        errors++;
        std::cout<<"error: Table2 is not empty"<<std::endl;
      }

      if (!Table2.Size() == 0) //Size
      {
        errors++;
        std::cout<<"error in size"<<std::endl;
      }
      
      if (!Table2.InsertAll(Lst)) //InsertAll
      {
        errors++;
        std::cout<<"error in InsertAll"<<std::endl;
      }

      Table3 = std::move(Table); //Move
      HTable Table4 = Table2; //Copy

      if (Table3 != Table4) //Comparison
      {
        errors++;
        std::cout<<"error in comparison"<<std::endl;
      }

      Table3.Clear(); //Clear

      if (!Table3.Empty())
      {
        errors++;
        std::cout<<"error in clear"<<std::endl;
      }

      std::cout<<"Exercise 3 ";
      if (errors == 0)
      {
        std::cout<<"all good.\n";
      }
      else 
      {
        std::cout<<errors<<" errors.\n";
      }
    }
    catch (std::exception & e)
    {
      std::cerr<<e.what()<<std::endl;
    }
  }
}

void mytest() {
  std::cout<<"Start of mytest"<<std::endl;

  // mytst::Test1A();
  // std::cout<<std::endl;
  mytst::Test2A();
  std::cout<<std::endl;
  mytst::Test2B();
  std::cout<<std::endl;
  // mytst::Test3<lasd::HashTableClsAdr<T>>();
  // std::cout<<std::endl;
  // mytst::Test3<lasd::HashTableOpnAdr<T>>();
  // std::cout<<std::endl;

  std::cout<<"End of mytest"<<std::endl;
  return;
}
