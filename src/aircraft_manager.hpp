//
// Created by Thomas on 11/03/2022.
//

#pragma once

#include "aircraft.hpp"
#include "aircraft_factory.hpp"

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

    void create_aircraft(Tower& tower);
    void init();
    int get_required_fuel() const;

    bool move();
    void displayCountAircraftOnAirline(int i);
};

