/*
  Based on: https://github.com/wmbusmeters/wmbusmeters/blob/master/src/driver_hydrus.cc
  Copyright (C) 2017-2023 Fredrik Öhrström (gpl-3.0-or-later)
*/

#pragma once

#include "driver.h"

#include <vector>
#include <string>

struct Hydrus: Driver
{
  Hydrus(std::string key = "") : Driver(std::string("hydrus"), key) {};

  virtual esphome::optional<std::map<std::string, double>> get_values(
      std::vector<unsigned char> &telegram) override {

    std::map<std::string, double> ret_val{};

    // Total water volume from 0C14, returned in m3.
    add_to_map(ret_val, "total_water_m3", this->get_0C14(telegram));

    // Current volume flow from 0B3B, returned in l/h.
    add_to_map(ret_val, "volume_flow_lh", this->get_0B3B(telegram));

    // Flow water temperature from 0A5A, returned in degrees C.
    add_to_map(ret_val, "flow_temperature_c", this->get_0A5A(telegram));

    if (ret_val.size() > 0) {
      return ret_val;
    }
    else {
      return {};
    }
  };

private:
};
