#include<stdio.h>
#include<iostream> 
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include "../Library/GridSurface.h"

const int divideNum = 40;
const float originX = 0.5;
const float originY = -0.5;
const float originZ = -1.0;
const float originX2 = -0.5;
const float originY2 = -0.5;
const float originZ2 = -0.2;
const float rest = (2*originX) / divideNum;

using namespace Asura;

// 均等の位置になるように位置を初期化する
GridSurface gridSurface(originX, originY, originZ, divideNum, rest, StringType::fixed);
// 均等の位置になるように位置を初期化する
GridSurface gridSurface2(originX2, originY2, originZ2, divideNum, rest, StringType::fixed);
/*
以下を参考にさせていただいてます.
OpenGL - サンプルコード
(http://www.slis.tsukuba.ac.jp/~fujisawa.makoto.fu/cgi-bin/wiki/index.php?OpenGL%20-%20%A5%B5%A5%F3%A5%D7%A5%EB%A5%B3%A1%BC%A5%C9)
*/
void idle(void)
{
    gridSurface.Update();
    gridSurface2.Update();
    glutPostRedisplay();
}

void myKbd(unsigned char key, int x, int y) {

}

void display(void) { 
    glClear(GL_COLOR_BUFFER_BIT);
    // DrawGroundGrid(10, 1, 1, D1);
    // printf("%d, %d, %d, %d", gridSurface.GetX(), gridSurface.GetY(), gridSurface.GetH(), gridSurface.DivideNum());
    gridSurface.Draw(6);
    gridSurface2.Draw(6);

    glutSwapBuffers();
}

void myInit(char *progname) {
    int width = 500, height = 500;
    float aspect = (float) width / (float) height;

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //ダブルバッファの宣言
    glutCreateWindow(progname);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    gridSurface.Initialize();
    gridSurface2.Initialize();
    // TODO: この実装は良いのか？
    gridSurface.SetColor4f(0.8, 0.0, 0.0, 0.3);
    gridSurface2.SetColor4f(0.0, 0.8, 0.0, 0.3);
    // gridの位置を各店ごとに対して初期化する
    // for(int i = 0; i <= divideNum; ++i) {
    //     for(int j = 0; j <= divideNum; ++j) {
    //         float deltaY = originY / divideNum;
    //         gridSurface.SetGrid(i, j, vector3d(deltaY * j, originY, originZ));
    //     }
    // }


    for(int i = 0; i <= divideNum; ++i) {
        gridSurface.SetGridIsFixed(0, i, true);
        gridSurface2.SetGridIsFixed(0, i, true);
    }
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