namespace lasd {

  /* ************************************************************************** */
  
   //Node 
  /* ************************************************************************** */
  
  //Costructors (Node)
  /* ************************************************************************** */
  
  //Specific Costructor 
  template<typename Data>
  List<Data>::Node::Node(Data && dat)noexcept{
      std::swap(element , dat);
  }
  
  
  //Move Costructor 
  template<typename Data>
  List<Data>::Node::Node(Node && nod)noexcept{
  std::swap(element,nod.element);
  std::swap(next,nod.next);
  
  }
  
  
  //Destructor (Node)
  /* ************************************************************************** */
  
  template<typename Data>
  List<Data>::Node::~Node() { delete next; }
  
  // Comparison operators (Node)
  /* ************************************************************************** */
  
  //Operator == 
  template <typename Data>
  inline bool List<Data>::Node::operator==(const Node &other) const noexcept {
    return element == other.element;
  }
  
  
  //Operator != 
  template <typename Data>
  inline bool List<Data>::Node::operator!=(const Node &other) const noexcept {
    return !((*this) == other);
  }
  
  
  // Specific member functions (Node)
  /* ************************************************************************** */
  
  //Clone 
  template <typename Data>
  typename List<Data>::Node * List<Data>::Node::Clone(Node * Tail){
    if(next == nullptr){
      return Tail;
    }else{
      Node * node = new Node(element);
      this->next = next->Clone(Tail);
  
      return node;
    }
  }
  
  /* ************************************************************************** */
  /* ************************************************************************** */
  /* ************************************************************************** */
  
  
  
  //List
  /* ************************************************************************** */
  
  //Costructors
  /* ************************************************************************** */
  
  // Copy constructor raversableContainer
  template <typename Data>
  List<Data>::List(const TraversableContainer<Data> &con) {
    con.Traverse([this](const Data &currData) { InsertAtBack(currData); });
  }
  
  // Move constructor MappableContainer
  template <typename Data> List<Data>::List(MappableContainer<Data> &&con) {
    con.Map([this](Data &currData) { InsertAtBack(std::move(currData)); });
  }
  
  
  // Copy constructor
  template <typename Data> List<Data>::List(const List<Data> &l) {
    if (!(size = l.size))
      return;
  
    Head = new Node(*(l.Head));
    Tail = Head;
  
    Node *temp = l.Head->next;
  
    while (temp) {
      Tail->next = new Node(*temp);
      Tail = Tail->next;
      temp = temp->next;
    }
  }
  
  //Move Costructor
  template <typename Data>
  List<Data>::List(List && l) noexcept {
    std::swap(size, l.size);
    std::swap(Head, l.Head);
    std::swap(Tail, l.Tail);
  }
  
  
  
  // Destructor
  /* ************************************************************************** */
  
  template <typename Data> List<Data>::~List() {
    delete Head;
    Head = Tail = nullptr;
    size = 0;
  }
  
  //Assignements
  /* ************************************************************************** */
  
  //Copy
  template <typename Data>
  List<Data> &List<Data>::operator=(const List<Data> &l) {
  
    if (!l.size) {
      Clear();
      return *this;
    }
  
    if (!size) {
      List<Data> temp{l};
      std::swap(temp, *this);
      return *this;
    }
  
    Node *wl{l.Head};
    Tail = Head;
  
    Tail->element = wl->element;
  
    while (Tail->next && wl->next) {
      Tail = Tail->next;
      wl = wl->next;
  
      Tail->element = wl->element;
    }
  
    if (Tail->next) {
      delete Tail->next;
      Tail->next = nullptr;
    } else
      for (wl = wl->next; wl; wl = wl->next) {
        InsertAtBack(wl->element);
      }
    size = l.size;
    return *this;
  }
  
  // Move 
  template <typename Data>
  List<Data> &List<Data>::operator=(List<Data> &&l) noexcept {
    std::swap(size, l.size);
    std::swap(Head, l.Head);
    std::swap(Tail, l.Tail);
    return *this;
  }
  
  
  // Comparison operators
  /* ************************************************************************** */
  
  //Operator ==
  template <typename Data>
  inline bool List<Data>::operator==(const List<Data> &l) const noexcept {
    if (size != l.size)
      return false;
  
    Node *temp = Head, *temp2 = l.Head;
  
    while (temp != nullptr) {
      if (temp->element != temp2->element)
        return false;
      temp = temp->next;
      temp2 = temp2->next;
    }
    return true;
  }
  
  
  //Operator !=
  template <typename Data>
  inline bool List<Data>::operator!=(const List<Data> &l) const noexcept {
    return !(*this == l);
  }
  
  
  // Specific member functions
  /* ************************************************************************** */
  
  
  //Front
  /* ************************************************************************** */
  
