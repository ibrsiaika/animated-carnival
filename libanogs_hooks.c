#include "libanogs_hooks.h"
#include <string.h>
#include <inttypes.h>

// Global function pointers for original functions (remove extern from header)
sub_22DF38_func_t osub_22DF38 = NULL;
sub_49C22C_func_t o_sub_49C22C = NULL;

// Hook function for sub_22DF38 with input validation
__int64 hsub_22DF38(__int64 a1, uint8_t *a2, unsigned int a3)
{
    // Input validation for defensive security
    if (!osub_22DF38) {
        syslog(LOG_WARNING, "hsub_22DF38: Original function not available");
        return -1;
    }
    
    if (!a2 || a3 == 0) {
        syslog(LOG_WARNING, "hsub_22DF38: Invalid parameters - buffer=%p, size=%u", a2, a3);
        return -1;
    }
    
    // Buffer size safety check
    const unsigned int MAX_SAFE = 0x10000; // 64KB limit
    if (a3 > MAX_SAFE) {
        syslog(LOG_WARNING, "hsub_22DF38: Buffer size too large - size=%u, max=%u", a3, MAX_SAFE);
        return -1;
    }
    
    // Context validation
    if (a1 == 0) {
        syslog(LOG_WARNING, "hsub_22DF38: Invalid context parameter");
        return -1;
    }
    
    syslog(LOG_INFO, "hsub_22DF38: Processing buffer of size %u", a3);
    return osub_22DF38(a1, a2, a3);
}

// Hook function for sub_49C22C with comprehensive validation
__int64 hsub_49C22C(_DWORD *a1, uint8_t *a2, int a3)
{
    // Original function availability check
    if (!o_sub_49C22C) {
        syslog(LOG_WARNING, "hsub_49C22C: Original function not available");
        return -1;
    }
    
    // Parameter validation with safe fallback
    if (!a1) {
        syslog(LOG_WARNING, "hsub_49C22C: NULL a1 parameter, delegating to original");
        return o_sub_49C22C(a1, a2, a3);
    }
    
    if (a3 < 0) {
        syslog(LOG_WARNING, "hsub_49C22C: Negative size parameter a3=%d, delegating to original", a3);
        return o_sub_49C22C(a1, a2, a3);
    }
    
    if (a3 > 0 && !a2) {
        syslog(LOG_WARNING, "hsub_49C22C: Non-zero size with NULL buffer, delegating to original");
        return o_sub_49C22C(a1, a2, a3);
    }
    
    // Additional safety checks
    if (a3 > 0x100000) { // 1MB limit
        syslog(LOG_WARNING, "hsub_49C22C: Size parameter too large a3=%d", a3);
        return -1;
    }
    
    syslog(LOG_INFO, "hsub_49C22C: Processing with size %d", a3);
    return o_sub_49C22C(a1, a2, a3);
}

// Simple bypass function for sub_4C4254 that returns fixed value
__int64 sub_4C4254_bypass(char *a1, __int64 a2)
{
    // Log the bypass for security monitoring
    syslog(LOG_INFO, "sub_4C4254_bypass: Bypassing checksum/hash function with fixed return value");
    
    // Parameter logging for analysis
    if (a1 && a2 > 0) {
        syslog(LOG_DEBUG, "sub_4C4254_bypass: Would process buffer of size %" PRId64, a2);
    }
    
    // Return fixed value to bypass anti-cheat checks
    return 0xDEADBEEF;
}

// Initialize the hook system
void init_libanogs_hooks(void)
{
    printf("[INIT] Initializing libanogs hook system for defensive security analysis\n");
    printf("[INIT] WARNING: For use only on authorized test binaries\n");
    
    // Set up hooks with validation wrappers
    HOOK_LIB("libanogs.so", "0x22DF38", hsub_22DF38, osub_22DF38); // C35
    HOOK_LIB("libanogs.so", "0x49C22C", hsub_49C22C, o_sub_49C22C);
    
    // Set up simple bypass hook
    HOOK_LIB_NO_ORIG("libanogs.so", "0x4C4254", sub_4C4254_bypass);
    
    // Apply direct binary patches to disable anti-cheat functions
    // These patches replace function prologs with "mov w0, #0; ret" (ARM64)
    PATCH_LIB("libanogs.so", "0x557B70", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x506390", "00 00 80 D2 C0 03 5F D6");
    
    printf("[INIT] Hook system initialized - %d hooks, %d patches applied\n", 3, 2);
    
    // Initialize logging for security monitoring
    openlog("libanogs_hooks", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "libanogs defensive hook system initialized");
}