#include <random>

namespace lasd {

/* ************************************************************************** */

//linear container
template <typename Data>
inline bool LinearContainer<Data>::operator==(
    const LinearContainer<Data> &con) const noexcept {
  if (size != con.size) {
    return false;
  }
    
  for (unsigned int i = 0; i < size; ++i) {
    if ((*this)[i] != con[i]) {
      return false;
    }
  }
  return true;
}

template <typename Data>
inline bool LinearContainer<Data>::operator!=(
    const LinearContainer<Data> &con) const noexcept {
  return !(*this == con);
}

template <typename Data>
inline const Data &LinearContainer<Data>::Front() const {
  if (size == 0) {
    throw std::length_error("Empty structure.");
  }
  return (*this)[0];
}

template <typename Data>
inline const Data &LinearContainer<Data>::Back() const {
  if (size == 0) {
    throw std::length_error("Empty structure.");
  }
  return (*this)[size - 1];
}


template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(const TraverseFun func) const {
  for (unsigned int i = 0; i < size; ++i) {
    func((*this)[i]);
  }
}

template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(const TraverseFun func) const {

  for (unsigned int i = size; i > 0;) {
    func((*this)[--i]);
  }
}

//mutable linear container
template <typename Data> inline Data &MutableLinearContainer<Data>::Front() {
  if (size != 0) {
    throw std::length_error("Empty structure.");
  }
  return (*this)[0];
}

template <typename Data> inline Data &MutableLinearContainer<Data>::Back() {
  if (size == 0) {
    throw std::length_error("Empty structure.");
  }
  return (*this)[size - 1];
}


//PreOrderMap
template <typename Data> void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
  for (unsigned int i= 0; i < size; ++i) {
    fun((*this)[i]);
  }
}

//PostOrderMap
template <typename Data> void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
  for (unsigned int i = size; i > 0;) {
    fun((*this)[--i]);
  }
}





// Sortable Linear Container
/* ************************************************************************** */

template <typename Data>
void SortableLinearContainer<Data>::quickSort(unsigned long start, unsigned long end) noexcept {
  
  if (start >= end) {
    return;
  }

  if (end - start < 16) {
    insertionSort(start, end);
    return;
  }

  unsigned long pivot_position = partition(start, end);

  quickSort(start, pivot_position);
  quickSort(pivot_position + 1, end);
}

template <typename Data>
void SortableLinearContainer<Data>::insertionSort(unsigned long start,
                                                  unsigned long end) noexcept {
  
  Data currentValue;
  unsigned long currentIndex;

  for (unsigned long i = start + 1; i <= end; i++) {
    
    currentValue = (*this)[i];
    currentIndex = i;

    while (currentIndex > start && (*this)[currentIndex - 1] > currentValue) {
      (*this)[currentIndex] = (*this)[currentIndex - 1];
      --currentIndex;
    }
  
    (*this)[currentIndex] = currentValue;
  }
}

template <typename Data>
unsigned long SortableLinearContainer<Data>::partition(unsigned long start, unsigned long end) noexcept {
    
    unsigned long left = start - 1;
    unsigned long right = end + 1;
    unsigned long pivotIndex = getRandomIndex(start, end);
    
    Data pivot = (*this)[pivotIndex];

    while (true) {

        do {
            --right;
        } while ((*this)[right] > pivot);
        
        do {
            ++left;
        } while ((*this)[left] < pivot);
        
        if (left >= right) {
            return right;
        }
      
        std::swap((*this)[left], (*this)[right]);
    }
}

template <typename Data>
unsigned long SortableLinearContainer<Data>::getRandomIndex(unsigned long start, unsigned long end) 
const noexcept {
    
    std::default_random_engine generator(std::random_device{}());
    
    std::uniform_int_distribution<unsigned long> distribution(start, end);
    return distribution(generator);
}

} // namespace lasd
