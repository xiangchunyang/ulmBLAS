#ifndef ULMBLAS_LEVEL3_PACK_TRLSPACK_TCC
#define ULMBLAS_LEVEL3_PACK_TRLSPACK_TCC 1

#include <ulmblas/auxiliary/conjugate.h>
#include <ulmblas/level3/pack/trlpack.h>
#include <ulmblas/level3/ukernel/ugemm.h>

namespace ulmBLAS {

template <typename IndexType, typename TL, typename Buffer>
static void
trlspack_MRxk(IndexType   k,
              bool        conj,
              bool        unit,
              const TL    *L,
              IndexType   incRowL,
              IndexType   incColL,
              Buffer      *buffer)
{
    const IndexType MR  = BlockSizeUGemm<Buffer>::MR;

    if (!conj) {
        for (IndexType j=0; j<k-MR; ++j) {
            for (IndexType i=0; i<MR; ++i) {
                buffer[i] = L[i*incRowL];
            }
            buffer += MR;
            L      += incColL;
        }
    } else {
        for (IndexType j=0; j<k-MR; ++j) {
            for (IndexType i=0; i<MR; ++i) {
                buffer[i] = conjugate(L[i*incRowL]);
            }
            buffer += MR;
            L      += incColL;
        }
    }
    for (IndexType j=0; j<MR; ++j) {
        for (IndexType i=0; i<j; ++i) {
            buffer[i] = Buffer(0);
        }
        buffer[j] = (unit) ? Buffer(1)
                           : conjugate(Buffer(1)/L[j*incRowL], conj);
        for (IndexType i=j+1; i<MR; ++i) {
            buffer[i] = conjugate(L[i*incRowL], conj);
        }
        buffer += MR;
        L      += incColL;
    }
}

template <typename IndexType, typename TL, typename Buffer>
void
trlspack(IndexType   mc,
         bool        conj,
         bool        unit,
         const TL    *L,
         IndexType   incRowL,
         IndexType   incColL,
         Buffer      *buffer)
{
    const IndexType MR  = BlockSizeUGemm<Buffer>::MR;
    const IndexType mp  = mc / MR;
    const IndexType mr_ = mc % MR;

    for (IndexType i=0; i<mp; ++i) {
        trlspack_MRxk((i+1)*MR, conj, unit, L, incRowL, incColL, buffer);
        buffer += (i+1)*MR*MR;
        L      += MR*incRowL;
    }

    if (mr_>0) {
        for (IndexType j=0; j<mp*MR; ++j) {
            for (IndexType i=0; i<mr_; ++i) {
                buffer[i] = conjugate(L[i*incRowL], conj);
            }
            for (IndexType i=mr_; i<MR; ++i) {
                buffer[i] = Buffer(0);
            }
            buffer += MR;
            L      += incColL;
        }
        for (IndexType j=0; j<mr_; ++j) {
            for (IndexType i=0; i<j; ++i) {
                buffer[i] = Buffer(0);
            }
            buffer[j] = (unit) ? Buffer(1)
                               : conjugate(Buffer(1)/L[j*incRowL], conj);
            for (IndexType i=j+1; i<mr_; ++i) {
                buffer[i] = conjugate(L[i*incRowL], conj);
            }
            for (IndexType i=mr_; i<MR; ++i) {
                buffer[i] = Buffer(0);
            }
            buffer += MR;
            L      += incColL;
        }
    }
}

} // namespace ulmBLAS

#endif // ULMBLAS_LEVEL3_PACK_TRLSPACK_TCC
