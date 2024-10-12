
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2024" << std::endl;
  
  int i = 0;
  std::cout << "Press 1 for lasdtest()\nPress 2 for mytest()\n";
  std::cin >> i;
  switch (i)
  {
    case 1:
    lasdtest();
    break;

    case 2:
    mytest();
    break;

    default:
    break;
  }
  return 0;
}
