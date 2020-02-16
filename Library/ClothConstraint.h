#include <iostream>
#include "Grid.h"

enum StringType{
    fixed, // fixedはバネの制約を無視して完全な剛体として振る舞う
    strech,
    shear,
    bending,
    none
};

struct ClothConstraint {
    Grid *grid1;
    Grid *grid2;
    float rest; // 質点間のバネの自然長
    StringType stringType;
    float Ks = 1.0f;

    // Initialize
    ClothConstraint() {
        // TODO: メモリを無駄に消費している？
        Grid grid1 = Grid();
        Grid grid2 = Grid();
        this->grid1 = &grid1;
        this->grid2 = &grid2;
        rest = 0.0;
        stringType = StringType::none;
    }

    // TODO: 参照渡しにしたい
    ClothConstraint(Grid *grid1, Grid *grid2, float rest, float Ks) {
        this->grid1 = grid1;
        this->grid2 = grid2;
        this->rest = rest;
        this->Ks = Ks;
    }
};