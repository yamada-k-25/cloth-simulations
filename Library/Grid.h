#include "AsuraVector.h"

// Grid is need to create cloth.
struct Grid 
{
    double mass;
    Asura::vector3d position;
    Asura::vector3d velocity;
    Asura::vector3d force;

    // Initialize
    Grid() 
    {
        position.Zero();
        velocity.Zero();
        force.Zero();
    }
};