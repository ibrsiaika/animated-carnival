#ifndef LIBANOGS_HOOKS_H
#define LIBANOGS_HOOKS_H

#include <stdint.h>
#include <stdio.h>
#include <syslog.h>

// Compatibility definitions for Linux/GCC
#ifndef __fastcall
#define __fastcall
#endif

#ifndef __int64
#define __int64 int64_t
#endif

#ifndef _DWORD
#define _DWORD uint32_t
#endif

#ifndef unsigned__int8
#define unsigned__int8 uint8_t
#endif

// Hook macros for defensive security analysis
// FOR USE ONLY ON YOUR OWN TEST BINARIES

// Hook with original function pointer stored
#define HOOK_LIB(lib, offset, hook_func, orig_func) \
    do { \
        printf("[HOOK] Hooking %s at %s with %s\n", lib, offset, #hook_func); \
        /* Implementation would use dynamic loading/patching here */ \
        orig_func = NULL; /* Placeholder - would store original function */ \
    } while(0)

// Hook without storing original function (bypass only)
#define HOOK_LIB_NO_ORIG(lib, offset, hook_func) \
    do { \
        printf("[HOOK] Bypassing %s at %s with %s\n", lib, offset, #hook_func); \
        /* Implementation would patch directly here */ \
    } while(0)

// Direct binary patch
#define PATCH_LIB(lib, offset, hex_bytes) \
    do { \
        printf("[PATCH] Patching %s at %s with bytes: %s\n", lib, offset, hex_bytes); \
        /* Implementation would write hex bytes directly to memory */ \
    } while(0)

// Function pointer types for the hooked functions
typedef __int64 (*sub_22DF38_func_t)(__int64 a1, uint8_t *a2, unsigned int a3);
typedef __int64 (*sub_49C22C_func_t)(_DWORD *a1, uint8_t *a2, int a3);
typedef __int64 (*sub_4C4254_func_t)(char *a1, __int64 a2);

// Global function pointers for original functions
extern sub_22DF38_func_t osub_22DF38;
extern sub_49C22C_func_t o_sub_49C22C;

// Hook function declarations
__int64 hsub_22DF38(__int64 a1, uint8_t *a2, unsigned int a3);
__int64 hsub_49C22C(_DWORD *a1, uint8_t *a2, int a3);
__int64 sub_4C4254_bypass(char *a1, __int64 a2);

// Initialization function
void init_libanogs_hooks(void);

#endif // LIBANOGS_HOOKS_H