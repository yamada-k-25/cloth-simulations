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
    this->grids = vector<vector<Grid> >(divideNum+1, vector<Grid>(divideNum+1));
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
                for(int i = 0; i < d; ++i) {
                    for(int j = 0; j < d; ++j) {
                        glColor3f(0,0.5,0);
                        glBegin(GL_LINES);
                            glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                            glVertex3f(grids[i+1][j].position.x , grids[i+1][j].position.y, grids[i+1][j].position.z);
                        glEnd();
                        glBegin(GL_LINES);
                            glVertex3f(grids[i+1][j].position.x , grids[i+1][j].position.y, grids[i+1][j].position.z);
                            glVertex3f(grids[i+1][j+1].position.x , grids[i+1][j+1].position.y, grids[i+1][j+1].position.z);
                        glEnd();
                        glBegin(GL_LINES);
                            glVertex3f(grids[i+1][j+1].position.x , grids[i+1][j+1].position.y, grids[i+1][j+1].position.z);
                            glVertex3f(grids[i][j+1].position.x , grids[i][j+1].position.y, grids[i][j+1].position.z);
                        glEnd();
                        glBegin(GL_LINES);
                            glVertex3f(grids[i][j+1].position.x , grids[i][j+1].position.y, grids[i][j+1].position.z);
                            glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                        glEnd();
                    }
                }
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