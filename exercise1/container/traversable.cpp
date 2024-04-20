
namespace lasd {

/* ************************************************************************** */
/*  TraversableContainer    */

template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> & foldFun, const Accumulator & init) const
{
    Accumulator acc = init;
    this->Traverse (
        [&acc, foldFun] (const Data & dat)
        {
            acc = foldFun (dat, acc);
        }
    );
    return acc;
}


template <typename Data>
bool TraversableContainer<Data>::Exists(const Data & val) const noexcept
{
    bool exists = false;
    this->Traverse (
        [val, &exists] (const Data & dat)
        {
            if (!exists)
            {
                exists = (val == dat);
            }
        }
    );
    return exists;
}

/* ************************************************************************** */
/*  PreOrderTraversableContainer    */

template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> & foldFun, const Accumulator & init) const
{
    Accumulator acc = init;
    this->PreOrderTraverse (
        [&acc, foldFun] (const Data & dat)
        {
            acc = foldFun (dat, acc);
        }
    );
    return acc;
}

/* ************************************************************************** */
/*  PostOrderTraversableContainer    */


template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> & foldFun, const Accumulator & init) const
{
    Accumulator acc = init;
    this->PostOrderTraverse (
        [&acc, foldFun] (const Data & dat)
        {
            acc = foldFun (dat, acc);
        }
    );
    return acc;
}

}
