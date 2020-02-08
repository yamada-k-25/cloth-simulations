#include <iostream>
#include "Grid.h"

enum stringType{
    fixed, // fixedはバネの制約を無視して完全な剛体として振る舞う
    strech,
    shear,
    bending,
    none
};

struct ClothConstraint {
    Grid grid1;
    Grid grid2;
    float rest; // 質点間のバネの自然長
    stringType stringType;

    // Initialize
    ClothConstraint() {
        grid1 = Grid();
        grid2 = Grid();
        rest = 0.0;
        stringType = stringType::none;
    }
};