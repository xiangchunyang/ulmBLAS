      DOUBLE PRECISION FUNCTION DZASUM(N,ZX,INCX)

      INTEGER           INCX, N
      DOUBLE COMPLEX    ZX(*)
      DOUBLE PRECISION  TEMP


      CALL DZASUM_SUB( N, ZX, INCX, TEMP )
      DZASUM = TEMP

      RETURN
      END