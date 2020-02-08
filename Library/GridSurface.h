#include <vector>
#include <iostream>
#include "AsuraVector.h"
#include "ClothConstraint.h"

typedef std::vector<std::vector<Grid> > Grids;
typedef std::vector<ClothConstraint> ClothConstraints;

class GridSurface {
public:
    GridSurface(float originX, float originY, float originH, int divideNum, StringType stringType);
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
    void SetAllGridStringType(StringType stringType);

private: // このクラス内でのみ参照できる
    float x; // origin position x 
    float y; // origin position y
    float h; // origin positoin h
    int d; // the number of division
    StringType stringType;
    float deltaX; // interval of division x
    float deltaY; // interval of division y
    Grids grids; // Gridを２次元配列的な感じで表現する
    ClothConstraints constraints; // definite constraints between point to point.

protected: // 継承クラスからの参照を許可する
    // Initializer
    void InitializeGrids();
    void InitializeClothConstraints();

    void EularMethod();
    void TestUpdate(); // Animationができるか確認するために, 点を動かすをx軸方向に動かす
    void UpdateExternalForces(); // gravitiyや風などの外力による質点の位置更新
    void UpdateInternalForces(); // 内部のバネによる位置の制約による修正
    void UpdateCollision(); // 衝突判定による位置の修正
};