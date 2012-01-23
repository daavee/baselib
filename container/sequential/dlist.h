#ifndef __INCLUDE_DOUBLE_LINKED_LIST_H_
#define __INCLUDE_DOUBLE_LINKED_LIST_H_

/**
 * todo:
 * - operator=
 * - range functions
 * - ...
 **/

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
#include "../../memory/allocator.h"

namespace BASE {
    namespace CNT {

            
using BASE::MEM::CAllocator;

/**
 * Representing a double-linked-list.
 * Inserted values will be copied and the list will take care
 * of allocated memory for copies. Allocator has to be from
 * this library or wrapped with CStdAllocatorWrapper.
 **/
template <typename T, template <typename> class TAllocator = CAllocator>
class CDoubleLinkedList
{
public: // public forward declarations

    class CConstIterator;
    class CIterator;
    class CConstReverseIterator;
    class CReverseIterator;

private: // private forward declarations

    struct SLink;
    struct SNode;

public: // public typdefs

    typedef T                 value_type;
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;
    typedef value_type&       reference;
    typedef const value_type& const_reference;
    typedef size_t            size_type;
    typedef int               index_type;

    typedef TAllocator<T>      allocator_type;

    typedef CDoubleLinkedList<T, TAllocator> self;

    typedef CIterator             iterator;
    typedef CConstIterator        const_iterator;
    typedef CReverseIterator      reverse_iterator;
    typedef CConstReverseIterator const_reverse_iterator;

private: // private typedefs

    typedef SLink link_type;
    typedef SNode node_type;

    //typedef typename allocator_type::template SRebind<node_type>::other node_allocator_type;
    typedef TAllocator<node_type> node_allocator_type;

public: // ctor, dtor

    CDoubleLinkedList(const allocator_type& _Allocator = allocator_type());
    CDoubleLinkedList(const CDoubleLinkedList<T, TAllocator>& _rList);
    ~CDoubleLinkedList();

public: // iterator creation

    iterator               Begin();                                         // returns iterator to first element
    const_iterator         Begin() const;                                   // returns const_iterator to first element
    reverse_iterator       RBegin();                                        // returns reverse_iterator to first element
    const_reverse_iterator RBegin() const;                                  // returns const_reverse_iterator to first element

    iterator               End();                                           // returns iterator to the first invalid element
    const_iterator         End() const;                                     // returns const_iterator to the first invalid element
    reverse_iterator       REnd();                                          // returns reverse_iterator to the first invalid element
    const_reverse_iterator REnd() const;                                    // returns const_reverse_iterator to the first invalid element

public: // list operations

    void PushBack(const_reference _rElement);                               // insert element at the end
    void PushFront(const_reference _rElement);                              // insert element at the front
    void PopBack();                                                         // remove last element
    void PopFront();                                                        // remove first element

    iterator Insert(iterator _Pos, const_reference _rElement);              // insert element infront of iterator
    iterator Remove(iterator _Pos);                                         // remove element at iterator

    void Insert(iterator _Pos, const_iterator _First, const_iterator _Last);    // insert elements _First to _Last from another list to _Pos

    void Clear();                                                           // clear the list of all inserted elements

public: // unintentional

    iterator        Insert(index_type _Index, const_reference _rElement);   // insert element at index
    iterator        Remove(index_type _Index);                              // remove element at index
    reference       GetElementAt(index_type _Index);                        // return element at index
    const_reference GetElementAt(index_type _Index) const;                  // return const element at index

public: // list properties

    bool      IsEmpty() const;                                              // return if list is empty
    size_type GetElementCount() const;                                      // return number of elements in list

public: // iterator declaration

    class CConstIterator
    {
    public:

        friend typename CDoubleLinkedList<T, TAllocator>;

    public:

        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef SLink link_type;
        typedef SNode node_type;
        
        typedef typename CDoubleLinkedList<T, TAllocator>::CConstIterator self;

    public: // ctor, dtor

        CConstIterator(const self& _rIterator);

    private: // private ctor

        CConstIterator(link_type* _pNode);

    public: // exposed operations

        bool operator==(const self& _rRhs) const;
        bool operator!=(const self& _rRhs) const;

        const_reference operator*() const;
        const_pointer   operator->() const;

        self operator++();
        self operator++(int);
        self operator--();
        self operator--(int);

    private: // member

        link_type* m_pLink;

    private: // internal operations

        void Increment();
        void Decrement();
    };

    class CIterator : public CConstIterator
    {
    public:

        friend typename CDoubleLinkedList<T, TAllocator>;

    public:

        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef SLink link_type;
        typedef SNode node_type;

        typedef typename CDoubleLinkedList<T, TAllocator>::CIterator self;

    public:

        CIterator(const self& _rIt);

    private:

        CIterator(link_type* _pLink);

    public:

