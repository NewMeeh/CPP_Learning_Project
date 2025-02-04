#pragma once

#include "GL/displayable.hpp"
#include "GL/dynamic_object.hpp"
#include "aircraft_types.hpp"
#include "geometry.hpp"
#include "tower.hpp"
#include "waypoint.hpp"

#include <X11/Xlib.h>
#include <string>
#include <string_view>

class Aircraft : public GL::Displayable, public GL::DynamicObject
{
private:
    const AircraftType& type;
    const std::string flight_number;
    Point3D pos, speed; // note: the speed should always be normalized to length 'speed'
    WaypointQueue waypoints = {};
    Tower& control;
    bool landing_gear_deployed = false; // is the landing gear deployed?
    bool got_served = false;
    int fuel;
    bool is_on_ground() const { return pos.z() < DISTANCE_THRESHOLD; }

    // turn the aircraft to arrive at the next waypoint
    // try to facilitate reaching the waypoint after the next by facing the
    // right way to this end, we try to face the point Z on the line spanned by
    // the next two waypoints such that Z's distance to the next waypoint is
    // half our distance so: |w1 - pos| = d and [w1 - w2].normalize() = W and Z
    // = w1 + W*d/2
    void turn_to_waypoint();
    void turn(Point3D direction);

    // select the correct tile in the plane texture (series of 8 sprites facing
    // [North, NW, W, SW, S, SE, E, NE])
    unsigned int get_speed_octant() const;
    // when we arrive at a terminal, signal the tower
    void arrive_at_terminal();
    // deploy and retract landing gear depending on next waypoints
    void operate_landing_gear();
    float max_speed() const { return is_on_ground() ? type.max_ground_speed : type.max_air_speed; }

    Aircraft(const Aircraft&) = delete;
    Aircraft& operator=(const Aircraft&) = delete;

    template <bool front> void add_waypoint(const Waypoint& wp)
    {
        if constexpr (front)
        {
            waypoints.push_front(wp);
        }
        else
        {
            waypoints.push_back(wp);
        }
    }

public:
    Aircraft(const AircraftType& type_, const std::string_view& flight_number_, const Point3D& pos_,
             const Point3D& speed_, Tower& control_, const int fuel_) :
        GL::Displayable { pos_.x() + pos_.y() },
        type { type_ },
        flight_number { flight_number_ },
        pos { pos_ },
        speed { speed_ },
        control { control_ },
        fuel { fuel_ }
    {
        assert(!flight_number_.empty());
        speed.cap_length(max_speed());
    }
    ~Aircraft()
    {
        if (has_terminal()) control.cancel_reservation(this);

    }

    bool is_at_terminal = false;

    const std::string get_flight_num() const { return flight_number; }
    float distance_to(const Point3D& p) const { return pos.distance_to(p); }
    bool has_terminal() const;
    bool is_circling() const;
    int fuel_left() const;
    bool is_low_on_fuel() const;
    void refill(int& fuel_stock);

    void display() const override;
    bool move() override;

    friend class Tower;
};
