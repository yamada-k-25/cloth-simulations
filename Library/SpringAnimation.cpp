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
    glColor3f(1.0, 0.5, 0.0); //描画対象の色を設定する
    glBegin(GL_POLYGON); //　多角形平面の描画
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(-0.5, 0.5, 0.0);
        glVertex3f(-0.5, -0.5, 0.0);
        glVertex3f(0.5, -0.5, 0.0);
    glEnd();

    glFlush();
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
    glutInitDisplayMode(GLUT_RGBA); //　GLUT_DOUBLE ダブルバッファの宣言の時は, back, frontを設定しないと描画されない
    glutCreateWindow(progname);

    // glClearColor(0.0, 0.0, 0.0, 1.0);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
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