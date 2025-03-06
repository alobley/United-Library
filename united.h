#ifndef UNITED_H
#define UNITED_H 1
#ifdef __cplusplus
extern "C" {
#endif

/* This is a relatively small C/C++ library meant to bridge the syntax of multiple compilers and C standards together to provide a consistent, readable interface for programmers. */
/* This means that the syntax of C and C++ (with this library) should be the same regardless of the compiler being used. C++ exclusive features are not supported. */
/* This is a work in progress and will be updated as needed. */

/* The goal is for multiple standards from ANSI C onwards to be supported and their gaps bridged, with as natural syntax as is possible and any C/C++ compiler. */
/* Unfortunately #warning isn't supported by all compilers before c23 so it can't be used. Also, comments must be done like this for ANSI C support. */
/* Note: some things simply cannot be done. Sacrifices will have to be made. However, backwards compatibility allows the code to remain unchanged regardless. */


/* TODO:
 * - Add more complete bridging for C89 to later standards
 * - Fully define restrict
 * - Fully define _Generic
 * - Fully define inline
 * - Fully define Thread_local for C89 and C99
 * - Fully define _Static_assert for C89 and C99
 * - Add atomic operations for each supported architecture
*/

/* Define an unreliable multiplatform size_t type */
typedef unsigned long united_size_t;

/* Define a type identifier type (not used at the moment) */
typedef enum {
    __typ_chr__ = 1,
    __typ_uchr__ = 2,
    __typ_shrt__ = 3,
    __typ_ushrt__ = 4,
    __typ_int__ = 5,
    __typ_uint__ = 6,
    __typ_long__ = 7,
    __typ_ulong__ = 8,
    __typ_llong__ = 9,
    __typ_ullong__ = 10,
    __typ_float__ = 11,
    __typ_double__ = 12,
    __typ_ldouble__ = 13,
    __typ_ptr__ = 14,
    __typ_vptr__ = 15
} united_type_t;


#if defined(__GNUC__)
    /*  GNU Compiler Collection */
    #define GCC 1
    #define MSVC 0
    #define ICC 0
    #define TCC 0
    #if defined(__clang__)
        /*  Clang (which is entirely compatible with GCC) */
        #define CLANG 1
        #define COMPILER "Clang"
    #else
        #define CLANG 0
        #define COMPILER "GCC/G++"
    #endif
#elif defined(_MSC_VER)
    /*  Microsoft Visual C++ */
    #define MSVC 1
    #define GCC 0
    #define CLANG 0
    #define ICC 0
    #define TCC 0
    #define COMPILER "MSVC/MSVC++"
#elif defined(__INTEL_COMPILER)
    /*  Intel C++ Compiler */
    #define ICC 1
    #define GCC 0
    #define CLANG 0
    #define MSVC 0
    #define TCC 0
    #define COMPILER "ICC/IC++"
#elif defined(__TINYC__)
    /*  Tiny C Compiler */
    #define TCC 1
    #define GCC 0
    #define CLANG 0
    #define MSVC 0
    #define ICC 0
    #define COMPILER "TinyC"
#elif defined(__STDC__)
    /*  Unknown compiler that supports ISO C syntax */
    #define GCC 0
    #define CLANG 0
    #define MSVC 0
    #define ICC 0
    #define TCC 0
    #define COMPILER "Unknown Standard C"
#elif defined(__cplusplus)
    /*  Unknown C++ compiler */
    #define GCC 0
    #define CLANG 0
    #define MSVC 0
    #define ICC 0
    #define TCC 0
    #define COMPILER "Unknown C++ compiler"
#else
    /*  TODO: add support for more compilers */
    #error "Unsupported compiler"
#endif

#if defined(__STDC__) && !MSVC
    /*  Ensures compatibility with both the ISO and GNU C standards for inline assembly (aligns syntax with GNU C) */
    #define asm __asm__
    /*  More... */
#elif !defined(__GNUC__) && !MSVC
    /*  Edge case for an arbitrary non-Microsoft standard */
    /*#warning "Unknown C standard, some features may not be supported"*/
    #define asm __asm
#elif MSVC
    #ifdef __x86_64__
        /*  64-bit MSVC does not support inline assembly */
        #warning "Inline assembly is not supported by 64-bit MSVC"
        #define asm
    #else
        /*  32-bit MSVC does support inline assembly */
        #define asm __asm
    #endif
#endif

/*  Attribute definitions based on the compiler being used */
#if GCC || ICC || TCC /*  GCC is 1 if Clang, all these compilers theoretically support the same attributes */
    #define ALIGNED__(x) __attribute__((aligned(x)))
    #define MALLOC__(x, y) __attribute__((__malloc__(x, y)))
    #define NORETURN__ __attribute__((noreturn))
    #define NOTHROW__ __attribute__((nothrow))
    #define NONNULL__(x) __attribute__((nonnull(x)))
    #define INLINE__ __attribute__((always_inline))
    #define DEPRECATED__ __attribute__((deprecated))
    #define UNUSED__ __attribute__((unused))
    #define FORMAT__(x, y, z) __attribute__((format(x, y, z)))
    #define PURE__ __attribute__((pure))
    #define CONST__ __attribute__((const))
    #define WEAK__ __attribute__((weak))
    #define PACKED__ __attribute__((packed))
    #define HOT__ __attribute__((hot))
    #define COLD__ __attribute__((cold))
    #define ALLOC_ALIGN__(x) __attribute__((alloc_align(x)))
    #define ALLOC_SIZE__(x, y) __attribute__((alloc_size(x, y)))
    #define ATOMIC__ volatile                                         /* Doesn't guaruntee atomicity but should work decently */
    #define INTERRUPT__ __attribute__((interrupt))

    #if defined(__x86_64__) || defined(__i386__)
        #define MS_ABI__ __attribute__((ms_abi))
        #define SYSV_ABI__ __attribute__((sysv_abi))
        #define CDECL__ __attribute__((cdecl))
        #define STDCALL__ __attribute__((stdcall))
        #define FASTCALL__ __attribute__((fastcall))
    #endif

    #if defined(__arm__) || defined(__aarch64__)
        #define AAPCS__ __attribute__((aapcs))
        #define AAPCS_VFP__ __attribute__((aapcs_vfp))
        #define AAPCS16__ __attribute__((aapcs16))
        #define AAPCS32__ __attribute__((aapcs32))
        #define AAPCS64__ __attribute__((aapcs64))
        #define APCS__ __attribute__((apcs))
        #define APCS_VFP__ __attribute__((apcs_vfp))
        #define APCS16__ __attribute__((apcs16))
        #define APCS32__ __attribute__((apcs32))
        #define APCS64__ __attribute__((apcs64))
    #endif

    #if defined(__riscv)
        #define RISCV_ABI__ __attribute__((riscv_abi))
    #endif

    #if defined(__powerpc__) || defined(__powerpc64__)
        #define PPC_ABI__ __attribute__((ppc_abi))
    #endif

    #if defined(__mips__) || defined(__mips64__)
        #define MIPS_ABI__ __attribute__((mips_abi))
    #endif

    /*  Others... */
#elif MSVC
    #define ALIGNED__(x) __declspec(align(x))
    #define MALLOC__(x, y) [[nodiscard]]  /*  closest equivalent */
    #define NORETURN__ [[noreturn]]
    #define NOTHROW__ noexcept
    #define NONNULL__(x) [[gnu::nonnull(x)]]  /*  no direct MSVC equivalent */
    #define INLINE__ __forceinline
    #define DEPRECATED__ [[deprecated]]
    #define UNUSED__ [[maybe_unused]]
    #define FORMAT__(x, y, z) [[gnu::format(x, y, z)]]  /*  no direct MSVC equivalent */
    #define PURE__ [[gnu::pure]]
    #define CONST__ [[gnu::const]]
    #define WEAK__ [[gnu::weak]]
    #define PACKED__ #pragma pack(push, 1)
    #define HOT__ [[msvc::hot]]
    #define COLD__ [[msvc::cold]]
    #define ALLOC_ALIGN__(x) [[align(x)]]
    #define ATOMIC__ [[msvc::atomic]]
    #define INTERRUPT__ [[msvc::interrupt]]

    #if defined(__x86_64__) || defined(__i386__)
        #define MS_API__ [[msvc::dllexport]]
        #define SYSV_ABI__ [[gnu::sysv_abi]]  /*  no direct MSVC equivalent */
        #define CDECL__ [[msvc::cdecl]]
        #define STDCALL__ [[msvc::stdcall]]
        #define FASTCALL__ [[msvc::fastcall]]
    #endif

    #if defined(__arm__) || defined(__aarch64__)
        /*  Generally unsupported by MSVC */
        #define AAPCS__ [[gnu::aapcs]]
        #define AAPCS_VFP__ [[gnu::aapcs_vfp]]
        #define AAPCS16__ [[gnu::aapcs16]]
        #define AAPCS32__ [[gnu::aapcs32]]
        #define AAPCS64__ [[gnu::aapcs64]]
        #define APCS__ [[gnu::apcs]]
        #define APCS_VFP__ [[gnu::apcs_vfp]]
        #define APCS16__ [[gnu::apcs16]]
        #define APCS32__ [[gnu::apcs32]]
        #define APCS64__ [[gnu::apcs64]]
    #endif

    #if defined(__riscv)
        /*  Generally unsupported by MSVC */
        #define RISCV_ABI__ [[gnu::riscv_abi]]
    #endif

    #if defined(__powerpc__) || defined(__powerpc64__)
        /*  Generally unsupported by MSVC */
        #define PPC_ABI__ [[gnu::ppc_abi]]
    #endif

    #if defined(__mips__) || defined(__mips64__)
        /*  Generally unsupported by MSVC */
        #define MIPS_ABI__ [[gnu::mips_abi]]
    #endif

    /*  Others... */
#elif defined(__cplusplus)
    /*  Default to the C++11 standard (Compiler MUST support C++11 or later. Valid C code is (usually) valid C++ code) */
    #define ALIGNED__(x) [[gnu::aligned(x)]]
    #define MALLOC__ [[gnu::malloc(x, y)]]
    #define NORETURN__ [[gnu::noreturn]]
    #define NOTHROW__ noexcept
    #define NONNULL__(x) [[gnu::nonnull(x)]]
    #define INLINE__ [[gnu::always_inline]]
    #define DEPRECATED__ [[gnu::deprecated]]
    #define UNUSED__ [[gnu::unused]]
    #define FORMAT__(x, y, z) [[gnu::format(x, y, z)]]
    #define PURE__ [[gnu::pure]]
    #define CONST__ [[gnu::const]]
    #define WEAK__ [[gnu::weak]]
    #define PACKED__ [[gnu::packed]]
    #define HOT__ [[gnu::hot]]
    #define COLD__ [[gnu::cold]]
    #define ALLOC_ALIGN__(x) [[gnu::alloc_align(x)]]
    #define ATOMIC__ [[gnu::atomic]]
    #define INTERRUPT__ [[gnu::interrupt]]

    #if defined(__x86_64__) || defined(__i386__)
        #define MS_API__ [[gnu::ms_abi]]
        #define SYSV_ABI__ [[gnu::sysv_abi]]
        #define CDECL__ [[gnu::cdecl]]
        #define STDCALL__ [[gnu::stdcall]]
        #define FASTCALL__ [[gnu::fastcall]]
    #endif

    #if defined(__arm__) || defined(__aarch64__)
        #define AAPCS__ [[gnu::aapcs]]
        #define AAPCS_VFP__ [[gnu::aapcs_vfp]]
        #define AAPCS16__ [[gnu::aapcs16]]
        #define AAPCS32__ [[gnu::aapcs32]]
        #define AAPCS64__ [[gnu::aapcs64]]
        #define APCS__ [[gnu::apcs]]
        #define APCS_VFP__ [[gnu::apcs_vfp]]
        #define APCS16__ [[gnu::apcs16]]
        #define APCS32__ [[gnu::apcs32]]
        #define APCS64__ [[gnu::apcs64]]
    #endif

    #if defined(__riscv)
        #define RISCV_ABI__ [[gnu::riscv_abi]]
    #endif

    #if defined(__powerpc__) || defined(__powerpc64__)
        #define PPC_ABI__ [[gnu::ppc_abi]]
    #endif

    #if defined(__mips__) || defined(__mips64__)
        #define MIPS_ABI__ [[gnu::mips_abi]]
    #endif

    /*  Others... */
#else
    #error "Unsupported compiler. Try a C++11 (or later) compiler or a C compiler that supports the GNU C or MSVC standard. \
            If you don't want attributes, comment out this line and this library will still work. It's line 296 and 297 in united.h."
    
    /* Define the attributes as empty */
    #define ALIGNED__(x)
    #define MALLOC__(x, y)
    #define NORETURN__
    #define NOTHROW__
    #define NONNULL__(x)
    #define INLINE__
    #define DEPRECATED__
    #define UNUSED__
    #define FORMAT__(x, y, z)
    #define PURE__
    #define CONST__
    #define WEAK__
    #define PACKED__
    #define HOT__
    #define COLD__
    #define ALLOC_ALIGN__(x)
    #define ATOMIC__
    #define INTERRUPT__

    #if defined(__x86_64__) || defined(__i386__)
        #define MS_API__
        #define SYSV_ABI__
        #define CDECL__
        #define STDCALL__
        #define FASTCALL__
    #endif

    #if defined(__arm__) || defined(__aarch64__)
        #define AAPCS__
        #define AAPCS_VFP__
        #define AAPCS16__
        #define AAPCS32__
        #define AAPCS64__
        #define APCS__
        #define APCS_VFP__
        #define APCS16__
        #define APCS32__
        #define APCS64__
    #endif

    #if defined(__riscv)
        #define RISCV_ABI__
    #endif

    #if defined(__powerpc__) || defined(__powerpc64__)
        #define PPC_ABI__
    #endif
#endif

/*  Attributes */
#define _aligned_(x) ALIGNED__(x)                                           /*  Align something to a boundary of x bytes */
#define _malloc_(x, y) MALLOC__(x, y)                                       /*  Declare that a function allocates memory and returns a pointer to it */
#define _noreturn_ NORETURN__                                               /*  Declare that a function never returns */
#define _nothrow_ NOTHROW__                                                 /*  Declare that a function never throws an exception */
#define _nonnull_(x) NONNULL__(x)                                           /*  Declare that a function doesn't accept NULL as an argument */
#define _forced_inline_ INLINE__                                            /*  Declare that a function should always be inlined */
#define _deprecated_ DEPRECATED__                                           /*  Declare that a function is deprecated */
#define _unused_ UNUSED__                                                   /*  Declare that a variable is unused */
#define _format_(archetype, index, first) __FORMAT__(archetype, index, first) /*  Declare that a function uses printf-style formatting */
#define _pure_ PURE__                                                       /*  Declare that a function has no side effects */
#define _const_ CONST__                                                     /*  Declare that a function has no side effects and doesn't read global memory */
#define _weak_ WEAK__                                                       /*  Declare that a function is weakly linked */
#define _packed_ PACKED__                                                   /*  Declare that a struct should be packed */
#define _hot_ HOT__                                                         /*  Declare that a function is "hot" (likely to be executed) */
#define _cold_ COLD__                                                       /*  Declare that a function is "cold" (unlikely to be executed) */
#define _alloc_align_(x) ALLOC_ALIGN__(x)                                   /*  Declare that a function allocates memory aligned to x bytes */
#if __STDC_VERSION__ >= 201112L || defined(__cplusplus)
    #define _atomic_ _Atomic                                                  /*  Declare that a function variable is atomic */
#else
    #define _atomic_ ATOMIC__                                               /*  Declare that a function or variable is atomic */
#endif
#define _interrupt_ INTERRUPT__                                             /*  Declare that a function is an interrupt handler */

/*  Calling conventions/ABIs */
#if defined(__x86_64__) || defined(__i386__)
    #define _ms_abi_ MS_ABI__                                                /*  Declare that a function uses the Microsoft ABI */
    #define _sysv_abi_ SYSV_ABI__                                            /*  Declare that a function uses the System V ABI (AMD64 only) */
    #define _cdecl_ CDECL__                                                  /*  Declare that a function uses the CDECL calling convention (i86 and i386 only) */
    #define _stdcall_ STDCALL__                                              /*  Declare that a function uses the STDCALL calling convention */
    #define _fastcall_ FASTCALL__                                            /*  Declare that a function uses the FASTCALL calling convention (16 and 32 bit only) */
    #define _efiapi_ MS_ABI__                                                /*  Declare that a function uses the EFI API */
#elif defined(__arm__) || defined(__aarch64__)
    #define _aapcs_ AAPCS__                                                  /*  Declare that a function uses the AAPCS ABI */
    #define _aapcs_vfp_ AAPCS_VFP__                                          /*  Declare that a function uses the AAPCS VFP ABI */
    #define _aapcs16_ AAPCS16__                                              /*  Declare that a function uses the AAPCS16 ABI */
    #define _aapcs32_ AAPCS32__                                              /*  Declare that a function uses the AAPCS32 ABI */
    #define _aapcs64_ AAPCS64__                                              /*  Declare that a function uses the AAPCS64 ABI */
    #define _apcs_ APCS__                                                    /*  Declare that a function uses the APCS ABI */
    #define _apcs_vfp_ APCS_VFP__                                            /*  Declare that a function uses the APCS VFP ABI */
    #define _apcs16_ APCS16__                                                /*  Declare that a function uses the APCS16 ABI */
    #define _apcs32_ APCS32__                                                /*  Declare that a function uses the APCS32 ABI */
    #define _apcs64_ APCS64__                                                /*  Declare that a function uses the APCS64 ABI */
#elif defined(__riscv)
    #define _riscv_abi_ RISCV_ABI__                                          /*  Declare that a function uses the RISC-V ABI */
#elif defined(__powerpc__) || defined(__powerpc64__)
    #define _ppc_abi_ PPC_ABI__                                              /*  Declare that a function uses the PowerPC ABI */
#else
    /*#warning "Unsupported architecture"*/
#endif

/* These builtins are supported by nearly every compiler in use today */
typedef __builtin_va_list _united_va_list_;
#define _united_va_start_(list, last) (__builtin_va_start(list, last))
#define _united_va_arg_(list, type) (__builtin_va_arg(list, type))
#define _united_va_end_(list) (__builtin_va_end(list))
#define _united_va_copy_(dest, src) (__builtin_va_copy(dest, src))

/* Do custom va stuff based on the architecture and calling convention... */

#if defined(__cplusplus)
    #define c_style extern "C"                                              /*  Declare that a function is C-style */
#else
    #define c_style                                                         /*  Declare that a function is C-style (not needed for a regular C compiler) */
#endif

/*  Ansi C (and its successors) compatibility */

/* C89 - C99 */

/* Define the boolean type */
#ifndef _Bool
    #define _Bool unsigned char
#endif

/* Define the complex type (can be used instead of imaginary) */
#ifndef _Complex
    #define _Complex struct { \
        double __real; \
        double __imag; \
    }
