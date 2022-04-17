#include "tower.hpp"

#include "airport.hpp"
#include "terminal.hpp"

#include <cassert>

WaypointQueue Tower::get_circle() const
{
    return { { Point3D { -1.5f, -1.5f, .5f }, wp_air },
             { Point3D { 1.5f, -1.5f, .5f }, wp_air },
             { Point3D { 1.5f, 1.5f, .5f }, wp_air },
             { Point3D { -1.5f, 1.5f, .5f }, wp_air } };
}

WaypointQueue Tower::reserve_terminal(Aircraft& aircraft)
{
    const auto vp = airport.reserve_terminal(aircraft);
    if (!vp.first.empty())
    {
        reserved_terminals.insert(std::pair<const Aircraft*, size_t>(&aircraft, vp.second));
        return vp.first;
    }
    else
    {
        return {};
    }
}

WaypointQueue Tower::get_instructions(Aircraft& aircraft)
{
    if (!aircraft.is_at_terminal)
    {
        // if the aircraft is far, then just guide it to the airport vicinity
        if (aircraft.distance_to(airport.pos) < 5)
        {
            return get_circle();
        }
        else
        {
            return {};
        }
    }
    else
    {
        // get a path for the craft to start
        const auto terminal_num = reserved_terminals[&aircraft];
        Terminal& terminal      = airport.get_terminal(terminal_num);
        if (!terminal.is_servicing())
        {
            terminal.finish_service();
            reserved_terminals.erase(&aircraft);
            aircraft.is_at_terminal = false;
            return airport.start_path(terminal_num);
        }
        else
        {
            return {};
        }
    }
}

void Tower::cancel_reservation(const Aircraft* aircraft)
{
    assert(aircraft);
    assert(!reserved_terminals.empty());
    assert(reserved_terminals.find(aircraft) != reserved_terminals.end());

    auto o = reserved_terminals[aircraft];
    airport.get_terminal(o).unassign_craft();
    reserved_terminals.erase(aircraft);

    assert(reserved_terminals.find(aircraft) == reserved_terminals.end());
}

void Tower::arrived_at_terminal(const Aircraft& aircraft)
{
    airport.get_terminal(reserved_terminals[&aircraft]).start_service(aircraft);
}
