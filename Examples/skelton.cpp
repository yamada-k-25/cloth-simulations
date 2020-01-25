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

void display(void) { 

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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //ダブルバッファの宣言
    glutCreateWindow(progname);
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