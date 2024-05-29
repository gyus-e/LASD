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

namespace mytst
{
  #define DIM 20
  #define TABLE_SIZE 400
  typedef int T;
  // using namespace std;

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
      lasd::Vector<int> vec (127);
      randInit(vec);
      print(vec);

      std::cout<<std::endl;
      
      lasd::Vector<int> movVec (std::move(vec));
      print(movVec);
      std::cout<<(movVec == vec ? "error" : "correct")<<std::endl;

      std::cout<<std::endl;

      lasd::Vector<int> copVec (movVec);
      print(copVec);
      std::cout<<(movVec != copVec ? "error" : "correct")<<std::endl;

      std::cout<<std::endl;

      lasd::Vector<int> movVec2 = std::move(copVec);
      print(movVec2);
      std::cout<<(movVec != movVec2 ? "error" : "correct")<<std::endl;
      std::cout<<(copVec == movVec2 ? "error" : "correct")<<std::endl;

      std::cout<<std::endl;

      lasd::Vector<int> copVec2 = movVec2;
      print(copVec2);
      std::cout<<(copVec2 != movVec2 ? "error" : "correct")<<std::endl;
      std::cout<<(copVec2 == movVec ? "correct" : "error")<<std::endl;

      std::cout<<std::endl;

      lasd::Vector<int> vec2 (450);
      randInit(vec2);
      print(vec2);
      std::cout<<std::endl;
      copVec2 = std::move(vec2);
      print(copVec2);
      std::cout<<std::endl;

      lasd::Vector<int> vec3 (std::move(copVec2));
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
    try 
    {
      lasd::SortableVector<T> V (DIM);
      randInit(V);
      // V.Sort();

      lasd::List<T> L (V);
      // lasd::List<T> L = V;

      lasd::BinaryTreeVec BTvec (L);
      print<T> (BTvec);
      
      lasd::BinaryTreeLnk BTlnk (V);
      print<T> (BTlnk);

      lasd::BinaryTreeVec copBTvec (BTvec);
      // lasd::BinaryTreeVec copBTvec = BTvec;
      print<T> (copBTvec);

      lasd::BinaryTreeVec movBTvec (std::move(BTvec));
      // lasd::BinaryTreeVec movBTvec = std::move(BTvec);
      print<T> (movBTvec);

      lasd::BinaryTreeLnk copBTlnk (BTlnk);
      // lasd::BinaryTreeLnk copBTlnk = BTlnk;
      print<T> (copBTlnk);

      lasd::BinaryTreeLnk movBTlnk (std::move(BTlnk));
      // lasd::BinaryTreeLnk movBTlnk = std::move(BTlnk);
      print<T> (movBTlnk);


      //TESTING ITERATORS
      std::cout<<"TESTING ITERATORS:\n";

      std::cout<<"Inorder:\n";
      unsigned long k = 0;
      lasd::BTInOrderMutableIterator itr (movBTlnk);
      while (!itr.Terminated())
      {
        *itr = k++;
        std::cout<<*itr<<" ";
        ++itr;
      }
      // if (*itr != movBTlnk.Min()) //provare con BST
      // {
      //   std::cout<<"iterator error\n";
      // }
      std::cout<<std::endl;
      movBTlnk.InOrderTraverse(
        [](const unsigned long & d)
        {
          std::cout<<d<<" ";
        }
      );
      itr.Reset();
      std::cout<<"\nmin = "<<*itr<<std::endl;

      std::cout<<"Postorder:\n";
      k=100;
      lasd::BTPostOrderMutableIterator itr2 (movBTlnk);
      while (!itr2.Terminated())
      {
        *itr2 = k--;
        std::cout<<*itr2<<" ";
        ++itr2;
      }
      std::cout<<std::endl;
      movBTlnk.PostOrderTraverse(
        [](const unsigned long & d)
        {
          std::cout<<d<<" ";
        }
      );
      itr2.Reset();
      // if (*itr2 != ???)
      // {
      //   std::cout<<"iterator error\n";
      // }
      std::cout<<"\nleft most leaf = "<<*itr2<<std::endl;

      std::cout<<"Preorder:\n";
      k=50;
      lasd::BTPreOrderMutableIterator itr3 (movBTlnk);
      while (!itr3.Terminated())
      {
        *itr3 = k++;
        std::cout<<*itr3<<" ";
        ++itr3;
      }
      std::cout<<std::endl;
      movBTlnk.PreOrderTraverse(
        [](const unsigned long & d)
        {
          std::cout<<d<<" ";
        }
      );
      itr3.Reset();
      if (*itr3 != movBTlnk.Root().Element())
      {
        std::cout<<"iterator error\n";
      }
      std::cout<<"\nroot = "<<*itr3<<std::endl;

      std::cout<<"Breadth:\n";
      k=0;
      lasd::BTBreadthMutableIterator itr4 (movBTlnk);
      while (!itr4.Terminated())
      {
        *itr4 = k++;
        std::cout<<*itr4<<" ";
        ++itr4;
      }
      std::cout<<std::endl;
      movBTlnk.BreadthTraverse(
        [](const unsigned long & d)
        {
          std::cout<<d<<" ";
        }
      );
      itr4.Reset();
      if (*itr4 != movBTlnk.Root().Element())
      {
        std::cout<<"iterator error\n";
      }
      std::cout<<"\nroot = "<<*itr4<<std::endl;
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
    std::uniform_int_distribution <long> dist (0, 9999);
    unsigned int errors = 0;

    try
    {
      HTable testingTable;
      testInsert<long>(testingTable);
      testRemove<long>(testingTable);

      testingTable.Clear();
      
      lasd::Vector<long> V (450);
      randInit(V);
      testInsertAll<long>(testingTable, V);
      testRemoveSome<long>(testingTable, V);


      HTable Table (TABLE_SIZE); //costruttore
      lasd::List<long> Lst;

      for (unsigned long i = 0; i < 999; i++)
      {
        bool inserted = false;
        unsigned long dat = dist(gen);

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
      
      lasd::List<long> tmpLst (Lst);
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

  mytst::Test1A();
  std::cout<<std::endl;
  mytst::Test2A();
  std::cout<<std::endl;
  mytst::Test2B();
  std::cout<<std::endl;
  mytst::Test3<lasd::HashTableClsAdr<long>>();
  std::cout<<std::endl;
  mytst::Test3<lasd::HashTableOpnAdr<long>>();
  std::cout<<std::endl;

  std::cout<<"End of mytest"<<std::endl;
  return;
}