#endif

/* Imaginary numbers are much like complex ones */
#ifndef _Imaginary
    #define _Imaginary _Complex
#endif

#ifndef __STDC_VERSION__
    /*  C89 detected, set the version to 1989 */
    #define __STDC_VERSION__ 198900L
    /* Allow the definition of for loops with self-contained variables */
    /* The code MUST be in brackets (should be more intuitive) */
    #define united_for(var, condition, increment, code) { \
        var; \
        while(condition) { \
            code \
            increment; \
        } \
    }

    #define localvar(code) { \
        code \
    }

    /* Since inline does not exist, declare it as static and hope the compiler inlines it */
    #define inline static

    /* Restrict doesn't exist in Ansi C, but it can be set to exist just for completeness. Overall, it shouldn't impact things too much. */
    #ifndef restrict
        #define restrict
    #endif

    /*  Set the long long type */
    /*#warning "C89 detected, some features can't be accurately bridged"*/
    typedef struct {
        int __low;
        int __high;
    } _long_long_;

    #define _make_long_long_(low, high) {low, high}
    #define _long_long_low_(x) (x.__low)
    #define _long_long_high_(x) (x.__high)

    /*  Add two long longs together. X is the result. */
    #define _long_long_add_(x, y) do { \
        (x).__low = (x).__low + (y).__low; \
        (x).__high = (x).__high + (y).__high + ((x).__low < (x).__low); \
    } while (0)

    #define _long_long_sub_ (a, b) do { \
        (a).__low = (a).__low - (b).__low; \
        (a).__high = (a).__high - (b).__high - ((a).__low < (b).__low); \
    } while (0)

    #define _long_long_mul_(x, y) do { \
        _long_long_ __temp; \
        __temp.__low = (x).__low * (y).__low; \
        __temp.__high = (x).__high * (y).__low + (x).__low * (y).__high; \
        (x) = __temp; \
    } while(0)

    #define _long_long_mod_(x, y) do { \
        _long_long_ __temp; \
        __temp.low = (x).__low % (y).__low; \
        __temp.high = (x).__high % (y).__low; \
        (x) = __temp; \
    } while(0)

    #define _long_long_and_(x, y) do { \
        (x).__low = (x).__low & (y).__low; \
        (x).__high = (x).__high & (y).__high; \
    } while(0)

    #define _long_long_or_(x, y) do { \
        (x).__low = (x).__low | (y).__low; \
        (x).__high = (x).__high | (y).__high; \
    } while(0)

    #define _long_long_xor_(x, y) do { \
        (x).__low = (x).__low ^ (y).__low; \
        (x).__high = (x).__high ^ (y).__high; \
    } while(0)

    #define _long_long_shl_(x, shift) do { \
        if(shift < 32) { \
            (x).__low = (x).__low << shift; \
            (x).__high = ((x).__high << shift) | ((x).__low >> (32 - shift)); \
        } else { \
            (x).__high = (x).__low << (shift - 32); \
            (x).__low = 0; \
        } \
    } while(0)

    #define _long_long_shr_(x, shift) do { \
        if(shift < 32) { \
            (x).__high = (x).__high >> shift; \
            (x).__low = ((x).__low >> shift) | ((x).__high << (32 - shift)); \
        } else { \
            (x).__low = (x).__high >> (shift - 32); \
            (x).__high = 0; \
        } \
    } while(0)

    #define _long_long_eq_(x, y) ((x).__low == (y).__low && (x).__high == (y).__high)

    #define _long_long_ne_(x, y) ((x).__low != (y).__low || (x).__high != (y).__high)

    #define _long_long_gt_(x, y) ((x).__high > (y).__high || ((x).__high == (y).__high && (x).__low > (y).__low))

    #define _long_long_lt_(x, y) ((x).__high < (y).__high || ((x).__high == (y).__high && (x).__low < (y).__low))

    #define _long_long_ge_(x, y) ((x).__high > (y).__high || ((x).__high == (y).__high && (x).__low >= (y).__low))

    #define _long_long_le_(x, y) ((x).__high < (y).__high || ((x).__high == (y).__high && (x).__low <= (y).__low))

    #define _long_long_not_(x) do { \
        (x).__low = ~(x).__low; \
        (x).__high = ~(x).__high; \
    } while(0)

    #define _long_long_neg_(x) do { \
        (x).low = -(x).low; \
        (x).__high = -(x).__high; \
    } while(0)

    typedef struct {
        unsigned int __low;
        unsigned int __high;
    } _ulong_long_;

    #define _make_ulong_long_(low, high) {low, high}
    #define _ulong_long_low_(x) (x.__low)
    #define _ulong_long_high_(x) (x.__high)

    #define _ulong_long_add_(x, y) do { \
        (x).__low = (x).__low + (y).__low; \
        (x).__high = (x).__high + (y).__high + ((x).__low < (x).__low); \
    } while (0)

    #define _ulong_long_sub_ (a, b) do { \
        (a).__low = (a).__low - (b).__low; \
        (a).__high = (a).__high - (b).__high - ((a).__low < (b).__low); \
    } while (0)

    #define _ulong_long_mul_(x, y) do { \
        _ulong_long_ __temp; \
        __temp.__low = (x).__low * (y).__low; \
        __temp.__high = (x).__high * (y).__low + (x).__low * (y).__high; \
        (x) = __temp; \
    } while(0)

    #define _ulong_long_mod_(x, y) do { \
        _ulong_long_ __temp; \
        __temp.__low = (x).__low % (y).__low; \
        __temp.__high = (x).__high % (y).__low; \
        (x) = __temp; \
    } while(0)

    #define _ulong_long_and_(x, y) do { \
        (x).__low = (x).__low & (y).__low; \
        (x).__high = (x).__high & (y).__high; \
    } while(0)

    #define _ulong_long_or_(x, y) do { \
        (x).__low = (x).__low | (y).__low; \
        (x).__high = (x).high | (y).high; \
    } while(0)

    #define _ulong_long_xor_(x, y) do { \
        (x).__low = (x).__low ^ (y).__low; \
        (x).__high = (x).__high ^ (y).__high; \
    } while(0)

    #define _ulong_long_shl_(x, shift) do { \
        if(shift < 32) { \
            (x).__low = (x).__low << shift; \
            (x).__high = ((x).__high << shift) | ((x).__low >> (32 - shift)); \
        } else { \
            (x).__high = (x).__low << (shift - 32); \
            (x).__low = 0; \
        } \
    } while(0)

    #define _ulong_long_shr_(x, shift) do { \
        if(shift < 32) { \
            (x).__low = (x).__low >> shift; \
            (x).__high = ((x).__high >> shift) | ((x).__low << (32 - shift)); \
        } else { \
            (x).__low = (x).__high >> (shift - 32); \
            (x).__high = 0; \
        } \
    } while(0)

    #define _ulong_long_eq_(x, y) ((x).__low == (y).__low && (x).__high == (y).__high)

    #define _ulong_long_ne_(x, y) ((x).__low != (y).__low || (x).__high != (y).__high)

    #define _ulong_long_gt_(x, y) ((x).__high > (y).__high || ((x).__high == (y).__high && (x).__low > (y).__low))

    #define _ulong_long_lt_(x, y) ((x).__high < (y).__high || ((x).__high == (y).__high && (x).__low < (y).__low))

    #define _ulong_long_ge_(x, y) ((x).__high > (y).__high || ((x).__high == (y).__high && (x).__low >= (y).__low))

    #define _ulong_long_le_(x, y) ((x).__high < (y).__high || ((x).__high == (y).__high && (x).__low <= (y).__low))

    #define _ulong_long_not_(x) do { \
        (x).__low = ~(x).__low; \
        (x).__high = ~(x).__high; \
    } while(0)

    #define _ulong_long_neg_(x) do { \
        (x).__low = -(x).__low; \
        (x).__high = -(x).__high; \
    } while(0)

    #define _long_long_cast_(name, value) ( \
        _long_long_ name = { \
            .__low = (long)(value), \
            .__high = (long)((value) >> 32) \
        } \
    )

    #define _ulong_long_cast_(name, value) ( \
        _ulong_long_ name = { \
            .__low = (unsigned long)(value), \
            .__high = (unsigned long)((value) >> 32) \
        } \
    )

    inline _ulong_long_ _ulong_long_div_(_ulong_long_ dividend, _ulong_long_ divisor) {
        _ulong_long_ quotient = {0, 0}, remainder = {0, 0};
        united_for(int i = 63, i >= 0, i--, {
            remainder.__high = (remainder.__high << 1) | (remainder.__low >> 31);
            remainder.__low = (remainder.__low << 1) | ((dividend.__high >> i) & 1);
            if ((remainder.__high > divisor.__high) || (remainder.__high == divisor.__high && remainder.__low >= divisor.__low)) {
                remainder.__low -= divisor.__low;
                remainder.__high -= divisor.__high;
                quotient.__low |= (1UL << i);
            }
        })
        return quotient;
    }

    inline _long_long_ _long_long_div_(_long_long_ dividend, _long_long_ divisor) {
        _long_long_ quotient = {0, 0}, remainder = {0, 0};
        united_for(int i = 63, i >= 0, i--, {
            remainder.__high = (remainder.__high << 1) | (remainder.__low >> 31);
            remainder.__low = (remainder.__low << 1) | ((dividend.__high >> i) & 1);
            if ((remainder.__high > divisor.__high) || (remainder.__high == divisor.__high && remainder.__low >= divisor.__low)) {
                remainder.__low -= divisor.__low;
                remainder.__high -= divisor.__high;
                quotient.__low |= (1UL << i);
            }
        })
        return quotient;
    }

    /* Try to add VLA support for ANSI C compilers (Warning: is not actually a VLA. Maybe there's another way?) */
    #define united_vla(type, name) const type* name
