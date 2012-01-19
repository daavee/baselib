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
        namespace ASOC {

            
using BASE::MEM::CAllocator;
using BASE::UTIL::HASH::SDummyHash;

/**
 * Representing a binary tree.
 * Inserted values will be copied and the list will take care
 * of allocated memory for copies. Allocator has to be from
 * this library.
 **/
template <
    typename Key,
    typename Value,
    template <typename> class Hash = SDummyHash,
    template <typename> class Allocator = CAllocator
>
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

    typedef CBinaryTree<Key, Value, Hash, Allocator> self;

    typedef Key    key_type;
    typedef Value  value_type;
    typedef size_t size_type;

    typedef Allocator<key_type> allocator_type;

    typedef CIterator             iterator;
    typedef CConstIterator        const_iterator;
    typedef CReverseIterator      reverse_iterator;
    typedef CConstReverseIterator const_reverse_iterator;

private: // private typedefs

    typedef SNode                              node_type;
    typedef Hash<key_type>                     hash_func_type;
    typedef typename hash_func_type::hash_type hash_key_type;

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

        friend typename CBinaryTree<Key, Value, Hash, Allocator>;

    public:

        typedef Value     value_type;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef typename CBinaryTree::node_type node_type;
        
        typedef CConstIterator self;

    public: // ctor, dtor

        CConstIterator(const self& _rIterator);

    private: // private ctor

        CConstIterator(node_type* _pNode);

    public: // exposed operations

        bool operator==(const self& _rRhs) const;
        bool operator!=(const self& _rRhs) const;

        const value_type& operator*() const;
        const value_type* operator->() const;

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

        friend typename CBinaryTree<Key, Value, Hash, Allocator>;

    public:

        typedef Value     value_type;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef typename CBinaryTree::node_type node_type;

        typedef CIterator self;

    public:

        CIterator(const self& _rIt);

    private:

        CIterator(node_type* _pLink);

    public:

        value_type& operator*() const;
        value_type* operator->() const;

        self operator++();
        self operator++(int);
        self operator--();
        self operator--(int);
    };

    class CConstReverseIterator
    {
    public:

        friend typename CBinaryTree<Key, Value, Hash, Allocator>;

    public:

        typedef Value     value_type;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef typename CBinaryTree::node_type node_type;

        typedef CConstReverseIterator self;

    public: // ctor, dtor

        CConstReverseIterator(const self& _rIterator);

    private:

        CConstReverseIterator(node_type* _pNode);

    public: // exposed operations

        bool operator==(const self& _rRhs) const;
        bool operator!=(const self& _rRhs) const;

        const value_type& operator*() const;
        const value_type* operator->() const;

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

        friend typename CBinaryTree<Key, Value, Hash, Allocator>;

    public:

        typedef Value     value_type;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    private:

        typedef typename CBinaryTree::node_type node_type;

        typedef CReverseIterator self;

    public:

        CReverseIterator(const self& _rIt);

    private:

        CReverseIterator(node_type* _pNode);

    public:

        value_type& operator*() const;
        value_type* operator->() const;

        self operator++();
        self operator++(int);
        self operator--();
        self operator--(int);
    };

private: // node declaration

    struct SNode
    {
        SNode(node_type* _pParent, node_type* _pLeftChild, node_type* _pRightChild, hash_key_type _HashKey, value_type _Value);

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
CBinaryTree<Key, Value, Hash, Allocator>::~CBinaryTree()
{
}

template <typename Key, typename Value, template <typename> class Hash, template <typename> class Allocator>
typename CBinaryTree<Key, Value, Hash, Allocator>::iterator
CBinaryTree<Key, Value, Hash, Allocator>::Insert(const key_type& _rKey, const value_type& _rValue)
{
    return InsertOnChild(&m_pRoot, 0, m_HashFunc(_rKey), _rValue);
}

template <typename Key, typename Value, template <typename> class Hash, template <typename> class Allocator>
typename CBinaryTree<Key, Value, Hash, Allocator>::iterator
CBinaryTree<Key, Value, Hash, Allocator>::InsertOnChild(node_type** _ppChild, node_type* _pParent,
    const hash_key_type& _rHashKey, const value_type& _rValue)
{
    if (*_ppChild == 0) // child doesn't exist
    {
        *_ppChild = new SNode(_pParent, 0, 0, _rHashKey, _rValue);
        ++m_Size;

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
    else
    {
        return *_ppChild;
    }
}

template <typename Key, typename Value, template <typename> class Hash, template <typename> class Allocator>
CBinaryTree<Key, Value, Hash, Allocator>::CConstIterator::CConstIterator(node_type* _pNode)
    : m_pNode(_pNode)
{
}

template <typename Key, typename Value, template <typename> class Hash, template <typename> class Allocator>
CBinaryTree<Key, Value, Hash, Allocator>::CIterator::CIterator(node_type* _pNode)
    : CConstIterator(_pNode)
{
}

template <typename Key, typename Value, template <typename> class Hash, template <typename> class Allocator>
CBinaryTree<Key, Value, Hash, Allocator>::SNode::SNode(node_type* _pParent, node_type* _pLeftChild,
    node_type* _pRightChild, hash_key_type _HashKey, value_type _Value)
    : m_pParent(_pParent)
    , m_pLeftChild(_pLeftChild)
    , m_pRightChild(_pRightChild)
    , m_HashKey(_HashKey)
    , m_Value(_Value)
{
}


        } // namespace ASOC
    } // namespace CNT
} // namespace BASE

#endif // __INCLUDE_BINARY_TREE_H_
