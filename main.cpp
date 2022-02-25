#include <iostream>
#include "tinyxml2.h"
#include <glog/logging.h>

using namespace google;

int main(int argc, char **argv) {
    InitGoogleLogging(argv[0]);
    SetLogDestination(INFO, "./log/LBike_log");
    FLAGS_alsologtostderr = true;
    FLAGS_colorlogtostderr = true;
    FLAGS_max_log_size = 1;
    LOG(INFO) << "Hello New Bike, XML Library is init success";
    return 0;
}