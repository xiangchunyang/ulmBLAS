#ifndef ULMBLAS_LEVEL2_SBUMV_H
#define ULMBLAS_LEVEL2_SBUMV_H 1

namespace ulmBLAS {

template <typename IndexType, typename Alpha, typename TA, typename TX,
          typename Beta, typename TY>
    void
    sbumv(IndexType    n,
          IndexType    k,
          const Alpha  &alpha,
          const TA     *A,
          IndexType    ldA,
          const TX     *x,
          IndexType    incX,
          const Beta   &beta,
          TY           *y,
          IndexType    incY);

} // namespace ulmBLAS

#endif // ULMBLAS_LEVEL2_SBUMV_H

#include <ulmblas/level2/sbumv.tcc>
