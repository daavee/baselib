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
#include "allocator.h"

namespace DWI {
    namespace CNT {
        namespace SEQ {

            
using DWI::MEM::CAllocator;

/**
 * Representing a binary tree.
 * Inserted values will be copied and the list will take care
 * of allocated memory for copies. Allocator has to be from
 * this library.
 **/
template <typename T, template <typename> class Allocator = CAllocator>
class CBinaryTree
{
public: // public forward declarations

    class CConstIterator;
    class CIterator;
    class CConstReverseIterator;
    class CReverseIterator;

private: // private forward declarations

    class CNode;

public: // public typdefs

    typedef T                 value_type;
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;
    typedef value_type&       reference;
    typedef const value_type& const_reference;
    typedef size_t            size_type;
    typedef int               index_type;

    typedef Allocator<T>      allocator_type;

    typedef CBinaryTree<T, Allocator> self;

    typedef CIterator             iterator;
    typedef CConstIterator        const_iterator;
    typedef CReverseIterator      reverse_iterator;
    typedef CConstReverseIterator const_reverse_iterator;

private: // private typedefs

    typedef CNode        node_type;
    typedef unsigned int hash_type;

    //typedef typename allocator_type::template SRebind<node_type>::other node_allocator_type;
    typedef Allocator<node_type> node_allocator_type;

public: // ctor, dtor

    CBinaryTree(const allocator_type& _Allocator = allocator_type());
    CBinaryTree(const self& _rList);
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

    iterator Insert(const_reference _rElement);                             // insert element infront of iterator
    iterator Remove(iterator _Pos);                                         // remove element at iterator

    void Insert(const_iterator _First, const_iterator _Last);               // insert elements _First to _Last from another container

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

    class CNode
    {
    public:

        node_type* m_pParent;
        node_type* m_pLeftChild;
        node_type* m_pRightChild;
        hash_type  m_Hash;
        value_type m_Element;
    };

private: // member

    allocator_type      m_Allocator;
    node_allocator_type m_NodeAllocator;
    node_type*          m_pRoot;
    size_type           m_Size;

private: // internal methods

};

template <typename T, template <typename> class Allocator>
iterator CBinaryTree<T, Allocator>::Insert(const_reference _rElement)
{
    //todo
}


        } // namespace SEQ
    } // namespace CNT
} // namespace DWI

#endif // __INCLUDE_BINARY_TREE_H_

