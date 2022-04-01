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
    for (auto it = aircrafts.begin(); it != aircrafts.end(); )
    {
        if (!(*it)->move()) {
            it = aircrafts.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return true;
}