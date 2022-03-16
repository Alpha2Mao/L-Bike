#ifndef UTILS__TIME_H_
#define UTILS__TIME_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stddef.h>

#include "utils_ret.h"

#define UTILS_S_TO_NS(second) ((seconds) * (1000LL * 1000LL * 1000LL))
#define UTILS_MS_TO_NS(millisecond) ((millisecond) * (1000LL * 1000LL))
#define UTILS_US_TO_NS(microsecond) ((microsecond) * 1000LL)

#define UTILS_NS_TO_S(nanoseconds) ((nanoseconds) / (1000LL * 1000LL * 1000LL))
#define UTILS_NS_TO_MS(nanoseconds) ((nanoseconds) / (1000LL * 1000LL))
#define UTILS_NS_TO_US(nanoseconds) ((nanoseconds) / (1000LL))
#define UTILS_STEADY_TIME_NOW utils_steady_time_now

typedef int64_t utils_time_point_value_t;
typedef int64_t utils_duration_value_t;

utils_ret_t utils_system_time_now(utils_duration_value_t *now);

utils_ret_t utils_steady_time_now(utils_duration_value_t *now);

utils_ret_t utils_time_point_value_as_nanoseconds_string(const utils_time_point_value_t *time_point,
                                                         char *str, size_t str_size);

utils_ret_t utils_time_point_value_as_seconds_string(const utils_time_point_value_t * time_point,
                                                     char * str, size_t str_size);

#ifdef __cplusplus
}
#endif


#endif