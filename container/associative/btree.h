#ifndef __INCLUDE_BINARY_TREE_H_
#define __INCLUDE_BINARY_TREE_H_

/**
 * todo:
 * - c-string compare
 * - everything left ...
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
#include <exception>
#include "../iterator/iterator.h"
#include "../../memory/allocator.h"
#include "../../typetraits/is_cstring.h"
#include "../../utility/hash/nohash.h"

namespace BASE {
    namespace CNT {


/**
 * Representing a binary tree.
 * Inserted values will be copied and the list will take care
 * of allocated memory for copies. Allocator has to be from
 * this library.
 **/
template <
    typename TKey,
    typename TValue,
    template <typename> class THash = BASE::UTIL::SNoHash,
    template <typename> class TAllocator = BASE::MEM::CAllocator
>
class CBinaryTree
{
public: // public forward declarations

    class CConstIterator;
    class CIterator;

private: // private forward declarations

    struct SNode;

public: // public typdefs

    typedef CBinaryTree<TKey, TValue, THash, TAllocator> self_type;

    typedef TKey            key_type;
    typedef key_type&       key_reference_type;
    typedef const key_type& key_const_reference_type;
    typedef key_type*       key_pointer_type;
    
    typedef TValue            value_type;
    typedef value_type&       value_reference_type;
    typedef const value_type& value_const_reference_type;
    typedef value_type*       value_pointer_type;
    
    typedef size_t size_type;

    typedef CIterator                        iterator;
    typedef CConstIterator                   const_iterator;
    typedef CReverseIterator<iterator>       reverse_iterator;
    typedef CReverseIterator<const_iterator> const_reverse_iterator;

private: // private typedefs

    typedef SNode                                  node_type;
    typedef THash<key_type>                        hash_func_type;
    typedef typename hash_func_type::key_hash_type key_hash_type;

    typedef TAllocator<node_type> allocator_type;

public: // ctor, dtor

    CBinaryTree();
    CBinaryTree(const self_type& _rList);                                   // copy ctor
    self_type& operator=(const self_type& _rList);                          // assignment operator

    ~CBinaryTree();

public: // iterator creation

    iterator               Begin();                                         // returns iterator to first element
    const_iterator         Begin() const;                                   // returns const_iterator to first element
    reverse_iterator       RBegin();                                        // returns reverse_iterator to first element
    const_reverse_iterator RBegin() const;                                  // returns const_reverse_iterator to first element

    iterator               End();                                           // returns iterator to the first invalid element
    const_iterator         End() const;                                     // returns const_iterator to the first invalid element
    reverse_iterator       REnd();                                          // returns reverse_iterator to the first invalid element
    const_reverse_iterator REnd() const;                                    // returns const_reverse_iterator to the first invalid element

public: // public operations

    iterator Insert(const key_type& _rKey, const value_type& _rValue);      // insert element infront of iterator
    iterator Remove(iterator _Pos);                                         // remove element at iterator
    iterator Remove(const key_type& _rKey);                                 // remove element by key

    iterator                   Find(const key_type& _rKey) const;           // find element by key
    value_reference_type       GetElement(const key_reference_type _rKey);  // get element by key
    value_const_reference_type GetElement(const key_reference_type _rKey) const;

    void Clear();                                                           // clear the list of all inserted elements

public: // public properties

    bool      IsEmpty() const;                                              // return if list is empty
    size_type GetElementCount() const;                                      // return number of elements in list

public: // iterator declaration

    class CConstIterator : public SIterator<SBidirectionalIteratorTag, TValue>
    {
    public:

        friend typename CBinaryTree<TKey, TValue, THash, TAllocator>;

    public:

        typedef CConstIterator                               self_type;
        typedef SIterator<SBidirectionalIteratorTag, TValue> base_type;

        typedef typename base_type::iterator_tag_type          iterator_tag_type;
        typedef typename base_type::value_type                 value_type;
        typedef typename const base_type::value_reference_type value_reference_type;
        typedef typename const base_type::value_pointer_type   value_pointer_type;
        typedef typename base_type::difference_type            difference_type;

    private:

        typedef typename CBinaryTree::node_type node_type;

    public: // ctor, dtor

        CConstIterator(const self_type& _rIterator);

    private: // private ctor

        CConstIterator(node_type* _pNode);

    public: // exposed operations

        const bool operator==(const self_type& _rRhs) const;
        const bool operator!=(const self_type& _rRhs) const;

        value_reference_type operator*() const;
        value_pointer_type   operator->() const;

        self_type&      operator++();
        const self_type operator++(int);
        self_type&      operator--();
        const self_type operator--(int);

    private: // member

        node_type* m_pNode;

    protected: // internal operations

        void Increment();
        void Decrement();
    };
    
    class CIterator : public CConstIterator
    {
    public:

