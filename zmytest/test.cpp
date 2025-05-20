#include <iostream>

#include "test.hpp"

/* ************************************************************************** */

// Test personalizzati per Vector
void MyTestVector() {
  std::cout << "------------ Test Vector ------------" << std::endl;
  
  // Test su Vector<int>
  std::cout << "Test su Vector<int>" << std::endl;
  
  // Creazione di un vector vuoto
  lasd::Vector<int> vec1;
  std::cout << "Vector vuoto creato con successo" << std::endl;
  
  // Test dimensione
  std::cout << "Dimensione (dovrebbe essere 0): " << vec1.Size() << std::endl;
  
  // Test Empty
  std::cout << "Empty (dovrebbe essere true): " << (vec1.Empty() ? "true" : "false") << std::endl;
  
  // Creazione di un vector con elementi
  lasd::Vector<int> vec2(5);
  std::cout << "Vector di dimensione 5 creato con successo" << std::endl;
  
  // Inserimento elementi
  for(unsigned long i = 0; i < vec2.Size(); i++) {
    vec2[i] = i * 10;
  }
  
  // Test accesso agli elementi
  std::cout << "Elementi inseriti: ";
  for(unsigned long i = 0; i < vec2.Size(); i++) {
    std::cout << vec2[i] << " ";
  }
  std::cout << std::endl;
  
  // Test operatore di uguaglianza
  lasd::Vector<int> vec3(vec2);
  std::cout << "Test operatore == (dovrebbe essere true): " << (vec2 == vec3 ? "true" : "false") << std::endl;
  
  // Test operator[]
  vec3[2] = 999;
  std::cout << "Test operatore == dopo modifica (dovrebbe essere false): " << (vec2 == vec3 ? "true" : "false") << std::endl;
  
  // Test casi limite
  try {
    vec2[10]; // Indice fuori range - senza memorizzare il valore
    std::cout << "ERRORE: Accesso a indice fuori range non ha generato eccezione!" << std::endl;
  } catch(std::out_of_range& e) {
    std::cout << "Test indice fuori range: eccezione correttamente generata" << std::endl;
  }
  
  // Altri test specifici...
}

// Test personalizzati per List
void MyTestList() {
  std::cout << "\n------------ Test List ------------" << std::endl;
  
  // Test su List<int>
  std::cout << "Test su List<int>" << std::endl;
  
  // Creazione di una lista vuota
  lasd::List<int> list1;
  std::cout << "Lista vuota creata con successo" << std::endl;
  
  // Test dimensione
  std::cout << "Dimensione (dovrebbe essere 0): " << list1.Size() << std::endl;
  
  // Test Empty
  std::cout << "Empty (dovrebbe essere true): " << (list1.Empty() ? "true" : "false") << std::endl;
  
  // Inserimento elementi
  for(int i = 0; i < 5; i++) {
    list1.InsertAtBack(i * 10);
  }
  
  std::cout << "Elementi inseriti con InsertAtBack, dimensione: " << list1.Size() << std::endl;
  
  // Test accesso agli elementi
  std::cout << "Front: " << list1.Front() << std::endl;
  std::cout << "Back: " << list1.Back() << std::endl;
  
  // Test operatore di uguaglianza
  lasd::List<int> list2(list1);
  std::cout << "Test operatore == (dovrebbe essere true): " << (list1 == list2 ? "true" : "false") << std::endl;
  
  // Test RemoveFromFront
  list2.RemoveFromFront();
  std::cout << "Test operatore == dopo RemoveFromFront (dovrebbe essere false): " << (list1 == list2 ? "true" : "false") << std::endl;
  
  // Test casi limite
  try {
    lasd::List<int> emptyList;
    emptyList.Front(); // Front su lista vuota - senza memorizzare il valore
    std::cout << "ERRORE: Front su lista vuota non ha generato eccezione!" << std::endl;
  } catch(std::length_error& e) {
    std::cout << "Test Front su lista vuota: eccezione correttamente generata" << std::endl;
  }
  
  // Altri test specifici...
}


  // Altri test specifici...


// Funzione principale per l'esecuzione dei test personalizzati
void mytest() {
  int scelta;
  
  std::cout << "Benvenuto nei test personalizzati per la libreria LASD!" << std::endl;
  
  do {
    std::cout << "\nScegli il test da eseguire:" << std::endl;
    std::cout << "1. Test Vector" << std::endl;
    std::cout << "2. Test List" << std::endl;
    std::cout << "3. Test Set" << std::endl;
    std::cout << "0. Esci" << std::endl;
    std::cout << "Scelta: ";
    std::cin >> scelta;
    
    switch(scelta) {
      case 1:
        MyTestVector();
        break;
      case 2:
        MyTestList();
        break;
      case 0:
        std::cout << "Uscita dai test personalizzati" << std::endl;
        break;
      default:
        std::cout << "Scelta non valida" << std::endl;
    }
  } while(scelta != 0);
}

/* ************************************************************************** */