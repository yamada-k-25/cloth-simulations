#include<stdio.h>
#include<iostream> 
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include "../Library/GridSurface.h"

GridSurface gridSurface(0.5, 0.5, -1, 10);

/*
以下を参考にさせていただいてます.
OpenGL - サンプルコード
(http://www.slis.tsukuba.ac.jp/~fujisawa.makoto.fu/cgi-bin/wiki/index.php?OpenGL%20-%20%A5%B5%A5%F3%A5%D7%A5%EB%A5%B3%A1%BC%A5%C9)
*/
void idle(void)
{
    gridSurface.Update();
    glutPostRedisplay();
}

void myKbd(unsigned char key, int x, int y) {

}

void display(void) { 
    glClear(GL_COLOR_BUFFER_BIT);
    // DrawGroundGrid(10, 1, 1, 1);
    // printf("%d, %d, %d, %d", gridSurface.GetX(), gridSurface.GetY(), gridSurface.GetH(), gridSurface.DivideNum());
    gridSurface.Draw(2);

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