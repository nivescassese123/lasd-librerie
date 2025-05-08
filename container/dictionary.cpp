namespace lasd {

  /* ************************************************************************** */
  
  //DictionaryContainer
  /* ************************************************************************** */
  
  //InsertAll copy
  template <typename Data>
  inline bool
  DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &Tcon) {
    bool result = true;
    Tcon.Traverse([this, &result](const Data &currData) {
      result &= this->Insert(currData);
    });
    return result;
  }
  
  
  //InsertAll move
  template <typename Data>
  inline bool
  DictionaryContainer<Data>::InsertAll(MappableContainer<Data> &&Mcon) {
    bool result = true;
    Mcon.Map([this, &result](const Data &currData) {
      result &= this->Insert(std::move(currData));
    });
    return result;
  }
  
  
  //RemoveAll
  template <typename Data>
  inline bool
  DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &Tcon) {
    bool result = true;
    Tcon.Traverse([this, &result](const Data &currData) {
      result &= this->Remove(currData);
    });
    return result;
  }
  
  
  //InsertSome copy
  template <typename Data>
  inline bool
  DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &Tcon) {
    bool result = false;
    Tcon.Traverse([this, &result](const Data &currData) {
      result |= this->Insert(currData);
    });
    return result;
  }
  
  
  //InsertSome move
  template <typename Data>
  inline bool
  DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&Mcon) {
    bool result = false;
    Mcon.Map([this, &result](const Data &currData) {
      result |= this->Insert(std::move(currData));
    });
    return result;
  }
  
  
  //RemoveSome
  template <typename Data>
  inline bool
  DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &Tcon) {
    bool result = false;
    Tcon.Traverse([this, &result](const Data &currData) {
      result |= this->Remove(currData);
    });
    return result;
  }
  
  
  /* ************************************************************************** */
  
  }
  