        reference operator*() const;
        pointer   operator->() const;

        self operator++();
        self operator++(int);
        self operator--();
        self operator--(int);
    };

    class CConstReverseIterator
    {
    public:

        friend typename CDoubleLinkedList<T, TAllocator>;

    public:

        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef SLink link_type;
        typedef SNode node_type;

        typedef typename CDoubleLinkedList<T, TAllocator>::CConstReverseIterator self;

    public: // ctor, dtor

        CConstReverseIterator(const self& _rIterator);

    private:

        CConstReverseIterator(link_type* _pNode);

    public: // exposed operations

        bool operator==(const self& _rRhs) const;
        bool operator!=(const self& _rRhs) const;

        const_reference operator*() const;
        const_pointer   operator->() const;

        self operator++();
        self operator++(int);
        self operator--();
        self operator--(int);

    private: // member

        link_type* m_pLink;

    private: // internal operations

        void Increment();
        void Decrement();
    };

    class CReverseIterator : public CConstReverseIterator
    {
    public:

        friend typename CDoubleLinkedList<T, TAllocator>;

    public:

        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef SLink link_type;
        typedef SNode node_type;

        typedef typename CDoubleLinkedList<T, TAllocator>::CReverseIterator self;

    public:

        CReverseIterator(const self& _rIt);

    private:

        CReverseIterator(link_type* _pLink);

    public:

        reference operator*() const;
        pointer   operator->() const;

        self operator++();
        self operator++(int);
        self operator--();
        self operator--(int);
    };

private: // node declaration

    struct SLink
    {
        link_type* m_pPrev;
        link_type* m_pNext;
    };

    struct SNode : public SLink
    {
        value_type m_Element;
    };

private: // member

    allocator_type      m_Allocator;
    node_allocator_type m_NodeAllocator;
    link_type           m_Anchor;

private: // internal methods

