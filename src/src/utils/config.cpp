//
// Created by 杜晓磊 on 2022/3/14.
//

#include "utils/config.h"
#include <glog/logging.h>

namespace LBike{

    Config* Config::instance = nullptr;

    Config* Config::getInstance() {
        if (!instance) {
            return new Config();
        }
        return instance;
    }

    Config::Config() {
        fp = fopen(LBIKE_CONFIG_FILE_PATH, "rw");
        if (!fp) {
            LOG(FATAL) << "Error in open " << LBIKE_CONFIG_FILE_PATH;
        }
        XMLError error =  doc.LoadFile(LBIKE_CONFIG_FILE_PATH);
        LOG_IF(FATAL, error > XML_SUCCESS) << "return code: " << error << ", load " <<
        LBIKE_CONFIG_FILE_PATH << "file error";

        // print xml content
        XMLPrinter streamer;
        doc.Print(&streamer);
        LOG(INFO) << "The content of xml file is\n" << streamer.CStr();
        init_config_map();
    }

    string Config::getConfigStringValue(LBIKE_CONFIG configId, string defaultStringValue) {
        auto pos = config_map.find(configId);
        if (pos != config_map.end()) {
            return getConfigStringValueInternal(configId, defaultStringValue);
        }
        return defaultStringValue;
    }

    int Config::getConfigIntValue(LBIKE_CONFIG configId, int defaultIntValue) {
        auto pos = config_map.find(configId);
        if (pos != config_map.end()) {
            return 0;
        }
        return defaultIntValue;
    }

    void Config::init_config_map() {
        for (const config_item_t& item : config_list){
            config_map.insert(map<int, string>::value_type(item.config_id, item.config_name));
        }
    }

    Config::~Config() {
        fclose(fp);
        delete instance;
        instance = nullptr;
    }

    string Config::getConfigStringValueInternal(LBIKE_CONFIG configId, string defaultStringValue){
        switch (configId) {
            case LOG_DIR:
            {
                return "";
            }
            case MQTT_IP:
            {
                auto mqtt_ip_element = doc.FirstChildElement("document")->
                        FirstChildElement("config")->
                        FirstChildElement("mqtt")->
                        FirstChildElement("mqtt_ip");
                if (mqtt_ip_element) {
                    string mqtt_ip = mqtt_ip_element->GetText();
                    LOG(INFO) << "The mqtt ip query success, the value is " << mqtt_ip;
                    return mqtt_ip;
                }
                LOG(ERROR) << "The mqtt ip query failed, return default value: " << defaultStringValue;
                return defaultStringValue;
            }
            case MQTT_PASSWORD:
            {
                auto mqtt_password_element = doc.FirstChildElement("document")->
                        FirstChildElement("config")->
                        FirstChildElement("mqtt")->
                        FirstChildElement("mqtt_password");
                if (mqtt_password_element) {
                    string mqtt_password = mqtt_password_element->GetText();
                    LOG(INFO) << "The mqtt ip query success, the value is " << mqtt_password;
                    return mqtt_password;
                }
                LOG(ERROR) << "The mqtt ip query failed, return default value: " << defaultStringValue;
                return defaultStringValue;
            }

        }

    }

    int Config::getConfigIntValueInternal(LBIKE_CONFIG configId, int defaultIntValue){
        return 0;
    }
}