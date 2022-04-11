//
// Created by Thomas on 11/03/2022.
//

#include "aircraft_manager.hpp"


void AircraftManager::create_aircraft(Airport *airport) {
    aircrafts.emplace_back(aircraftFactory.create_random_aircraft(airport));
}

void AircraftManager::init() {
    aircraftFactory.init_aircraft_types();
}

bool AircraftManager::move()
{
    aircrafts.erase(
        std::remove_if(
            aircrafts.begin(),
            aircrafts.end(),
            [](const auto &it){return !it->move();}),
        aircrafts.end());

    return true;
}

void AircraftManager::displayCountAircraftOnAirline(int i) {
    auto airline = aircraftFactory.airlines[i];
    std::cout << std::count_if(aircrafts.begin(),
                         aircrafts.end(),
                         [airline](std::unique_ptr<Aircraft>& a){auto name = a->get_flight_num();
                                         return name.find(airline) != std::string::npos;}) << " aircrafts on airline " << airline << std::endl;
}