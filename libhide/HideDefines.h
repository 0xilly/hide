#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef float  f32;
typedef double f64;

#define GLOBAL  static
#define LOCAL   static

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#defined HIDE_PLATFORM_WINDOWS 1
#elif defined(__linux__) || defined(__gnu_linux__) //damn it RMS
#define HIDE_PLATFORM_LINUX 1
#elif __APPLE_
#define HIDE_PLATFORM_APPLE 1
#else
#error "Unsupported platform"
#endif

#ifdef __cplusplus
}
#endif
