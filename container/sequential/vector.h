#ifndef __INCLUDE_VECTOR_H_
#define __INCLUDE_VECTOR_H_

/************************************************************************************
 * This work is licensed under the                                                  *
 *      Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. *
 * To view a copy of this license, visit                                            *
 *      http://creativecommons.org/licenses/by-nc-sa/3.0/                           *
 *                                                                                  *
 * @author  David Wieland                                                           *
 * @email   david.dw.wieland@googlemail.com                                         *
 ************************************************************************************/

#include <assert.h>
#include "../iterator/iterator.h"
#include "../../memory/allocator.h"

namespace BASE {
    namespace CNT {

            
template <
    typename TValue,
    template <typename> class TAllocator = BASE::MEM::CAllocator
>
class CVector
{
public: // static constants

    static const int s_DefaultCapacity = 1;
    static const int s_DefaultIncrease = 8;

public: // forward declarations

    class CConstIterator;
	class CIterator;

public: // typedefs

	typedef CVector<TValue, TAllocator> self_type;

	typedef TValue            value_type;
	typedef value_type&       value_reference_type;
	typedef const value_type& value_const_reference_type;
	typedef value_type*       value_pointer_type;
    typedef const value_type* value_const_pointer_type;

    typedef size_t size_type;

    typedef CIterator                        iterator;
    typedef CConstIterator                   const_iterator;
    typedef CReverseIterator<iterator>       reverse_iterator;
    typedef CReverseIterator<const_iterator> const_reverse_iterator;

    typedef TAllocator<value_type> allocator_type;

public: // ctor, dtor

    CVector();
    CVector(int _Capacity, int _Increase);
    CVector(const self_type& _rVector);
    self_type& operator=(const self_type& _rVector);

    ~CVector();

public: // iterator creation

    iterator               Begin();
    const_iterator         Begin() const;
    reverse_iterator       RBegin();
    const_reverse_iterator RBegin() const;

    iterator               End();
    const_iterator         End() const;
    reverse_iterator       REnd();
    const_reverse_iterator REnd() const;

public: // operations

    void PushBack(value_const_reference_type _rItem);
    void PopBack();
    iterator Remove(iterator _Pos);
    iterator Remove(iterator _First, iterator _Last);

    value_reference_type       operator[](size_type _Index) throw();
    value_const_reference_type operator[](size_type _Index) const throw();
    value_reference_type       At(size_type _Index);
    value_const_reference_type At(size_type _Index) const;

public: // properties

    size_type GetCount() const;

public: // iterator declaration

    class CConstIterator : public SIterator<SRandomAccessIteratorTag, TValue>
    {
    public:

        friend typename CVector<TValue, TAllocator>;

    public:

        typedef CConstIterator                              self_type;
        typedef SIterator<SRandomAccessIteratorTag, TValue> base_type;

        typedef typename base_type::iterator_tag_type          iterator_tag_type;
        typedef typename base_type::value_type                 value_type;
        typedef typename const base_type::value_reference_type value_reference_type;
        typedef typename const base_type::value_pointer_type   value_pointer_type;
        typedef typename base_type::difference_type            difference_type;

    public: // ctor, dtor

        CConstIterator(const self_type& _rIterator);

    private: // private ctor

        CConstIterator(value_pointer_type _pValue);

    public: // exposed operations

        const bool operator==(const self_type& _rRhs) const;
        const bool operator!=(const self_type& _rRhs) const;

        value_reference_type operator*() const;
        value_pointer_type   operator->() const;

        self_type&      operator++();
        const self_type operator++(int);
        self_type&      operator--();
        const self_type operator--(int);

        const self_type& operator+=(difference_type _Off);
        self_type        operator+(difference_type _Off) const;
        const self_type& operator-=(difference_type _Off);
        self_type        operator-(difference_type _Off) const;

    private: // member

        value_type* m_pValue;

    protected: // internal operations

        void Increment();
        void Decrement();
    };

    class CIterator : public CConstIterator
    {
    public:

        friend typename CVector<TValue, TAllocator>;

    public:

        typedef CIterator      self_type;

        typedef typename base_type::value_reference_type value_reference_type;
        typedef typename base_type::value_pointer_type   value_pointer_type;

    public:

        CIterator(const self_type& _rIt);

    private:

        CIterator(value_pointer_type _pValue);

    public:

