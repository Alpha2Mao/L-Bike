//
// Created by 杜晓磊 on 2022/3/14.
//

#ifndef L_BIKE_CONFIG_H
#define L_BIKE_CONFIG_H
#include "tinyxml2.h"
#include <string>
#include <map>

using namespace std;

namespace LBike{
    enum LBIKE_CONFIG{
        LOG_DIR,
        MQTT_IP,
    };

    typedef struct config_item_s{
        LBIKE_CONFIG config_id;
        string config_name;
    } config_item_t;

    static config_item_t config_list[] = {
            {LBIKE_CONFIG::LOG_DIR, "log_dir"},
            {LBIKE_CONFIG::MQTT_IP, "mqtt_ip"}
    };



    class Config;

    Config *init();


    class Config {
    public:
        Config();
        string getConfigStringValue(LBIKE_CONFIG configId, string defaultStringValue);
        int getConfigIntValue(LBIKE_CONFIG configId, int defaultIntValue);


    protected:
        void init_config_map();

    private:
        FILE *fp;
        map<int, string> config_map;
    };
}


#endif //L_BIKE_CONFIG_H
