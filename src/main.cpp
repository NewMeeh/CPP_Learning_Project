#include "tower_sim.hpp"
Point<std::time_t, 2> test_generic_points() {
    Point<std::time_t, 2> p1  {std::time(nullptr),std::time(nullptr)};
    Point<std::time_t, 2> p2  {std::time(nullptr),std::time(nullptr)};
    auto p3 = p1 + p2;
    p1 += p2;
    p1 *= 3; // ou 3.f, ou 3.0 en fonction du type de Point
    return p3;
}

int main(int argc, char** argv)
{


    std::cout << test_generic_points().y() << std::endl;

    TowerSimulation simulation { argc, argv };
    simulation.launch();


    return 0;
}