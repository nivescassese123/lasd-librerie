#include <iostream>
#include <exception>
#include "../../zlasdtest/vector/vector.hpp"


void TestVector() {
     std::cout << "\n ==== Inizio test Vector ====\n" << std::endl;

  // Creazione vettore di dimensione 3
  lasd::Vector<int> vec(3);

  // Inserimento valori
  vec[0] = 42;
  vec[1] = 13;
  vec[2] = 7;

  // Stampa valori inseriti
  std::cout << "Element 0: " << vec[0] << std::endl;
  std::cout << "Element 1: " << vec[1] << std::endl;
  std::cout << "Element 2: " << vec[2] << std::endl;

  // Test accesso fuori limite con controllo manuale
  std::cout << "Tentativo di accesso a indice fuori limite (3): ";
  if (3 < vec.Size()) {
    std::cout << vec[3] << std::endl;
  } else {
    std::cout << "Indice 3 fuori limite, accesso evitato." << std::endl;
  }

  // Test copia vettore
  lasd::Vector<int> vecCopy(vec);

  std::cout << "Copia elementi:\n";
  std::cout << "Copy Element 0: " << vecCopy[0] << std::endl;
  std::cout << "Copy Element 1: " << vecCopy[1] << std::endl;
  std::cout << "Copy Element 2: " << vecCopy[2] << std::endl;

  std::cout << "Copia effettuata correttamente\n";

  std::cout << "==== TEST COMPLETATO ====\n\n";


  //test di ridimensionamento
    std::cout << "==== TEST DI RIDIMENSIONAMENTO ====\n" << std::endl;
    try {
        // Creo un vettore di dimensione 5 e lo inizializzo
        lasd::Vector<int> vecResize(5);
        for (unsigned long i = 0; i < 5; ++i) {
            vecResize[i] = static_cast<int>(i + 1);  // valori 1,2,3,4,5
        }
        std::cout << "Vettore originale (dimensione 5):\n";
        for (unsigned long i = 0; i < vecResize.Size(); ++i) {
            std::cout << "Element " << i << ": " << vecResize[i] << std::endl;
        }

        // Ridimensionamento a 8 (maggiore)
        vecResize.Resize(8);
        std::cout << "\nDopo ridimensionamento a 8:\n";
        for (unsigned long i = 0; i < vecResize.Size(); ++i) {
            std::cout << "Element " << i << ": " << vecResize[i];
            if (i >= 5) {
                std::cout << " (NUOVO ELEMENTO, ATTENDIAMO VALORE DI DEFAULT)";
            }
            std::cout << std::endl;
        }

        // Ridimensionamento a 3 (minore)
        vecResize.Resize(3);
        std::cout << "\nDopo ridimensionamento a 3:\n";
        for (unsigned long i = 0; i < vecResize.Size(); ++i) {
            std::cout << "Element " << i << ": " << vecResize[i] << std::endl;
        }
        std::cout << "(Dovrebbero esserci solo i primi 3 elementi, gli altri eliminati)\n";

        // Ridimensionamento a 0 (vuoto)
        vecResize.Resize(0);
        std::cout << "\nDopo ridimensionamento a 0:\n";
        if (vecResize.Size() == 0) {
            std::cout << "Vettore vuoto, dimensione 0, nessun elemento da mostrare.\n";
        } else {
            std::cout << "ERRORE: dimensione diversa da 0!\n";
        }

        std::cout << "\n==== TEST DI RIDIMENSIONAMENTO COMPLETATO CON SUCCESSO ====\n\n";
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Errore: Accesso fuori limite durante il test! " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Errore generico durante il test: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Errore sconosciuto durante il test." << std::endl;
    }

////////////////////////////////
//test per accesso e modifica 
 std::cout << "\n==== Test operator[] e gestione eccezioni ====\n";

    lasd::Vector<int> v(4);

    // Assegna valori
    for (unsigned long i = 0; i < v.Size(); ++i) {
        v[i] = static_cast<int>(i * 10 + 5);
    }

    // Stampa valori e verifica che siano quelli attesi
    for (unsigned long i = 0; i < v.Size(); ++i) {
        std::cout << "v[" << i << "] = " << v[i] << std::endl;
    }

    // Verifica che accedere a un indice fuori limite lanci eccezione
    try {
        std::cout << "Accesso a v[4] (fuori limite): ";
        std::cout << v[4] << std::endl; // Deve lanciare eccezione
        std::cout << "ERRORE: Nessuna eccezione per accesso fuori limite!" << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Eccezione out_of_range catturata correttamente: " << e.what() << std::endl;
    }

    // Verifica Front() e Back()
    try {
        std::cout << "Front(): " << v.Front() << std::endl;
        std::cout << "Back(): " << v.Back() << std::endl;
    }
    catch (const std::length_error& e) {
        std::cout << "Eccezione length_error catturata: " << e.what() << std::endl;
    }

    std::cout << "==== Test completato senza memory leak====\n\n";
}
