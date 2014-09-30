#ifndef ULMBLAS_LEVEL3_PACK_TRUPACK_TCC
#define ULMBLAS_LEVEL3_PACK_TRUPACK_TCC 1

#include <ulmblas/level3/pack/trupack.h>
#include <ulmblas/level3/ugemm.h>

namespace ulmBLAS {

template <typename IndexType, typename TL, typename Buffer>
static void
trupack_MRxk(IndexType   k,
             bool        unit,
             const TL    *U,
             IndexType   incRowU,
             IndexType   incColU,
             Buffer      *buffer)
{
    const IndexType MR  = ugemm_mr<Buffer>();

    for (IndexType j=0; j<MR; ++j) {
        for (IndexType i=0; i<j; ++i) {
            buffer[i] = U[i*incRowU];
        }
        buffer[j] = (unit) ? Buffer(1) : U[j*incRowU];
        for (IndexType i=j+1; i<MR; ++i) {
            buffer[i] = Buffer(0);
        }
        buffer += MR;
        U      += incColU;
    }
    for (IndexType j=0; j<k-MR; ++j) {
        for (IndexType i=0; i<MR; ++i) {
            buffer[i] = U[i*incRowU];
        }
        buffer += MR;
        U      += incColU;
    }
}

template <typename IndexType, typename TU, typename Buffer>
void
trupack(IndexType   mc,
        bool        unit,
        const TU    *U,
        IndexType   incRowU,
        IndexType   incColU,
        Buffer      *buffer)
{
    const IndexType MR  = ugemm_mr<Buffer>();
    const IndexType mp  = mc / MR;
    const IndexType _mr = mc % MR;

    for (IndexType i=0; i<mp; ++i) {
        trupack_MRxk(mc-i*MR, unit, U, incRowU, incColU, buffer);
        buffer += (mc-i*MR)*MR;
        U      += MR*(incRowU+incColU);
    }
    if (_mr>0) {
        for (IndexType j=0; j<_mr; ++j) {
            for (IndexType i=0; i<j; ++i) {
                buffer[i] = U[i*incRowU];
            }
            buffer[j] = (unit) ? Buffer(1) : U[j*incRowU];
            for (IndexType i=j+1; i<MR; ++i) {
                buffer[i] = Buffer(0);
            }
            buffer += MR;
            U      += incColU;
        }
    }
 }

} // namespace ulmBLAS

#endif // ULMBLAS_LEVEL3_PACK_TRUPACK_TCC
