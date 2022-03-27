#ifdef __cplusplus
extern "C"
{
#endif

#include <time.h>
#include <unistd.h>
#include <math.h>

#if defined(__MACH__)
#include <mach/clock.h>
#include <mach/mach.h>
#endif
#include "utils/time.h"
#include "utils/utils_ret.h"
#include <stdio.h>

#define __WOULD_BE_NEGATIVE(seconds, subseconds) (seconds < 0 || (subseconds < 0 && seconds == 0))


utils_ret_t utils_system_time_now(utils_duration_value_t *now) {
    struct timespec timespec_now;
#if defined(__MACH__)
    clock_serv_t clock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &clock);
    clock_get_time(clock, &mts);
    mach_port_deallocate(mach_task_self(), clock);
    timespec_now.tv_sec = mts.tv_sec;
    timespec_now.tv_nsec = mts.tv_nsec;
#else // defined(__MACH__)
    clock_gettime(CLOCK_REALTIME, &timespec_now);
#endif // defined(__MACH__)
    if (__WOULD_BE_NEGATIVE(timespec_now.tv_sec, timespec_now.tv_nsec)) {
        printf("Unexpect negative time");
        return UTILS_RET_ERROR;
    }
    *now = UTILS_NS_TO_S(timespec_now.tv_nsec) + timespec_now.tv_sec;
    return UTILS_RET_OK;
}

utils_ret_t utils_steady_time_now(utils_duration_value_t *now) {
    return UTILS_RET_OK;
}

utils_ret_t utils_time_point_value_as_nanoseconds_string(const utils_time_point_value_t *time_point,
                                                         char *str, size_t str_size) {
    return UTILS_RET_OK;
}

utils_ret_t utils_time_point_value_as_seconds_string(const utils_time_point_value_t *time_point,
                                                     char *str, size_t str_size) {
    return UTILS_RET_OK;
}


#ifdef __cplusplus
}
#endif