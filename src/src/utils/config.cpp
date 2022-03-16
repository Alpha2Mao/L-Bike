//
// Created by 杜晓磊 on 2022/3/14.
//

#include "utils/config.h"
#include "glog/logging.h"

namespace LBike{
    Config *init() {
        return new Config();
    }



    Config::Config() {
        fp = fopen("./etc/lbike-config.xml", "rw");
        if (!fp) {
            LOG(INFO) << "Error in open lbike-config.xml";
        }
        init_config_map();
    };

    string Config::getConfigStringValue(LBIKE_CONFIG configId, string defaultStringValue) {
        auto pos = config_map.find(configId);
        if (pos != config_map.end()) {
            return "";
        }
        return defaultStringValue;
    }

    int Config::getConfigIntValue(LBIKE_CONFIG configId, int defaultIntValue) {
        auto pos = config_map.find(configId);
        if (pos != config_map.end()) {
            return 0;
        }
        return 0;
    }

    void Config::init_config_map() {
        for (config_item_t item : config_list){
            config_map.insert(map<int, string>::value_type(item.config_id, item.config_name));
        }
    }
}