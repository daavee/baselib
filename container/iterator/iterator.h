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
    class TCategory,
    class TValue,
    class TDifference = ptrdiff_t,
    class TPointer = TValue*,
    class TReference = TValue&
>
struct SIterator
{
    typedef TCategory   iterator_tag_type;
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


    } // namespace CNT
} // namespace BASE

#endif // __INCLUDE_ITERATOR_H_