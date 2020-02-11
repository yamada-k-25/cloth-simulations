#ifndef INCLUDE_SPHERE
#define INCLUDE_SPHERE

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "Object.h"
#include "AsuraVector.h"
#include "Constants.h"
#include <math.h>

struct Sphere: Object {
    float rad;

    Sphere(float rad, float mass, Asura::vector3d position, Asura::vector3d velocity, Asura::vector3d accelaration) { 
        this->position = position;
        this->velocity = velocity;
        this->accelaration = accelaration;
        this->mass = mass;
        this->rad = rad;
    }
    void Initialize() {};
    void Update() {};
    void Draw() {
        glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            glRotated(90, 1.0, 0.0, 0.0);
            glutSolidSphere(rad, 20, 10);
        glPopMatrix();
    };
    void EulerMethod() {
        // force.x = force.x;
        // accelaration = force.x / mass;
        // velocity.x += accelaration.x * dt;
        // position.x += velocity.x * dt;
    };

    // バネ定数kと自然長natural_lengthを受け取って弾性運動による更新を行う
    void UpdateBySpring(float k, float natural_length, Sphere targetSphere) {
        // 釣り合いが取れている位置
        // float originX = (position.x - targetSphere.position.x);
        force.x = targetSphere.force.x - k * (-natural_length +  position.x - targetSphere.position.x);
        accelaration.x = force.x / mass;
        velocity.x += accelaration.x * dt;
        position.x += velocity.x * dt;
    }
};

#endif