#ifndef INCLUDE_GRID
#define INCLUDE_GRID


#include "AsuraVector.h"
#include "Object.h"

// Grid is need to create cloth.
struct Grid: Object
{
    
    // Initialize
    Grid() 
    {
        position.Zero();
        velocity.Zero();
        force.Zero();
        mass = 0.0f;
    }
    // Override Methods
    void Initialize() {};
    void Update() {};
    void Draw() {};
};

#endif