#ifndef __INCLUDE_ALLOCATOR_H_
#define __INCLUDE_ALLOCATOR_H_

/************************************************************************************
 * This work is licensed under the                                                  *
 *      Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. *
 * To view a copy of this license, visit                                            *
 *      http://creativecommons.org/licenses/by-nc-sa/3.0/                           *
 *                                                                                  *
 * @author  David Wieland                                                           *
 * @email   david.dw.wieland@googlemail.com                                         *
 ************************************************************************************/

namespace DWI {
    namespace MEM {


template <typename T>
class CAllocator
{
public:

    typedef T                 value_type;
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;
    typedef value_type&       reference;
    typedef const value_type& const_reference;
    typedef size_t            size_type;

    typedef CAllocator<T> self;

public:

    template <typename U>
    struct SRebind
    {
        typedef CAllocator<U> other;
    };

public:

    CAllocator();
    CAllocator(const self&);

    template <typename U>
    CAllocator(const CAllocator<U>&);

    template <typename U>
    self& operator=(const CAllocator<U>&);

public:

    pointer       AddressOf(reference _rElement) const;
    const_pointer AddressOf(const_reference _rElement) const;

    pointer Allocate(size_type _Count);
    void    Deallocate(pointer _pMem, size_type);

    void Construct(pointer _pMem, const_reference _rValue);
    void Destroy(pointer _pMem);

    size_type GetMaxSize() const;
};

template <typename T>
CAllocator<T>::CAllocator()
{

}

template <typename T>
CAllocator<T>::CAllocator(const self&)
{

}

template <typename T>
template <typename U>
CAllocator<T>::CAllocator(const CAllocator<U>&)
{

}

template <typename T>
template <typename U>
typename CAllocator<T>::self&
CAllocator<T>::operator=(const CAllocator<U>&)
{
    return (*this);
}

template <typename T>
typename CAllocator<T>::pointer
CAllocator<T>::AddressOf(reference _rElement) const
{
    return &_rElement;
}

template <typename T>
typename CAllocator<T>::const_pointer
    CAllocator<T>::AddressOf(const_reference _rElement) const
{
    return &_rElement;
}

template <typename T>
typename CAllocator<T>::pointer
CAllocator<T>::Allocate(size_type _Count)
{
    void* pMem = 0;
    if (_Count > 0 && _Count <= GetMaxSize())
        pMem = ::operator new(_Count * sizeof(T));

    return static_cast<T*>(pMem);
}

template <typename T>
void
CAllocator<T>::Deallocate(pointer _pMem, size_type)
{
    ::operator delete(_pMem);
}

template <typename T>
void
CAllocator<T>::Construct(pointer _pMem, const_reference _rValue)
{
    void* pMem = _pMem;
    ::new (pMem) T(_rValue);
}

#pragma warning(disable: 4100)
template <typename T>
void
CAllocator<T>::Destroy(pointer _pMem)
{
    _pMem->~T();
}
#pragma warning(default: 4100)

template <typename T>
typename CAllocator<T>::size_type
CAllocator<T>::GetMaxSize() const
{
    size_type MaxSize = static_cast<size_type>(-1) / sizeof(T);
    return (0 < MaxSize ? MaxSize : 1);
}

template <typename T1, typename T2>
bool
operator==(const T1&, const T2&)
{
    return true;
}

template <typename T1, typename T2>
bool
operator!=(const T1&, const T2&)
{
    return false;
}


    } // namespace MEM
} // namespace DWI


#endif // __INCLUDE_ALLOCATOR_H_