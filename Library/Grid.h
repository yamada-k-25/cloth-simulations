#ifndef INCLUDE_GRID
#define INCLUDE_GRID


#include "AsuraVector.h"
#include "Object.h"
#include "Constants.h"

// Grid is need to create cloth.
struct Grid: Object
{
    bool isFixed = false;
    // Initialize
    Grid() 
    {
        position.Zero();
        velocity.Zero();
        force.Zero();
        mass = 0.1f;
    }
    // Override Methods
    void Initialize() {};
    void Update() {};
    void Draw() {};

    // バネ定数kと自然長natural_lengthを受け取って弾性運動による更新を行う
    void UpdateBySpring(float k, float natural_length, Grid targetGrid) {
        // 釣り合いが取れている位置
        // float originX = (position.x - targetSphere.position.x);
        force.x = targetGrid.force.x - k * (-natural_length +  position.x - targetGrid.position.x);
        accelaration.x = force.x / mass;
        velocity.x += accelaration.x * dt;
        position.x += velocity.x * dt;
    }
};

#endif