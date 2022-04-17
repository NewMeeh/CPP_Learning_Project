#pragma once

#include "aircraft.hpp"
#include "aircraft_types.hpp"

#include <string>

class Airport;
class AircraftFactory
{
private:
    std::unordered_set<std::string> usedNames;
    static constexpr size_t NUM_AIRCRAFT_TYPES = 3;
    static constexpr int min_fuel = 150;
    static constexpr int max_fuel = 3000;

    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};

    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type, Tower& tower);

public:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    // note: textures have to be initialized after initializing glut, so we'll need
    // our own init here
    inline void init_aircraft_types()
    {
        assert(std::all_of(aircraft_types, aircraft_types + NUM_AIRCRAFT_TYPES,
                           [](AircraftType* aircraftType) { return aircraftType == nullptr; }));
        aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
        aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
        aircraft_types[2] = new AircraftType { .02f, .10f, .02f, MediaPath { "concorde_af.png" } };
    }

    std::unique_ptr<Aircraft> create_random_aircraft(Tower& tower);
};
