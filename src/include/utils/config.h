//
// Created by 杜晓磊 on 2022/3/14.
//

#ifndef L_BIKE_CONFIG_H
#define L_BIKE_CONFIG_H
#include "tinyxml2.h"
#include <string>
#include <map>
#include "config_define.h"

using namespace std;
using namespace tinyxml2;

namespace LBike{
    enum LBIKE_CONFIG{
        LOG_DIR,
        MQTT_IP,
        MQTT_PASSWORD,
    };

    typedef struct config_item_s{
        LBIKE_CONFIG config_id;
        string config_name;
    } config_item_t;

    static config_item_t config_list[] = {
            {LBIKE_CONFIG::LOG_DIR, "log_dir"},
            {LBIKE_CONFIG::MQTT_IP, "mqtt_ip"},
            {LBIKE_CONFIG::MQTT_PASSWORD, "mqtt_password"}
    };

    class Config {
    public:
        string getConfigStringValue(LBIKE_CONFIG configId, string defaultStringValue = "");
        int getConfigIntValue(LBIKE_CONFIG configId, int defaultIntValue = 0);

        static Config *getInstance();

        Config(Config const&) = delete;
        Config& operator=(Config const&) = delete;


    protected:
        void init_config_map();

    private:
        string getConfigStringValueInternal(LBIKE_CONFIG configId, string defaultStringValue);
        int getConfigIntValueInternal(LBIKE_CONFIG configId, int defaultIntValue);
        Config();
        ~Config();

    private:
        FILE *fp;
        map<int, string> config_map;
        static Config *instance;
        XMLDocument doc;
    };
}


#endif //L_BIKE_CONFIG_H
