#include "aircraft_manager.hpp"

void AircraftManager::create_aircraft(Tower& tower)
{
    assert(initialized);
    aircrafts.emplace_back(aircraftFactory.create_random_aircraft(tower));
}

void AircraftManager::init()
{
    assert((initialized = !initialized));
    aircraftFactory.init_aircraft_types();
}

bool AircraftManager::move()
{
    assert(initialized);
    //   for(auto &o : aircrafts) {
    //       std::cout << o->get_flight_num() << " - " << (o->has_terminal() ? " Reserved " : " NotReserved ")
    //       << "/ Fuel: " <<  o->fuel_left() << std::endl;
    //   }

    std::sort(aircrafts.begin(), aircrafts.end(),
              [](std::unique_ptr<Aircraft>& a1, std::unique_ptr<Aircraft>& a2)
              {
                  if (a1->has_terminal())
                  {
                      if (a2->has_terminal())
                      {
                          return a1->fuel_left() < a2->fuel_left();
                      }
                      return true;
                  }
                  else
                  {
                      if (a2->has_terminal())
                      {
                          return false;
                      }
                      else
                      {
                          return a1->fuel_left() < a2->fuel_left();
                      }
                  }
              });

    /*
    std::cout << "----------------------------------------------------------\n" << std::endl;
    for(auto &o : aircrafts) {
        std::cout << o->get_flight_num() << " - " << (o->has_terminal() ? " Reserved " : " NotReserved ") <<
    "/ Fuel: " <<  o->fuel_left() << std::endl;
    }
     */

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [this](const auto& it)
                                   {
                                       try
                                       {
                                           return !it->move();
                                       } catch (const AircraftCrash& aircraftCrash)
                                       {
                                           nb_crash++;
                                           std::cerr << aircraftCrash.what() << std::endl;
                                           return true;
                                       }
                                   }),
                    aircrafts.end());

    return true;
}

int AircraftManager::get_required_fuel() const
{
    assert(initialized);
    return std::accumulate(aircrafts.begin(), aircrafts.end(), 0,
                           [](int acc, const std::unique_ptr<Aircraft>& aircraft)
                           {
                               return acc + (aircraft->is_low_on_fuel() && aircraft->is_at_terminal
                                                 ? 3000 - aircraft->fuel_left()
                                                 : 0);
                           });
}

void AircraftManager::displayCountAircraftOnAirline(const int i) const
{
    assert(initialized);

    auto airline = aircraftFactory.airlines[i];

    std::cout << std::count_if(aircrafts.begin(), aircrafts.end(),
                               [airline](const std::unique_ptr<Aircraft>& a)
                               {
                                   auto name = a->get_flight_num();
                                   return name.find(airline) != std::string::npos;
                               })
              << " aircrafts on airline " << airline << std::endl;
}
