#ifndef ULMBLAS_SRC_LEVEL1_KERNEL_SSE_AXPY_H
#define ULMBLAS_SRC_LEVEL1_KERNEL_SSE_AXPY_H 1

#include <src/level1/kernel/ref/axpy.h>

namespace ulmBLAS { namespace sse {

using ref::axpy;

template <typename IndexType>
    void
    axpy(IndexType      n,
         const double   &alpha,
         const double   *x,
         IndexType      incX,
         double         *y,
         IndexType      incY);

} } // namespace sse, ulmBLAS

#endif // ULMBLAS_SRC_LEVEL1_KERNEL_SSE_AXPY_H 1

#include <src/level1/kernel/sse/axpy.tcc>
