/*
 * Double-precision vector sincospi function.
 *
 * Copyright (c) 2024, Arm Limited.
 * SPDX-License-Identifier: MIT OR Apache-2.0 WITH LLVM-exception
 */
#include "v_sincospi_common.h"
#include "v_math.h"
#include "pl_test.h"

/* Double-precision vector function allowing calculation of both sin and cos in
   one function call, using separate argument reduction and shared low-order
   polynomials.
   Approximation for vector double-precision sincospi(x).
   Maximum Error 3.09 ULP:
  _ZGVnN2v_sincospi_sin(0x1.7a41deb4b21e1p+14) got 0x1.fd54d0b327cf1p-1
					      want 0x1.fd54d0b327cf4p-1
   Maximum Error 3.16 ULP:
  _ZGVnN2v_sincospi_cos(-0x1.11e3c7e284adep-5) got 0x1.fd2da484ff3ffp-1
					      want 0x1.fd2da484ff402p-1.  */
VPCS_ATTR void
_ZGVnN2vl8l8_sincospi (float64x2_t x, float64x2_t *out_sin,
		       float64x2_t *out_cos)
{
  const struct v_sincospi_data *d = ptr_barrier (&v_sincospi_data);

  float64x2x2_t sc = v_sincospi_inline (x, d);

  vst1q_f64 ((double *) out_sin, sc.val[0]);
  vst1q_f64 ((double *) out_cos, sc.val[1]);
}

#if WANT_TRIGPI_TESTS
PL_TEST_ULP (_ZGVnN2v_sincospi_sin, 2.59)
PL_TEST_ULP (_ZGVnN2v_sincospi_cos, 2.66)
#  define V_SINCOS_INTERVAL(lo, hi, n)                                        \
    PL_TEST_SYM_INTERVAL (_ZGVnN2v_sincospi_sin, lo, hi, n)                   \
    PL_TEST_SYM_INTERVAL (_ZGVnN2v_sincospi_cos, lo, hi, n)
V_SINCOS_INTERVAL (0, 0.5, 10000)
V_SINCOS_INTERVAL (0.5, 0x1p63, 10000)
V_SINCOS_INTERVAL (0x1p63, inf, 10000)
#endif