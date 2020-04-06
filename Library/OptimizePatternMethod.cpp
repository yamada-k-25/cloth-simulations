#include <cmath>
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <vector>
#include "AsuraVector.h"
#include <tuple>
#include "OptimizationMethod.h"

using namespace std;

/*
TODO: 最適ばパターンを計算するためのプログラム
1. 初期化：
    * Input: 
    Target Patterns(Animation Frameなど),
    Embeded Pattern(Moireとして印字するための)

    * Constant:
    T: Step Time

    * 途中でつかう変数
    BackPattern : 求めたパターン
    BackPatterns : 求めたパターン列
    t_curr : シミュレーション内の現在時刻
    b_curr : B_curr
    Result : 最終的なt_curr = 0の時のパターン
*/

/// t_0 = 0の時からの時間の経過を入力する
/// Return Tuple<backgroundImage, best_result, best_time>
tuple<ImageData, float, float> OptimizationMethod::Solve(float startTime, float endTime, float deltaTime, evaluateMethodType evalType) {
    float best_eval = 999999.0f;
    float best_time = 0.0f;
    ImageData resultPattern;


    for(float time = startTime; time < endTime; time += deltaTime) {
        ImageData backGroundPattern = getPatternWithTime(time);
        float eval = Evaluate(backGroundPattern, resultPattern, evalType);
        if(eval < best_eval) {
            best_eval = eval;
            resultPattern = backGroundPattern;
        }
    }

    return tuple<ImageData, float, float>(resultPattern, best_eval, best_time);
}

ImageData getPatternWithTime(float time) {
    ImageData result;
    // TODO: 初期状態の布から開始して、パターンを作成する
    
    return result;
}


float OptimizationMethod::Evaluate(ImageData img1, ImageData img2, evaluateMethodType evalType) {
    float result = 0.0f;
    // ２つの画像を使を評価する
    // 具体的な実装は内部実装
    switch(evalType) {
        case CORRELATION:
            return correlation(img1, img2);
        break;
        case RMSE:
            // TODO: 未実装
            return rmse(img1, img2);
    }
    return result;
}

// TODO: 二つの画像から相関を計算して出力する
float OptimizationMethod::correlation(ImageData img1, ImageData img2) {
    float result = 0.0f;

    return result;
}

float OptimizationMethod::rmse(ImageData img1, ImageData img2) {
    float result = 0.0f;
    return -123456789.0f;
}