/*
 * Copyright 2024 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FUZZ_HOST_HYPERCALL_TYPES_H_
#define FUZZ_HOST_HYPERCALL_TYPES_H_

enum bad_state {
  RUNNING_AFTER_CONTINUATION = 0,
};

enum log_subsystem {
  VIRTUAL_MEMORY = 0,
  TICKET_LOCK = 1,
  THREAD = 2,
  ABORT = 3,
  ANY_SUBSYSTEM = 4,
};

#endif /* FUZZ_HOST_HYPERCALL_TYPES_H_ */
