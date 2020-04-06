#include "GridSurface.h"
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <vector>
#include "Constants.h"
#include "AsuraVector.h"
#include <cmath>

enum ImageType {
    // 8bitで詰める
    GRAY8 = 0,
    //. 8bitで詰める
    RGB8 = 1,
};


// TODO: この名前が正しいのかはわからない
struct ImageData {
    // TODO: 多分これはRBGを想定しておらず、GrayScaleを想定している形になっている
    ImageType imageType;
    unsigned char* data;
    int height;
    int width;
    
};

struct SimulationParameters {
    std::vector<Asura::vector3f> simForces;
};

struct ClothParameters {
    float originX;
    float originY;
    float originH;
    int divideNum;
    float rest;
    StringType stringType;
};

