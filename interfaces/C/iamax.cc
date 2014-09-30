#include <interfaces/C/config.h>
#include <ulmblas/level1/iamax.h>

extern "C" {

int
ULMBLAS(idamax)(const int       n,
                const double    *x,
                const int       incX)
{
    return ulmBLAS::iamax(n, x, incX);
}

} // extern "C"
