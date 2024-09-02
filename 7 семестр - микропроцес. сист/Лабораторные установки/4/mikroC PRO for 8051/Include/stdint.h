#ifndef __stdint_h
#define __stdint_h

// Exact-width signed integer types
typedef signed char        int8_t;
typedef signed int         int16_t;
typedef signed long int    int32_t;

// Exact-width unsigned integer types
typedef unsigned char      uint8_t;
typedef unsigned int       uint16_t;
typedef unsigned long int  uint32_t;

// Minimum-width signed integer types
typedef signed char        int_least8_t;
typedef signed int         int_least16_t;
typedef signed long int    int_least32_t;

// Minimum-width unsigned integer types
typedef unsigned char      uint_least8_t;
typedef unsigned int       uint_least16_t;
typedef unsigned long int  uint_least32_t;


// Fastest minimum-width signed integer types
typedef signed char        int_fast8_t;
typedef signed int         int_fast16_t;
typedef signed long int    int_fast32_t;

// Fastest minimum-width unsigned integer types
typedef unsigned char      uint_fast8_t;
typedef unsigned int       uint_fast16_t;
typedef unsigned long int  uint_fast32_t;

// Integer types capable of holding object pointers
typedef signed   int  intptr_t;
typedef unsigned int  uintptr_t;

// Greatest-width integer types
typedef signed   long int intmax_t;
typedef unsigned long int uintmax_t;


// Minimum values of exact-width signed integer types
#define INT8_MIN                   -128
#define INT16_MIN                -32768
#define INT32_MIN          (~0x7fffffff)     // -2147483648 is unsigned

// Maximum values of exact-width signed integer types
#define INT8_MAX                    127
#define INT16_MAX                 32767
#define INT32_MAX            2147483647

// Maximum values of exact-width unsigned integer types
#define UINT8_MAX                   255
#define UINT16_MAX                65535
#define UINT32_MAX           4294967295u

// Minimum values of minimum-width signed integer types
#define INT_LEAST8_MIN                 INT8_MIN
#define INT_LEAST16_MIN                INT16_MIN
#define INT_LEAST32_MIN                INT32_MIN

// Maximum values of minimum-width signed integer types
#define INT_LEAST8_MAX                 INT8_MAX
#define INT_LEAST16_MAX                INT16_MAX
#define INT_LEAST32_MAX                INT32_MAX

// Maximum values of minimum-width unsigned integer types
#define UINT_LEAST8_MAX                UINT8_MAX   
#define UINT_LEAST16_MAX               UINT16_MAX  
#define UINT_LEAST32_MAX               UINT32_MAX  

// Minimum values of fastest minimum-width signed integer types
#define INT_FAST8_MIN                 INT8_MIN 
#define INT_FAST16_MIN                INT16_MIN
#define INT_FAST32_MIN                INT32_MIN

// Maximum values of fastest minimum-width signed integer types
#define INT_FAST8_MAX                 INT8_MAX 
#define INT_FAST16_MAX                INT16_MAX
#define INT_FAST32_MAX                INT32_MAX

// Maximum values of fastest minimum-width unsigned integer types
#define UINT_FAST8_MAX                UINT8_MAX 
#define UINT_FAST16_MAX               UINT16_MAX
#define UINT_FAST32_MAX               UINT32_MAX

// Minimum value of pointer-holding signed integer type
#define INTPTR_MIN   INT16_MIN

// Maximum value of pointer-holding signed integer type
#define INTPTR_MAX   INT16_MAX

// Maximum value of pointer-holding unsigned integer type
#define UINTPTR_MAX  UINT16_MAX

// Minimum value of greatest-width signed integer type
#define INTMAX_MIN   INT32_MIN

// Maximum value of greatest-width signed integer type
#define INTMAX_MAX   INT32_MAX

// Maximum value of greatest-width unsigned integer type
#define UINTMAX_MAX  UINT32_MAX


// limits of ptrdiff_t
#define PTRDIFF_MIN   INT16_MIN
#define PTRDIFF_MAX   INT16_MAX

// limits of sig_atomic_t
#define SIG_ATOMIC_MIN   INT8_MIN
#define SIG_ATOMIC_MAX   INT8_MAX

// limit of size_t
#define SIZE_MAX 65535u

// limits of wchar_t
#define WCHAR_MIN   0
#define WCHAR_MAX   65535

// Limits of wint_t
#define WINT_MIN (~0x7fff)
#define WINT_MAX 65535

// Macros for minimum-width integer constants
#define INT8_C(x)   (x)
#define INT16_C(x)  (x)
#define INT32_C(x)  (x ## l)

#define UINT8_C(x)  (x ## u)
#define UINT16_C(x) (x ## u)
#define UINT32_C(x) (x ## ul)

// Macros for greatest-width integer constants
#define INTMAX_C(x)  (x ## l)
#define UINTMAX_C(x) (x ## ul)

#endif 
// end of stdint.h