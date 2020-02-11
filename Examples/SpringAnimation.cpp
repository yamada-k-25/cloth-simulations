/*
アニメーションするサンプルプログラム

+ idle()
+ ダブルバッファの実装が必要になる
*/

#include <stdio.h>
#include <iostream> 
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include <vector>

// these need Spring Animation
#include "../Library/Constants.h"
#include "../Library/ClothConstraint.h"
#include "../Library/Object.h"
#include "../Library/Sphere.h"

using namespace std;
using namespace Asura;

typedef vector<ClothConstraint> ClothConstraints;

// Constants
const double mass = 4.0;
const double gravity = 9.80665;
const double k = 1.0f;
const double natural_length = 0.6f;
const double first_accel = gravity;
const double first_velocity = 10.0;
const double first_position = 10.0;
double position = first_position;
double velocity = first_velocity;
double accel = first_accel;

// GridSurface gridSurface(0.5, 0.5, -1, 10, StringType::fixed);
float rad = 0.01f;
Sphere sphere1(rad, mass, vector3d(0.0f, 0.0f, 0.0f), vector3d(0.0f, 0.0f, 0.0f), vector3d(0.0f, 0.0f, 0.0f));
Sphere sphere2(rad, mass, vector3d(0.1f, 0.0f, 0.0f), vector3d(0.0f, 0.0f, 0.0f), vector3d(0.0f, 0.0f, 0.0f));
Sphere sphere3(rad, mass, vector3d(0.2f, 0.0f, 0.0f), vector3d(0.0f, 0.0f, 0.0f), vector3d(0.0f, 0.0f, 0.0f));

// Gridsを初期化する。
// Gridの位置を更新する
// Girdを描画する

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.5, 0.0); //描画対象の色を設定する
    sphere1.Draw();
    sphere2.Draw();
    sphere3.Draw();
    glutSwapBuffers();
}

void idle(void)
{
    // sphere1.Update();
    // sphere2.Update();
    // sphere1.EulerMethod();
    sphere2.UpdateBySpring(k, natural_length, sphere1);
    sphere3.UpdateBySpring(k, natural_length, sphere2);
    // sphere2.UpdateBySpring(k, natural_length, sphere1);

    glutPostRedisplay();
}

void myKbd(unsigned char key, int x, int y) {

}

void myInit(char *progname) {
    int width = 500, height = 500;
    float aspect = (float) width / (float) height;

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //　GLUT_DOUBLE ダブルバッファの宣言の時は, back, frontを設定しないと描画されない
    glutCreateWindow(progname);
    
    // 実質何もしてない、ただの呼び出し
    sphere1.Initialize();
    sphere2.Initialize();
    // sphere1.force.x = 1.0f;
}

// Sphereを描画する
// void createSphere(float rad, Object obj) {
//     glPushMatrix();
//         glTranslatef(obj.position.x, obj.position.y, obj.position.z);
//         glRotated(90, 1.0, 0.0, 0.0);
//         glutSolidSphere(rad, 20, 10);
//     glPopMatrix();
// }

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutDisplayFunc(display);
    // イベントがない場合には以下のidleが実行される
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}

// TODO: 取り合えず、あとで実装しよう
void UpdateConstraints(ClothConstraints clothConstraints) {
    vector<ClothConstraint>::iterator ite = clothConstraints.begin();
    for(ite; ite != clothConstraints.end(); ++ite) {
        ite->grid1.EulerMethod();
        ite->grid2.EulerMethod();
    }
}