  //InsertAtFront Copy
  template <typename Data> void List<Data>::InsertAtFront(const Data &dat) {
    Node *temp = new Node(dat);
    temp->next = Head;
    Head = temp;
    if (Tail == nullptr)
      Tail = Head;
    ++size;
  }
  
  
  //InsertAtFront Move
  template <typename Data> void List<Data>::InsertAtFront(Data &&d) {
    Node *temp = new Node(std::move(d));
    temp->next = Head;
    Head = temp;
    if (Tail == nullptr)
      Tail = Head;
    ++size;
  }
  
  
  //RemoveFromFront
  template <typename Data> void List<Data>::RemoveFromFront() {
    if (!Head)
      throw std::length_error("Cannot remove from an empty list");
    
    Node *temp{Head};
    if (Head == Tail) {
      Head = Tail = nullptr;
    } else {
      Head = Head->next;
    }
    temp->next = nullptr;
    delete temp;
    --size;
  }
  
  
  //FrontNRemove
  template <typename Data> Data List<Data>::FrontNRemove() {
    if (!size)
      throw std::length_error("Cannot remove from Empty list");
    Node *temp{Head};
    Head == Tail ? Head = Tail = nullptr : Head = Head->next;
    temp->next = nullptr;
    Data d{std::move(temp->element)};
    delete temp;
    --size;
    return d;
  }
  
  
  
  //Back
  /* ************************************************************************** */
  
  
  //InsertAtBack Copy
  template <typename Data> void List<Data>::InsertAtBack(const Data &d) {
    Node *temp{new Node(d)};
    size++ ? Tail->next = temp : Head = Tail = temp;
    Tail = temp;
  }
  
  //InsertAtBack Move
  template <typename Data> void List<Data>::InsertAtBack(Data &&d) {
    Node *temp{new Node(std::move(d))};
    size++ ? Tail->next = temp : Head = Tail = temp;
    Tail = temp;
  }
  
  
  //RemoveFromBack
  template <typename Data>
  void List<Data>::RemoveFromBack() {
    if (!Head)
      throw std::length_error("Cannot remove from an empty list");
  
    if (Head == Tail) {
      delete Head;
      Head = Tail = nullptr;
    } else {
      Node* current = Head;
      while (current->next != Tail) {
        current = current->next;
      }
      delete Tail;
      Tail = current;
      Tail->next = nullptr;
    }
    --size;
  }
  
  //BackNRemove
  template <typename Data>
  Data List<Data>::BackNRemove() {
    if (!size)
      throw std::length_error("Cannot remove from Empty list");
  
    Data d;
  
    if (Head == Tail) {
      d = std::move(Head->element);
      delete Head;
      Head = Tail = nullptr;
    } else {
      Node* prev = Head;
      while (prev->next != Tail) {
        prev = prev->next;
      }
  
      d = std::move(Tail->element);
      delete Tail;
      Tail = prev;
      Tail->next = nullptr;
    }
  
    --size;
    return d;
  }
  
  
  
  // Specific member functions (inherited from MutableLinearContainer)
  /* ************************************************************************** */
  
  
  //Operator[] Move
  template <typename Data>
  inline Data &List<Data>::operator[](unsigned long ind) {
    if (ind >= size)
      throw std::length_error("List does not have enough elements");
  
    Node *temp{Head};
    for (uint i{0}; i < ind; ++i, temp = temp->next)
      ;
    return temp->element;
  }
  
  
  //Front() Move
  template <typename Data> inline Data &List<Data>::Front() {
    if (size)
      return Head->element;
    throw std::length_error("Empty List");
  }
  
  
  
  //Back() Move
  template <typename Data> inline Data &List<Data>::Back() {
    if (size)
      return Tail->element;
    throw std::length_error("Empty List");
  }
  
  
  // Specific member functions (inherited from LinearContainer)
  /* ************************************************************************** */
  
  
  //Operator[] Copy
  template <typename Data>
  inline const Data &List<Data>::operator[](unsigned long ind) const {
    if (ind >= size)
      throw std::length_error("List does not have enough elements");
  
    Node *temp{Head};
    for (uint i{0}; i < ind; ++i, temp = temp->next)
      ;
    return temp->element;
  }
  
  
  
  //Front() Copy
  template <typename Data> inline const Data &List<Data>::Front() const {
    if (size)
      return Head->element;
    throw std::length_error("Empty List");
  }
  
  
  
  //Back() Copy
  template <typename Data> inline const Data &List<Data>::Back() const {
    if (size)
      return Tail->element;
    throw std::length_error("Empty List");
  }
  
  
  //Clear
  template <typename Data> void List<Data>::Clear() noexcept{
    delete Head;
    Head = Tail = nullptr;
    size = 0;
  }
  
  
  
  
  
  
  
  //Protected Methods
  /* ************************************************************************ */
  
  //PreOrderTraverse
  template <typename Data>
  void List<Data>::PreOrderTraverse(TraverseFun fun, Node *curr) const {
    if (!curr)
      return;
  
    fun(curr->element);
    PreOrderTraverse(fun, curr->next);
  }
  
  
  //PostOrderTraverse
  template <typename Data>
  void List<Data>::PostOrderTraverse(TraverseFun fun, Node *curr) const {
    if (!curr)
      return;
    PostOrderTraverse(fun, curr->next);
    fun(curr->element);
  }
  
  
  //PreOrderMap
  template <typename Data>
  void List<Data>::PreOrderMap(MapFun fun, Node *curr) const {
    if (!curr)
      return;
    fun(curr->element);
    PreOrderMap(fun, curr->next);
  }
  
  
  //PostOrderMap
  template <typename Data>
  void List<Data>::PostOrderMap(MapFun fun, Node *curr) const {
    if (!curr)
      return;
    PostOrderMap(fun, curr->next);
    fun(curr->element);
  }
  
  
  }
  
  