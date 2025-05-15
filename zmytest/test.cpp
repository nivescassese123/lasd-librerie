
 #include "test.hpp"
 #include "vector/testvector.cpp"
/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

void mytest() {
  cout << "\n ==== Inizio test ====\n" << endl;
  // Call your test functions here
  TestVector(); // Example test function for vector
  // Add more test functions as needed
  cout << "\n ==== Fine test ====\n" << endl;
  // ...
}
