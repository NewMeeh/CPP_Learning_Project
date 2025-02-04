#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");

    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { aircraftManager.create_aircraft(airport->get_tower()); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('a', []() { GL::faster(); });
    GL::keystrokes.emplace('z', []() { GL::slower(); });
    GL::keystrokes.emplace('p', []() { GL::pause(); });
    GL::keystrokes.emplace(
        'm', [this]()
        { std::cout << aircraftManager.get_nb_crash() << " crashes since the beginning" << std::endl; });
    for (char c = '0'; c < '8'; c++)
    {
        GL::keystrokes.emplace(c, [this, c]() { aircraftManager.displayCountAircraftOnAirline(c - '0'); });
    }
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [c, f] : GL::keystrokes)
    {
        std::cout << c << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    assert(airport == nullptr);
    airport =
        new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                      new img::Image { one_lane_airport_sprite_path.get_full_path() }, aircraftManager };

    GL::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
    GL::move_queue.emplace(&aircraftManager);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();

    assert(airport);

    aircraftManager.init();
    GL::loop();
}
