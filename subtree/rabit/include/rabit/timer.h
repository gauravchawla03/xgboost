/*!
 * \file timer.h
 * \brief This file defines the utils for timing
 * \author Tianqi Chen, Nacho, Tianyi
 */
#ifndef RABIT_TIMER_H_
#define RABIT_TIMER_H_
#include <time.h>
#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif
#include "./utils.h"

namespace rabit {
namespace utils {
/*!
 * \brief return time in seconds, not cross platform, avoid to use this in most places
 */
inline double GetTime(void) {
  #ifdef __MACH__ 
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  utils::Check(clock_get_time(cclock, &mts) == 0, "failed to get time");
  mach_port_deallocate(mach_task_self(), cclock);
  return static_cast<double>(mts.tv_sec) + static_cast<double>(mts.tv_nsec) * 1e-9;
  #else
  timespec ts;
  utils::Check(clock_gettime(CLOCK_REALTIME, &ts) == 0, "failed to get time");
  return static_cast<double>(ts.tv_sec) + static_cast<double>(ts.tv_nsec) * 1e-9;
  #endif
}
}  // namespace utils
}  // namespace rabit
#endif  // RABIT_TIMER_H_
