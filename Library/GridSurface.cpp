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
    this->grids = vector<vector<Grid> >(divideNum+1, vector<Grid>(divideNum+1));
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

        for(int i = 0; i <= d; ++i){
            for(int j = 0; j <= d; ++j) {
                // x0 = x0 + deltaX;
                // y0 = y0 + deltaY;
                grids[j][i].position.x = x0 + deltaX*i;
                grids[j][i].position.y = y0 + deltaY*j;
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

        // 描画範囲の枠線の描画
        // glColor3f(0,0.5,0);
        // glLineWidth(6.0);
        // glBegin(GL_LINE_LOOP);
        // glVertex3d(-x,  y, h);
        // glVertex3d( x,  y, h);  
        // glVertex3d( x, -y, h);
        // glVertex3d(-x, -y, h);
        // glEnd();
        // glLineWidth(3.0);

        // TODO: ここのdrawingTypeをenumで書き換えたほうが良いかも
        switch(drawingType) {
            case 1: // draw vertexs
            for(int i = 0; i < d; ++i) {
                for(int j = 0; j < d; ++j) {
                glBegin(GL_POINTS);
                    glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                glEnd();
                }
            }
            break;

            case 2: // draw wireframe 
            break;

            case 3: // draw surface
                for(int i = 0; i < d; ++i) {
                    for(int j = 0; j < d; ++j) {
                        glColor3f(0,0.5,0);
                        glBegin(GL_QUADS);
                            glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                            glVertex3f(grids[i+1][j].position.x , grids[i+1][j].position.y, grids[i+1][j].position.z);
                            glVertex3f(grids[i+1][j+1].position.x , grids[i+1][j+1].position.y, grids[i+1][j+1].position.z);
                            glVertex3f(grids[i][j+1].position.x , grids[i][j+1].position.y, grids[i][j+1].position.z);
                        glEnd();
                    }
                }
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