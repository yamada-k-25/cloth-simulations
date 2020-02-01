#include "GridSurface.h"
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <vector>
#include "AsuraVector.h"
using namespace std;

GridSurface::GridSurface(float originX, float originY, float originH, int divideNum) {
    this->x = originX;
    this->y = originY;
    this->h = originH;
    this->d = divideNum;
    // TODO: 多分ここら辺が間違っているので, 修正する
    this->grids = vector<vector<Grid> >(divideNum, vector<Grid>(divideNum));
    // this->grids = vector<vector<Grid> >(100, vector<Grid>(100));
    
}

void GridSurface::Initialize() {
    // initialize grids
        // x方向
        float x0, x1, y0, y1;
        float deltaX, deltaY;
        // x0, x1, y0, y1がそれぞれ何を表しているのか考える
        x0 = -x; x1 = -x;
        y0 = -y; y1 = y;
        // Gridの点の位置座標の間隔
        deltaX = (2*x)/d;
        deltaY = (2*y)/d;  

        for(int i = 0; i < d; ++i){
            for(int j = 0; j < d; ++j) {
                // x0 = x0 + deltaX;
                // y0 = y0 + deltaY;
                grids[j][i].position.x = x0 + deltaX*(i+1);
                grids[j][i].position.y = y0 + deltaY*(j+1);
            }
        }
    
        // y方向
        x0 = -x; x1 = x;
        deltaY = (2*y)/d;
    
        for(int i = 0; i < d; ++i){
            y0 = y0 + deltaY;
        }
}

void GridSurface::Draw(int drawingType) {
    glPushMatrix();   
        glDisable(GL_LIGHTING);
    
        glColor3f(0,0.5,0);
        glLineWidth(6.0);
        glBegin(GL_LINE_LOOP);
        glVertex3d(-x,  y, h);
        glVertex3d( x,  y, h);  
        glVertex3d( x, -y, h);
        glVertex3d(-x, -y, h);
        glEnd();
        glLineWidth(3.0);

        switch(drawingType) {
            case 1:
            for(int i = 0; i < d; ++i) {
                for(int j = 0; j < d; ++j) {
                glBegin(GL_POINTS);
                    glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                glEnd();
                }
            }
            break;

            case 2:

            break;

            case 3:

            break;
        }
        
        // x方向
        float x0, x1, y0, y1;
        float deltaX, deltaY;
    
        x0 = -x; x1 = -x;
        y0 = -y; y1 = y;
        deltaX = (2*x)/d;
    
        // for(int i = 0; i < d; ++i){
        //     x0 = x0 + deltaX;
        //     glBegin(GL_LINES);
        //     glVertex3f(x0, y0, h);
        //     glVertex3f(x0, y1, h);
        //     glEnd();
        // }
    
        // y方向
        x0 = -x; x1 = x;
        deltaY = (2*y)/d;
    
        // for(int i = 0; i < d; ++i){
        //     y0 = y0 + deltaY;
        //     glBegin(GL_LINES);
        //     glVertex3f(x0, y0, h);
        //     glVertex3f(x1, y0, h);
        //     glEnd();
        // }
    
        glLineWidth(1.0);
    glPopMatrix();
}

/// 毎フレームごとに
void GridSurface::Update() {

}

// protected methods
void GridSurface::EularMethod() {

}

void GridSurface::UpdateForce() {

}