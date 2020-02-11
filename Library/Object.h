#ifndef INCLUDE_OBJECT
#define  INCLUDE_OBJECT

#include "AsuraVector.h"

struct Object{
    Asura::vector3d position;
    Asura::vector3d velocity;
    Asura::vector3d accelaration;
    Asura::vector3d force;
    float mass;

    Object() {
        position.Zero();
        velocity.Zero();
        accelaration.Zero();
        force.Zero();
        mass = 0.0f;
    }

    // 関数ポインタで関数の内部処理を外側からセットするようにする
    // TODO: 外側からどんな形のオブジェクトなのかをセットできるようにする
    virtual void Update() {};
    virtual void Draw() {};
    virtual void Initialize() {};
    virtual void EulerMethod() {};
};

#endif