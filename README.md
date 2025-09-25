# libanogs.so Defensive Hook System

## Overview

This repository implements a defensive security analysis system for the `libanogs.so` anti-cheat library. The hook system provides input validation, buffer overflow protection, and comprehensive logging for security research purposes.

⚠️ **IMPORTANT**: This code is for defensive security research and authorized testing only. Use only on systems you own or have explicit permission to test.

## Components

### Hook Infrastructure

- **libanogs_hooks.h** - Header file with hook macros and function declarations
- **libanogs_hooks.c** - Implementation of defensive hook functions
- **test_hooks.c** - Test program demonstrating the hook system

### Implemented Hooks

#### 1. sub_22DF38 Hook (hsub_22DF38)
- **Purpose**: Buffer processing function with input validation
- **Features**:
  - NULL pointer validation
  - Buffer size limits (64KB maximum)
  - Context parameter validation
  - Comprehensive logging

#### 2. sub_49C22C Hook (hsub_49C22C)  
- **Purpose**: Data processing function with comprehensive validation
- **Features**:
  - Parameter validation with safe fallback behavior
  - Buffer size limits (1MB maximum)
  - Negative size parameter handling
  - Safe delegation to original function when appropriate

#### 3. sub_4C4254 Bypass (sub_4C4254_bypass)
- **Purpose**: Simple bypass for checksum/hash function
- **Behavior**: Returns fixed value `0xDEADBEEF` to bypass anti-cheat checks
- **Logging**: Tracks all bypass attempts for security monitoring

### Binary Patches

The system applies direct binary patches to disable anti-cheat components:

- **0x557B70**: Patched with `00 00 80 D2 C0 03 5F D6` (ARM64: mov w0, #0; ret)
- **0x506390**: Patched with `00 00 80 D2 C0 03 5F D6` (ARM64: mov w0, #0; ret)

## Building

```bash
# Build all components
make all

# Run tests
make test

# Clean build artifacts
make clean

# Security analysis
make analyze
```

## Usage

```c
#include "libanogs_hooks.h"

int main() {
    // Initialize the hook system
    init_libanogs_hooks();
    
    // Hook functions are now active with input validation
    // Check system logs for security monitoring information
    
    return 0;
}
```

## Security Features

### Input Validation
- Comprehensive NULL pointer checks
- Buffer size validation with configurable limits
- Parameter bounds checking
- Context validation for all functions

### Buffer Overflow Protection
- Maximum buffer size enforcement
- Safe memory handling practices
- Bounds checking for all memory operations

### Logging and Monitoring
- System log integration via syslog
- Detailed security event logging
- Parameter tracking for forensic analysis
- Bypass attempt monitoring

### Safe Fallback Behavior
- Graceful error handling
- Safe delegation to original functions when appropriate
- Error code propagation
- Resource cleanup

## Log Analysis

The system logs all security events to syslog. Monitor with:

```bash
# View recent logs
journalctl --identifier=libanogs_hooks --since="1 hour ago"

# Or check syslog
tail -f /var/log/syslog | grep libanogs_hooks
```

## Defensive Use Cases

1. **Security Analysis**: Understanding anti-cheat behavior and vulnerabilities
2. **Penetration Testing**: Authorized testing of game protection systems
3. **Malware Analysis**: Defensive analysis of anti-cheat components
4. **Research**: Academic security research on game protection mechanisms

## Implementation Details

### Hook Macros

- `HOOK_LIB(lib, offset, hook_func, orig_func)` - Hook with original function storage
- `HOOK_LIB_NO_ORIG(lib, offset, hook_func)` - Simple bypass hook
- `PATCH_LIB(lib, offset, hex_bytes)` - Direct binary patch

### Function Types

All functions use standardized types for cross-platform compatibility:
- `__int64` → `int64_t`
- `unsigned __int8` → `uint8_t`  
- `_DWORD` → `uint32_t`
- `__fastcall` → (removed for GCC compatibility)

## Security Considerations

- All hooks include comprehensive input validation
- Buffer overflow protection is enforced at the hook level
- Logging provides audit trail for all security events
- Safe fallback behavior prevents system crashes
- Error handling follows security best practices

## License

This code is for educational and defensive security research purposes only. Use in accordance with applicable laws and with proper authorization.

## Contact

For security research inquiries or responsible disclosure, please refer to the repository maintainer guidelines.