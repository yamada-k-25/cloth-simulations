#include<stdio.h>
#include<iostream> 
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include "../Library/GridSurface.h"

/*
以下を参考にさせていただいてます.
OpenGL - サンプルコード
(http://www.slis.tsukuba.ac.jp/~fujisawa.makoto.fu/cgi-bin/wiki/index.php?OpenGL%20-%20%A5%B5%A5%F3%A5%D7%A5%EB%A5%B3%A1%BC%A5%C9)
*/

struct Grid {
    int x;
    int y;
    int z;
};

struct Grids {
    Grid grids;
};

static int DrawGroundGrid(int d, double x, double y, double h)
{
    glPushMatrix();   
        glDisable(GL_LIGHTING);
    
        glColor3f(0,0.5,0);
        // TODO: 
        // ラインでの描画も残して置きたいので, 
        // 別としてPOLYGONで描画するようにする
        glLineWidth(6.0);
        glBegin(GL_LINE_LOOP);
        glVertex3d(-x,  y, h);
        glVertex3d( x,  y, h);  
        glVertex3d( x, -y, h);
        glVertex3d(-x, -y, h);
        glEnd();
        glLineWidth(3.0);
        
        // x方向
        // TODO: ここら辺の点の生成をコンストラクタで行う
        // TODO: 構造体などで切り分ける
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

    glFlush();
 
    return 0;
}


void idle(void)
{
 
}

void myKbd(unsigned char key, int x, int y) {

}

void display(void) { 
    glClear(GL_COLOR_BUFFER_BIT);
    // DrawGroundGrid(10, 1, 1, 1);
    GridSurface gridSurface(0.5, 0.5, 1, 10);
    // printf("%d, %d, %d, %d", gridSurface.GetX(), gridSurface.GetY(), gridSurface.GetH(), gridSurface.DivideNum());
    gridSurface.Draw();

    glFlush();
}

void myInit(char *progname) {
    int width = 500, height = 500;
    float aspect = (float) width / (float) height;

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode( GLUT_RGBA); //ダブルバッファの宣言
    glutCreateWindow(progname);

    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutDisplayFunc(display);
    // イベントがない場合には以下のidleが実行される
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}