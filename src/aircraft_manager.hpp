//
// Created by Thomas on 11/03/2022.
//

#pragma once

#include "aircraft.hpp"

#include <string>
#include <map>
#include <memory>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts = std::vector<std::unique_ptr<Aircraft>>();
public:
    AircraftManager() {};
    ~AircraftManager() {};

    void register_aircraft(std::unique_ptr<Aircraft> aircraft);

    bool move();
};

