#ifndef __INCLUDE_ITERATOR_H_
#define __INCLUDE_ITERATOR_H_

namespace BASE {
    namespace CNT {


struct SOutputIteratorTag
{
};

struct SInputIteratorTag
{
};

struct SForwardIteratorTag : public SInputIteratorTag
{
};

struct SBidirectionalIteratorTag : public SForwardIteratorTag
{
};

struct SRandomAccessIteratorTag : public SBidirectionalIteratorTag
{
};

template <
    class TTag,
    class TValue,
    class TDifference = ptrdiff_t,
    class TPointer = TValue*,
    class TReference = TValue&
>
struct SIterator
{
    typedef TTag        iterator_tag_type;
    typedef TValue      value_type;
    typedef TPointer    value_pointer_type;
    typedef TReference  value_reference_type;
    typedef TDifference difference_type;
};

template <class TIterator>
class CReverseIterator
{
public: // typedefs

    typedef CReverseIterator<TIterator> self_type;
    typedef TIterator iterator_type;
    
    typedef typename iterator_type::iterator_tag_type    iterator_tag_type; 
    typedef typename iterator_type::value_type           value_type;
    typedef typename iterator_type::value_pointer_type   value_pointer_type;
    typedef typename iterator_type::value_reference_type value_reference_type;
    typedef typename iterator_type::difference_type      difference_type;

public: // ctor / dtor

    CReverseIterator();
    explicit CReverseIterator(iterator_type _It);
    CReverseIterator(const self_type& _rRIt);

public: // biderectional functions

    iterator_type GetBaseIterator() const;

    value_reference_type operator*() const;
    value_pointer_type   operator->() const;

    const bool operator==(self_type _Rhs) const;
    const bool operator!=(self_type _Rhs) const;

    self_type&      operator++();
    const self_type operator++(int);
    self_type&      operator--();
    const self_type operator--(int);

public: // random access function

    const self_type operator+(difference_type _Diff) const;
    self_type&      operator+=(difference_type _Diff);
    const self_type operator-(difference_type _Diff) const;
    self_type&      operator-=(difference_type _Diff);

    value_reference_type operator[](difference_type _Pos) const;

private: // member

    iterator_type m_Base;
};

template <class TIterator>
CReverseIterator<TIterator>::CReverseIterator()
    : m_Base()
{
}

template <class TIterator>
CReverseIterator<TIterator>::CReverseIterator(iterator_type _It)
    : m_Base(_It)
{
}

template <class TIterator>
CReverseIterator<TIterator>::CReverseIterator(const self_type& _rRIt)
    : m_Base(_rRIt.m_Base)
{
}

template <class TIterator>
typename CReverseIterator<TIterator>::iterator_type
    CReverseIterator<TIterator>::GetBaseIterator() const
{
    return m_Base; // returns copy
}

template <class TIterator>
typename CReverseIterator<TIterator>::value_reference_type
    CReverseIterator<TIterator>::operator*() const
{
    iterator_type Temp(m_Base);
    return *Temp;
}

template <class TIterator>
typename CReverseIterator<TIterator>::value_pointer_type
    CReverseIterator<TIterator>::operator->() const
{
    return &(operator*());
}

template <class TIterator>
const bool
    CReverseIterator<TIterator>::operator==(self_type _Rhs) const
{
    return m_Base == _Rhs.m_Base;
}

template <class TIterator>
const bool
    CReverseIterator<TIterator>::operator!=(self_type _Rhs) const
{
    return m_Base != _Rhs.m_Base;
}

template <class TIterator>
typename CReverseIterator<TIterator>::self_type&
    CReverseIterator<TIterator>::operator++()
{
    --m_Base;
    return *this;
}

template <class TIterator>
const typename CReverseIterator<TIterator>::self_type
    CReverseIterator<TIterator>::operator++(int)
{
    self_type Temp(*this);
    --m_Base;
    return Temp;
}

template <class TIterator>
typename CReverseIterator<TIterator>::self_type&
    CReverseIterator<TIterator>::operator--()
{
    ++m_Base;
    return *this;
}

template <class TIterator>
const typename CReverseIterator<TIterator>::self_type
    CReverseIterator<TIterator>::operator--(int)
{
    self_type Temp(*this);
    ++m_Base;
    return Temp;
}

template <class TIterator>
const typename CReverseIterator<TIterator>::self_type
    CReverseIterator<TIterator>::operator+(difference_type _Diff) const
{
    return self_type(m_Base - _Diff);
}

template <class TIterator>
typename CReverseIterator<TIterator>::self_type&
    CReverseIterator<TIterator>::operator+=(difference_type _Diff)
{
    m_Base -= _Diff;
    return *this;
}

template <class TIterator>
const typename CReverseIterator<TIterator>::self_type
    CReverseIterator<TIterator>::operator-(difference_type _Diff) const
{
    return self_type(m_Base + _Diff);
}

template <class TIterator>
typename CReverseIterator<TIterator>::self_type&
    CReverseIterator<TIterator>::operator-=(difference_type _Diff)
{
    m_Base += _Diff;
    return *this;
}

template <class TIterator>
typename CReverseIterator<TIterator>::value_reference_type
    CReverseIterator<TIterator>::operator[](difference_type _Pos) const
{
    return *(*this + _Pos);
}


    } // namespace CNT
} // namespace BASE

#endif // __INCLUDE_ITERATOR_H_