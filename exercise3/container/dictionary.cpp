
namespace lasd {

/* ************************************************************************** */

// Copy of the value; From TraversableContainer; True if all are inserted
template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> & con)
{
    if (con.Empty())
    {
        return false;
    }
    bool inserted = true;
    con.Traverse (
        [this, &inserted](const Data & dat)
        {
            inserted &= this->Insert(dat);
        }
    );
    return inserted;
}

// Move of the value; From MappableContainer; True if all are inserted
template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> && con)
{
    if (con.Empty())
    {
        return false;
    }
    bool inserted = true;
    con.Map (
        [this, &inserted](Data && dat)
        {
            inserted &= this->Insert(std::move(dat)); 
        }
    );
    return inserted;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> & con)
{
    if (con.Empty())
    {
        return false;
    }
    bool removed = true;
    con.Traverse (
        [this, &removed](const Data & dat)
        {
            removed &= this->Remove(dat);
        }
    );
    return removed;
}

// Copy of the value; From TraversableContainer; True if some are inserted
template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> & con)
{
    if (con.Empty())
    {
        return false;
    }
    bool inserted = false;
    con.Traverse (
        [this, &inserted](const Data & dat)
        {
            inserted |= this->Insert(dat);
        }
    );
    return inserted;
}

// Move of the value; From MappableContainer; True if some are inserted
template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> && con)
{
    if (con.Empty())
    {
        return false;
    }
    bool inserted = false;
    con.Map (
        [this, &inserted](Data && dat)
        {
            inserted |= this->Insert(std::move(dat)); 
        }
    );
    return inserted;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> & con)
{
    if (con.Empty())
    {
        return false;
    }
    bool removed = false;
    con.Traverse (
        [this, &removed](const Data & dat)
        {
            removed |= this->Remove(dat);
        }
    );
    return removed;
}

/* ************************************************************************** */

}
