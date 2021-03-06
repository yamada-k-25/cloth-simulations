/*
テクスチャを平面に貼り付けるプログラム

+ idle()
+ ダブルバッファの実装が必要になる
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
のパラメータ:GL_REPEATをオフにする
*/

#include<stdio.h>
#include<iostream> 
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include "../Tools/ReadCSV.h"
#include <bitset>

const int imageHeight = 256;
const int imageWidth = 256;
unsigned char image[imageHeight][imageWidth][4];
unsigned char bitmap1[imageHeight][imageWidth]=
{
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff}
};

// TODO: ここはbitmapを返す関数にしたい
// TODO: imageHeight, imageWidthを受け取る形にする
// void makeImage(int imageHeight, int imageWidth, unsigned char *bitmap1[], unsinged char *image[4]) { 
//     for(int i = 0; i < imageHeight; ++i) {
//         for(int j = 0; j < imageWidth; ++j) {
//             image[i][j][0] = (unsigned char) bitmap1[i][j];
//             image[i][j][1] = (unsigned char) bitmap1[i][j];
//             image[i][j][2] = (unsigned char) bitmap1[i][j];
//             image[i][j][3] = (unsigned char) bitmap1[i][j];
//         }
//     }
// }

void makeImage(vector<vector<unsigned char> > bitmapImage)
{
	int i,j;
	for (i = 0; i < imageHeight; i++) {
   		for (j = 0; j < imageWidth; j++) {
			image[i][j][0] = (unsigned char) bitmapImage[i][j];
        	image[i][j][1] = (unsigned char) bitmapImage[i][j];
			image[i][j][2] = (unsigned char) bitmapImage[i][j];
        	image[i][j][3] = (unsigned char) 255 - bitmapImage[i][j];
     	}
	}
}



void display(void) {
    // glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
    // glDepthMask(GL_FALSE);
	// glEnable( GL_DEPTH_TEST );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0, 0.5, 0.0, 0.8); //描画対象の色を設定する
    glBegin(GL_POLYGON); //　多角形平面の描画
        glTexCoord2d(0.0,0.0); glVertex3f(0.1, 0.1, -1.0);
        glTexCoord2d(0.0,1.0); glVertex3f(-0.1, 0.1, -1.0);
        glTexCoord2d(1.0,1.0); glVertex3f(-0.1, -0.1, -1.0);
        glTexCoord2d(1.0,0.0); glVertex3f(0.1, -0.1, -1.0);
    glEnd();

    glColor4f(1.0, 0.5, 0.0, 0.4); //描画対象の色を設定する
    glBegin(GL_POLYGON); //　多角形平面の描画
        glTexCoord2d(0.0,0.0); glVertex3f(0.5, 0.5, 0.0);
        glTexCoord2d(0.0,1.0); glVertex3f(-0.5, 0.5, 0.0);
        glTexCoord2d(1.0,1.0); glVertex3f(-0.5, -0.5, 0.0);
        glTexCoord2d(1.0,0.0); glVertex3f(0.5, -0.5, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glFlush();
}

void idle(void)
{
    
}

void myKbd(unsigned char key, int x, int y) {

}

void InitTexture(void) {
    string file_path = "Assets/Lenna.csv";
    vector<vector<unsigned char> > lennaData = ReadCSVData(file_path);
    makeImage(lennaData);
    // アライメントを設定する
    // 最適にメモリアクセスができるようにするために、メモリのアライメントを設定する
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidth, imageHeight,
                0, GL_RGBA, GL_UNSIGNED_BYTE, image);
}


void myInit(char *progname) {
    int width = 500, height = 500;
    float aspect = (float) width / (float) height;

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA); //　GLUT_DOUBLE ダブルバッファの宣言の時は, back, frontを設定しないと描画されない
    glutCreateWindow(progname);
    InitTexture();

    // glClearColor(0.0, 0.0, 0.0, 1.0);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutDisplayFunc(display);
    // // イベントがない場合には以下のidleが実行される
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}