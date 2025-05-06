
namespace lasd {

/* ************************************************************************** */
// Constructors

// Data copy constructor
template <typename Data> List<Data>::Node::Node(const Data &d) : value{d} {}

// Data move constructor
template <typename Data> List<Data>::Node::Node(Data &&d) noexcept {
  std::swap(d, value);
}

// Copy constructor
template <typename Data>
List<Data>::Node::Node(const Node &other) : value(other.value) {}

// Move constructor
template <typename Data> List<Data>::Node::Node(Node &&other) noexcept {
  std::swap(other.value, value);
  std::swap(other.next, next);
}

// Destructor
template <typename Data> List<Data>::Node::~Node() { delete next; }

// Operators

// Comparison operators
template <typename Data>
inline bool List<Data>::Node::operator==(const Node &other) const noexcept {
  return value == other.value;
}

template <typename Data>
inline bool List<Data>::Node::operator!=(const Node &other) const noexcept {
  return !((*this) == other);
}


// Copy constructor from Different DataStructures
template <typename Data>
List<Data>::List(const TraversableContainer<Data> &con) {
  con.Traverse([this](const Data &currData) { InsertAtBack(currData); });
}

// Move constructor from Different DataStructures
template <typename Data> List<Data>::List(MappableContainer<Data> &&con) {
  con.Map([this](Data &currData) { InsertAtBack(std::move(currData)); });
}

// Copy constructor
template <typename Data> List<Data>::List(const List<Data> &l) {
  if (!(size = l.size))
    return;

  head = new Node(*(l.head));
  tail = head;

  Node *temp = l.head->next;

  while (temp) {
    tail->next = new Node(*temp);
    tail = tail->next;
    temp = temp->next;
  }
}

// Move constructor
template <typename Data> List<Data>::List(List &&l) {
  std::swap(size, l.size);
  std::swap(head, l.head);
  std::swap(tail, l.tail);
}

// Destructor
template <typename Data> List<Data>::~List() {
  delete head;
  head = tail = nullptr;
  size = 0;
}

// Operators

// Copy assignment
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

  Node *wl{l.head};
  tail = head;

  tail->value = wl->value;

  while (tail->next && wl->next) {
    tail = tail->next;
    wl = wl->next;

    tail->value = wl->value;
  }

  if (tail->next) {
    delete tail->next;
    tail->next = nullptr;
  } else
    for (wl = wl->next; wl; wl = wl->next) {
      InsertAtBack(wl->value);
    }
  size = l.size;
  return *this;
}

// Move assignment
template <typename Data>
List<Data> &List<Data>::operator=(List<Data> &&l) noexcept {
  std::swap(size, l.size);
  std::swap(head, l.head);
  std::swap(tail, l.tail);
  return *this;
}

// Comparison operators
template <typename Data>
inline bool List<Data>::operator==(const List<Data> &l) const noexcept {
  if (size != l.size)
    return false;

  Node *temp = head, *temp2 = l.head;

  while (temp != nullptr) {
    if (temp->value != temp2->value)
      return false;
    temp = temp->next;
    temp2 = temp2->next;
  }
  return true;
}

template <typename Data>
inline bool List<Data>::operator!=(const List<Data> &l) const noexcept {
  return !(*this == l);
}

// Specific methods

template <typename Data> void List<Data>::InsertAtFront(const Data &d) {
  Node *temp = new Node(d);
  temp->next = head;
  head = temp;
  if (tail == nullptr)
    tail = head;
  ++size;
}

template <typename Data> void List<Data>::InsertAtFront(Data &&d) {
  Node *temp = new Node(std::move(d));
  temp->next = head;
  head = temp;
  if (tail == nullptr)
    tail = head;
  ++size;
}

template <typename Data> void List<Data>::RemoveFromFront() {
  if (!size)
    throw std::length_error("Cannot remove from Empty list");
  Node *temp{head};
  head == tail ? head = tail = nullptr : head = head->next;
  temp->next = nullptr;
  delete temp;
  --size;
}

