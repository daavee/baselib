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
        namespace SEQ {

            
using BASE::MEM::CAllocator;

/**
 * Representing a double-linked-list.
 * Inserted values will be copied and the list will take care
 * of allocated memory for copies. Allocator has to be from
 * this library or wrapped with CStdAllocatorWrapper.
 **/
template <typename T, template <typename> class Allocator = CAllocator>
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

    typedef Allocator<T>      allocator_type;

    typedef CDoubleLinkedList<T, Allocator> self;

    typedef CIterator             iterator;
    typedef CConstIterator        const_iterator;
    typedef CReverseIterator      reverse_iterator;
    typedef CConstReverseIterator const_reverse_iterator;

private: // private typedefs

    typedef SLink link_type;
    typedef SNode node_type;

    //typedef typename allocator_type::template SRebind<node_type>::other node_allocator_type;
    typedef Allocator<node_type> node_allocator_type;

public: // ctor, dtor

    CDoubleLinkedList(const allocator_type& _Allocator = allocator_type());
    CDoubleLinkedList(const CDoubleLinkedList<T, Allocator>& _rList);
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

        friend typename CDoubleLinkedList<T, Allocator>;

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
        
        typedef typename CDoubleLinkedList<T, Allocator>::CConstIterator self;

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

        friend typename CDoubleLinkedList<T, Allocator>;

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

        typedef typename CDoubleLinkedList<T, Allocator>::CIterator self;

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

        friend typename CDoubleLinkedList<T, Allocator>;

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

        typedef typename CDoubleLinkedList<T, Allocator>::CConstReverseIterator self;

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

        friend typename CDoubleLinkedList<T, Allocator>;

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

        typedef typename CDoubleLinkedList<T, Allocator>::CReverseIterator self;

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

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::CConstIterator::CConstIterator(link_type* _pLink)
    : m_pLink(_pLink)
{

}

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::CConstIterator::CConstIterator(const self& _rIt)
    : m_pLink(_rIt.m_pLink)
{

}

template <typename T, template <typename> class Allocator>
bool
CDoubleLinkedList<T, Allocator>::CConstIterator::operator==(const self& _rRhs) const
{
    return this->m_pLink == _rRhs.m_pLink;
}

template <typename T, template <typename> class Allocator>
bool
CDoubleLinkedList<T, Allocator>::CConstIterator::operator!=(const self& _rRhs) const
{
    return this->m_pLink != _rRhs.m_pLink; // oder: return *this == _rRhs;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstIterator::const_reference
CDoubleLinkedList<T, Allocator>::CConstIterator::operator*() const
{
    return static_cast<node_type*>(m_pLink)->m_Element;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstIterator::const_pointer
CDoubleLinkedList<T, Allocator>::CConstIterator::operator->() const
{
    return &(operator*());
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstIterator
CDoubleLinkedList<T, Allocator>::CConstIterator::operator++()
{
    this->Increment();
    return *this;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstIterator
CDoubleLinkedList<T, Allocator>::CConstIterator::operator++(int)
{
    self Temp = *this;
    this->Increment();
    return Temp;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstIterator
CDoubleLinkedList<T, Allocator>::CConstIterator::operator--()
{
    this->Decrement();
    return *this;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstIterator
CDoubleLinkedList<T, Allocator>::CConstIterator::operator--(int)
{
    self Temp = *this;
    this->Decrement();
    return Temp;
}

template <typename T, template <typename> class Allocator>
void
CDoubleLinkedList<T, Allocator>::CConstIterator::Increment()
{
    m_pLink = m_pLink->m_pNext;
}

template <typename T, template <typename> class Allocator>
void
CDoubleLinkedList<T, Allocator>::CConstIterator::Decrement()
{
    m_pLink = m_pLink->m_pPrev;
}

/*************************************************************************
 * ITERATOR SUBSECTION
 *************************************************************************/

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::CIterator::CIterator(link_type* _pLink)
    : CConstIterator(_pLink)
{

}

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::CIterator::CIterator(const self& _rIt)
    : CConstIterator(_rIt)
{

}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CIterator::reference
CDoubleLinkedList<T, Allocator>::CIterator::operator*() const
{
    return static_cast<node_type*>(m_pLink)->m_Element;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CIterator::pointer
CDoubleLinkedList<T, Allocator>::CIterator::operator->() const
{
    return &(operator*());
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CIterator
CDoubleLinkedList<T, Allocator>::CIterator::operator++()
{
    this->Increment();
    return *this;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CIterator
CDoubleLinkedList<T, Allocator>::CIterator::operator++(int)
{
    self Temp = *this;
    this->Increment();
    return Temp;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CIterator
CDoubleLinkedList<T, Allocator>::CIterator::operator--()
{
    this->Decrement();
    return *this;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CIterator
CDoubleLinkedList<T, Allocator>::CIterator::operator--(int)
{
    self Temp = *this;
    this->Decrement();
    return Temp;
}

/*************************************************************************
 * CONST REVERSE ITERATOR SUBSECTION
 *************************************************************************/

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::CConstReverseIterator(link_type* _pLink)
    : m_pLink(_pLink)
{

}

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::CConstReverseIterator(const self& _rIt)
    : m_pLink(_rIt.m_pLink)
{

}

template <typename T, template <typename> class Allocator>
bool
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::operator==(const self& _rRhs) const
{
    return this->m_pLink == _rRhs.m_pLink;
}

template <typename T, template <typename> class Allocator>
bool
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::operator!=(const self& _rRhs) const
{
    return this->m_pLink != _rRhs.m_pLink; // oder: return *this == _rRhs;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstReverseIterator::const_reference
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::operator*() const
{
    return static_cast<node_type*>(m_pLink)->m_Element;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstReverseIterator::const_pointer
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::operator->() const
{
    return &(operator*());
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstReverseIterator
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::operator++()
{
    this->Increment();
    return *this;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstReverseIterator
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::operator++(int)
{
    self Temp = *this;
    this->Increment();
    return Temp;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstReverseIterator
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::operator--()
{
    this->Decrement();
    return *this;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CConstReverseIterator
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::operator--(int)
{
    self Temp = *this;
    this->Decrement();
    return Temp;
}

template <typename T, template <typename> class Allocator>
void
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::Increment()
{
    m_pLink = m_pLink->m_pPrev;
}

template <typename T, template <typename> class Allocator>
void
CDoubleLinkedList<T, Allocator>::CConstReverseIterator::Decrement()
{
    m_pLink = m_pLink->m_pNext;
}

/*************************************************************************
 * REVERSE ITERATOR SUBSECTION
 *************************************************************************/

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::CReverseIterator::CReverseIterator(link_type* _pLink)
    : CConstReverseIterator(_pLink)
{

}

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::CReverseIterator::CReverseIterator(const self& _rIt)
    : CConstReverseIterator(_rIt)
{

}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CReverseIterator::reference
CDoubleLinkedList<T, Allocator>::CReverseIterator::operator*() const
{
    return static_cast<node_type*>(m_pLink)->m_Element;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CReverseIterator::pointer
CDoubleLinkedList<T, Allocator>::CReverseIterator::operator->() const
{
    return &(operator*());
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CReverseIterator
CDoubleLinkedList<T, Allocator>::CReverseIterator::operator++()
{
    this->Increment();
    return *this;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CReverseIterator
CDoubleLinkedList<T, Allocator>::CReverseIterator::operator++(int)
{
    self Temp = *this;
    this->Increment();
    return Temp;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CReverseIterator
CDoubleLinkedList<T, Allocator>::CReverseIterator::operator--()
{
    this->Decrement();
    return *this;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::CReverseIterator
CDoubleLinkedList<T, Allocator>::CReverseIterator::operator--(int)
{
    self Temp = *this;
    this->Decrement();
    return Temp;
}

/*************************************************************************
 * DOUBLE LINKED LIST SUBSECTION
 *************************************************************************/

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::CDoubleLinkedList(const allocator_type& _Allocator)
    : m_Allocator(_Allocator)
    , m_Anchor()
{
    m_Anchor.m_pNext = &m_Anchor;
    m_Anchor.m_pPrev = &m_Anchor;
}

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::CDoubleLinkedList(const self& _rList)
    : m_Anchor()
{
    m_Anchor.m_pNext = &m_Anchor;
    m_Anchor.m_pPrev = &m_Anchor;
    Insert(Begin(), _rList.Begin(), _rList.End());
}

template <typename T, template <typename> class Allocator>
CDoubleLinkedList<T, Allocator>::~CDoubleLinkedList()
{
    Clear();
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::iterator
CDoubleLinkedList<T, Allocator>::Begin()
{
    return m_Anchor.m_pNext;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::const_iterator
CDoubleLinkedList<T, Allocator>::Begin() const
{
    return m_Anchor.m_pNext;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::reverse_iterator
CDoubleLinkedList<T, Allocator>::RBegin()
{
    return m_Anchor.m_pPrev;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::const_reverse_iterator
CDoubleLinkedList<T, Allocator>::RBegin() const
{
    return m_Anchor.m_pPrev;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::iterator
CDoubleLinkedList<T, Allocator>::End()
{
    return &m_Anchor;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::const_iterator
CDoubleLinkedList<T, Allocator>::End() const
{
    //return &m_Anchor;
    return const_cast<link_type*>(&m_Anchor);
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::reverse_iterator
CDoubleLinkedList<T, Allocator>::REnd()
{
    return &m_Anchor;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::const_reverse_iterator
CDoubleLinkedList<T, Allocator>::REnd() const
{
    //return &m_Anchor;
    return const_cast<link_type*>(&m_Anchor);
}

template <typename T, template <typename> class Allocator>
void
CDoubleLinkedList<T, Allocator>::PushBack(const_reference _rElement)
{
    Insert(End(), _rElement);
}

template <typename T, template <typename> class Allocator>
void
CDoubleLinkedList<T, Allocator>::PushFront(const_reference _rElement)
{
    Insert(Begin(), _rElement);
}

template <typename T, template <typename> class Allocator>
void
CDoubleLinkedList<T, Allocator>::PopBack()
{
    Remove(--End());
}

template <typename T, template <typename> class Allocator>
void
CDoubleLinkedList<T, Allocator>::PopFront()
{
    Remove(Begin());
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::iterator
CDoubleLinkedList<T, Allocator>::Insert(iterator _Pos, const_reference _rElement)
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

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::iterator
CDoubleLinkedList<T, Allocator>::Remove(iterator _Pos)
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

template <typename T, template <typename> class Allocator>
void
CDoubleLinkedList<T, Allocator>::Insert(iterator _Pos, const_iterator _First, const_iterator _Last)
{
    for (; _First != _Last; ++_First)
    {
        Insert(_Pos, *_First);
    }
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::iterator
CDoubleLinkedList<T, Allocator>::Insert(index_type _Index, const_reference _rElement)
{
    return Insert(GetIteratorByIndex(_Index), _rElement);
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::iterator
CDoubleLinkedList<T, Allocator>::Remove(index_type _Index)
{
    return Remove(GetIteratorByIndex(_Index));
}

template <typename T, template <typename> class Allocator>
void
CDoubleLinkedList<T, Allocator>::Clear()
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

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::reference
CDoubleLinkedList<T, Allocator>::GetElementAt(index_type _Index)
{
    return *GetIteratorByIndex(_Index);
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::const_reference
CDoubleLinkedList<T, Allocator>::GetElementAt(index_type _Index) const
{
    return *GetIteratorByIndex(_Index);
}

template <typename T, template <typename> class Allocator>
bool
CDoubleLinkedList<T, Allocator>::IsEmpty() const
{
    return m_Anchor.m_pNext == &m_Anchor;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::size_type
CDoubleLinkedList<T, Allocator>::GetElementCount() const
{
    size_type Size = 0;
    for (const_iterator It = Begin(); It != End(); ++It, ++Size);
    return Size;
}

template <typename T, template <typename> class Allocator>
typename CDoubleLinkedList<T, Allocator>::iterator
CDoubleLinkedList<T, Allocator>::GetIteratorByIndex(index_type _Index)
{
    iterator It = Begin();
    for (;_Index > 0; --_Index, ++It)
    {
        assert(It != End() && "Index out of bound");
    }
    return It;
}


        } // namespace SEQ
    } // namespace CNT
} // namespace BASE

#endif // __INCLUDE_DOUBLE_LINKED_LIST_H_

;