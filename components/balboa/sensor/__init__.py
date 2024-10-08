import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, CONF_SENSOR_DATAPOINT

from .. import (
    CONF_BALBOA_ID,
    CONF_REQUEST_MOD,
    CONF_REQUEST_ONCE,
    CONF_SRC_ADDRESS,
    BALBOA_CLIENT_SCHEMA,
    BalboaClient,
    balboa_ns,
)

DEPENDENCIES = ["balboa"]

BalboaSensor = balboa_ns.class_(
    "BalboaSensor", sensor.Sensor, cg.Component, BalboaClient
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(BalboaSensor)
    .extend(
        {
            cv.Required(CONF_SENSOR_DATAPOINT): cv.string,
        }
    )
    .extend(BALBOA_CLIENT_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)

    paren = await cg.get_variable(config[CONF_BALBOA_ID])
    cg.add(var.set_balboa_parent(paren))
    cg.add(var.set_request_mod(config[CONF_REQUEST_MOD]))
    cg.add(var.set_request_once(config[CONF_REQUEST_ONCE]))
    cg.add(var.set_sensor_id(config[CONF_SENSOR_DATAPOINT]))
    cg.add(var.set_src_adr(config[CONF_SRC_ADDRESS]))
