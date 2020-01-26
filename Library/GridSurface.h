#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

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
    void Draw();
    void Update();
private:
    float x;
    float y;
    float h;
    int d;
};