#ifdef __cplusplus
extern "C"
{
#endif

#include "utils/time.h"
#include "utils/utils_ret.h"


utils_ret_t utils_system_time_now(utils_duration_value_t *now){
    return UTILS_RET_OK;
}

utils_ret_t utils_steady_time_now(utils_duration_value_t *now){
    return UTILS_RET_OK;
}

utils_ret_t utils_time_point_value_as_nanoseconds_string(const utils_time_point_value_t *time_point,
                                                         char *str, size_t str_size){
    return UTILS_RET_OK;
}

utils_ret_t utils_time_point_value_as_seconds_string(const utils_time_point_value_t * time_point,
                                                     char * str, size_t str_size){
    return UTILS_RET_OK;
}



#ifdef __cplusplus
}
#endif