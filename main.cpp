

#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2023" << std::endl;
  
  int scelta;
  
  do {
    std::cout << "\nScegli l'operazione da eseguire:" << std::endl;
    std::cout << "1. Esegui i test standard (del professore)" << std::endl;
    std::cout << "2. Esegui i miei test personalizzati" << std::endl;
    std::cout << "0. Esci" << std::endl;
    std::cout << "Scelta: ";
    std::cin >> scelta;
    
    switch(scelta) {
      case 1:
        lasdtest();  // Funzione definita in zlasdtest/test.hpp
        break;
      case 2:
        mytest();  // Funzione definita in zmytest/test.hpp
        break;
      case 0:
        std::cout << "Arrivederci!" << std::endl;
        break;
      default:
        std::cout << "Scelta non valida" << std::endl;
    }
  } while(scelta != 0);
  
  return 0;
}