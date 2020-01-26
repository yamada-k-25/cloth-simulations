#include "GridSurface.h"
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

GridSurface::GridSurface(float originX, float originY, float originH, int divideNum) {
    this->x = originX;
    this->y = originY;
    this->h = originH;
    this->d = divideNum;
}

void GridSurface::Draw() {
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
        
        // x方向
        float x0, x1, y0, y1;
        float deltaX, deltaY;
    
        x0 = -x; x1 = -x;
        y0 = -y; y1 = y;
        deltaX = (2*x)/d;
    
        for(int i = 0; i < d; ++i){
            x0 = x0 + deltaX;
            glBegin(GL_LINES);
            glVertex3f(x0, y0, h);
            glVertex3f(x0, y1, h);
            glEnd();
        }
    
        // y方向
        x0 = -x; x1 = x;
        deltaY = (2*y)/d;
    
        for(int i = 0; i < d; ++i){
            y0 = y0 + deltaY;
            glBegin(GL_LINES);
            glVertex3f(x0, y0, h);
            glVertex3f(x1, y0, h);
            glEnd();
        }
    
        glLineWidth(1.0);
    glPopMatrix();
}

void GridSurface::Update() {

}