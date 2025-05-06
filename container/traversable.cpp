
namespace lasd {

/* ************************************************************************** */

template <typename Data, typename Accumulator>
using FoldFun =
    typename TraversableContainer<Data>::template FoldFun<Accumulator>;

template <typename Data>
template <typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> func,
                                                    Accumulator ac) const {
  Traverse(
      [&ac, func](const Data &cData) { ac = func(cData, ac); });
  return ac;
};



template <typename Data>
inline bool
TraversableContainer<Data>::Exists(const Data &data) const noexcept {
  bool exists = false;
  Traverse(
      [data, &exists](const Data &cData) { exists |= (data == cData); });
  return exists;
}



template <typename Data>
inline void
PreOrderTraversableContainer<Data>::Traverse(TraverseFun func) const {
  PreOrderTraverse(func);
}

template <typename Data>
template <typename Accumulator>
inline Accumulator
PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> func,
                                                 Accumulator ac) const {
  PreOrderTraverse(
      [&ac, func](const Data &cData) { ac = func(cData, ac); });
  return ac;
};


template <typename Data>
inline void
PostOrderTraversableContainer<Data>::Traverse(TraverseFun func) const {
  PostOrderTraverse(func);
}

template <typename Data>
template <typename Accumulator>
inline Accumulator
PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> func,
                                                   Accumulator ac) const {
  PostOrderTraverse(
      [&ac, &func](const Data &cData) { 
        ac = func(cData, ac); });
  return ac;
};



/* ************************************************************************** */

}
