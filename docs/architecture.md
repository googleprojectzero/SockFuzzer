# SockFuzzer XNU Guest Library Architecture

## Overview

The XNU Guest Library is a core component of SockFuzzer, enabling the execution of XNU kernel code in a userspace environment. This document outlines the architecture of the XNU Guest Library, including symbol management, build system, configuration, and the Hypercall Interface.

## XNU Guest Library Architecture

### Library Structure

The XNU Guest Library (`libxnu`) is a compiled version of the XNU kernel source code, modified to run in userspace. It includes:

- Core XNU kernel components
- BSD subsystem
- Mach subsystem
- Virtual memory subsystem (with null pmap layer)
- Networking stack
- Other essential kernel services

### Symbol Management

To avoid conflicts between XNU symbols and host symbols, SockFuzzer employs an explicit symbol management strategy:

- All XNU symbols are prefixed with `xnu_` during the build process to ensure that internal references within the XNU kernel library resolve correctly while allowing custom code to interact with it.
- A `libxnu.redef` file maps original function names to their prefixed versions. This allows for controlled exposure of specific XNU functions to the custom code.
- An `xnu_version_script.lds` file explicitly defines which symbols are exposed from the XNU library. This includes custom XNU-side functions (e.g., `XNUThreadMarkWaitLocked`) and other necessary symbols.

### Fake Implementations

For kernel subsystems unrelated to the target functionality or incompatible with userspace execution, SockFuzzer provides fake implementations:

- Simplified versions of complex kernel services
- Null implementations for non-essential functions
- Host-based implementations for core services (e.g., memory allocation)

## Build System and Configuration

SockFuzzer uses Bazel as its build system, which provides efficient and reproducible builds. Custom rules are used to handle the unique requirements of building the XNU kernel as a library.

### Build Process

1. XNU source code is compiled into individual object files
2. The `cc_object` custom rule is applied to handle symbol management
3. Object files are linked together to form `libxnu.o`
4. Symbol prefixing and redefinition are applied
5. The resulting library is linked with SockFuzzer components

### Key Build Files

- `BUILD.bazel`: Defines the build targets and dependencies
- `libxnu.redef`: Contains symbol redefinition mappings
- `xnu_version_script.lds`: Specifies exposed symbols

### Custom Bazel Rules

SockFuzzer employs custom Bazel rules to facilitate the unique build requirements:

- `cc_object`: A custom rule for creating object files with symbol modifications
  - Handles partial linking of XNU components
  - Applies symbol redefinitions
  - Manages symbol visibility

Example usage of `cc_object`:

```python
cc_object(
    name = "libxnu.o",
    redefine_syms = "libxnu.redef",
    deps = LIBXNU_DEPS,
)
```

## Hypercall Interface

The Hypercall Interface facilitates communication between the XNU Guest Library and the host environment. This enables XNU guest code to request services from the host and allows the host to control and monitor XNU guest execution.

### Key Hypercalls

- `ThreadPrintf`: Print debug information from XNU guest code
- `ThreadBlockReason`: Implement thread blocking in the custom scheduler
- `ThreadSetContinuation`: Set a continuation for a blocked thread
- Various thread state management calls (e.g., `ThreadSetWaiting`, `ThreadClearWait`)

### Implementation

- Hypercalls are implemented as function pointers in a structure
- The host environment populates this structure with appropriate implementations
- XNU guest code calls these functions through a global interface pointer

### Usage in XNU Guest

Example of a hypercall in XNU guest code:

```c
GetHypercallInterface()->ThreadPrintf("Debug message from XNU guest\n");
```
