#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "../balboa.h"

namespace esphome {
namespace balboa {

class BalboaSensor : public sensor::Sensor, public Component {
 public:
  void setup() override;
  void dump_config() override;
  void set_sensor_id(const std::string &sensor_id) { this->sensor_id_ = sensor_id; }
  void set_balboa_parent(Balboa *parent) { this->parent_ = parent; }
  void set_request_mod(int8_t request_mod) { this->request_mod_ = request_mod; }
  void set_request_once(bool request_once) { this->request_once_ = request_once; }
  void set_src_adr(uint32_t src_adr) { this->src_adr_ = src_adr; }

 protected:
  Balboa *parent_;
  std::string sensor_id_{""};
  int8_t request_mod_{0};
  bool request_once_{false};
  uint32_t src_adr_{0};
};

}  // namespace balboa
}  // namespace esphome
