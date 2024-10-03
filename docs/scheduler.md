# SockFuzzer Custom Scheduler Documentation

## Overview

The SockFuzzer custom scheduler enables deterministic and reproducible testing of kernel components in a userspace environment by leveraging the Concurrence project. This document outlines the scheduler's architecture, key components, and its integration with the host/XNU guest design.

## Host/XNU Guest Design

SockFuzzer employs a host/XNU guest design to facilitate the fuzzing process:

- Host: The userspace environment that manages the fuzzing process and provides core services.
- XNU Guest: The XNU kernel compiled as a library (`libxnu`) that runs within the host environment.

This separation allows for fine-grained control over kernel execution and enables efficient fuzzing of XNU components.

## Scheduler Architecture

The custom scheduler is based on the Concurrence project and consists of two main components:

1. Executor
2. FuzzedScheduler

### Executor

The Executor provides low-level thread management capabilities:

- Thread creation and deletion
- Context switching
- Thread state management

Key methods:
- `CreateThread(std::function<void()> target)`
- `DeleteThread(ThreadHandle handle)`
- `SwitchTo(ThreadHandle handle)`
- `GetCurrentThreadHandle()`

### FuzzedScheduler

The FuzzedScheduler builds upon the Executor to provide high-level scheduling decisions and thread state management:

- Thread state transitions (runnable, blocked, etc.)
- Fuzzer-driven thread selection
- Integration with the XNU guest library

Key methods:
- `CreateThread(std::function<void()> target, bool runnable)`
- `ChooseThread(bool can_choose_existing)`
- `MakeRunnable(ThreadHandle handle)`
- `Block()`
- `Yield()`

## Integration with Host/XNU Guest Design

The scheduler operates within the host environment but manages threads running XNU guest code. This integration is achieved through several mechanisms:

1. Hypercall Interface: Allows XNU guest code to communicate with the host scheduler.
2. Thread Mapping: Maps XNU thread structures to host-managed ThreadHandles.
3. Cooperative Multitasking: XNU guest code yields control to the scheduler at appropriate points.

## Key Features

1. Deterministic Execution: Enables reproducible fuzzing sessions.
2. Fuzzer-Driven Scheduling: Allows exploration of different thread interleavings.
3. Full Threading Support: Simulates real kernel threading behavior.
4. Cooperative Multitasking: Ensures controlled execution of XNU guest code.

## Usage in SockFuzzer

The custom scheduler is used throughout the fuzzing process:

1. Initialization: Set up initial XNU guest threads.
2. Fuzzing Loop: Manage thread execution during fuzz test runs.
3. Crash Analysis: Provide thread state information for crash reports.

## Limitations and Future Work

- Performance Optimization: Further improve scheduling efficiency.
- Advanced Scheduling Policies: Implement more sophisticated scheduling algorithms.
- Race Condition Detection: Enhance capabilities to detect and reproduce race conditions.