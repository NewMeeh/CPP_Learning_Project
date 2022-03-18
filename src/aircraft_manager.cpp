//
// Created by Thomas on 11/03/2022.
//

#include "aircraft_manager.hpp"


void AircraftManager::register_aircraft(std::unique_ptr<Aircraft> aircraft) {
    aircrafts.emplace_back(std::move(aircraft));
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