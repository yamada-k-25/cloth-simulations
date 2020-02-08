#include <vector>
#include <iostream>
#include "AsuraVector.h"
#include "Grid.h"

// Grid is need to create cloth.
// struct Grid 
// {
//     double mass;
//     Asura::vector3d position;
//     Asura::vector3d velocity;
//     Asura::vector3d force;

//     // Initialize
//     Grid() 
//     {
//         position.Zero();
//         velocity.Zero();
//         force.Zero();
//     }
// };

typedef std::vector<std::vector<Grid> > Grids;

class GridSurface {
public:
    GridSurface(float originX, float originY, float originH, int divideNum);
    int DivideNum() {
        return this->d;
    }
    float GetX() {
        return this->x;
    }
    float GetY() {
        return this->y;
    }
    float GetH() {
        return this->h;
    }
    void Draw(int drawingType);
    void Update();
    void Initialize();
private: // このクラス内でのみ参照できる
    float x; // origin position x 
    float y; // origin position y
    float h; // origin positoin h
    int d; // the number of division
    float deltaX; // interval of division x
    float deltaY; // interval of division y
    Grids grids; // Gridを２次元配列的な感じで表現する

protected: // 継承クラスからの参照を許可する
    void EularMethod();
    void TestUpdate(); // Animationができるか確認するために, 点を動かすをx軸方向に動かす
    void UpdateExternalForces(); // gravitiyや風などの外力による質点の位置更新
    void UpdateInternalForces(); // 内部のバネによる位置の制約による修正
    void UpdateCollision(); // 衝突判定による位置の修正
};