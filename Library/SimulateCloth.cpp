#include "GridSurface.h"
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <vector>
#include "Constants.h"
#include "AsuraVector.h"
#include <cmath>
#include "SimulationInterfaces.h"

class ClothSimulation {

public:
    /// Singleton
    static ClothSimulation& singleton() {
        static ClothSimulation instance;
        return instance;
    }

    // TODO: 詳細部分を全然実装していない
    ImageData Simulate(SimulationParameters simParameters, float time) {
        /// TODO: ここに実際に Simulationを書く
        ImageData result;
        // ここでDrawSurfaceの表示なしで実装を進めたい
        gridSurface.Initialize();

        gridSurface.Update();
        return result;
    }

    void SetupSimulation(ClothParameters params) {
        gridSurface = GridSurface(params.originX, params.originY, params.originH, params.divideNum, params.rest, params.stringType);
    }

private:
    GridSurface gridSurface;
    

    // インスタンス化の禁止
    ClothSimulation() {
        /// TODO: 本当はNULLを代入するなどで、初期化がされていないとSimulationできないようにしたいのだが
        gridSurface = GridSurface();
    }
    ~ClothSimulation() = default;
};