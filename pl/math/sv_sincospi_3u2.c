/*
 * Double-precision SVE sincospi(x, *y, *z) function.
 *
 * Copyright (c) 2024, Arm Limited.
 * SPDX-License-Identifier: MIT OR Apache-2.0 WITH LLVM-exception
 */

#include "sv_math.h"
#include "pl_test.h"
#include "mathlib.h"
#include "sv_sincospi_common.h"

/* Double-precision vector function allowing calculation of both sinpi and
   cospi in one function call, using shared argument reduction and polynomials.
    Worst-case error for sin is 3.09 ULP:
    _ZGVsMxvl8l8_sincospi_sin(0x1.7a41deb4b21e1p+14) got 0x1.fd54d0b327cf1p-1
						    want 0x1.fd54d0b327cf4p-1.
   Worst-case error for sin is 3.16 ULP:
    _ZGVsMxvl8l8_sincospi_cos(-0x1.11e3c7e284adep-5) got 0x1.fd2da484ff3ffp-1
						    want 0x1.fd2da484ff402p-1.
 */
void
_ZGVsMxvl8l8_sincospi (svfloat64_t x, double *out_sin, double *out_cos,
		       svbool_t pg)
{
  const struct sv_sincospi_data *d = ptr_barrier (&sv_sincospi_data);

  svfloat64x2_t sc = sv_sincospi_inline (pg, x, d);

  svst1 (pg, out_sin, svget2 (sc, 0));
  svst1 (pg, out_cos, svget2 (sc, 1));
}

#if WANT_TRIGPI_TESTS
PL_TEST_ULP (_ZGVsMxvl8l8_sincospi_sin, 2.59)
PL_TEST_ULP (_ZGVsMxvl8l8_sincospi_cos, 2.66)
#  define SV_SINCOSPI_INTERVAL(lo, hi, n)                                     \
    PL_TEST_SYM_INTERVAL (_ZGVsMxvl8l8_sincospi_sin, lo, hi, n)               \
    PL_TEST_SYM_INTERVAL (_ZGVsMxvl8l8_sincospi_cos, lo, hi, n)
SV_SINCOSPI_INTERVAL (0, 1, 500000)
SV_SINCOSPI_INTERVAL (1, 0x1p54, 500000)
SV_SINCOSPI_INTERVAL (0x1p54, inf, 10000)
#endif
