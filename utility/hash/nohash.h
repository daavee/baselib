#ifndef __INCLUDE_NO_HASH_H_
#define __INCLUDE_NO_HASH_H_

#include "keyhash.h"

namespace BASE {
    namespace UTIL {


template <typename T>
struct SNoHash
{
    typedef T                               value_type;
    typedef void                            hash_type;
    typedef SKeyHash<value_type, hash_type> key_hash_type;

    key_hash_type operator()(const value_type& _rValue) const
    {
        return _rValue;
    }

    key_hash_type operator()(const value_type* _pValue) const
    {
        return operator()(*_pValue);
    }
};


    } // namespace UTIL
} // namespace BASE

#endif // __INCLUDE_NO_HASH_H_