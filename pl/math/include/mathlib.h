/*
 * Public API.
 *
 * Copyright (c) 2015-2024, Arm Limited.
 * SPDX-License-Identifier: MIT OR Apache-2.0 WITH LLVM-exception
 */

#ifndef _MATHLIB_H
#define _MATHLIB_H

float acosf (float);
float acoshf (float);
float asinf (float);
float asinhf (float);
float atan2f (float, float);
float atanf (float);
float atanhf (float);
float cbrtf (float);
float coshf (float);
float erfcf (float);
float erff (float);
float erfinvf (float);
float expm1f (float);
float log10f (float);
float log1pf (float);
float sinhf (float);
float tanf (float);
float tanhf (float);

double acos (double);
double acosh (double);
double asin (double);
double asinh (double);
double atan (double);
double atan2 (double, double);
double atanh (double);
double cbrt (double);
double cosh (double);
double erfc (double);
double erfinv (double);
double expm1 (double);
double log10 (double);
double log1p (double);
double sinh (double);
double tanh (double);

long double erfinvl (long double);
long double exp10l (long double);

#if __aarch64__ && __linux__
# if __GNUC__ >= 5
typedef __Float32x4_t __f32x4_t;
typedef __Float64x2_t __f64x2_t;
# elif __clang_major__ * 100 + __clang_minor__ >= 305
typedef __attribute__ ((__neon_vector_type__ (4))) float __f32x4_t;
typedef __attribute__ ((__neon_vector_type__ (2))) double __f64x2_t;
# else
#  error Unsupported compiler
# endif

# if __GNUC__ >= 9 || __clang_major__ >= 8
#  define __vpcs __attribute__ ((__aarch64_vector_pcs__))

typedef struct __f32x4x2_t
{
  __f32x4_t val[2];
} __f32x4x2_t;

typedef struct __f64x2x2_t
{
  __f64x2_t val[2];
} __f64x2x2_t;

/* Vector functions following the vector PCS using ABI names.  */
__vpcs __f32x4_t _ZGVnN4v_erfinvf (__f32x4_t);
__vpcs __f32x4_t _ZGVnN4vl4_modff (__f32x4_t, __f32x4_t *);
__vpcs __f32x4x2_t _ZGVnN4v_cexpif (__f32x4_t);
__vpcs void _ZGVnN4vl4l4_sincosf (__f32x4_t, __f32x4_t *, __f32x4_t *);

__vpcs __f64x2_t _ZGVnN2v_erfinv (__f64x2_t);
__vpcs __f64x2_t _ZGVnN2vl8_modf (__f64x2_t, __f64x2_t *);
__vpcs __f64x2x2_t _ZGVnN2v_cexpi (__f64x2_t);
__vpcs void _ZGVnN2vl8l8_sincos (__f64x2_t, __f64x2_t *, __f64x2_t *);

# endif

# if WANT_SVE_MATH
#  include <arm_sve.h>
svfloat32_t _ZGVsMxv_erfinvf (svfloat32_t, svbool_t);
svfloat32_t _ZGVsMxvl4_modff (svfloat32_t, float *, svbool_t);
svfloat32_t _ZGVsMxvv_powi (svfloat32_t, svint32_t, svbool_t);
svfloat32x2_t _ZGVsMxv_cexpif (svfloat32_t, svbool_t);
void _ZGVsMxvl4l4_sincosf (svfloat32_t, float *, float *, svbool_t);

svfloat64_t _ZGVsMxv_erfinv (svfloat64_t, svbool_t);
svfloat64_t _ZGVsMxvl8_modf (svfloat64_t, double *, svbool_t);
svfloat64_t _ZGVsMxvv_powk (svfloat64_t, svint64_t, svbool_t);
svfloat64x2_t _ZGVsMxv_cexpi (svfloat64_t, svbool_t);
void _ZGVsMxvl8l8_sincos (svfloat64_t, double *, double *, svbool_t);
#  endif

# endif

#endif
