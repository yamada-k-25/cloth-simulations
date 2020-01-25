/*
アニメーションするサンプルプログラム

+ idle()
+ ダブルバッファの実装が必要になる
*/

#include<stdio.h>
#include<iostream> 
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>

static int DrawGroundGrid(int d, double x, double y, double h)
{
 
    glPushMatrix();
    
    glDisable(GL_LIGHTING);
 
    glColor3f(1,0,0);
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
 
    return 0;
}

void display(void) { 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawGroundGrid(10, 100, 100, 100);
    glutSolidTeapot(0.5);
}

void idle(void)
{
 
}

void myKbd(unsigned char key, int x, int y) {

}

void myInit(char *progname) {
    int width = 500, height = 500;
    float aspect = (float) width / (float) height;

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //ダブルバッファの宣言
    glutCreateWindow(progname);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutDisplayFunc(display);
    // イベントがない場合には以下のidleが実行される
    // glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}