template <typename Data> Data List<Data>::FrontNRemove() {
  if (!size)
    throw std::length_error("Cannot remove from Empty list");
  Node *temp{head};
  head == tail ? head = tail = nullptr : head = head->next;
  temp->next = nullptr;
  Data d{std::move(temp->value)};
  delete temp;
  --size;
  return d;
}

template <typename Data> void List<Data>::InsertAtBack(const Data &d) {
  Node *temp{new Node(d)};
  size++ ? tail->next = temp : head = tail = temp;
  tail = temp;
}

template <typename Data> void List<Data>::InsertAtBack(Data &&d) {
  Node *temp{new Node(std::move(d))};
  size++ ? tail->next = temp : head = tail = temp;
  tail = temp;
}

template <typename Data>
void List<Data>::RemoveFromBack() {
  if (size == 0)
    throw std::length_error("Cannot remove from an empty list");

  if (head == tail) {
    // Only one element in the list
    delete head;
    head = tail = nullptr;
  } else {
    // More than one element: traverse to find the penultimate node
    Node* temp = head;
    while (temp->next != tail)
      temp = temp->next;

    delete tail;
    tail = temp;
    tail->next = nullptr;
  }

  --size;
}

template <typename Data>
Data List<Data>::BackNRemove() {
  if (size == 0)
    throw std::length_error("Cannot remove from an empty list");

  Data val;

  if (head == tail) {
    // Only one element
    val = std::move(head->val);
    delete head;
    head = tail = nullptr;
  } else {
    // More than one element
    Node* temp = head;
    while (temp->next != tail)
      temp = temp->next;

    val = std::move(tail->val);
    delete tail;
    tail = temp;
    tail->next = nullptr;
  }

  --size;
  return val;
}



// Specific member functions (inherited from MutableLinearContainer)
template <typename Data>
inline Data &List<Data>::operator[](unsigned long ind) {
  if (ind >= size)
    throw std::out_of_range("List does not have enough elements");

  Node *temp{head};
  for (unsigned int i{0}; i < ind; ++i, temp = temp->next)
    ;
  return temp->value;
}

template <typename Data> inline Data &List<Data>::Front() {
  if (size)
    return head->value;
  throw std::length_error("Empty List");
}

template <typename Data> inline Data &List<Data>::Back() {
  if (size)
    return tail->value;
  throw std::length_error("Empty List");
}

// Specific member functions (inherited from LinearContainer)
template <typename Data>
inline const Data &List<Data>::operator[](unsigned long ind) const {
  if (ind >= size)
    throw std::out_of_range("List does not have enough elements");

  Node *temp{head};
  for (unsigned int i{0}; i < ind; ++i, temp = temp->next)
    ;
  return temp->value;
}

template <typename Data> inline const Data &List<Data>::Front() const {
  if (size)
    return head->value;
  throw std::length_error("Empty List");
}

template <typename Data> inline const Data &List<Data>::Back() const {
  if (size)
    return tail->value;
  throw std::length_error("Empty List");
}

// Overrided Methods

template <typename Data> void List<Data>::Clear() {
  delete head;
  head = tail = nullptr;
  size = 0;
}

template <typename Data>
inline void List<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

template <typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun) const {
  PreOrderTraverse(fun, head);
}

template <typename Data>
inline void List<Data>::PostOrderTraverse(TraverseFun fun) const {
  PostOrderTraverse(fun, head);
}

template <typename Data> inline void List<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

template <typename Data> inline void List<Data>::PreOrderMap(MapFun fun) {
  PreOrderMap(fun, head);
}

template <typename Data> inline void List<Data>::PostOrderMap(MapFun fun) {
  PostOrderMap(fun, head);
}

// Internal Methods
template <typename Data>
inline void List<Data>::PreOrderTraverse(TraverseFun fun, Node *curr) const {

  while (curr) {
    fun(curr->value);
    curr = curr->next;
  }
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, Node *curr) const {
  if (!curr)
    return;
  PostOrderTraverse(fun, curr->next);
  fun(curr->value);
}
template <typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node *curr) const {

  while (curr) {
    fun(curr->value);
    curr = curr->next;
  }
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node *curr) const {
  if (!curr)
    return;
  PostOrderMap(fun, curr->next);
  fun(curr->value);
}


}
 