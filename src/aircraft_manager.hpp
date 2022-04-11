//
// Created by Thomas on 11/03/2022.
//

#pragma once

#include "aircraft.hpp"
#include "aircraft_factory.hpp"

#include <string>
#include <map>
#include <memory>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts = std::vector<std::unique_ptr<Aircraft>>();
    AircraftFactory aircraftFactory;

public:
    AircraftManager() {
    };
    ~AircraftManager() {};

    void create_aircraft(Airport *airport);
    void init();

    bool move();
    void displayCountAircraftOnAirline(int i);
};