        value_reference_type operator*() const;
        value_pointer_type   operator->() const;

        self_type&      operator++();
        const self_type operator++(int);
        self_type&      operator--();
        const self_type operator--(int);

        const self_type& operator+=(difference_type _Off);
        self_type        operator+(difference_type _Off) const;
        const self_type& operator-=(difference_type _Off);
        self_type        operator-(difference_type _Off) const;
    };

private: // internal operations

    bool Resize(size_type _minIncrease = 1);
    void ShiftLeft(iterator _Begin, int _Count);
    void ShiftRight(iterator _Begin, int _Count);

private: // member

    allocator_type     m_Allocator;
    size_type          m_Capacity;
    size_type          m_Increase;
    size_type          m_ElementCount;
    value_pointer_type m_pData;

};

/*************************************************************************
 * CONST ITERATOR SUBSECTION
 *************************************************************************/

template <typename TValue, template <typename> class TAllocator>
CVector<TValue, TAllocator>::CConstIterator::CConstIterator(value_pointer_type _pValue)
    : m_pValue(_pValue)
{
}

template <typename TValue, template <typename> class TAllocator>
CVector<TValue, TAllocator>::CConstIterator::CConstIterator(const self_type& _rIt)
    : m_pValue(_rIt.m_pValue)
{
}

template <typename TValue, template <typename> class TAllocator>
const bool
CVector<TValue, TAllocator>::CConstIterator::operator==(const self_type& _rRhs) const
{
    return this->m_pValue == _rRhs.m_pValue;
}

template <typename TValue, template <typename> class TAllocator>
const bool
CVector<TValue, TAllocator>::CConstIterator::operator!=(const self_type& _rRhs) const
{
    return this->m_pValue != _rRhs.m_pValue; // oder: return *this == _rRhs;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CConstIterator::value_reference_type
CVector<TValue, TAllocator>::CConstIterator::operator*() const
{
    return *m_pValue;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CConstIterator::value_pointer_type
CVector<TValue, TAllocator>::CConstIterator::operator->() const
{
    return &(operator*());
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CConstIterator::self_type&
CVector<TValue, TAllocator>::CConstIterator::operator++()
{
    this->Increment();
    return *this;
}

template <typename TValue, template <typename> class TAllocator>
const typename CVector<TValue, TAllocator>::CConstIterator::self_type
CVector<TValue, TAllocator>::CConstIterator::operator++(int)
{
    self Temp = *this;
    this->Increment();
    return Temp;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CConstIterator::self_type&
CVector<TValue, TAllocator>::CConstIterator::operator--()
{
    this->Decrement();
    return *this;
}

template <typename TValue, template <typename> class TAllocator>
const typename CVector<TValue, TAllocator>::CConstIterator::self_type
CVector<TValue, TAllocator>::CConstIterator::operator--(int)
{
    self Temp = *this;
    this->Decrement();
    return Temp;
}

template <typename TValue, template <typename> class TAllocator>
const typename CVector<TValue, TAllocator>::CConstIterator::self_type&
CVector<TValue, TAllocator>::CConstIterator::operator+=(difference_type _Off)
{
    m_pValue += _Off;
    return *this;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CConstIterator::self_type
CVector<TValue, TAllocator>::CConstIterator::operator+(difference_type _Off) const
{
    CConstIterator temp(*this);
    return temp += _Off;
}

template <typename TValue, template <typename> class TAllocator>
const typename CVector<TValue, TAllocator>::CConstIterator::self_type&
CVector<TValue, TAllocator>::CConstIterator::operator-=(difference_type _Off)
{
    m_pValue -= _Off;
    return *this;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CConstIterator::self_type
CVector<TValue, TAllocator>::CConstIterator::operator-(difference_type _Off) const
{
    CConstIterator temp(*this);
    return temp -= _Off;
}

template <typename TValue, template <typename> class TAllocator>
void
CVector<TValue, TAllocator>::CConstIterator::Increment()
{
    ++m_pValue;
}

template <typename TValue, template <typename> class TAllocator>
void
CVector<TValue, TAllocator>::CConstIterator::Decrement()
{
    --m_pValue;
}

/*************************************************************************
 * ITERATOR SUBSECTION
 *************************************************************************/

template <typename TValue, template <typename> class TAllocator>
CVector<TValue, TAllocator>::CIterator::CIterator(value_pointer_type _pValue)
    : CConstIterator(_pValue)
{
}

template <typename TValue, template <typename> class TAllocator>
CVector<TValue, TAllocator>::CIterator::CIterator(const self_type& _rIt)
    : CConstIterator(_rIt)
{
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CIterator::value_reference_type
CVector<TValue, TAllocator>::CIterator::operator*() const
{
    return *m_pValue;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CIterator::value_pointer_type
CVector<TValue, TAllocator>::CIterator::operator->() const
{
    return &(operator*());
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CIterator::self_type&
CVector<TValue, TAllocator>::CIterator::operator++()
{
    Increment();
    return *this;
}

template <typename TValue, template <typename> class TAllocator>
const typename CVector<TValue, TAllocator>::CIterator::self_type
CVector<TValue, TAllocator>::CIterator::operator++(int)
{
    self Temp = *this;
    Increment();
    return Temp;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CIterator::self_type&
CVector<TValue, TAllocator>::CIterator::operator--()
{
    Decrement();
    return *this;
}

template <typename TValue, template <typename> class TAllocator>
const typename CVector<TValue, TAllocator>::CIterator::self_type
CVector<TValue, TAllocator>::CIterator::operator--(int)
{
    self Temp = *this;
    Decrement();
    return Temp;
}

template <typename TValue, template <typename> class TAllocator>
const typename CVector<TValue, TAllocator>::CIterator::self_type&
CVector<TValue, TAllocator>::CIterator::operator+=(difference_type _Off)
{
    m_pValue += _Off;
    return *this;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CIterator::self_type
CVector<TValue, TAllocator>::CIterator::operator+(difference_type _Off) const
{
    CIterator temp(*this);
    return temp += _Off;
}

template <typename TValue, template <typename> class TAllocator>
const typename CVector<TValue, TAllocator>::CIterator::self_type&
CVector<TValue, TAllocator>::CIterator::operator-=(difference_type _Off)
{
    m_pValue -= _Off;
    return *this;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::CIterator::self_type
CVector<TValue, TAllocator>::CIterator::operator-(difference_type _Off) const
{
    CIterator temp(*this);
    return temp -= _Off;
}

///////////////////////// VECTOR



template <typename TValue, template <typename> class TAllocator>
CVector<TValue, TAllocator>::CVector()
    : m_Allocator()
    , m_Capacity(s_DefaultCapacity)
    , m_Increase(s_DefaultIncrease)
    , m_ElementCount(0)
    , m_pData(0)
{
    m_pData = m_Allocator.Allocate(m_Capacity);
}

template <typename TValue, template <typename> class TAllocator>
CVector<TValue, TAllocator>::CVector(int _Capacity, int _Increase)
    : m_Allocator()
    , m_Capacity(_Capacity)
    , m_Increase(_Increase)
    , m_ElementCount(0)
    , m_pData(0)
{
    m_data = m_Allocator.Allocate(m_Capacity);
}

template <typename TValue, template <typename> class TAllocator>
CVector<TValue, TAllocator>::CVector(const self_type& _rVector)
    : m_Allocator()
    , m_Capacity(_rVector.m_Capacity)
    , m_Increase(_rVector.m_Increase)
    , m_ElementCount(0)
    , m_pData(0)
{
    m_data = m_Allocator.Allocate(m_Capacity);
    
    // todo: batch insertion
    for (auto it = _rVector.Begin(); it != _rVector.End(); ++it)
        PushBack(*it);
}

template <typename TValue, template <typename> class TAllocator>
CVector<TValue, TAllocator>::~CVector()
{
    Remove(Begin(), End());
    m_Allocator.Deallocate(m_pData, m_Capacity);
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::self_type& CVector<TValue, TAllocator>::operator=(const self_type& _rVector)
{
    if (this != &_rVector)
    {
        // todo: assign

    }
    return *this;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::iterator CVector<TValue, TAllocator>::Begin()
{
    return m_pData;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::const_iterator CVector<TValue, TAllocator>::Begin() const
{
    return m_pData;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::reverse_iterator CVector<TValue, TAllocator>::RBegin()
{
    return m_pData + m_ElementCount - 1;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::const_reverse_iterator CVector<TValue, TAllocator>::RBegin() const
{
    return m_pData + m_ElementCount - 1;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::iterator CVector<TValue, TAllocator>::End()
{
    return m_pData + m_ElementCount;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::const_iterator CVector<TValue, TAllocator>::End() const
{
    return m_pData + m_ElementCount;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::reverse_iterator CVector<TValue, TAllocator>::REnd()
{
    return m_pData - m_ElementCount;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::const_reverse_iterator CVector<TValue, TAllocator>::REnd() const
{
    return m_pData - m_ElementCount;
}

template <typename TValue, template <typename> class TAllocator>
void CVector<TValue, TAllocator>::PushBack(value_const_reference_type _rItem)
{
    if (m_ElementCount == m_Capacity && !Resize())
    {
        return;
    }

    m_Allocator.Construct(m_pData + m_ElementCount, _rItem);
    ++m_ElementCount;
}

template <typename TValue, template <typename> class TAllocator>
void CVector<TValue, TAllocator>::PopBack()
{
    value_pointer_type pMem = (--End()).m_pValue;
    m_Allocator.Destroy(pMem);
    --m_ElementCount;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::iterator CVector<TValue, TAllocator>::Remove(iterator _Pos)
{
    m_Allocator.Destroy(_Pos.m_pValue);
    ShiftLeft(++_Pos, 1);
    --m_ElementCount;
    return _Pos;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::iterator CVector<TValue, TAllocator>::Remove(iterator _First, iterator _Last)
{
    for (iterator It = _First; It != _Last; ++It)
    {
        m_Allocator.Destroy(It.m_pValue);
    }
    
    int distance = (_Last.m_pValue - _First.m_pValue) / sizeof(value_type);
    ShiftLeft(_Last, distance);
    m_ElementCount -= distance;

    return _First;
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::value_reference_type CVector<TValue, TAllocator>::operator[](size_type _Index) throw()
{
    return *(m_pData + _Index);
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::value_const_reference_type CVector<TValue, TAllocator>::operator[](size_type _Index) const throw()
{
    return *(m_pData + _Index);
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::value_reference_type CVector<TValue, TAllocator>::At(size_type _Index)
{
    if (_Index >= m_ElementCount)
    {
        throw std::exception("index out of range");
    }
    
    return *(m_pData + _Index);
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::value_const_reference_type CVector<TValue, TAllocator>::At(size_type _Index) const
{
    if (_Index >= m_ElementCount)
    {
        throw std::exception("index out of range");
    }

    return *(m_pData + _Index);
}

template <typename TValue, template <typename> class TAllocator>
typename CVector<TValue, TAllocator>::size_type CVector<TValue, TAllocator>::GetCount() const
{
    return m_ElementCount;
}

template <typename TValue, template <typename> class TAllocator>
bool CVector<TValue, TAllocator>::Resize(size_type _minIncrease = 1)
{
    size_type targetCapacity = m_Capacity + (_minIncrease > m_Increase ? _minIncrease : m_Increase);
    value_pointer_type pTempData = m_Allocator.Allocate(targetCapacity);

    for (size_type Pos = 0; Pos < m_ElementCount; ++Pos)
    {
        m_Allocator.Construct(pTempData + Pos, *(m_pData + Pos));
        m_Allocator.Destroy(m_pData + Pos);
    }

    m_Allocator.Deallocate(m_pData, m_Capacity);
    m_pData = pTempData;
    m_Capacity = targetCapacity;

    return true;
}

template <typename TValue, template <typename> class TAllocator>
void CVector<TValue, TAllocator>::ShiftLeft(iterator _Begin, int _Count)
{
    iterator TargetIt(_Begin - _Count);

    for (; _Begin != End(); ++TargetIt, ++_Begin)
    {
        *TargetIt = *_Begin;
    }

    for (; TargetIt != End(); ++TargetIt)
    {
        m_Allocator.Destroy(TargetIt.m_pValue);
    }
}

template <typename TValue, template <typename> class TAllocator>
void CVector<TValue, TAllocator>::ShiftRight(iterator _Begin, int _Count)
{
    iterator targetIt = End() + (_Count - 1);
    iterator sourceIt = End() - 1;

    for (; targetIt != --End(); --sourceIt, --targetIt)
    {
        m_Allocator.Construct(targetIt.m_pValue, *sourceIt);
    }

    for (; sourceIt != --_Begin; --sourceIt, --targetIt)
    {
        *targetIt = *sourceIt;
    }
}


    } // namespace CNT
} // namespace BASE

#endif // __INCLUDE_VECTOR_H_