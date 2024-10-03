# SockFuzzer Unit Testing

## Overview

This project aims to test various components of the XNU kernel in a Linux user-mode environment. We use a combination of custom fake implementations, real XNU code, and a shared testing framework to achieve this goal. The structure accommodates the different subsystems of XNU (e.g., BSD, OSFMK) and their unique build requirements while maximizing code reuse where possible.

## Key Components

1. XNU Source Code: Located in `third_party/xnu/`
2. Fake Implementations: 
   - OSFMK: `fuzz/xnu/osfmk/fakes/`
   - BSD: `fuzz/xnu/bsd/fakes/`
   - (Other XNU subsystems follow a similar pattern)
3. Test Implementations: 
   - OSFMK: `fuzz/xnu/osfmk/test/`
   - BSD: `fuzz/xnu/bsd/test/`
   - (Other XNU subsystems follow a similar pattern)
4. Common Test Utilities: `fuzz/xnu/common/test_utils.h` and `fuzz/xnu/common/test_utils.c`
5. Shared Test Runner: `fuzz/host/test_runner.c`
6. Build System: Using Bazel

## Testing Framework

We use cmocka as our primary testing framework for its C compatibility, lightweight nature, and mocking capabilities. However, to handle the unique requirements of testing XNU components, we've implemented a custom assertion mechanism that works within the XNU environment and integrates with cmocka in the test runner.

## Test Structure

Our test structure consists of:

1. Common Test Utilities (`fuzz/xnu/common/test_utils.h` and `test_utils.c`): Provides a `TestResult` structure and custom assertion macros that can be used within XNU subsystem tests.
2. Subsystem-specific Test Implementations (e.g., `fuzz/xnu/osfmk/test/osfmk_test_impl.c`): Contain the actual test logic that interacts with XNU code for each subsystem, using the common test utilities.
3. Subsystem-specific Test Headers (e.g., `fuzz/xnu/osfmk/test/osfmk_test_impl.h`): Declare the test functions implemented in the corresponding test implementation files.
4. Shared Test Runner (`fuzz/host/test_runner.c`): Contains the main cmocka test runner, calls the XNU subsystem tests, and integrates their results with cmocka's reporting mechanism.

This approach allows us to:
- Isolate XNU-specific code and its dependencies in subsystem-specific implementations.
- Use a consistent assertion and result reporting mechanism across all XNU subsystem tests.
- Integrate XNU test results with cmocka's test runner and reporting features.
- Share common test setup, teardown, and utility functions across all subsystems.
- Simplify the addition of new tests for different subsystems.

## Build Configuration

We use the following Bazel targets:

1. Common Test Utilities: A cc_library target that provides the TestResult structure and assertion utilities.
2. Subsystem-specific Test Implementation Libraries: cc_library targets that include XNU headers, fake implementations, and the common test utilities for each subsystem.
3. Shared Test Runner: A cc_library that includes cmocka and common test utilities.
4. Test Executable: A cc_test target that links the shared test runner with subsystem-specific test implementations.

## Directory Structure

```
fuzz/
├── host/
│   ├── BUILD.bazel
│   └── test_runner.c
└── xnu/
    ├── common/
    │   ├── test_utils.h
    │   └── test_utils.c
    ├── bsd/
    │   └── fakes/
    │       └── (BSD-specific fake implementations)
    └── osfmk/
        ├── BUILD.bazel
        ├── fakes/
        │   └── (OSFMK-specific fake implementations)
        └── test/
            ├── osfmk_test_impl.c
            └── osfmk_test_impl.h
```

## Assumptions and Design Decisions

1. XNU Code Isolation: XNU code can be compiled and run in a Linux user-mode environment with appropriate fake implementations.
2. Subsystem Separation: Each XNU subsystem has its own directory for fakes and tests due to different build requirements and header dependencies.
3. Common Test Utilities: Assertion and result reporting mechanisms are shared across all XNU subsystem tests.
4. Shared Test Runner: Common test functionality and integration with cmocka are shared across all subsystems.
5. Header Usage: We use headers from `third_party/xnu/` directly in test implementations.
6. Fake Implementations: Treated as hidden implementation details in the test code.
7. Compilation Flag Isolation: Test implementation headers are separated from their implementation to avoid propagating XNU-specific compilation flags to the test runner.

## Guidelines for Contributors

1. Familiarize yourself with the XNU subsystem you're working on and its API.
2. Understand the separation between the shared test runner, common test utilities, and subsystem-specific test implementations.
3. When adding new tests:
   - Implement the test logic in the appropriate subsystem's `*_test_impl.c` file.
   - Use the `XNU_ASSERT` macro from the common test utilities for assertions.
   - Declare the test function in the corresponding `*_test_impl.h` file.
   - Add the new test case to the `tests` array in the shared test runner (`fuzz/host/test_runner.c`).
   - Ensure you're working in the correct subsystem directory (osfmk, bsd, etc.) for subsystem-specific code.
4. Ensure all XNU-specific code is isolated in the subsystem-specific test implementations.
5. Use fake implementations where necessary, but don't explicitly include them in test code.
6. When adding new fake implementations, place them in the appropriate subsystem's `fakes/` directory.
7. For common test utilities or setup/teardown functions, consider adding them to the common test utilities or the shared test runner as appropriate.
8. When adding new subsystem tests, update the `BUILD.bazel` files accordingly:
   - Add new `cc_library` targets for test implementation and headers in the subsystem's `BUILD.bazel` file.
   - Update the `deps` in the test executable target in `fuzz/host/BUILD.bazel` to include the new test implementation.