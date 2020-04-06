#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <OpenGL/OpenGL.h>
#include <iostream>

using namespace std;

float x = 0.0f;
float y = 0.0f;
float dx = 0.001f;

int frameCount = 0;
const int TERMINATE_FRAME_COUNT = 120;

void update() {
    x += dx;
}

void draw() {
    glColor3f(1.0, 0.5, 0.0); //描画対象の色を設定する
    glBegin(GL_POLYGON); //　多角形平面の描画
        glVertex3f(0.5 + x, 0.5, 0.0);
        glVertex3f(-0.5 + x, 0.5, 0.0);
        glVertex3f(-0.5 + x, -0.5, 0.0);
        glVertex3f(0.5 + x, -0.5, 0.0);
    glEnd();
    glFlush();
}

void mainLoop(GLFWwindow *window) {

    glfwInit();

    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return;
    }

    // ここの処理は一体...
    glfwMakeContextCurrent(window);

    frameCount = 0;
    while(!glfwWindowShouldClose(window)) {
        // ここの設定が何か知りたい
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        update();
        draw();

        glfwSwapBuffers(window);
        // ここの関数が何か知りたい
        glfwPollEvents();

        if(frameCount == TERMINATE_FRAME_COUNT){ 
            glfwTerminate();
            break;
        }

        else frameCount++;
    }
}

void terminatePrint() {
    cout << frameCount << endl;
}

int main(int argc, char *argv[]) {
    GLFWwindow* window;
    /*
    いまのプログラムをどうやってこれに取り入れば、最適化を回せる形になるのか考える
    */
   // TODO: 現状のSkeltonのプログラムをここに組み込めるのか試してみる
   // そのためにまずは下の処理がそれぞれ何をしているのか調べる
   // また、glutで使っている関数と対応する関数を調べる

    for(int i = 0; i < 100; i++) {
        if(i % 10 == 0){
            mainLoop(window);
            cout << "index: " << i << endl;
        }
    }

    glfwTerminate();
    return 0;
}