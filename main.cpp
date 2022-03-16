#include <iostream>
#include "tinyxml2.h"
#include <glog/logging.h>
#include "utils/time.h"
#include "utils/config.h"

using namespace google;

int main(int argc, char **argv) {
    InitGoogleLogging(argv[0]);
    SetLogDestination(INFO, "./log/LBike_log");
    FLAGS_alsologtostderr = true;
    FLAGS_colorlogtostderr = true;
    FLAGS_max_log_size = 1;
    LOG(INFO) << "Hello New Bike, XML Library is init success";
    utils_time_point_value_t time_now;
    utils_system_time_now(&time_now);
    LOG(INFO) << " The time_now is " << time_now;
    LBike::Config *config = LBike::init();
    return 0;

}