#else
    typedef long long _long_long_;
    #define _make_long_long_(low, high) (((long long)low) | (((long long)high) << 32))
    #define _long_long_low_(x) ((int)((x) & 0xFFFFFFFF))
    #define _long_long_high_(x) ((int)((x) >> 32))
    #define _ulong_long_ unsigned long long
    #define _make_ulong_long_(low, high) (((unsigned long long)low) | (((unsigned long long)high) << 32))
    #define _ulong_long_low_(x) ((unsigned int)((x) & 0xFFFFFFFF))
    #define _ulong_long_high_(x) ((unsigned int)((x) >> 32))

    #define _long_long_add_(x, y) (x = (x) + (y))
    #define _long_long_sub_(x, y) (x = (x) - (y))
    #define _long_long_mul_(x, y) (x = (x) * (y))
    #define _long_long_div_(x, y) (x = (x) / (y))
    #define _long_long_mod_(x, y) (x = (x) % (y))
    #define _long_long_and_(x, y) (x = (x) & (y))
    #define _long_long_or_(x, y) (x = (x) | (y))
    #define _long_long_xor_(x, y) (x = (x) ^ (y))
    #define _long_long_shl_(x, shift) (x = (x) << (shift))
    #define _long_long_shr_(x, shift) (x = (x) >> (shift))
    #define _long_long_eq_(x, y) ((x) == (y))
    #define _long_long_ne_(x, y) ((x) != (y))
    #define _long_long_gt_(x, y) ((x) > (y))
    #define _long_long_lt_(x, y) ((x) < (y))
    #define _long_long_ge_(x, y) ((x) >= (y))
    #define _long_long_le_(x, y) ((x) <= (y))
    #define _long_long_not_(x) (x = ~(x))
    #define _long_long_neg_(x) (x = -(x))
    #define _long_long_cast_(x) ((long long)(x))

    #define _ulong_long_add_(x, y) (x = (x) + (y))
    #define _ulong_long_sub_(x, y) (x = (x) - (y))
    #define _ulong_long_mul_(x, y) (x = (x) * (y))
    #define _ulong_long_div_(x, y) (x = (x) / (y))
    #define _ulong_long_mod_(x, y) (x = (x) % (y))
    #define _ulong_long_and_(x, y) (x = (x) & (y))
    #define _ulong_long_or_(x, y) (x = (x) | (y))
    #define _ulong_long_xor_(x, y) (x = (x) ^ (y))
    #define _ulong_long_shl_(x, shift) (x = (x) << (shift))
    #define _ulong_long_shr_(x, shift) (x = (x) >> (shift))
    #define _ulong_long_eq_(x, y) ((x) == (y))
    #define _ulong_long_ne_(x, y) ((x) != (y))
    #define _ulong_long_gt_(x, y) ((x) > (y))
    #define _ulong_long_lt_(x, y) ((x) < (y))
    #define _ulong_long_ge_(x, y) ((x) >= (y))
    #define _ulong_long_le_(x, y) ((x) <= (y))
    #define _ulong_long_not_(x) (x = ~(x))
    #define _ulong_long_neg_(x) (x = -(x))
    #define _ulong_long_cast_(name, value) ((unsigned long long)(value))

    #define united_vla(type, name) type name[]

    /* Define a for loop. Code MUST be in brackets. */
    #define united_for(var, condition, increment, code) for(var; condition; increment){ code }

    #define localvar(code) code
