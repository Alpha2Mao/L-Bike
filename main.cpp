#include <iostream>
#include "tinyxml2.h"
#include <glog/logging.h>
#include "utils/time.h"
#include "utils/config.h"
#include "lbike_versions.hpp"
#include <thread>

using namespace google;
using namespace std;

int main(int argc, char **argv) {
    // init glog module
    InitGoogleLogging(argv[0]);
    SetLogDestination(INFO, "./log/LBike_log");
    FLAGS_alsologtostderr = true;
    FLAGS_colorlogtostderr = true;
    FLAGS_timestamp_in_logfile_name= false;
    FLAGS_max_log_size = 1;

    // print application info
    LOG(INFO) << LBIKE_LATEST_RELEASE_VERSION;
    LOG(INFO) << LBIKE_BUILDDATE;
    LOG(INFO) << LBIKE_SHA1;
    LBIKE_PRINT_BUILDINFO();

    utils_time_point_value_t time_now;
    utils_system_time_now(&time_now);
    LOG(INFO) << " The time_now is " << time_now;

    // instance config instance
    LBike::Config *config = LBike::Config::getInstance();
    string mqtt_ip = config->getConfigStringValue(LBike::MQTT_IP);
    LOG(WARNING) << "The mqtt ip is " << mqtt_ip;

    return 0;
}