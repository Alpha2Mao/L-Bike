#include <iostream>
#include "tinyxml2.h"
#include <glog/logging.h>
#include "utils/time.h"
#include "utils/config.h"
#include "lbike_versions.hpp"
#include <thread>
#include "utils/lbike_timer.h"
#include <cstdlib>
#include <getopt.h>

using namespace google;
using namespace std;

void printApplicationInfo() {
    LOG(INFO) << "============================================";
    LOG(INFO) << LBIKE_LATEST_RELEASE_VERSION;
    LOG(INFO) << LBIKE_BUILDDATE;
    LOG(INFO) << LBIKE_SHA1;
    LBIKE_PRINT_BUILDINFO();

}

static void __attribute__ ((__noreturn__))
Usage(FILE *out) {
    fputs(USAGE_HEADER, out);
    fprintf(out, " %s [options] [variable[=value] ...]\n", "lbike");
    fputs(USAGE_OPTIONS, out);
    fputs("  -a, --all            display all configure variable\n", out);
    fputs("  -r, --remote         set remote server ip address\n", out);
    fputs("  -p, --port           set remove server port\n", out);
    fputs(USAGE_SEPARATOR, out);
    fputs(USAGE_HELP, out);
    fputs(USAGE_VERSION, out);

    exit(out == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}

static const struct option longopts[] = {
        {"all", no_argument, NULL, 'a'},
        {"remote", no_argument, NULL, 'r'},
        {"port", no_argument, NULL, 'p'},
        {NULL, 0, NULL, 0}
};

/**
 * init glog module
 */
static void initGlog(int argc, char **argv) {
    // init glog module
    InitGoogleLogging(argv[0]);
    SetLogDestination(INFO, LBIKE_LOG_PATH);
    FLAGS_alsologtostderr = true;
    FLAGS_colorlogtostderr = true;
    FLAGS_timestamp_in_logfile_name= false;
    FLAGS_max_log_size = 1;
}


int main(int argc, char **argv) {
    initGlog(argc, argv);

    int optc = 0;
    while ((optc = getopt_long(argc, argv, "arphv", longopts, NULL)) != -1) {
        switch (optc) {
            case 'a':
                LOG(INFO) << "Print all the config info";
                break;
            case 'r':
                LOG(INFO) << "Set remote ip is ";
                break;
            case 'p':
                LOG(INFO) << "Set remove port is ";
                break;
            case 'h':
                Usage(stdout);
            case 'v':
                printApplicationInfo();
                return EXIT_SUCCESS;
            default:
                Usage(stderr);
        }
    }

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

//    std::shared_ptr<lbike::Timer> testTimer = std::make_shared<lbike::Timer>();
//    testTimer->Start(0, &printApplicationInfo, 2000);
//    for (;;){
//
//    }
    return EXIT_SUCCESS;
}