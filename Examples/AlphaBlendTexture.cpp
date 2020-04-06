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
// #include "../Assets/testLenna.h"
#include "../Tools/ReadCSV.h"
#include <bitset>

const int imageHeight = 256;
const int imageWidth = 256;
const int bitmapWidth = 8;
const int bitmapHeight = 8;
unsigned char image[imageHeight][imageWidth][4];
unsigned char bitmap1[bitmapHeight][bitmapWidth] =
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

vector< vector<unsigned char> > ReadCSVData(string file_path) {
    ifstream ifs(file_path);
    vector<vector<unsigned char> > result;
    string line;
    while (getline(ifs, line)) {
        
        vector<unsigned char> strvec = split_hex(line, ',');
        // cout << "the number of line: " + strvec.size() << endl;

        // for (int i=0; i<strvec.size();i++){
        //     printf("%x\n", strvec.at(i));
        // }
        result.push_back(strvec);
    }
    return result;
}

void display(void) {
    // glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glEnable(GL_BLEND);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    // glDepthMask(GL_FALSE);
	// glEnable( GL_DEPTH_TEST );
    // 小さい平面が後になる
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POLYGON); //　多角形平面の描画
        glTexCoord2d(0.0,0.0); glVertex3f(0.1, 0.1, -1.0);
        glTexCoord2d(0.0,1.0); glVertex3f(-0.1, 0.1, -1.0);
        glTexCoord2d(1.0,1.0); glVertex3f(-0.1, -0.1, -1.0);
        glTexCoord2d(1.0,0.0); glVertex3f(0.1, -0.1, -1.0);
    glEnd();
    
    glBegin(GL_POLYGON); //　多角形平面の描画
        glTexCoord2d(0.0,0.0); glVertex3f(0.5, 0.5, 0.0);
        glTexCoord2d(0.0,1.0); glVertex3f(-0.5, 0.5, 0.0);
        glTexCoord2d(1.0,1.0); glVertex3f(-0.5, -0.5, 0.0);
        glTexCoord2d(1.0,0.0); glVertex3f(0.5, -0.5, 0.0);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glFlush();
}

void idle(void)
{
    
}

void myKbd(unsigned char key, int x, int y) {

}

void InitTexture(void) {
    string file_path = "Assets/GratingSampleData2.csv";
    vector<vector<unsigned char> > imageData = ReadCSVData(file_path);
    makeImage(imageData);
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