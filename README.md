# SockFuzzer: XNU Kernel Fuzzing Framework

## Project Status

SockFuzzer, originally designed as a networking-focused fuzzer for the XNU kernel (used in macOS and iOS), has evolved into a comprehensive kernel fuzzing framework. While retaining its original name as a nod to its roots, SockFuzzer now covers a wide range of kernel subsystems, including BSD, Mach, virtual memory, and more. The project implements a unique approach by converting the XNU kernel into a library that can be "booted" and fuzzed in userspace, allowing for efficient vulnerability discovery and reproduction across multiple subsystems.

## Project Goals

1. Comprehensively test the XNU kernel in a controlled environment
2. Discover and reproduce vulnerabilities across various XNU subsystems
3. Provide a framework for continuous fuzzing and improvement of XNU security
4. Demonstrate the value of implementing advanced fuzzing techniques in kernel research
5. Enable efficient testing of complex kernel interactions and subsystems

## Architecture Overview

SockFuzzer employs a host/"XNU guest" design, where the XNU kernel is compiled as a library and run within a custom userspace environment. This architecture consists of several key components:

1. Host Environment
2. XNU Guest Library
3. Custom Scheduler (based on Concurrence)
4. Fuzzing Engine (Centipede from Google's fuzztest project)
5. Test Runner and Harness

### Host Environment

The host environment provides the foundation for running the XNU guest library and managing the fuzzing process. It includes:

- Custom implementations of core kernel services
- Hypercall interface for communication between the host and XNU guest
- Test runner and harness for executing fuzz tests

### XNU Guest Library

The XNU kernel is compiled as a library (`libxnu`) with minimal modifications to run in userspace. Key aspects include:

- Symbol prefixing and management to avoid conflicts with host symbols
- Selective exposure of internal XNU functions through a version script
- Support for multiple subsystems: BSD, Mach, virtual memory, threads, processes, etc.
- Null pmap layer for virtual memory support (with plans to support ARM pmap in the future)

### Custom Scheduler

Based on the improved Concurrence project, the custom scheduler now supports full threading capabilities:

- Executor: Provides thread creation, deletion, and context switching
- FuzzedScheduler: Manages thread states and scheduling decisions
- Integration with the XNU guest library for proper multithreading support

### Test Runner and Harness

The test runner and harness manage the execution of fuzz tests and provide:

- Initialization of the XNU guest environment
- Execution of fuzz inputs across various subsystems
- Crash detection and reporting

## Key Features

1. Comprehensive XNU Kernel Coverage: Test multiple subsystems including BSD, Mach, virtual memory, threads, and processes
2. Userspace XNU Execution: Run XNU kernel components in a controlled userspace environment
3. Full Threading Support: Leverage improved Concurrence for proper multithreading capabilities
4. Virtual Memory Support: Utilize a null pmap layer with plans for ARM pmap support
5. MIG Fuzzing: Support for fuzzing Mach Interface Generator (MIG) interfaces
6. Hypercall Interface: Facilitate communication between host and XNU guest components

## Supported Features

1. BSD
2. Mach
3. Virtual Memory (with null pmap layer)
4. Threads and Processes
5. Networking
6. Mach Messages
7. MIG Interfaces

## Workflow

1. The XNU kernel is compiled as a library with necessary modifications
2. The host environment initializes the XNU guest library and custom scheduler
3. Centipede generates structured inputs using protobuf definitions
4. The test harness executes the inputs, invoking syscalls, Mach messages, and other kernel interfaces
5. The custom scheduler manages thread execution within the XNU guest
6. ASAN monitors for memory corruption issues
7. Crashes and coverage information are collected and analyzed

## Limitations and Future Work

1. IOKit Support: The current implementation does not support IOKit subsystems
2. Binary-only Fuzzing: The approach currently relies on source code which doesn't include all modules

Future work includes:
- Implementing IOKit support
- Integrating ARM pmap support for virtual memory
- Adapting techniques for binary-only fuzzing scenarios
- Continuing to expand coverage and support for XNU subsystems

## Public Release Limitations

In order to keep this repository well-factored, several dependencies will need to be added by users themselves to third_party, such as xnu, bootstrap_cmds, and a few other libraries.