#endif

/* C99 - C11/C17 */

/* Define the _Alignas keyword */
#ifndef _Alignas
    #define _Alignas(x) _aligned_(x)
#endif

/* Define the _Alignof keyword */
#ifndef _Alignof
    #define _Alignof(x) ((united_size_t)(&((struct { char c; type x; } *)0)->x))
#endif

/* Define _Atomic if it doesn't exist (must figure out how to do this properly) */
/* Although it might not be needed for the C89 use case, since it's typically in single-core environments */
#ifndef _Atomic
    #define _Atomic 
#endif

/* The _Generic type */
#ifndef _Generic
    #if __STDC_VERSION__ >= 199901L
        /*  Define _Generic if it doesn't exist */
        #define _Generic(x, ...) __VA_ARGS__
    #else
        /* Ansi C workaround unfortunately seems to be extremely difficult or impossible. Will investigate further. */
        #define _Generic
    #endif
#endif

/* Define the _Noreturn keyword */
#ifndef _Noreturn
    #define _Noreturn _noreturn_
#endif

/* C17-C23 */

#ifndef _BitInt
    /* Define a signed integer of n bits (math must be done manually) */
    #define __bit_int__(n) \
    typedef struct { \
        int __bits[((n / 8) / sizeof(int))]; \
    } _BitInt##n; \

    /* Define an unsigned integer of n bits (math must be done manually) */
    #define __ubit_int__(n) \
    typedef struct { \
        unsigned int __bits[((n / 8) / sizeof(unsigned int))]; \
    } _UBitInt##n;

    /* Set the maximum bit width for an integer (128 should be file) */
    #define BITINT_MAXWIDTH 128
