#ifndef __INCLUDE_KEY_HASH_H_
#define __INCLUDE_KEY_HASH_H_

namespace BASE {
    namespace UTIL {


template <class TKey, class THash>
struct SKeyHash
{
    typedef SKeyHash<TKey, THash> self_type;

    typedef TKey  key_type;
    typedef THash hash_type;

    SKeyHash(const key_type& _rKey, const hash_type& _rHash);

    const bool operator==(const self_type& _rRhs) const;
    const bool operator!=(const self_type& _rRhs) const;

    const bool operator<(const self_type& _rRhs) const;
    const bool operator<=(const self_type& _rRhs) const;
    const bool operator>(const self_type& _rRhs) const;
    const bool operator>=(const self_type& _rRhs) const;

    TKey  m_Key;
    THash m_Hash;
};

template <class TKey>
struct SKeyHash<TKey, void>
{
    typedef SKeyHash<TKey, void> self_type;

    typedef TKey key_type;
    typedef void hash_type;

    SKeyHash(const key_type& _rKey);

    const bool operator==(const self_type& _rRhs) const;
    const bool operator!=(const self_type& _rRhs) const;

    const bool operator>(const self_type& _rRhs) const;
    const bool operator>=(const self_type& _rRhs) const;
    const bool operator<(const self_type& _rRhs) const;
    const bool operator<=(const self_type& _rRhs) const;

    TKey m_Key;
};

template <class TKey, class THash>
SKeyHash<TKey, THash>::SKeyHash(const key_type& _rKey, const hash_type& _rHash)
    : m_Key(_rKey)
    , m_Hash(_rHash)
{
}

template <class TKey, class THash>
const bool
    SKeyHash<TKey, THash>::operator==(const self_type& _rRhs) const
{
    if (m_Hash != _rRhs.m_Hash)
    {
        return false;
    }

    return m_Key == _rRhs.m_Key;
}

template <class TKey, class THash>
const bool
    SKeyHash<TKey, THash>::operator!=(const self_type& _rRhs) const
{
    return !(*this == _rRhs);
}

template <class TKey, class THash>
const bool
    SKeyHash<TKey, THash>::operator<(const self_type& _rRhs) const
{
    return m_Hash < _rRhs.m_Hash;
}

template <class TKey, class THash>
const bool
    SKeyHash<TKey, THash>::operator<=(const self_type& _rRhs) const
{
    return *this < _rRhs || *this == _rRhs;
}

template <class TKey, class THash>
const bool
    SKeyHash<TKey, THash>::operator>(const self_type& _rRhs) const
{
    return !(*this <= _rRhs);
}

template <class TKey, class THash>
const bool
    SKeyHash<TKey, THash>::operator>=(const self_type& _rRhs) const
{
    return !(*this < _rRhs);
}

template <class TKey>
SKeyHash<TKey, void>::SKeyHash(const key_type& _rKey)
    : m_Key(_rKey)
{
}

template <class TKey>
const bool
    SKeyHash<TKey, void>::operator==(const self_type& _rRhs) const
{
    return m_Key == _rRhs.m_Key;
}

template <class TKey>
const bool
    SKeyHash<TKey, void>::operator!=(const self_type& _rRhs) const
{
    return !(*this == _rRhs);
}

template <class TKey>
const bool
    SKeyHash<TKey, void>::operator<(const self_type& _rRhs) const
{
    return m_Key < _rRhs.m_Key;
}

template <class TKey>
const bool
    SKeyHash<TKey, void>::operator<=(const self_type& _rRhs) const
{
    return *this < _rRhs || *this == _rRhs;
}

template <class TKey>
const bool
    SKeyHash<TKey, void>::operator>(const self_type& _rRhs) const
{
    return !(*this <= _rRhs);
}

template <class TKey>
const bool
    SKeyHash<TKey, void>::operator>=(const self_type& _rRhs) const
{
    return !(*this < _rRhs);
}


    }
}

#endif // __INCLUDE_KEY_HASH_H_