
#include <limits>
#include "setvec.hpp"

namespace lasd {

/* ************************************************************************** */


// Specific constructors
/* ************************************************************************** */

//Traversable
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& Tcon) {
    Tcon.Traverse([this](const Data& elem) {
        if (!Exists(elem)) {
            Insert(elem);
        }
    });
}




//MappableContainer
template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& Mcon) {
    Mcon.Traverse([this](const Data& elem) {
        if (!Exists(elem)) {
            Insert(elem);
        }
    });
}




//Copy constructor
template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other) {
    for (unsigned long i = 0; i < other.Size(); ++i) {
        Insert(other[i]);  // Usa Insert per mantenere l'ordinamento e l'unicità
    }
}


//Move costructor
template <typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& Setvec) {
    elements = Setvec.elements;
    size = Setvec.size;

    Setvec.Clear();
    
}



//Destructor
/* ************************************************************************** */

template <typename Data>
SetVec<Data>::~SetVec() {
  Clear();  
}



//Constructor
/* ************************************************************************** */

//Copy
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
    if (this != &other) {  // Evita l'auto-assegnazione
        // Pulisce il contenitore di destinazione
        Clear();

        // Copia gli elementi dal contenitore "other"
        for (unsigned long i = 0; i < other.Size(); ++i) {
            Insert(other[i]);  // Usa Insert per mantenere l'ordinamento e evitare duplicati
        }
    }
    return *this;
}



//Move
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
    if (this != &other) {  
       
        Clear();

        elements = std::move(other.elements);  
        size = other.size;  

        other.Clear();  
    }
    return *this;
}




// Comparison operators
/* ************************************************************************** */

//Operator ==
template <typename Data>
bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
    if (size != other.size) {
        return false;
    }
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] != other.elements[i]) {
            return false;
        }
    }
    
    return true;

}







//Operator !=
template <typename Data>
bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
    return !(*this == other);
}



// Specific member functions (inherited from OrderedDictionaryContainer)
/* ************************************************************************** */

//Min
/* ************************************************************************ */


//Min
template <typename Data>
Data SetVec<Data>::Min() const {
    if (size == 0) {
        throw std::length_error("SetVec is empty");
    }
    return elements[0];
}


//MinNRemove
template <typename Data>
Data SetVec<Data>::MinNRemove() {
    Data val = Min();
    Remove(val);
    return val;
}



//RemoveMin
template <typename Data>
void SetVec<Data>::RemoveMin() {
    if (size == 0) {
        throw std::length_error("SetVec is empty");
    }
    Remove(elements[0]);
}


//Max
/* ************************************************************************ */


//Max
template <typename Data>
Data SetVec<Data>::Max() const {
    if (size == 0) {
        throw std::length_error("SetVec is empty");
    }
    return elements[size - 1];
}


//MaxNRemove
template <typename Data>
Data SetVec<Data>::MaxNRemove() {
    Data val = Max();
    Remove(val);
    return val;
}



//RemoveMax
template <typename Data>
void SetVec<Data>::RemoveMax() {
    if (size == 0) {
        throw std::length_error("SetVec is empty");
    }
    Remove(elements[size - 1]);
}


//Predecessor
/* ************************************************************************ */


//Predecessor
template <typename Data>
Data SetVec<Data>::Predecessor(const Data& val) const {
    if (size == 0) {
        throw std::length_error("SetVec is empty");
    }

    long index = -1;

    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] < val) {
            index = i;  // Manteniamo l'ultimo più piccolo
        } else {
            break; // Siccome è ordinato, possiamo fermarci
        }
    }

    if (index == -1) {
        throw std::length_error("No predecessor found smaller than the given value");
    }

    return elements[index];
}




//PredecessorNRemove
template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& val) {
    if (size < 2) throw std::length_error("Not enough elements for a predecessor.");

    unsigned long index = 0;
    while (index < size && elements[index] < val) {
        ++index;
    }

    if (index == 0)
        throw std::length_error("No predecessor to remove (all elements are >= val).");

    Data pred = elements[index - 1];
    Remove(pred);
    return pred;
}





