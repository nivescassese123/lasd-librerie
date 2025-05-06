
namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &container) {
  bool inserted = true;
  container.Traverse([&inserted, this](const Data &data) {
    if (inserted && !Insert(data)) {
      inserted = false;
    }
  });
  return inserted;
}

template <typename Data>
inline bool
DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&container) {
  bool result = true;
  container.Map([this, &result](Data &cData) {
    result &= this->Insert(std::move(cData));
  });
  return result;
}

template <typename Data>
inline bool
DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &container) {
  bool result = true;
  container.Traverse([this, &result](const Data &cData) {
    result &= this->Remove(cData);
  });
  return result;
}

template <typename Data>
inline bool
DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &container) {
  bool result = false;
  container.Traverse([this, &result](const Data &cData) {
    result |= this->Insert(cData);
  });
  return result;
}

template <typename Data>
inline bool
DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&container) {
  bool result = false;
  container.Map([this, &result](Data &cData) {
    result |= this->Insert(std::move(cData));
  });
  return result;
}

template <typename Data>
inline bool     
DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &container) {
  bool result = false;
  container.Traverse([this, &result](const Data &cData) {
    result |= this->Remove(cData);
  });
  return result;
}
/* ************************************************************************** */

}
