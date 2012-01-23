#ifndef __INCLUDE_IS_CSTRING_H_
#define __INCLUDE_IS_CSTRING_H_

namespace BASE {
    namespace TYPET {


template <class T>
struct SIsCString
{
    enum
    {
        Result = false
    };
};

template <>
struct SIsCString<char*>
{
    enum
    {
        Result = true
    };
};

template <>
struct SIsCString<const char*>
{
    enum
    {
        Result = true
    };
};


    }
}




#endif // __INCLUDE_IS_CSTRING_H_