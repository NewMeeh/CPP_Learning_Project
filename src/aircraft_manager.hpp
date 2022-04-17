#pragma once

#include "aircraft.hpp"
#include "aircraft_factory.hpp"

#include <memory>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts = std::vector<std::unique_ptr<Aircraft>>();
    AircraftFactory aircraftFactory;
    int nb_crash     = 0;
    bool initialized = false;

public:
    AircraftManager() {};
    ~AircraftManager() {};

    void create_aircraft(Tower& tower);
    void init();
    int get_required_fuel() const;
    int get_nb_crash() const { return nb_crash; }

    bool move();
    void displayCountAircraftOnAirline(int i) const;
};
