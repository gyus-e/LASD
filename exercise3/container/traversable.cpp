
namespace lasd {

/* ************************************************************************** */
/*  TraversableContainer    */

template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFun, const Accumulator & init) const
{
    Accumulator acc = init;
    if (!this->Empty())
    {
        this->Traverse (
            [&acc, foldFun] (const Data & dat)
            {
                acc = foldFun (dat, acc);
            }
        );
    }
    return acc;
}


template <typename Data>
bool TraversableContainer<Data>::Exists(const Data & val) const noexcept
{
    bool exists = false;
    if (!this->Empty())
    {
        this->Traverse (
            [val, &exists] (const Data & dat)
            {
                if (val == dat)
                {
                    exists = true;
                }
            }
        );
    }
    return exists;
}

// template <typename Data>
// bool TraversableContainer<Data>::operator==(const TraversableContainer & cont) const noexcept
// {
//     if (this->size != cont.Size())
//     {
//         return false;
//     }

//     Data * contElements = nullptr;
//     try 
//     {
//         contElements = new Data [cont.Size()];
//     }
//     catch (std::bad_alloc & exc)
//     {
//         return false;
//     }

//     unsigned long i = 0;
//     cont.Traverse (
//         [contElements, &i] (const Data & dat)
//         {
//             contElements[i] = dat;
//             i++;
//         }
//     );
//     bool ret = true;
//     unsigned long j = 0;
//     this->Traverse (
//         [contElements, &j, &ret] (const Data & dat)
//         {
//             // if (ret)
//             // {
//                 ret = ret && (contElements[j] == dat);
//                 j++;
//             // }
//         }
//     );

//     delete contElements;
//     return ret;
// }

/* ************************************************************************** */
/*  PreOrderTraversableContainer    */

template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> foldFun, const Accumulator & init) const
{
    Accumulator acc = init;
    if (!this->Empty())
    {
        this->PreOrderTraverse (
            [&acc, foldFun] (const Data & dat)
            {
                acc = foldFun (dat, acc);
            }
        );
    }
    return acc;
}

/* ************************************************************************** */
/*  PostOrderTraversableContainer    */


template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> foldFun, const Accumulator & init) const
{
    Accumulator acc = init;
    if (!this->Empty())
    {
        this->PostOrderTraverse (
            [&acc, foldFun] (const Data & dat)
            {
                acc = foldFun (dat, acc);
            }
        );
    }
    return acc;
}

/* ************************************************************************** */
/*  InOrderTraversableContainer    */

template <typename Data>
template <typename Accumulator>
Accumulator InOrderTraversableContainer<Data>::InOrderFold (FoldFun<Accumulator> foldFun, const Accumulator & init) const
{
    Accumulator acc = init;
    if (!this->Empty())
    {
        this->InOrderTraverse (
            [&acc, foldFun] (const Data & dat)
            {
                acc = foldFun (dat, acc);
            }
        );
    }
    return acc;
}

/* ************************************************************************** */
/*  BreadthTraversableContainer    */

template <typename Data>
template <typename Accumulator>
Accumulator BreadthTraversableContainer<Data>::BreadthFold (FoldFun<Accumulator> foldFun, const Accumulator & init) const
{
    Accumulator acc = init;
    if (!this->Empty())
    {
        this->BreadthTraverse (
            [&acc, foldFun] (const Data & dat)
            {
                acc = foldFun (dat, acc);
            }
        );
    }
    return acc;
}

}
