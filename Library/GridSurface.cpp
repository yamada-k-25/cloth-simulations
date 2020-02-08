#include "GridSurface.h"
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <vector>
#include "Constants.h"
#include "AsuraVector.h"
using namespace std;

GridSurface::GridSurface(float originX, float originY, float originH, int divideNum) {
    this->x = originX;
    this->y = originY;
    this->h = originH;
    this->d = divideNum;
    // Gridの点の位置座標の間隔
    this->deltaX = (2*originX)/divideNum;
    this->deltaY = (2*originY)/divideNum;  
    this->grids = vector<vector<Grid> >(divideNum+1, vector<Grid>(divideNum+1));
}

void GridSurface::Initialize() {
    // initialize grids
        // x方向
        float x0, x1, y0, y1;
        // x0, x1, y0, y1がそれぞれ何を表しているのか考える
        x0 = -x; x1 = -x;
        y0 = -y; y1 = y;

        for(int i = 0; i <= d; ++i){
            for(int j = 0; j <= d; ++j) {
                // x0 = x0 + deltaX;
                // y0 = y0 + deltaY;
                grids[j][i].position.x = x0 + deltaX*i;
                grids[j][i].position.y = y0 + deltaY*j;
                // TODO: ここは、もっと３次元的な位置で初期化できるようにする必要がある
                grids[j][i].position.z = this->h;
                grids[i][j].velocity = Asura::vector3d(0.0f, 0.0f, 0.0f);
                grids[i][j].force = Asura::vector3d(0.0f, 0.0f, 0.0f);

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
    // WindowForce
    // TestUpdate();
    UpdateExternalForces();
}

// ============ Protected Methods ============

void GridSurface::EularMethod() {

}

void GridSurface::TestUpdate() {
    // X方向に点が伸びるように実装してみる
    float deltaX = this->deltaX/30;
    for(int i=0; i<=d; ++i) {
        for(int j=0; j<=d; ++j) {
            grids[i][j].position.x += deltaX;
        }
    }
}

void GridSurface::UpdateExternalForces() {
    // 各頂点を外力によって位置を更新する
    for(int i = 0; i <= d; ++i) {
        for(int j = 0; j <= d; ++j) {
            this->grids[i][j].velocity.y += GRAVITY;
            // TODO: 実際にはここの行はdeltaTimeを使う必要がありそう
            // TODO: gires.forcesをつかって弾性力などを実装する必要がありそう
            this->grids[i][j].position.y -= this->grids[i][j].velocity.y;

        }
    }
}

void GridSurface::UpdateInternalForces() {

}

void GridSurface::UpdateCollision() { 

}