    iterator GetIteratorByIndex(index_type _Index);
};

/*************************************************************************
 * CONST ITERATOR SUBSECTION
 *************************************************************************/

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::CConstIterator::CConstIterator(link_type* _pLink)
    : m_pLink(_pLink)
{

}

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::CConstIterator::CConstIterator(const self& _rIt)
    : m_pLink(_rIt.m_pLink)
{

}

template <typename T, template <typename> class TAllocator>
bool
CDoubleLinkedList<T, TAllocator>::CConstIterator::operator==(const self& _rRhs) const
{
    return this->m_pLink == _rRhs.m_pLink;
}

template <typename T, template <typename> class TAllocator>
bool
CDoubleLinkedList<T, TAllocator>::CConstIterator::operator!=(const self& _rRhs) const
{
    return this->m_pLink != _rRhs.m_pLink; // oder: return *this == _rRhs;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstIterator::const_reference
CDoubleLinkedList<T, TAllocator>::CConstIterator::operator*() const
{
    return static_cast<node_type*>(m_pLink)->m_Element;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstIterator::const_pointer
CDoubleLinkedList<T, TAllocator>::CConstIterator::operator->() const
{
    return &(operator*());
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstIterator
CDoubleLinkedList<T, TAllocator>::CConstIterator::operator++()
{
    this->Increment();
    return *this;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstIterator
CDoubleLinkedList<T, TAllocator>::CConstIterator::operator++(int)
{
    self Temp = *this;
    this->Increment();
    return Temp;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstIterator
CDoubleLinkedList<T, TAllocator>::CConstIterator::operator--()
{
    this->Decrement();
    return *this;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstIterator
CDoubleLinkedList<T, TAllocator>::CConstIterator::operator--(int)
{
    self Temp = *this;
    this->Decrement();
    return Temp;
}

template <typename T, template <typename> class TAllocator>
void
CDoubleLinkedList<T, TAllocator>::CConstIterator::Increment()
{
    m_pLink = m_pLink->m_pNext;
}

template <typename T, template <typename> class TAllocator>
void
CDoubleLinkedList<T, TAllocator>::CConstIterator::Decrement()
{
    m_pLink = m_pLink->m_pPrev;
}

/*************************************************************************
 * ITERATOR SUBSECTION
 *************************************************************************/

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::CIterator::CIterator(link_type* _pLink)
    : CConstIterator(_pLink)
{

}

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::CIterator::CIterator(const self& _rIt)
    : CConstIterator(_rIt)
{

}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CIterator::reference
CDoubleLinkedList<T, TAllocator>::CIterator::operator*() const
{
    return static_cast<node_type*>(m_pLink)->m_Element;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CIterator::pointer
CDoubleLinkedList<T, TAllocator>::CIterator::operator->() const
{
    return &(operator*());
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CIterator
CDoubleLinkedList<T, TAllocator>::CIterator::operator++()
{
    Increment();
    return *this;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CIterator
CDoubleLinkedList<T, TAllocator>::CIterator::operator++(int)
{
    self Temp = *this;
    Increment();
    return Temp;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CIterator
CDoubleLinkedList<T, TAllocator>::CIterator::operator--()
{
    Decrement();
    return *this;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CIterator
CDoubleLinkedList<T, TAllocator>::CIterator::operator--(int)
{
    self Temp = *this;
    Decrement();
    return Temp;
}

/*************************************************************************
 * CONST REVERSE ITERATOR SUBSECTION
 *************************************************************************/

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::CConstReverseIterator(link_type* _pLink)
    : m_pLink(_pLink)
{

}

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::CConstReverseIterator(const self& _rIt)
    : m_pLink(_rIt.m_pLink)
{

}

template <typename T, template <typename> class TAllocator>
bool
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::operator==(const self& _rRhs) const
{
    return this->m_pLink == _rRhs.m_pLink;
}

template <typename T, template <typename> class TAllocator>
bool
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::operator!=(const self& _rRhs) const
{
    return this->m_pLink != _rRhs.m_pLink; // oder: return *this == _rRhs;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::const_reference
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::operator*() const
{
    return static_cast<node_type*>(m_pLink)->m_Element;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::const_pointer
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::operator->() const
{
    return &(operator*());
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstReverseIterator
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::operator++()
{
    this->Increment();
    return *this;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstReverseIterator
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::operator++(int)
{
    self Temp = *this;
    this->Increment();
    return Temp;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstReverseIterator
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::operator--()
{
    this->Decrement();
    return *this;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CConstReverseIterator
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::operator--(int)
{
    self Temp = *this;
    this->Decrement();
    return Temp;
}

template <typename T, template <typename> class TAllocator>
void
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::Increment()
{
    m_pLink = m_pLink->m_pPrev;
}

template <typename T, template <typename> class TAllocator>
void
CDoubleLinkedList<T, TAllocator>::CConstReverseIterator::Decrement()
{
    m_pLink = m_pLink->m_pNext;
}

/*************************************************************************
 * REVERSE ITERATOR SUBSECTION
 *************************************************************************/

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::CReverseIterator::CReverseIterator(link_type* _pLink)
    : CConstReverseIterator(_pLink)
{

}

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::CReverseIterator::CReverseIterator(const self& _rIt)
    : CConstReverseIterator(_rIt)
{

}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CReverseIterator::reference
CDoubleLinkedList<T, TAllocator>::CReverseIterator::operator*() const
{
    return static_cast<node_type*>(m_pLink)->m_Element;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CReverseIterator::pointer
CDoubleLinkedList<T, TAllocator>::CReverseIterator::operator->() const
{
    return &(operator*());
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CReverseIterator
CDoubleLinkedList<T, TAllocator>::CReverseIterator::operator++()
{
    this->Increment();
    return *this;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CReverseIterator
CDoubleLinkedList<T, TAllocator>::CReverseIterator::operator++(int)
{
    self Temp = *this;
    this->Increment();
    return Temp;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CReverseIterator
CDoubleLinkedList<T, TAllocator>::CReverseIterator::operator--()
{
    this->Decrement();
    return *this;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::CReverseIterator
CDoubleLinkedList<T, TAllocator>::CReverseIterator::operator--(int)
{
    self Temp = *this;
    this->Decrement();
    return Temp;
}

/*************************************************************************
 * DOUBLE LINKED LIST SUBSECTION
 *************************************************************************/

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::CDoubleLinkedList(const allocator_type& _Allocator)
    : m_Allocator(_Allocator)
    , m_Anchor()
{
    m_Anchor.m_pNext = &m_Anchor;
    m_Anchor.m_pPrev = &m_Anchor;
}

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::CDoubleLinkedList(const self& _rList)
    : m_Anchor()
{
    m_Anchor.m_pNext = &m_Anchor;
    m_Anchor.m_pPrev = &m_Anchor;
    Insert(Begin(), _rList.Begin(), _rList.End());
}

template <typename T, template <typename> class TAllocator>
CDoubleLinkedList<T, TAllocator>::~CDoubleLinkedList()
{
    Clear();
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::iterator
CDoubleLinkedList<T, TAllocator>::Begin()
{
    return m_Anchor.m_pNext;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::const_iterator
CDoubleLinkedList<T, TAllocator>::Begin() const
{
    return m_Anchor.m_pNext;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::reverse_iterator
CDoubleLinkedList<T, TAllocator>::RBegin()
{
    return m_Anchor.m_pPrev;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::const_reverse_iterator
CDoubleLinkedList<T, TAllocator>::RBegin() const
{
    return m_Anchor.m_pPrev;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::iterator
CDoubleLinkedList<T, TAllocator>::End()
{
    return &m_Anchor;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::const_iterator
CDoubleLinkedList<T, TAllocator>::End() const
{
    //return &m_Anchor;
    return const_cast<link_type*>(&m_Anchor);
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::reverse_iterator
CDoubleLinkedList<T, TAllocator>::REnd()
{
    return &m_Anchor;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::const_reverse_iterator
CDoubleLinkedList<T, TAllocator>::REnd() const
{
    //return &m_Anchor;
    return const_cast<link_type*>(&m_Anchor);
}

template <typename T, template <typename> class TAllocator>
void
CDoubleLinkedList<T, TAllocator>::PushBack(const_reference _rElement)
{
    Insert(End(), _rElement);
}

template <typename T, template <typename> class TAllocator>
void
CDoubleLinkedList<T, TAllocator>::PushFront(const_reference _rElement)
{
    Insert(Begin(), _rElement);
}

template <typename T, template <typename> class TAllocator>
void
CDoubleLinkedList<T, TAllocator>::PopBack()
{
    Remove(--End());
}

template <typename T, template <typename> class TAllocator>
void
CDoubleLinkedList<T, TAllocator>::PopFront()
{
    Remove(Begin());
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::iterator
CDoubleLinkedList<T, TAllocator>::Insert(iterator _Pos, const_reference _rElement)
{
    node_type* pTemp = m_NodeAllocator.Allocate(1);
    m_NodeAllocator.Construct(pTemp, node_type());
    pTemp->m_Element = _rElement;
    pTemp->m_pPrev = _Pos.m_pLink->m_pPrev;
    pTemp->m_pNext = _Pos.m_pLink;
    _Pos.m_pLink->m_pPrev->m_pNext = pTemp;
    _Pos.m_pLink->m_pPrev = pTemp;
    return pTemp;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::iterator
CDoubleLinkedList<T, TAllocator>::Remove(iterator _Pos)
{
    assert(_Pos.m_pLink != &m_Anchor && "invalid iterator");
    link_type* pPrevLink = _Pos.m_pLink->m_pPrev;
    link_type* pNextLink = _Pos.m_pLink->m_pNext;
    node_type* pNode = static_cast<node_type*>(_Pos.m_pLink);
    pPrevLink->m_pNext = pNextLink;
    pNextLink->m_pPrev = pPrevLink;
    m_NodeAllocator.Destroy(pNode);
    m_NodeAllocator.Deallocate(pNode, 1);
    return pNextLink;
}

template <typename T, template <typename> class TAllocator>
void
CDoubleLinkedList<T, TAllocator>::Insert(iterator _Pos, const_iterator _First, const_iterator _Last)
{
    for (; _First != _Last; ++_First)
    {
        Insert(_Pos, *_First);
    }
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::iterator
CDoubleLinkedList<T, TAllocator>::Insert(index_type _Index, const_reference _rElement)
{
    return Insert(GetIteratorByIndex(_Index), _rElement);
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::iterator
CDoubleLinkedList<T, TAllocator>::Remove(index_type _Index)
{
    return Remove(GetIteratorByIndex(_Index));
}

template <typename T, template <typename> class TAllocator>
void
CDoubleLinkedList<T, TAllocator>::Clear()
{
    node_type* pCurrent = static_cast<node_type*>(m_Anchor.m_pNext);
    while (pCurrent != &m_Anchor)
    {
        node_type* pTemp = pCurrent;
        pCurrent = static_cast<node_type*>(pCurrent->m_pNext);
        m_NodeAllocator.Destroy(pTemp);
        m_NodeAllocator.Deallocate(pTemp, 1);
    }
    m_Anchor.m_pPrev = &m_Anchor;
    m_Anchor.m_pNext = &m_Anchor;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::reference
CDoubleLinkedList<T, TAllocator>::GetElementAt(index_type _Index)
{
    return *GetIteratorByIndex(_Index);
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::const_reference
CDoubleLinkedList<T, TAllocator>::GetElementAt(index_type _Index) const
{
    return *GetIteratorByIndex(_Index);
}

template <typename T, template <typename> class TAllocator>
bool
CDoubleLinkedList<T, TAllocator>::IsEmpty() const
{
    return m_Anchor.m_pNext == &m_Anchor;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::size_type
CDoubleLinkedList<T, TAllocator>::GetElementCount() const
{
    size_type Size = 0;
    for (const_iterator It = Begin(); It != End(); ++It, ++Size);
    return Size;
}

template <typename T, template <typename> class TAllocator>
typename CDoubleLinkedList<T, TAllocator>::iterator
CDoubleLinkedList<T, TAllocator>::GetIteratorByIndex(index_type _Index)
{
    iterator It = Begin();
    for (;_Index > 0; --_Index, ++It)
    {
        assert(It != End() && "Index out of bound");
    }
    return It;
}


    } // namespace CNT
} // namespace BASE

#endif // __INCLUDE_DOUBLE_LINKED_LIST_H_

;