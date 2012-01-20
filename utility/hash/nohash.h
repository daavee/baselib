#ifndef __INCLUDE_NO_HASH_H_
#define __INCLUDE_NO_HASH_H_

namespace BASE {
    namespace UTIL {
        namespace HASH {


template <typename T>
struct SNoHash
{
    typedef T value_type;
    typedef T hash_type;

    const hash_type& operator()(const value_type& _rValue) const
    {
        return _rValue;
    }

    const hash_type& operator()(const value_type* _pValue) const
    {
        return operator()(*_pValue);
    }
};


        } // namespace HASH
    } // namespace UTIL
} // namespace BASE

#endif // __INCLUDE_NO_HASH_H_