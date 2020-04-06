#ifndef INCLUDE_GRIDSURFACE
#define INCLUDE_GRIDSURFACE 


#include <vector>
#include <iostream>
#include "AsuraVector.h"
#include "ClothConstraint.h"

typedef std::vector<std::vector<Grid> > Grids;
typedef std::vector<ClothConstraint> ClothConstraints;

class GridSurface {
private: // このクラス内でのみ参照できる
    float x; // origin position x 
    float y; // origin position y
    float h; // origin positoin h
    int d; // the number of division
    float Ks = 0.1f; // Spring Constant
    float rest;
    StringType stringType;
    float isFixed = false; // whether the grid is fixed
    float deltaX; // interval of division x
    float deltaY; // interval of division y
    float counter = 0;

    float red;
    float green;
    float blue;
    float alpha;
    // Texture Property
    string filePath="";
    int texNum = 1;

    bool isColor = false;

    Grids grids; // Gridを２次元配列的な感じで表現する
    Grids preGrids;
    Grids nextGrids;
    ClothConstraints constraints; // definite constraints between point to point.

public:
    GridSurface(float originX, float originY, float originH, int divideNum, float width, float height, float rest, StringType stringType);
    // TODO: ここで引数なしのコンストラクタを許すとどんな弊害が起きるのかわからん...
    GridSurface();
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

    bool IsFixed() {
        return this->isFixed;
    }

    void SetGrid(int h, int w, Asura::vector3d position) {
        grids[h][w].position = position;
    }


    void SetGridIsFixed(int h, int w, bool isFixed) {
        grids[h][w].isFixed = isFixed;
    }

    // range of 0, 255
    void SetColor4f(float red, float green, float blue, float alpha) {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->alpha = alpha;
        this->isColor = true;
    }

    void SetTexture(string filePath, int texNum){
        this->filePath = filePath;
        this->texNum = texNum;
    }

    // TODO: 実はこれを公開関数として定義するのは間違っている？
    // ======= Force Methods ========
    /// 与えられた点に対して力を一定の方向に加える
    void  PullGridSurface(Asura::vector3d force, int col, int row);

    void Draw(int drawingType);
    void Update();
    void Initialize();
    void SetAllGridStringType(StringType stringType);
    void UpdateClothConstraints();


protected: // 継承クラスからの参照を許可する
    // Initializer
    void InitializeGrids();
    void InitializeClothConstraints(float rest);
    void InitTexture();

    void EularMethod();
    void TestUpdate(); // Animationができるか確認するために, 点を動かすをx軸方向に動かす
    void UpdateExternalForces(); // gravitiyや風などの外力による質点の位置更新
    void UpdateInternalForces(); // 内部のバネによる位置の制約による修正
    void UpdateCollision(); // 衝突判定による位置の修正

    // 布の物理特性によって質点のプロパティを更新する
    void UpdateSpringForces();

    void UpdateShear();
    void UpdateStreach();
    void UpdateBending();
    void UpdateGravityForce();
    
    // void UpdateWind();

};

#endif