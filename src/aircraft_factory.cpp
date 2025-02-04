#include "aircraft_factory.hpp"

std::unique_ptr<Aircraft> AircraftFactory::create_aircraft(const AircraftType& type, Tower& tower)
{
    assert(std::all_of(aircraft_types, aircraft_types + NUM_AIRCRAFT_TYPES,
                       [](AircraftType* aircraftType) { return aircraftType != nullptr; }));
    std::string flight_number;
    do
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }
    while (usedNames.find(flight_number) != usedNames.end());
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();
    usedNames.emplace(flight_number);

    return std::make_unique<Aircraft>(type, flight_number, start, direction, tower, rand() % (max_fuel - min_fuel) + min_fuel);
}

std::unique_ptr<Aircraft> AircraftFactory::create_random_aircraft(Tower& tower)
{
    assert(std::all_of(aircraft_types, aircraft_types + NUM_AIRCRAFT_TYPES,
                       [](AircraftType* aircraftType) { return aircraftType != nullptr; }));
    return create_aircraft(*(aircraft_types[rand() % 3]), tower);
}