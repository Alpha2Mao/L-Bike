#include <iostream>
#include "include/glog/logging.h"
#include "src/third/ThirdConfig.h"

using namespace google;

int main(int argc, char **argv) {
    ThirdConfig* thirdConfig = ThirdConfig::getInstance(argv);
    return 0;
}