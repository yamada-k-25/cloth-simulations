#include <iostream>
#include "Grid.h"

struct ClothConstraint {
    Grid grid1;
    Grid grid2;
    float rest; // 質点間のバネの自然長
    // 0 -> Stretch 1-> Shear2 -> Bending
    int stringType;  //　TODO: 最終的にはenuにすべきか

    // Initialize
    ClothConstraint() {
        grid1 = Grid();
        grid2 = Grid();
        rest = 0.0;
        stringtype = 0;
    }
};