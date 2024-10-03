/*
 * Copyright 2024 Google LLC
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#include <kern/clock.h>

#include "fuzz/host/hypercall/hypercall.h"

void absolutetime_to_nanoseconds(uint64_t abstime, uint64_t *result) {
  *result = abstime;
}

void clock_interval_to_absolutetime_interval(uint32_t interval,
                                             uint32_t scale_factor,
                                             uint64_t *result) {
  uint64_t nanosecs = (uint64_t)interval * scale_factor;
  uint64_t t64;

  *result = (t64 = nanosecs / NSEC_PER_SEC) * 1;
  nanosecs -= (t64 * NSEC_PER_SEC);
  *result += (nanosecs * 1) / NSEC_PER_SEC;
}

void absolutetime_to_microtime(uint64_t abstime, clock_sec_t *secs,
                               clock_usec_t *microsecs) {
  uint64_t t64;

  *secs = t64 = abstime / 1;
  abstime -= (t64 * 1);

  *microsecs = (uint32_t)(abstime / 1);
}

void clock_get_system_microtime(clock_sec_t *secs, clock_usec_t *microsecs) {
  absolutetime_to_microtime(mach_absolute_time(), secs, microsecs);
}

void clock_get_system_nanotime(clock_sec_t *secs, clock_nsec_t *nanosecs) {
  uint64_t abstime;
  uint64_t t64;

  abstime = mach_absolute_time();
  *secs = (t64 = abstime / 1);
  abstime -= (t64 * 1);

  *nanosecs = (clock_nsec_t)((abstime * NSEC_PER_SEC) / 1);
}

uint64_t g_abstime;
uint64_t g_sec;
uint64_t g_frac;
uint64_t g_scale;
uint64_t g_tick_per_sec;

void commpage_set_timestamp(uint64_t abstime, uint64_t sec, uint64_t frac,
                            uint64_t scale, uint64_t tick_per_sec) {
  g_abstime = abstime;
  g_sec = sec;
  g_frac = frac;
  g_scale = scale;
  g_tick_per_sec = tick_per_sec;
}

void clock_gettimeofday_set_commpage(uint64_t abstime, uint64_t sec,
                                     uint64_t frac, uint64_t scale,
                                     uint64_t tick_per_sec) {
  commpage_set_timestamp(abstime, sec, frac, scale, tick_per_sec);
}

void PESetUTCTimeOfDay(clock_sec_t secs, clock_usec_t usecs) {}

void commpage_update_boottime(uint64_t boottime_usec) {}

void PEGetUTCTimeOfDay(clock_sec_t *secs, clock_usec_t *usecs) {
  GetHypercallInterface()->Abort();
}

void commpage_update_mach_continuous_time(uint64_t sleeptime) {
  GetHypercallInterface()->Abort();
}

boolean_t ml_delay_should_spin(uint64_t interval) {
  GetHypercallInterface()->Abort();
}

void machine_delay_until(uint64_t interval, uint64_t deadline) {
#pragma unused(interval)
  uint64_t now;

  do {
    GetHypercallInterface()->Yield();
    // __builtin_arm_wfe();
    now = mach_absolute_time();
  } while (now < deadline);
}

void rtclock_init() {}

// TODO(nedwill): implement these functions to support time passage
uint64_t mach_absolute_time() {
  return 0;
}

uint64_t mach_approximate_time() {
  return 1337;
}
