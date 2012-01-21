#ifndef __INCLUDE_VECTOR_H_
#define __INCLUDE_VECTOR_H_

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

            
using BASE::MEM::CAllocator;

template <typename T, typename Allocator = CAllocator<T>>
class CVector
{
};


    } // namespace CNT
} // namespace BASE

#endif // __INCLUDE_VECTOR_H_