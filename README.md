# SockFuzzer

This repository contains SockFuzzer, a fork of XNU that contains support
for fuzzing the network stack in userland on macOS and Linux-based hosts.

# Building and Using the Fuzzer

Build the fuzzer the same way you would typically build a project using CMake
for your platform. For example:

```
$ mkdir build; cd build
$ cmake -GNinja ..
$ ninja
```

You can now run the `net_fuzzer` binary, optionally providing parameters as
described in the [libFuzzer documentation](https://llvm.org/docs/LibFuzzer.html).

A Dockerfile is included which shows how to prepare a Debian environment to build
the project. Feel free to use this container to build and run the fuzzer.

# Extending the Fuzzer

This project is currently an all-in-one fuzzer for XNU networking. You can extend
it by adding additional targets to CMakeLists.txt or by extending the existing
network target. Nothing about this project specifically prevents the testing of
additional non-networking subsystems, so feel free to extend it to test other
areas.

# Generating and Reviewing Coverage Reports

Coverage reports are an important way to review the quality of the current
fuzzer implementation. On Linux, a `net_cov` binary is generated containing
[LLVM's source based code-coverage](https://clang.llvm.org/docs/SourceBasedCodeCoverage.html)
instrumentation.

At the time of writing, the following commands product an HTML coverage report located
in the `report` folder after running all of the testcases located in the `corpus` folder.

```
./net_cov corpus
llvm-profdata merge -sparse default.profraw -o default.profdata
llvm-cov show -format=html -output-dir=report -instr-profile=default.profdata net_cov
```

# Importing upstream XNU releases

A macOS environment is needed to generate the new files. Unpack the new source tarball
replacing third_party/xnu. Then run the following command, updating SDKROOT as needed.
Then you can add BUILD/obj/EXPORT_HDRS and BUILD/obj/DEBUG_X86_64 to the git repo.
You'll also need to rebase any changes to the original XNU sources. In some cases, the
outer CMakeLists.txt must also be updated to reflect new or deleted source paths.

I use an upstream branch to facilitate merging my patches with the upstream changes.

```
# From inside third_party/xnu
$ make SDKROOT=macosx11.1 ARCH_CONFIGS=X86_64 KERNEL_CONFIGS=DEBUG
$ git add BUILD/obj/EXPORT_HDRS EXTERNAL_HEADERS
```

# Disclaimer

This is not an official Google product.