//RemovePredecessor
template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& val) {
    if (size < 2) throw std::length_error("Not enough elements for a predecessor.");

    unsigned long index = 0;
    while (index < size && elements[index] < val) {
        ++index;
    }

    if (index == 0)
        throw std::length_error("No predecessor to remove (all elements are >= val).");

    Remove(elements[index - 1]);
}


//Successor
/* ************************************************************************ */

//Successor
template <typename Data>
Data SetVec<Data>::Successor(const Data& val) const {
    if (size < 2) throw std::length_error("Not enough elements for a successor.");

    ulong index = 0;
    while (index < size && elements[index] <= val) {
        ++index;
    }

    if (index == size)
        throw std::length_error("No successor found (all elements are <= val).");

    return elements[index];
}




//SuccessorNRemove
template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& val) {
    Data successor = Successor(val);
    Remove(successor);
    return successor;
}





//RemoveSuccessor
template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& val) {
    Data successor=Successor(val);
    Remove(successor);
}





// Specific member functions (inherited from DictionaryContainer)
/* ************************************************************************ */

//Insert Copy
template <typename Data>
bool SetVec<Data>::Insert(const Data& val) {
    if (Exists(val)) {
        return false;
    }

    Resize(size + 1); // aumenta lo spazio

    // Trova posizione dove inserire (in ordine crescente)
    unsigned long pos = 0;
    while (pos < size - 1 && elements[pos] < val) {
        ++pos;
    }

    // Sposta gli elementi a destra
    for (ulong i = size - 1; i > pos; --i) {
        elements[i] = std::move(elements[i - 1]);
    }

    elements[pos] = val;
    return true;
}

  
//Insert Move
template <typename Data>
bool SetVec<Data>::Insert(Data&& val) {
    if (Exists(val)) {
        return false;  // Se l'elemento esiste, non fare nulla
    }

    Resize(size + 1);  // Aumenta lo spazio per l'elemento

    // Trova la posizione giusta per mantenere l'ordinamento
    unsigned long pos = 0;
    while (pos < size - 1 && elements[pos] < val) {
        ++pos;
    }

    // Sposta gli elementi a destra
    for (unsigned long i = size - 1; i > pos; --i) {
        elements[i] = std::move(elements[i - 1]);
    }

    elements[pos] = std::move(val);  // Muove l'elemento al posto giusto
    return true;
}



//Remove
template <typename Data>
bool SetVec<Data>::Remove(const Data& val) {
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] == val) {
            for (unsigned long j = i; j < size - 1; ++j) {
                elements[j] = std::move(elements[j + 1]);
            }
            Resize(size - 1);
            return true;
        }
    }
    return false;
}







// Specific member functions (inherited from LinearContainer)
/* ************************************************************************ */

// Operator[] const
template <typename Data>
const Data& SetVec<Data>::operator[](unsigned long index) const {
    // Verifica se l'indice è fuori dai limiti
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }

    // Restituisce il dato al dato indice
    return elements[index];
}



// Specific member function (inherited from TestableContainer)
/* ************************************************************************** */

//Exists
template <typename Data>
bool SetVec<Data>::Exists(const Data& val) const noexcept {
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] == val) {
            return true;
        }
    }
    return false;
}



 // Specific member function (inherited from ClearableContainer)
/* ************************************************************************ */

 //Clear
template <typename Data>
void SetVec<Data>::Clear() {
    elements.Clear();
    size = 0;
}


  

//Auxilary function
/* ************************************************************************** */

template <typename Data>
long SetVec<Data>::FindIndexHelper(const Data& val) const {
    for (unsigned long i = 0; i < size; ++i) {
        if (elements[i] == val) {
            return i;
        }
    }
    return -1;
}

//FindIndex
template <typename Data>
long SetVec<Data>::FindIndex(const Data& val) const {
    long index = FindIndexHelper(val);
    // Se vuoi lanciare un'eccezione invece di restituire -1:
    // if (index == -1) throw std::length_error("Elemento non trovato");
    return index;
}

template <typename Data>
void lasd::SetVec<Data>::Resize(unsigned long newSize) {
    elements.Resize(newSize);
    size = newSize;
}



}