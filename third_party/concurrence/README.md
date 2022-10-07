# Concurrence

Concurrence is a library for fuzzing multi-threaded targets. It schedules one
thread at a time cooperatively and selects threads using fuzzed input data. This
project is still in early stages and this repository serves as a reference.

There are three main components. The executor handles how contexts (threads) get
created, deleted, and defines how to switch between them. The scheduler depends
on the abstract executor interface. We provide a fuzzed scheduler implementation
to expose the scheduling decisions to fuzzed inputs. The sync primitives depend
on the scheduler and provide an example of how to integrate with the scheduler.

In order to support developers' goals, every component is interchangeable. You
could have your own notion of thread creation and switching and write a custom
executor implementation. You could also opt for another scheduler implementation.
Finally, the sync primitives might not match the behavior of your codebase. You
could use your existing sync primitives without an issue so long as you can
Block() or Yield() appropriately so the scheduler knows which contexts are runnable.

# Kernel vs. Userspace

Currently, the project targets a kernel which means it has to handle things
like interrupt masking and deleting a thread that's waiting to return from a
context switch. These aspects are incompatible with userspace target fuzzing.
A future version of this library will attempt to bridge this gap so it can be
used for arbitrary targets. Until then, do not expect the API to remain stable.

# Documentation

See presentations/catch_me_if_you_can.pdf to read the slides from my Black Hat 2022
presentation on this project. It covers the design and motivation and provides some
real world examples of bugs found using this project.

# Build

This project is built using Bazel. The //scheduler:fuzzed_scheduler target, when paired
with a suitable executor for your codebase, is the core class of this project and is
probably what you're looking for if you're not using this as a generic execution library.

You can use or review //sync:mutex and //sync:rwlock to see how to interact with the
scheduler from your target code to explicitly yield or block in code that was designed
for multi-threaded environments.
