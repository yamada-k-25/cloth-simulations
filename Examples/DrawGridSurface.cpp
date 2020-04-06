#include<stdio.h>
#include<iostream> 
#include <math.h>
#include <bitset>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <GLFW/glfw3.h>
#include "../Library/GridSurface.h"

#define KEY_ESC 27

void polarView( void );
void resetView( void );

float xOrigin = 0.0, yOrigin = 0.0; 
int xStart = 0, yStart = 0;
unsigned char MouseON = GL_FALSE;
int action;
enum actions{ MOVE_EYE, TWIST_EYE, ZOOM };
float twist, elevation, azimuth, dist;
float nearw = 1.0, farw = 30.0, fovy = 60.0;

const int divideNum = 20;
const float originX = -0.5;
const float originY = -0.5;
const float originZ = -2.0;
const float originX2 = 0.0;
const float originY2 = -0.5;
const float originZ2 = -2.2;

const float width = 1.0;
const float height = 1.0;

const float rest = width / divideNum;

using namespace Asura;

// 均等の位置になるように位置を初期化する
GridSurface gridSurface(originX, originY, originZ, divideNum, width, height, rest, StringType::fixed);
// 均等の位置になるように位置を初期化する
GridSurface gridSurface2(originX2, originY2, originZ2, divideNum, width, height, rest, StringType::fixed);
/*
以下を参考にさせていただいてます.
OpenGL - サンプルコード
(http://www.slis.tsukuba.ac.jp/~fujisawa.makoto.fu/cgi-bin/wiki/index.php?OpenGL%20-%20%A5%B5%A5%F3%A5%D7%A5%EB%A5%B3%A1%BC%A5%C9)
*/
void idle(void)
{
    // TODO: 引っ張りの方向は正しいのか
    vector3d rightDirectionForce = vector3d(0.0001f, 0.0f, 0.0f);
    vector3d leftDirectionForce = vector3d(-0.00004f, 0.0f, 0.0f);
    vector3d upDirectionForce = vector3d(0.0f, 0.0001f, 0.0f);
    // leftSide
    // TODO: Gridの埋め方がどうだったか確認する
    // -x 方向にi行0列目に対して力を加える
    // for(int i = 0; i <= divideNum; i++) gridSurface2.PullGridSurface(leftDirectionForce, i, 0);
    gridSurface2.PullGridSurface(leftDirectionForce, 0, 0);
    leftDirectionForce = vector3d(-0.001f, 0.0f, 0.0f);
    gridSurface2.PullGridSurface(leftDirectionForce, divideNum, 0);
    gridSurface2.PullGridSurface(leftDirectionForce, (int)(divideNum / 2), 0);
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
    gridSurface.Draw(5);
    gridSurface2.Draw(5);

    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{
	switch(c) {
    case KEY_ESC:
        exit( 0 );
        // glutLeaveMainLoop();
  	default:
   		break;
	}
}

void myInit(char *progname) {
    int width = 500, height = 500;
    float aspect = (float) width / (float) height;

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //ダブルバッファの宣言
    glutCreateWindow(progname);
    glutKeyboardFunc(keyboard);
    resetView();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    gridSurface.SetTexture("Assets/GratingSampleData2.csv", 1);
    gridSurface2.SetTexture("Assets/Lenna.csv", 2);
    gridSurface.Initialize();
    gridSurface2.Initialize();
    // TODO: この実装は良いのか？

    // gridSurface.SetColor4f(0.8, 0.0, 0.0, 1.0);
    // gridSurface2.SetColor4f(0.0, 0.8, 0.0, 0.3);
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

void reshape(int width, int height)
{
    double aspect;

    aspect = (double) width / (double) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, nearw, farw);
    glMatrixMode(GL_MODELVIEW);
}


void polarView( void )
{
    glTranslatef( 0.0, 0.0, -dist);
    glRotatef( -twist, 0.0, 0.0, 1.0);
    glRotatef( -elevation, 1.0, 0.0, 0.0);
    glRotatef( -azimuth, 0.0, 1.0, 0.0);
}

void resetView( void )
{
	dist = 3.0;
    twist = 0.0;
    elevation = -30.0;
    azimuth = 30.0;
}

void mouse( int button, int state, int x, int y )
{
    if (state == GLUT_DOWN) {
        MouseON = GL_TRUE;
        switch(button) {
        case GLUT_LEFT_BUTTON:
            action = MOVE_EYE;
            break;
        case GLUT_MIDDLE_BUTTON:
            action = TWIST_EYE;
            break;
        case GLUT_RIGHT_BUTTON:
            action = ZOOM;
            break;
        }

        xStart = x;
        yStart = y;
    }
}

void motion(int x, int y)
{
    int xEnd, yEnd;
    int xOffset, yOffset;

    if (MouseON == GL_TRUE) {
        xEnd = x;
        yEnd = y;
        xOffset = xEnd - xStart;
        yOffset = yEnd - yStart;
        switch(action){
        case MOVE_EYE:
            azimuth += (double) xOffset/2.0;
            elevation -= (double) yOffset/2.0;
            break;
        case TWIST_EYE:
            twist = fmod (twist + xOffset, 360.0);
            break;
        case ZOOM:
            dist -= (double) yOffset/40.0;
            break;
        }
    xStart = xEnd;
    yStart = yEnd;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    myInit(argv[0]);
	glutReshapeFunc (reshape);
    glutDisplayFunc(display);
	glutMotionFunc( motion );
	glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}