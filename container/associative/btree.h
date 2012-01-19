#ifndef __INCLUDE_BINARY_TREE_H_
#define __INCLUDE_BINARY_TREE_H_

/**
 * todo:
 * - everything ...
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
#include "../../utility/hash/dummyhash.h"

namespace BASE {
    namespace CNT {
        namespace SEQ {

            
using BASE::MEM::CAllocator;
using BASE::UTIL::HASH::SDummyHash;

/**
 * Representing a binary tree.
 * Inserted values will be copied and the list will take care
 * of allocated memory for copies. Allocator has to be from
 * this library.
 **/
template <typename Key, typename Value, template <typename> class Hash = SDummyHash, template <typename> class Allocator = CAllocator>
class CBinaryTree
{
public: // public forward declarations

    class CConstIterator;
    class CIterator;
    class CConstReverseIterator;
    class CReverseIterator;

private: // private forward declarations

    struct SNode;

public: // public typdefs

    typedef Key    key_type;
    typedef Value  value_type;
    typedef size_t size_type;

    typedef Allocator<T> allocator_type;

    typedef CBinaryTree<T, Allocator> self;

    typedef CIterator             iterator;
    typedef CConstIterator        const_iterator;
    typedef CReverseIterator      reverse_iterator;
    typedef CConstReverseIterator const_reverse_iterator;

private: // private typedefs

    typedef SNode                     node_type;
    typedef Hash                      hash_func_type;
    typedef hash_func_type::hash_type hash_key_type;

    //typedef typename allocator_type::template SRebind<node_type>::other node_allocator_type;
    typedef Allocator<node_type> node_allocator_type;

public: // ctor, dtor

    CBinaryTree();
    CBinaryTree(const self& _rList);                                        // copy ctor
    self& operator=(const self& _rList);                                    // assignment operator

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

public: // list operations

    iterator Insert(const key_type& _rKey, const value_type& _rValue);      // insert element infront of iterator
    iterator Remove(iterator _Pos);                                         // remove element at iterator

    void Clear();                                                           // clear the list of all inserted elements

public: // list properties

    bool      IsEmpty() const;                                              // return if list is empty
    size_type GetElementCount() const;                                      // return number of elements in list

public: // iterator declaration

    class CConstIterator
    {
    public:

        friend typename CBinaryTree<T, Allocator>;

    public:

        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef CBinaryTree::node_type node_type;
        
        typedef typename CBinaryTree<T, Allocator>::CConstIterator self;

    public: // ctor, dtor

        CConstIterator(const self& _rIterator);

    private: // private ctor

        CConstIterator(node_type* _pNode);

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

        node_type* m_pNode;

    private: // internal operations

        void Increment();
        void Decrement();
    };

    class CIterator : public CConstIterator
    {
    public:

        friend typename CBinaryTree<T, Allocator>;

    public:

        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef CBinaryTree::node_type node_type;

        typedef typename CBinaryTree<T, Allocator>::CIterator self;

    public:

        CIterator(const self& _rIt);

    private:

        CIterator(node_type* _pLink);

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

        friend typename CBinaryTree<T, Allocator>;

    public:

        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef CBinaryTree::node_type node_type;

        typedef typename CBinaryTree<T, Allocator>::CConstReverseIterator self;

    public: // ctor, dtor

        CConstReverseIterator(const self& _rIterator);

    private:

        CConstReverseIterator(node_type* _pNode);

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

        node_type* m_pNode;

    private: // internal operations

        void Increment();
        void Decrement();
    };

    class CReverseIterator : public CConstReverseIterator
    {
    public:

        friend typename CBinaryTree<T, Allocator>;

    public:

        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef CBinaryTree::node_type node_type;

        typedef typename CBinaryTree<T, Allocator>::CReverseIterator self;

    public:

        CReverseIterator(const self& _rIt);

    private:

        CReverseIterator(node_type* _pNode);

    public:

        reference operator*() const;
        pointer   operator->() const;

        self operator++();
        self operator++(int);
        self operator--();
        self operator--(int);
    };

private: // node declaration

    struct SNode
    {
        node_type*    m_pParent;
        node_type*    m_pLeftChild;
        node_type*    m_pRightChild;
        hash_key_type m_HashKey;
        value_type    m_Value;
    };

private: // member

    hash_func_type      m_HashFunc;
    allocator_type      m_Allocator;
    node_allocator_type m_NodeAllocator;
    node_type*          m_pRoot;
    size_type           m_Size;

private: // internal methods

    iterator InsertOnChild(node_type** _ppChild, node_type* _pParent, const hash_key_type& _rHashKey, const value_type& _rValue);
};

template <typename Key, typename Value, template <typename> class Hash, template <typename> class Allocator>
CBinaryTree<Key, Value, Hash, Allocator>::CBinaryTree()
    : m_HashFunc()
    , m_Allocator()
    , m_NodeAllocator()
    , m_pRoot(0)
    , m_Size(0)
{
}

template <typename Key, typename Value, template <typename> class Hash, template <typename> class Allocator>
CBinaryTree<Key, Value, Hash, Allocator>::iterator
CBinaryTree<Key, Value, Hash, Allocator>::Insert(const key_type& _rKey, const value_type& _rValue)
{
    InsertOnNode(m_pRoot, m_HashFunc(_rKey), _rValue);
}

template <typename Key, typename Value, template <typename> class Hash, template <typename> class Allocator>
CBinaryTree<Key, Value, Hash, Allocator>::iterator
CBinaryTree<Key, Value, Hash, Allocator>::InsertOnChild(node_type** _ppChild, node_type* _pParent, const hash_key_type& _rHashKey, const value_type& _rValue)
{
    if (*_ppChild == 0) // child doesn't exist
    {
        *_ppChild = new SNode();
        pNode->m_pParent = _pParent;
        pNode->m_pLeftChild = 0;
        pNode->m_pRightChild = 0;
        pNode->m_HashKey = _rHashKey;
        pNode->m_Value = _rValue;

        return *_ppChild;
    }
    else if (_rHashKey < (*_ppChild)->m_HashKey)
    {
        InsertOnChild(&(*_ppChild)->m_pLeftChild, *_ppChild, _rHashKey, _rValue);
    }
    else if (_rHashKey > (*_ppChild)->m_HashKey)
    {
        InsertOnChild(&(*_ppChild)->m_pRightChild, *_ppChild, _rHashKey, _rValue);
    }
    else
    {
        return *_ppChild;
    }
}


        } // namespace SEQ
    } // namespace CNT
} // namespace BASE

#endif // __INCLUDE_BINARY_TREE_H_
