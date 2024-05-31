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
  #define DIM 20
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

  template <typename BT>
  void Test2A ()
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
      std::cout<<"constructed\n";
      while (!itr.Terminated())
      {
        k = dist(gen);
        *itr = k;
        std::cout<<*itr<<" ";
        ++itr;
      }
      std::cout<<std::endl;
      printInOrder(btmov);
      itr.Reset();
      std::cout<<"left most node = "<<*itr<<std::endl;

      std::cout<<"Postorder:\n";
      lasd::BTPostOrderMutableIterator itr2 (btmov);
      while (!itr2.Terminated())
      {
        k = dist(gen);
        *itr2 = k;
        std::cout<<*itr2<<" ";
        ++itr2;
      }
      std::cout<<std::endl;
      printPostOrder(btmov);
      itr2.Reset();
      std::cout<<"left most leaf = "<<*itr2<<std::endl;

      std::cout<<"Preorder:\n";
      lasd::BTPreOrderMutableIterator itr3 (btmov);
      while (!itr3.Terminated())
      {
        k = dist(gen);
        *itr3 = k;
        std::cout<<*itr3<<" ";
        ++itr3;
      }
      std::cout<<std::endl;
      printPreOrder(btmov);
      itr3.Reset();
      if (*itr3 != btmov.Root().Element())
      {
        std::cout<<"iterator error\n";
      }
      std::cout<<"root = "<<*itr3<<std::endl;

      std::cout<<"Breadth:\n";
      lasd::BTBreadthMutableIterator itr4 (btmov);
      while (!itr4.Terminated())
      {
        k = dist(gen);
        *itr4 = k;
        std::cout<<*itr4<<" ";
        ++itr4;
      }
      std::cout<<std::endl;
      printBreadth(btmov);
      itr4.Reset();
      if (*itr4 != btmov.Root().Element())
      {
        std::cout<<"iterator error\n";
      }
      
      std::cout<<"root = "<<*itr4<<std::endl;


    }
    catch (std::exception & e)
    {
      std::cerr<<e.what()<<std::endl;
    }
  }

  void Test2B ()
  {
    try 
    {
      lasd::BST<T> bst;
      
      testInsert(bst);

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
  // mytst::Test2A<lasd::BinaryTreeLnk<T>>();
  // std::cout<<std::endl;
  mytst::Test2A<lasd::BinaryTreeVec<T>>();
  std::cout<<std::endl;
  mytst::Test2B();
  std::cout<<std::endl;
  mytst::Test3<lasd::HashTableClsAdr<T>>();
  std::cout<<std::endl;
  mytst::Test3<lasd::HashTableOpnAdr<T>>();
  std::cout<<std::endl;

  std::cout<<"End of mytest"<<std::endl;
  return;
}
