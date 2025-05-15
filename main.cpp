
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  /*std::cout << "LASD Libraries 2025" << std::endl;
  lasdtest();
  mytest(); // include my test function here
  return 0;

  */
 std::cout << "LASD Libraries 2025\n";
  std::cout << "Scegli quale test eseguire:\n";
  std::cout << "1) Test professore\n";
  std::cout << "2) Test personali\n";
  std::cout << "3) Entrambi\n";
  std::cout << "Scelta: ";

  int scelta = 0;
  std::cin >> scelta;

  switch(scelta) {
    case 1:
      lasdtest();
      break;
    case 2:
      mytest();
      break;
    case 3:
      lasdtest();
      mytest();
      break;
    default:
      std::cout << "Scelta non valida.\n";
  }

  return 0;
}