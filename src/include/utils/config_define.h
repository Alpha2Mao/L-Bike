//
// Created by 杜晓磊 on 2022/3/27.
//

#ifndef L_BIKE_CONFIG_DEFINE_H
#define L_BIKE_CONFIG_DEFINE_H
#include <string>
using namespace std;

//#define LBIKE_CONFIG_FILE_PATH "./etc/lbike-config.xml"
#if DEBUG
#define LBIKE_CONFIG_FILE_PATH "../../src/resource/lbike-config.xml"
#define LBIKE_LOG_PATH "./log/LBike_log"
#else
#define LBIKE_CONFIG_FILE_PATH "/etc/lbike/lbike-config.xml"
#define LBIKE_LOG_PATH "/tmp/log/LBike_log"
#endif

/**
 * Constant String for Usage function
 */
#define USAGE_HEADER "\nUsage:\n"
#define USAGE_OPTIONS "\nOptions:\n"
#define USAGE_SEPARATOR "\n"
#define USAGE_HELP    " -h, --help       display this help and exit\n"
#define USAGE_VERSION " -v, --version    output version information and exit\n"

#endif //L_BIKE_CONFIG_DEFINE_H
