#include "esphome/core/log.h"
#include "balboa_sensor.h"

namespace esphome {
namespace balboa {

static const char *const TAG = "balboa.sensor";

void BalboaSensor::setup() {
  if (this->parent_ == nullptr) {
    ESP_LOGE(TAG, "Parent Balboa component is not set!");
    this->mark_failed();
    return;
  }

  this->parent_->register_listener(
      this->sensor_id_, this->request_mod_, this->request_once_,
      [this](const BalboaDatapoint &datapoint) {
        if (datapoint.type == BalboaDatapointType::FLOAT) {
          ESP_LOGV(TAG, "MCU reported sensor %s is: %f", this->sensor_id_.c_str(), datapoint.value_float);
          this->publish_state(datapoint.value_float);
        } else if (datapoint.type == BalboaDatapointType::ENUM_TEXT) {
          ESP_LOGV(TAG, "MCU reported sensor %s is: %u", this->sensor_id_.c_str(), datapoint.value_enum);
          this->publish_state(datapoint.value_enum);
        }
      },
      false, this->src_adr_);
}

void BalboaSensor::dump_config() {
  LOG_SENSOR("", "Balboa Sensor", this);
  ESP_LOGCONFIG(TAG, "  Sensor has datapoint ID %s", this->sensor_id_.c_str());
}

}  // namespace balboa
}  // namespace esphome
