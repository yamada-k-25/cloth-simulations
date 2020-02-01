#include <vector>
#include <iostream>
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
    float x;
    float y;
    float h;
    int d;
    Grids grids; // Gridを２次元配列的な感じで表現する
protected: // 継承クラスからの参照を許可する
    void UpdateForce();
    void EularMethod();
};