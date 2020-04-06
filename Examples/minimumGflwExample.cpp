#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

int main(int argc, char *argv[]) {
    GLFWwindow* window;
    /*
    いまのプログラムをどうやってこれに取り入れば、最適化を回せる形になるのか考える
    */
   // TODO: 現状のSkeltonのプログラムをここに組み込めるのか試してみる
   // そのためにまずは下の処理がそれぞれ何をしているのか調べる
   // また、glutで使っている関数と対応する関数を調べる
   

    glfwInit();

    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if(!window) {
        glfwTerminate();
        return -1;
    }

    // ここの処理は一体...
    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window)) {
        // ここの設定が何か知りたい
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
        // ここの関数が何か知りたい
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}