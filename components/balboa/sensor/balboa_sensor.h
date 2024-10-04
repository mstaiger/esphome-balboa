#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "../balboa.h"

namespace esphome {
namespace balboa {

class BalboaSensor : public sensor::Sensor, public Component, public BalboaClient {
 public:
  void setup() override;
  void dump_config() override;
  void set_sensor_id(const std::string &sensor_id) { this->sensor_id_ = sensor_id; }

 protected:
  std::string sensor_id_{""};
};

}  // namespace balboa
}  // namespace esphome
