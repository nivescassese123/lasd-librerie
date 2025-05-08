
namespace lasd {

  /* ************************************************************************** */
  
  
  // Specific constructors
  /* ************************************************************************ */
  
  // Specific constructor from TraversableContainer
  template <typename Data>
  SetLst<Data>::SetLst(const TraversableContainer<Data>& Tcon) {
    Tcon.Traverse(
      [this](const Data& dat) {
        this->Insert(dat); 
      }
    );
  }
  
  
  // Specific constructor from MappableContainer
  template <typename Data>
  SetLst<Data>::SetLst(MappableContainer<Data>&& Mcon) {
    Mcon.Map(
      [this](Data& dat) {
        this->Insert(std::move(dat));
      }
    );
  }
  
  
  
  //Assignement
  /* ************************************************************************** */
  
  // Copy assignment
  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& other) {
    List<Data>::operator=(other); // usa l'operatore di assegnazione di List
    return *this;
  }
  
  
  // Move assignment
  template <typename Data>
  SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& other) noexcept {
    List<Data>::operator=(std::move(other)); // usa l'operatore di move di List
    return *this;
  }
  
  /* ************************************************************************** */
  
  // Comparison operators
  
  template <typename Data>
  bool SetLst<Data>::operator==(const SetLst<Data>& other) const noexcept {
    return List<Data>::operator==(other); // Confronta le liste
  }
  
  template <typename Data>
  bool SetLst<Data>::operator!=(const SetLst<Data>& other) const noexcept {
    return !(*this == other); // Opposto di ==
  }
  
  
  // Specific member functions (inherited from OrderedDictionaryContainer)
  /* ************************************************************************** */
  
  //Min
  /* ************************************************************************** */
  
  //Min
  template <typename Data>
  Data SetLst<Data>::Min() const {
    if (this->Empty()) throw std::length_error("Set is empty");
    return this->Front(); // La testa della lista è il minimo, perché è ordinato
  }
  
  
  //MinNRemove
  template <typename Data>
  Data SetLst<Data>::MinNRemove() {
    if (this->Empty()) throw std::length_error("Set is empty");
  
    Data minElem = this->Front(); 
    Remove(minElem); 
  
    return minElem;
  }
  
  
  //RemoveMin
  template <typename Data>
  void SetLst<Data>::RemoveMin() {
    if (this->Empty()) throw std::length_error("Set is empty");
    Remove(this->Front()); 
  }
  
  
  
  //Max
  /* ************************************************************************** */
  
  
  //Max
  template <typename Data>
  Data SetLst<Data>::Max() const {
    if (this->Empty()) throw std::length_error("Set is empty");
    return this->Back(); // La coda della lista è il massimo
  }
  
  
  //MaxNRemove
  template <typename Data>
  Data SetLst<Data>::MaxNRemove() {
    if (this->Empty()) throw std::length_error("Set is empty");
  
    Data maxElem = this->Back(); 
    Remove(maxElem); 
  
    return maxElem;
  }
  
  
  //RemoveMax
  template <typename Data>
  void SetLst<Data>::RemoveMax() {
    if (this->Empty()) throw std::length_error("Set is empty");
    Remove(this->Back()); 
  }
  
  
  
  //predecessor
  /* ************************************************************************** */
  
  
  //Predecessor
  template <typename Data>
  Data SetLst<Data>::Predecessor(const Data& val) const {
      // Verifica che la lista non sia vuota
      if (this->Head == nullptr) {
          throw std::length_error("The list is empty.");
      }
  
      typename List<Data>::Node* current = this->Head;
      typename List<Data>::Node* previous = nullptr;
  
      // Scorre la lista per trovare l'elemento precedente
      while (current != nullptr && current->element < val) {
          previous = current;
          current = current->next;
      }
  
      // Se non troviamo un predecessore (l'elemento è il primo della lista), lancia un errore
      if (previous == nullptr) {
          throw std::length_error("No predecessor found.");
      }
  
      // Restituisci l'elemento del predecessore
      return previous->element;
  }
  
  
  
  
  
  
  //PredecessorNRemove
  template <typename Data>
  Data SetLst<Data>::PredecessorNRemove(const Data& elem) {
    Data predecessorElem = Predecessor(elem);
    Remove(predecessorElem);
    return predecessorElem;
  }
  
  
  //RemovePredecessor
  template <typename Data>
  void SetLst<Data>::RemovePredecessor(const Data& elem) {
    Data predecessorElem = Predecessor(elem);
    Remove(predecessorElem);
  }
  
  
  
  //Successor
  /* ************************************************************************** */
  
  
  //Successor
  template <typename Data>
  Data SetLst<Data>::Successor(const Data& elem) const {
    if (this->size < 2)
          throw std::length_error("Not enough elements for a successor.");
  
      typename List<Data>::Node* current = this->Head;
      const Data* successor = nullptr;
  
      while (current != nullptr) {
          if (current->element > elem) {
              if (successor == nullptr || current->element < *successor) {
                  successor = &(current->element);
              }
          }
          current = current->next;
      }
  
      if (successor == nullptr)
          throw std::length_error("No successor found (all elements are <= val).");
  
      return *successor;
  }
  
  
  
  //SuccessorNRemove
  template <typename Data>
  Data SetLst<Data>::SuccessorNRemove(const Data& elem) {
    Data successorElem = Successor(elem);
    Remove(successorElem);
    return successorElem;
  }
  
  
  //RemoveSuccesor
  template <typename Data>
  void SetLst<Data>::RemoveSuccessor(const Data& elem) {
    Data successorElem = Successor(elem);
    Remove(successorElem);
  }
  
  
  // Specific member functions (inherited from DictionaryContainer)
  /* ************************************************************************ */
  
  //Insert Copy
    template <typename Data>
  bool SetLst<Data>::Insert(const Data& elem) {
      typename List<Data>::Node* newNode = new typename List<Data>::Node(elem);
    // Creiamo un nuovo nodo con la copia dell'elemento
  
      // Caso base: la lista è vuota
      if (this->Head == nullptr) {
          this->Head = this->Tail = newNode;  // La testa e la coda sono il nuovo nodo
          this->size = 1;
          return true;
      }
  
      typename List<Data>::Node* current = this->Head;
      typename List<Data>::Node* previous = nullptr;
  
      // Scorriamo la lista per trovare la posizione giusta
      while (current != nullptr && current->element < elem) {
          previous = current;
          current = current->next;
      }
  
      // Se l'elemento è già presente, non inseriamo nulla
      if (current != nullptr && current->element == elem) {
          delete newNode;  // Rimuoviamo il nodo appena creato per evitare perdite di memoria
          return false;
      }
  
      // Inseriamo in testa se l'elemento è più piccolo di tutti
      if (previous == nullptr) {
          newNode->next = this->Head;
          this->Head = newNode;
      } 
      // Inseriamo in coda se l'elemento è più grande di tutti
      else if (current == nullptr) {
          previous->next = newNode;
          this->Tail = newNode;
      } 
      // Inseriamo tra due nodi
      else {
          previous->next = newNode;
          newNode->next = current;
      }
  
      this->size++;
      return true;
  }
  
  
  //Insert Move
  template <typename Data>
  bool SetLst<Data>::Insert(Data&& elem) {
      typename List<Data>::Node* newNode = new typename List<Data>::Node(std::move(elem));
    // Creiamo un nuovo nodo spostando l'elemento
  
      // Caso base: la lista è vuota
      if (this->Head == nullptr) {
          this->Head = this->Tail = newNode;  // La testa e la coda sono il nuovo nodo
          this->size = 1;
          return true;
      }
  
      typename List<Data>::Node* current = this->Head;
      typename List<Data>::Node* previous = nullptr;
  
      // Scorriamo la lista per trovare la posizione giusta
      while (current != nullptr && current->element < newNode->element) {
          previous = current;
          current = current->next;
      }
  
      // Se l'elemento è già presente, non inseriamo nulla
      if (current != nullptr && current->element == newNode->element) {
          delete newNode;  // Rimuoviamo il nodo appena creato per evitare perdite di memoria
          return false;
      }
  
      // Inseriamo in testa se l'elemento è più piccolo di tutti
      if (previous == nullptr) {
          newNode->next = this->Head;
          this->Head = newNode;
      }
      // Inseriamo in coda se l'elemento è più grande di tutti
      else if (current == nullptr) {
          previous->next = newNode;
          this->Tail = newNode;
      }
      // Inseriamo tra due nodi
      else {
          previous->next = newNode;
          newNode->next = current;
      }
  
      this->size++;
      return true;
  }
  
  
  
  //Remove
  template <typename Data>
  bool SetLst<Data>::Remove(const Data& elem) {
      if (this->Head == nullptr) {  // La lista è vuota
          return false;
      }
  
      typename List<Data>::Node* current = this->Head;
      typename List<Data>::Node* previous = nullptr;
  
      // Scorriamo la lista per trovare l'elemento
      while (current != nullptr && current->element != elem) {
          previous = current;
          current = current->next;
      }
  
      // Se l'elemento non è stato trovato, restituiamo false
      if (current == nullptr) {
          return false;
      }
  
      // Se l'elemento da rimuovere è la testa
      if (previous == nullptr) {
          this->Head = current->next;
          if (this->Head == nullptr) {  // Se la lista diventa vuota
              this->Tail = nullptr;
          }
      }
      // Se l'elemento da rimuovere è nel mezzo o alla fine
      else {
          previous->next = current->next;
          if (current == this->Tail) {  // Se l'elemento da rimuovere è la coda
              this->Tail = previous;
          }
      }
  
      // Prima di cancellare current, aggiorna la memoria per evitare problemi di accesso dopo deallocazione.
      typename List<Data>::Node* nodeToDelete = current;
      nodeToDelete->next = nullptr;  // Scollega esplicitamente il nodo dalla lista
      current = nullptr;
  
      delete nodeToDelete;
    // Rimuoviamo il nodo dalla memoria
      this->size--;    // Decrementiamo la dimensione della lista
  
      return true;
  }
  
  
  // Specific member functions (inherited from LinearContainer)
  /* ************************************************************************ */
  
  //Operator[]
  template <typename Data>
  const Data& SetLst<Data>::operator[](const unsigned long index) const {
      if (index >= this->size) {  // Verifica se l'indice è valido
          throw std::out_of_range("Index out of range.");
      }
  
      typename List<Data>::Node* current = this->Head;
      for (unsigned long i = 0; i < index; ++i) {  // Scorre la lista fino all'indice desiderato
          current = current->next;
      }
  
      return current->element;  // Restituisce l'elemento alla posizione richiesta
  }

  
  
  
    // Specific member function (inherited from TestableContainer)
  /* ************************************************************************** */
  
  //Exists
  template <typename Data>
  bool SetLst<Data>::Exists(const Data& elem) const noexcept {
      typename List<Data>::Node* current = this->Head;
  
      while (current != nullptr) {
          if (current->element == elem) {
              return true;  // trovato
          } else if (current->element > elem) {
              return false; // non può essere più avanti in una lista ordinata
          }
          current = current->next;
      }
  
      return false; // fine della lista
    }
  
  
  
  // Specific member function (inherited from ClearableContainer)
  /* ************************************************************************ */
  
  //Clear
  template <typename Data>
  void SetLst<Data>::Clear() noexcept {
      List<Data>::Clear(); // Riutilizzo diretto della logica già implementata nella lista
  }
  
  
  /* ************************************************************************** */
  
  }
  

