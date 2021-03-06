/**
 * Arduino DSMR parser.
 *
 * This software is licensed under the MIT License.
 *
 * Copyright (c) 2015 Matthijs Kooijman <matthijs@stdin.nl>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Field parsing functions
 */

#include "fields.h"


using namespace dsmr;
using namespace dsmr::fields;

// Since C++11 it is possible to define the initial values for static
// const members in the class declaration, but if their address is
// taken, they still need a normal definition somewhere (to allocate
// storage).
constexpr char units::none[];
constexpr char units::kWh[];
constexpr char units::Wh[];
constexpr char units::kW[];
constexpr char units::W[];
constexpr char units::V[];
constexpr char units::mV[];
constexpr char units::A[];
constexpr char units::mA[];
constexpr char units::m3[];
constexpr char units::dm3[];
constexpr char units::GJ[];
constexpr char units::MJ[];

constexpr ObisId identification::id;
constexpr const std::string_view identification::name;

constexpr ObisId p1_version::id;
constexpr const std::string_view p1_version::name;

constexpr ObisId timestamp::id;
constexpr const std::string_view timestamp::name;

constexpr ObisId equipment_id::id;
constexpr const std::string_view equipment_id::name;

constexpr ObisId energy_delivered_tariff1::id;
constexpr const std::string_view energy_delivered_tariff1::name;

constexpr ObisId energy_delivered_tariff2::id;
constexpr const std::string_view energy_delivered_tariff2::name;

constexpr ObisId energy_returned_tariff1::id;
constexpr const std::string_view energy_returned_tariff1::name;

constexpr ObisId energy_returned_tariff2::id;
constexpr const std::string_view energy_returned_tariff2::name;

constexpr ObisId electricity_tariff::id;
constexpr const std::string_view electricity_tariff::name;

constexpr ObisId power_delivered::id;
constexpr const std::string_view power_delivered::name;

constexpr ObisId power_returned::id;
constexpr const std::string_view power_returned::name;

constexpr ObisId electricity_threshold::id;
constexpr const std::string_view electricity_threshold::name;

constexpr ObisId electricity_switch_position::id;
constexpr const std::string_view electricity_switch_position::name;

constexpr ObisId electricity_failures::id;
constexpr const std::string_view electricity_failures::name;

constexpr ObisId electricity_long_failures::id;
constexpr const std::string_view electricity_long_failures::name;

constexpr ObisId electricity_failure_log::id;
constexpr const std::string_view electricity_failure_log::name;

constexpr ObisId electricity_sags_l1::id;
constexpr const std::string_view electricity_sags_l1::name;

constexpr ObisId electricity_sags_l2::id;
constexpr const std::string_view electricity_sags_l2::name;

constexpr ObisId electricity_sags_l3::id;
constexpr const std::string_view electricity_sags_l3::name;

constexpr ObisId electricity_swells_l1::id;
constexpr const std::string_view electricity_swells_l1::name;

constexpr ObisId electricity_swells_l2::id;
constexpr const std::string_view electricity_swells_l2::name;

constexpr ObisId electricity_swells_l3::id;
constexpr const std::string_view electricity_swells_l3::name;

constexpr ObisId message_short::id;
constexpr const std::string_view message_short::name;

constexpr ObisId message_long::id;
constexpr const std::string_view message_long::name;

constexpr ObisId voltage_l1::id;
constexpr const std::string_view voltage_l1::name;

constexpr ObisId voltage_l2::id;
constexpr const std::string_view voltage_l2::name;

constexpr ObisId voltage_l3::id;
constexpr const std::string_view voltage_l3::name;

constexpr ObisId current_l1::id;
constexpr const std::string_view current_l1::name;

constexpr ObisId current_l2::id;
constexpr const std::string_view current_l2::name;

constexpr ObisId current_l3::id;
constexpr const std::string_view current_l3::name;

constexpr ObisId power_delivered_l1::id;
constexpr const std::string_view power_delivered_l1::name;

constexpr ObisId power_delivered_l2::id;
constexpr const std::string_view power_delivered_l2::name;

constexpr ObisId power_delivered_l3::id;
constexpr const std::string_view power_delivered_l3::name;

constexpr ObisId power_returned_l1::id;
constexpr const std::string_view power_returned_l1::name;

constexpr ObisId power_returned_l2::id;
constexpr const std::string_view power_returned_l2::name;

constexpr ObisId power_returned_l3::id;
constexpr const std::string_view power_returned_l3::name;

constexpr ObisId gas_device_type::id;
constexpr const std::string_view gas_device_type::name;

constexpr ObisId gas_equipment_id::id;
constexpr const std::string_view gas_equipment_id::name;

constexpr ObisId gas_valve_position::id;
constexpr const std::string_view gas_valve_position::name;

constexpr ObisId gas_delivered::id;
constexpr const std::string_view gas_delivered::name;

constexpr ObisId thermal_device_type::id;
constexpr const std::string_view thermal_device_type::name;

constexpr ObisId thermal_equipment_id::id;
constexpr const std::string_view thermal_equipment_id::name;

constexpr ObisId thermal_valve_position::id;
constexpr const std::string_view thermal_valve_position::name;

constexpr ObisId thermal_delivered::id;
constexpr const std::string_view thermal_delivered::name;

constexpr ObisId water_device_type::id;
constexpr const std::string_view water_device_type::name;

constexpr ObisId water_equipment_id::id;
constexpr const std::string_view water_equipment_id::name;

constexpr ObisId water_valve_position::id;
constexpr const std::string_view water_valve_position::name;

constexpr ObisId water_delivered::id;
constexpr const std::string_view water_delivered::name;

constexpr ObisId slave_device_type::id;
constexpr const std::string_view slave_device_type::name;

constexpr ObisId slave_equipment_id::id;
constexpr const std::string_view slave_equipment_id::name;

constexpr ObisId slave_valve_position::id;
constexpr const std::string_view slave_valve_position::name;

constexpr ObisId slave_delivered::id;
constexpr const std::string_view slave_delivered::name;

