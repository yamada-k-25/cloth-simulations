#include <cmath>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <vector>
#include "AsuraVector.h"
#include <vector>
#include <tuple>
#include "SimulationInterfaces.h"

enum evaluateMethodType {
    CORRELATION = 0,
    SSIM = 1,
    RMSE = 2,
    MSE = 3,
};

typedef std::vector<ImageData> ImageDataArray;

class OptimizationMethod {
private:
    // ここは最終的に画像のデータが入るデータ構造にする
    ImageDataArray target_ps;
    ImageData embeded_p;
    ImageData backPattern;
    ImageDataArray backPatterns;
    int t_curr;
    int b_curr;
    float T;
    SimulationParameters simParameters;
    ClothParameters clothParameters;

public:

    // Constructor
    OptimizationMethod(ClothParameters clothParameters, SimulationParameters simParameters) {
        this->clothParameters = clothParameters;
        this->simParameters = simParameters;
    }

    /// you need set target images.
    void SetTargetPattern(ImageDataArray targetPatterns) {
        this->target_ps = targetPatterns;
    }
    
    /// you need set embeded pattern.
    void SetEmbededPattern(ImageData embededPattern) {
        this->embeded_p = embededPattern;
    }

    /// if you want to set a time step, you can set a time step. default time step is hoge.
    void SetTimeStep(float timeStep) {
        this->T = timeStep;
    }

    /// you need to set parameters, for example direction of forces, validate gravity or wind force

    // TODO: Solve: Optimizeをしていく、関数
    // T : 
    tuple<ImageData, float, float> OptimizationMethod::Solve(float startTime, float endTime, float deltaTime, evaluateMethodType evalTime);
    
    // TODO: Evaluation : ２つの画像ががどの程度似ているのか評価する？
    float Evaluate(ImageData img1, ImageData img2, evaluateMethodType evalType);

private:
    // 相関関数を用いて、計算した結果を返す
    float correlation(ImageData img1, ImageData img2);
    float OptimizationMethod::rmse(ImageData img1, ImageData img2);
};