        friend typename CBinaryTree<TKey, TValue, THash, TAllocator>;

    public:

        typedef CIterator self_type;

    private:

        typedef typename CBinaryTree::node_type node_type;

    public:

        CIterator(const self_type& _rIt);

    private:

        CIterator(node_type* _pLink);

    public:

        value_reference_type operator*() const;
        value_pointer_type   operator->() const;

        self_type&      operator++();
        const self_type operator++(int);
        self_type&      operator--();
        const self_type operator--(int);
    };

private: // node declaration

    struct SNode
    {
        SNode(node_type* _pParent, node_type* _pLeftChild, node_type* _pRightChild, key_hash_type _HashKey, value_type _Value);

        node_type*    m_pParent;
        node_type*    m_pLeftChild;
        node_type*    m_pRightChild;
        key_hash_type m_HashKey;
        value_type    m_Value;
    };

private: // member

    hash_func_type m_HashFunc;
    allocator_type m_Allocator;
    node_type*     m_pRoot;
    size_type      m_ElementCount;

private: // internal methods

    iterator InsertOnChild(node_type** _ppChild, node_type* _pParent, const key_hash_type& _rHashKey, const value_type& _rValue);
    iterator FindOnChild(node_type* _pChild, const key_hash_type& _rHashKey) const;
    SNode*   FindMostLeftChild(node_type* _pChild, node_type* _pParent) const;
    SNode*   FindMostRightChild(node_type* _pChild, node_type* _pParent) const;
    SNode**  GetParentChildLink(node_type* _pChild) const;
    void     SwapNodes(node_type* _pNode1, node_type* _pNode2);
};

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
CBinaryTree<TKey, TValue, THash, TAllocator>::CBinaryTree()
    : m_HashFunc()
    , m_Allocator()
    , m_pRoot(0)
    , m_ElementCount(0)
{
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
CBinaryTree<TKey, TValue, THash, TAllocator>::~CBinaryTree()
{
    Clear();
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::Begin()
{
    return FindMostLeftChild(m_pRoot, 0);
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::const_iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::Begin() const
{
    return FindMostLeftChild(m_pRoot, 0);
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::reverse_iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::RBegin()
{
    return reverse_iterator(FindMostRightChild(m_pRoot, 0));
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::const_reverse_iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::RBegin() const
{
    return const_reverse_iterator(FindMostRightChild(m_pRoot, 0));
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::End()
{
    return 0;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::const_iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::End() const
{
    return 0;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::reverse_iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::REnd()
{
    return reverse_iterator(0);
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::const_reverse_iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::REnd() const
{
    return const_reverse_iterator(0);
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::Insert(const key_type& _rKey, const value_type& _rValue)
{
    return InsertOnChild(&m_pRoot, 0, m_HashFunc(_rKey), _rValue);
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::InsertOnChild(node_type** _ppChild, node_type* _pParent,
    const key_hash_type& _rHashKey, const value_type& _rValue)
{
    if (*_ppChild == 0)
    { // child doesn't exist
        *_ppChild = new SNode(_pParent, 0, 0, _rHashKey, _rValue);
        ++m_ElementCount;

        return *_ppChild;
    }
    else if (_rHashKey < (*_ppChild)->m_HashKey)
    {
        return InsertOnChild(&(*_ppChild)->m_pLeftChild, *_ppChild, _rHashKey, _rValue);
    }
    else if (_rHashKey > (*_ppChild)->m_HashKey)
    {
        return InsertOnChild(&(*_ppChild)->m_pRightChild, *_ppChild, _rHashKey, _rValue);
    }

    return *_ppChild;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::Remove(const key_type& _rKey)
{
    return Remove(Find(_rKey));
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::Remove(iterator _It)
{
    assert(_It != End() && "Invalid iterator for removal.");

    node_type*  pNode = _It.m_pNode; // for convenience
    node_type*  pNextNode = (++_It).m_pNode; // getting next node for further actions and return value
    node_type*  pParent = pNode->m_pParent; // also convenience
    node_type** ppParentLink = GetParentChildLink(pNode); // pointer to the parent's pointer to our node

    if (pNode->m_pLeftChild == 0 && pNode->m_pRightChild == 0)
    { // leaf node
        *ppParentLink = 0;
        delete pNode;
    }
    else if (pNode->m_pLeftChild == 0)
    { // only right leaf
        pNode->m_pRightChild->m_pParent = pParent;
        *ppParentLink = pNode->m_pRightChild;
        delete pNode;
    }
    else if (pNode->m_pRightChild == 0)
    { // only left leaf
        pNode->m_pLeftChild->m_pParent = pParent;
        *ppParentLink = pNode->m_pLeftChild;
        delete pNode;
    }
    else
    { // node has two leaves
        SwapNodes(pNode, pNextNode); // after this operation the tree is inconsistent (no thread-safety)
        Remove(pNode); // pNode now has 1 child max and we can use remove it recursively
    }
    
    return pNextNode;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
void
    CBinaryTree<TKey, TValue, THash, TAllocator>::Clear()
{
    // could think of some more effective ways, that cause no pointer redirection
    for (auto It = Begin(); It != End();)
    {
        Remove(It++);
    }
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::Find(const key_type& _rKey) const
{
    return FindOnChild(m_pRoot, m_HashFunc(_rKey));
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::iterator
    CBinaryTree<TKey, TValue, THash, TAllocator>::FindOnChild(node_type* _pChild, const key_hash_type& _rHashKey) const
{
    if (_pChild == 0)
    {
        return 0;
    }
    else if (_rHashKey < _pChild->m_HashKey)
    {
        return FindOnChild(_pChild->m_pLeftChild, _rHashKey);
    }
    else if (_rHashKey > _pChild->m_HashKey)
    {
        return FindOnChild(_pChild->m_pRightChild, _rHashKey);
    }

    return _pChild;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::value_reference_type
    CBinaryTree<TKey, TValue, THash, TAllocator>::GetElement(const key_reference_type _rKey)
{
    iterator It = Find(_rKey);

    if (It == 0)
    {
        throw std::exception("Element not in binary tree.");
    }

    return *Find(_rKey);
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::value_const_reference_type
    CBinaryTree<TKey, TValue, THash, TAllocator>::GetElement(const key_reference_type _rKey) const
{
    const_iterator It = Find(_rKey);

    if (It == 0)
    {
        throw std::exception("Element not in binary tree.");
    }

    return *Find(_rKey);
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::node_type*
    CBinaryTree<TKey, TValue, THash, TAllocator>::FindMostLeftChild(node_type* _pChild, node_type* _pParent) const
{
    return (_pChild == 0) ? _pParent : FindMostLeftChild(_pChild->m_pLeftChild, _pChild);
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::node_type*
    CBinaryTree<TKey, TValue, THash, TAllocator>::FindMostRightChild(node_type* _pChild, node_type* _pParent) const
{
    return (_pChild == 0) ? _pParent : FindMostRightChild(_pChild->m_pRightChild, _pChild);
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
bool
    CBinaryTree<TKey, TValue, THash, TAllocator>::IsEmpty() const
{
    return m_ElementCount == 0;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::size_type
    CBinaryTree<TKey, TValue, THash, TAllocator>::GetElementCount() const
{
    return m_ElementCount;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::node_type**
    CBinaryTree<TKey, TValue, THash, TAllocator>::GetParentChildLink(node_type* _pChild) const
{
    if (_pChild->m_pParent == 0)
    {
        return const_cast<node_type**>(&m_pRoot);
    }
    else if (_pChild->m_pParent->m_pLeftChild == _pChild)
    {
        return &_pChild->m_pParent->m_pLeftChild;
    }
    else
    {
        return &_pChild->m_pParent->m_pRightChild;
    }
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
void
    CBinaryTree<TKey, TValue, THash, TAllocator>::SwapNodes(node_type* _pNode1, node_type* _pNode2)
{
    assert(_pNode1 != _pNode2 && "Can't swap node with itself.");

    node_type*  pTemp = 0;
    node_type** ppPCLink1 = GetParentChildLink(_pNode1);
    node_type** ppPCLink2 = GetParentChildLink(_pNode2);

    // don't switch order of segments below as it is essential for success
    // swap parent pointer of children
    if (_pNode1->m_pLeftChild  != 0) _pNode1->m_pLeftChild->m_pParent  = _pNode2;
    if (_pNode1->m_pRightChild != 0) _pNode1->m_pRightChild->m_pParent = _pNode2;
    if (_pNode2->m_pLeftChild  != 0) _pNode2->m_pLeftChild->m_pParent  = _pNode1;
    if (_pNode2->m_pRightChild != 0) _pNode2->m_pRightChild->m_pParent = _pNode1;

    // swap parent pointer of nodes
    pTemp              = _pNode1->m_pParent;
    _pNode1->m_pParent = _pNode2->m_pParent;
    _pNode2->m_pParent = pTemp;

    // swap pointer from parents to nodes
    *ppPCLink1 = _pNode2; *ppPCLink2 = _pNode1;

    // swap children pointer of nodes
    pTemp = _pNode1->m_pLeftChild;  _pNode1->m_pLeftChild  = _pNode2->m_pLeftChild;  _pNode2->m_pLeftChild  = pTemp;
    pTemp = _pNode1->m_pRightChild; _pNode1->m_pRightChild = _pNode2->m_pRightChild; _pNode2->m_pRightChild = pTemp;
}

//////////////////////////////////////////////////////////////////////////
// CONST ITERATOR - SECTION
//////////////////////////////////////////////////////////////////////////

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
CBinaryTree<TKey, TValue, THash, TAllocator>::CConstIterator::CConstIterator(node_type* _pNode)
    : m_pNode(_pNode)
{
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
CBinaryTree<TKey, TValue, THash, TAllocator>::CConstIterator::CConstIterator(const self_type& _rIt)
    : m_pNode(_rIt.m_pNode)
{
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
const bool
    CBinaryTree<TKey, TValue, THash, TAllocator>::CConstIterator::operator==(const self_type& _rRhs) const
{
    return m_pNode == _rRhs.m_pNode;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
const bool
    CBinaryTree<TKey, TValue, THash, TAllocator>::CConstIterator::operator!=(const self_type& _rRhs) const
{
    return m_pNode != _rRhs.m_pNode;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
void 
    CBinaryTree<TKey, TValue, THash, TAllocator>::CConstIterator::Increment()
{
    assert(m_pNode != 0 && "Incrementing invalid iterator");

    // we basically have to get one step to the right (child) and then left as much as possible
    // or find the first parent, that we are left of
    node_type* CurrentNode = m_pNode;

    if (CurrentNode->m_pRightChild != 0)
    { // we have a right child
        CurrentNode = CurrentNode->m_pRightChild;
        while (CurrentNode->m_pLeftChild != 0)
        { // go left all the way
            CurrentNode = CurrentNode->m_pLeftChild;
        }
    }
    else
    { // we have no right child
        while (CurrentNode->m_pParent != 0 && CurrentNode->m_pParent->m_pRightChild == CurrentNode)
        { // go top, until we are on the left side of our parent
            CurrentNode = CurrentNode->m_pParent;
        }

        if (CurrentNode->m_pParent == 0)
        { // we arrived the root and found nothing
            CurrentNode = 0;
        }
        else
        { // we are the left child
            CurrentNode = CurrentNode->m_pParent;
        }
    }

    m_pNode = CurrentNode;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
void 
    CBinaryTree<TKey, TValue, THash, TAllocator>::CConstIterator::Decrement()
{
    assert(m_pNode != 0 && "Decrementing invalid iterator");

    // just as Increment() but the other way around
    node_type* CurrentNode = m_pNode;

    if (CurrentNode->m_pLeftChild != 0)
    { // we have a left child
        CurrentNode = CurrentNode->m_pLeftChild;
        while (CurrentNode->m_pRightChild != 0)
        { // go right all the way
            CurrentNode = CurrentNode->m_pRightChild;
        }
    }
    else
    { // we have no left child
        while (CurrentNode->m_pParent != 0 && CurrentNode->m_pParent->m_pLeftChild == CurrentNode)
        { // go top, until we are on the right side of our parent
            CurrentNode = CurrentNode->m_pParent;
        }

        if (CurrentNode->m_pParent == 0)
        { // we arrived the root and found nothing
            CurrentNode = 0;
        }
        else
        { // we are the right child
            CurrentNode = CurrentNode->m_pParent;
        }
    }

    m_pNode = CurrentNode;
}

//////////////////////////////////////////////////////////////////////////
// ITERATOR - SECTION
//////////////////////////////////////////////////////////////////////////

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::CIterator(node_type* _pNode)
    : CConstIterator(_pNode)
{
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::CIterator(const self_type& _rIt)
    : CConstIterator(_rIt)
{
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::value_reference_type
    CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::operator*() const
{
    return m_pNode->m_Value;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::value_pointer_type
    CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::operator->() const
{
    return &(operator*());
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::self_type&
    CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::operator++()
{
    Increment();
    return *this;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
const typename CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::self_type
    CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::operator++(int)
{
    self_type Temp = *this;
    Increment();
    return Temp;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
typename CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::self_type&
    CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::operator--()
{
    Decrement();
    return *this;
}

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
const typename CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::self_type
    CBinaryTree<TKey, TValue, THash, TAllocator>::CIterator::operator--(int)
{
    self_type Temp = *this;
    Decrement();
    return Temp;
}

//////////////////////////////////////////////////////////////////////////
// SNODE - SECTION
//////////////////////////////////////////////////////////////////////////

template <typename TKey, typename TValue, template <typename> class THash, template <typename> class TAllocator>
CBinaryTree<TKey, TValue, THash, TAllocator>::SNode::SNode(node_type* _pParent, node_type* _pLeftChild,
    node_type* _pRightChild, key_hash_type _HashKey, value_type _Value)
    : m_pParent(_pParent)
    , m_pLeftChild(_pLeftChild)
    , m_pRightChild(_pRightChild)
    , m_HashKey(_HashKey)
    , m_Value(_Value)
{
}


    } // namespace CNT
} // namespace BASE

#endif // __INCLUDE_BINARY_TREE_H_
