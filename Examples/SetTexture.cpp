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
#include <../Library/read_bitmap.h>

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

    // 画像のパスを指定して、Textureに使用可能なデータに変換する
    // ただし、画像のサイズは縦横2^nである必要がある
    char *filePath = "Assets/Lenna.bmp";
    unsigned char **bitmapImage;
    int imgWidth, imgHeight;
    ReadBitMapData(filePath, &imgWidth, &imgHeight, bitmapImage);
    printf("%d", bitmapImage[0][0]);

    // glClearColor(0.0, 0.0, 0.0, 1.0);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    // 画像を取得する

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