#else
    #define __bit_int__(n) _BitInt##n
    #define __ubit_int__(n) unsigned _BitInt##n
#endif

/* Checked Integer Operations */
#ifndef ckd_add
    #define ckd_add(x, y) __builtin_add_overflow(x, y, &x)
#endif

#ifndef ckd_sub
    #define ckd_sub(x, y) __builtin_sub_overflow(x, y, &x)
#endif

#ifndef ckd_mul
    #define ckd_mul(x, y) __builtin_mul_overflow(x, y, &x)
#endif

/* Set the keywords */
#if __STDC_VERSION__ < 202311L
    #ifndef true
        #define true 1
    #endif

    #ifndef false
        #define false 0
    #endif

    /* Define the nullptr_t type */
    #ifndef nullptr_t
        typedef void* nullptr_t;
        #define nullptr ((nullptr_t)0)
    #endif

    /* Define the _Static_assert keyword (Need C99 and C89 alternative) */
    #ifndef _Static_assert
        #define _Static_assert
    #endif

    /* Define the _Thread_local keyword (Once again, need C99 and C89 alternative. May differ based on architecture.) */
    #ifndef _Thread_local
        #define _Thread_local
    #endif

    /* Define the typeof macro */
    #if !defined typeof && GCC
        #define typeof(x) __typeof__(x)
    #elif !defined typeof && MSVC
        #define typeof(x) decltype(x)
    #elif !defined typeof && defined __cplusplus
        #define typeof(x) decltype(x)
    #endif

    /* Define the typeof_unequal macro */
    #if !defined typeof_unequal && GCC
        #define typeof_unequal(x, y) __builtin_types_compatible_p(typeof(x), typeof(y))
    #elif !defined typeof_unequal && MSVC
        #define typeof_unequal(x, y) __is_same(typeof(x), typeof(y))
    #elif !defined typeof_unequal && defined __cplusplus
        #define typeof_unequal(x, y) std::is_same<typeof(x), typeof(y)>::value
    #endif

    /* Define the contexpr macro */
    #if !defined constexpr && GCC
        #define constexpr __attribute__((const))
    #elif !defined constexpr && MSVC
        #define constexpr __declspec(const)
    #elif !defined constexpr && defined __cplusplus
        /* This should not be reached since it should be defined in C++11 and later */
        #define constexpr constexpr
    #endif

    /* Decimal floating-point keywords */
    #ifndef _Decimal32
        #define _Decimal32 float
    #endif

    #ifndef _Decimal64
        #define _Decimal64 double
    #endif

    #ifndef _Decimal128
        #define _Decimal128 long double
    #endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* COMPILER_H */
