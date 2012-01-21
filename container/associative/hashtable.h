#ifndef __INCLUDE_HASH_TABLE_H_
#define __INCLUDE_HASH_TABLE_H_

/**
 * todo:
 * - policies
 * - hashes
 * - everything :(
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
#include "hash.h"

namespace BASE {
    namespace CNT {

            
using BASE::MEM::CAllocator;

template <typename Key,                         // key type
    typename Value,                             // value type
    typename Hash = CHash<Key>,                 // hash type including hash algorithm
    //typename AddressingPolicy,                  // policy for addressing (open, closed, etc.)
    typename Allocator = CAllocator<Value>>     // allocator
class CHashTable
{
public: // public forward declarations

private: // private forward declarations

    struct SHashEntry;

public: // public typedefs

    typedef Key               key_type;
    typedef Value             value_type;
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;
    typedef value_type&       reference;
    typedef const value_type& const_reference;
    typedef size_t            size_type;

    typedef Hash              hash_type;
    //typedef AddressingPolicy  addressing_policy_type;
    typedef Allocator         allocator_type;

private: // private typedefs

    typedef SHashEntry hash_entry_type;

    typedef typename allocator_type::template SRebind<hash_entry_type>::other entry_allocator_type;

private: // hash entry declaration

    struct SHashEntry : public addressing_policy_type::SHashEntryBase
    {
        hash_type m_Hash;
        key_type  m_Key;
    };

private: // member

    allocator_type       m_Allocator;
    entry_allocator_type m_EntryAllocator;
    hash_entry_type*     m_pHashEntries;
    size_type            m_TableSize;
    size_type            m_EntryCount;
};


    } // namespace CNT
} // namespace BASE

#endif // __INCLUDE_HASH_TABLE_H_