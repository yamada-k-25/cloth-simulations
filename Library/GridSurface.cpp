#include "GridSurface.h"
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <vector>
#include "Constants.h"
#include "AsuraVector.h"
#include <cmath>
using namespace std;

// TODO: ここは後で、別のファイルに切り離した方が良いかもしれない
const int imageHeight = 8;
const int imageWidth = 8;
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

void makeImage(void)
{
	int i,j;
	for (i = 0; i < imageHeight; i++) {
   		for (j = 0; j < imageWidth; j++) {
			image[i][j][0] = (unsigned char) bitmap1[i][j];
        	image[i][j][1] = (unsigned char) bitmap1[i][j];
			image[i][j][2] = (unsigned char) bitmap1[i][j];
        	image[i][j][3] = (unsigned char) 255 - bitmap1[i][j];
     	}
	}
}

void InitTexture(void) {
    makeImage();
    // アライメントを設定する
    // 最適にメモリアクセスができるようにするために、メモリのアライメントを設定する
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidth, imageHeight,
                0, GL_RGBA, GL_UNSIGNED_BYTE, image);
}

GridSurface::GridSurface(float originX, float originY, float originH, int divideNum, float rest, StringType stringType = StringType::none) {
    this->x = originX;
    this->y = originY;
    this->h = originH;
    this->d = divideNum;
    this->stringType = stringType; // ここで布全体のstringTypeが決定される
    // TODO: あとで全ての点から計算する
    this->rest = rest;
    // Gridの点の位置座標の間隔
    this->deltaX = (2*originX)/divideNum;
    this->deltaY = (2*originY)/divideNum;  
    this->grids = vector<vector<Grid> >(divideNum+1, vector<Grid>(divideNum+1));
    // ２点間の組み合わせ総数
    // TODO: 実際には、全ての組み合わせを取る必要はないので、最適化の余地あり
    this->constraints = vector<ClothConstraint>(0);
}

void GridSurface::Initialize() {
    // initialize grids
    InitTexture();
    InitializeGrids();
    InitializeClothConstraints(rest);
}

void GridSurface::Draw(int drawingType) {
    glPushMatrix();   
        glDisable(GL_LIGHTING);

        // 描画範囲の枠線の描画
        // glColor3f(0,0.5,0);
        // glLineWidth(6.0);
        // glBegin(GL_LINE_LOOP);
        // glVertex3d(-x,  y, h);
        // glVertex3d( x,  y, h);  
        // glVertex3d( x, -y, h);
        // glVertex3d(-x, -y, h);
        // glEnd();
        // glLineWidth(3.0);

        // TODO: ここのdrawingTypeをenumで書き換えたほうが良いかも
        switch(drawingType) {
            case 1: // draw vertexs
            for(int i = 0; i < d; ++i) {
                for(int j = 0; j < d; ++j) {
                glBegin(GL_POINTS);
                    glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                glEnd();
                }
            }
            break;

            case 2: // draw wireframe 
                for(int i = 0; i < d; ++i) {
                    for(int j = 0; j < d; ++j) {
                        glColor3f(0,0.5,0);
                        glBegin(GL_LINES);
                            glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                            glVertex3f(grids[i+1][j].position.x , grids[i+1][j].position.y, grids[i+1][j].position.z);
                        glEnd();
                        glBegin(GL_LINES);
                            glVertex3f(grids[i+1][j].position.x , grids[i+1][j].position.y, grids[i+1][j].position.z);
                            glVertex3f(grids[i+1][j+1].position.x , grids[i+1][j+1].position.y, grids[i+1][j+1].position.z);
                        glEnd();
                        glBegin(GL_LINES);
                            glVertex3f(grids[i+1][j+1].position.x , grids[i+1][j+1].position.y, grids[i+1][j+1].position.z);
                            glVertex3f(grids[i][j+1].position.x , grids[i][j+1].position.y, grids[i][j+1].position.z);
                        glEnd();
                        glBegin(GL_LINES);
                            glVertex3f(grids[i][j+1].position.x , grids[i][j+1].position.y, grids[i][j+1].position.z);
                            glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                        glEnd();
                    }
                }
            break;

            case 3: // draw surface
                for(int i = 0; i < d; ++i) {
                    for(int j = 0; j < d; ++j) {
                        glColor3f(0,0.5,0);
                        glBegin(GL_QUADS);
                            glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                            glVertex3f(grids[i+1][j].position.x , grids[i+1][j].position.y, grids[i+1][j].position.z);
                            glVertex3f(grids[i+1][j+1].position.x , grids[i+1][j+1].position.y, grids[i+1][j+1].position.z);
                            glVertex3f(grids[i][j+1].position.x , grids[i][j+1].position.y, grids[i][j+1].position.z);
                        glEnd();
                    }
                }
            break;

            case 4: // Grid Surfafe with Texture 
                for(int i = 0; i < d; ++i) {
                    for(int j = 0; j < d; ++j) {
                        glEnable(GL_BLEND);
                        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                        glEnable(GL_TEXTURE_2D);
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                        glColor4f(0,0.5,0, 0.5);
                        glBegin(GL_QUADS);
                            glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                            glVertex3f(grids[i+1][j].position.x , grids[i+1][j].position.y, grids[i+1][j].position.z);
                            glVertex3f(grids[i+1][j+1].position.x , grids[i+1][j+1].position.y, grids[i+1][j+1].position.z);
                            glVertex3f(grids[i][j+1].position.x , grids[i][j+1].position.y, grids[i][j+1].position.z);
                        glEnd();
                    }
                }
            break;

            case 5: // Grid Surfafe with Texture 
                for(int i = 0; i < d; ++i) {
                    for(int j = 0; j < d; ++j) {
                        glEnable(GL_BLEND);
                        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                        glEnable(GL_TEXTURE_2D);
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                        glColor4f(0,0.5,0, 0.5);
                        glBegin(GL_QUADS);
                            glTexCoord3f(
                                (grids[i][j].position.x - grids[0][0].position.x) / (grids[d][d].position.x - grids[0][0].position.x), 
                                (grids[i][j].position.y - grids[0][0].position.y) / (grids[d][d].position.y - grids[0][0].position.y),
                                (grids[i][j].position.z - grids[0][0].position.z) / (grids[d][d].position.z - grids[0][0].position.z) 
                            ); 
                            glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                            glTexCoord3f(
                                (grids[i+1][j].position.x - grids[0][0].position.x) / (grids[d][d].position.x - grids[0][0].position.x), 
                                (grids[i+1][j].position.y - grids[0][0].position.y) / (grids[d][d].position.y - grids[0][0].position.y),
                                (grids[i+1][j].position.z - grids[0][0].position.z) / (grids[d][d].position.z - grids[0][0].position.z) 
                            ); 
                            glVertex3f(grids[i+1][j].position.x , grids[i+1][j].position.y, grids[i+1][j].position.z);
                            glTexCoord3f(
                                (grids[i+1][j+1].position.x - grids[0][0].position.x) / (grids[d][d].position.x - grids[0][0].position.x), 
                                (grids[i+1][j+1].position.y - grids[0][0].position.y) / (grids[d][d].position.y - grids[0][0].position.y),
                                (grids[i+1][j+1].position.z - grids[0][0].position.z) / (grids[d][d].position.z - grids[0][0].position.z) 
                            ); 
                            glVertex3f(grids[i+1][j+1].position.x , grids[i+1][j+1].position.y, grids[i+1][j+1].position.z);
                            glTexCoord3f(
                                (grids[i][j+1].position.x - grids[0][0].position.x) / (grids[d][d].position.x - grids[0][0].position.x), 
                                (grids[i][j+1].position.y - grids[0][0].position.y) / (grids[d][d].position.y - grids[0][0].position.y),
                                (grids[i][j+1].position.z - grids[0][0].position.z) / (grids[d][d].position.z - grids[0][0].position.z) 
                            ); 
                            glVertex3f(grids[i][j+1].position.x , grids[i][j+1].position.y, grids[i][j+1].position.z);
                        glEnd();
                    }
                }
            break;
        }
    glPopMatrix();
}

void GridSurface::Update() {
    // TestUpdate();
    // forceを0に戻す
    for(int i = 0; i <= d; ++i) {
        for(int j = 0; j <= d; ++j) {
            // grids[i][j].force = Asura::vector3d(0.0f, 0.0f, 0.0f);
        }
    }

    // ===== Update Forces Phase ======
    // 重力
    UpdateGravityForce();
    // 風
    float r1 = counter / 70.0;
    float r2 = counter / 25.0;
    Asura::vector3d windowForce(0.0001f, 0.0001f, 0.0005f);
    for(int i = 0; i <= d; ++i) {
        for(int j = 0; j <=d; ++j) {
            if(!grids[i][j].isFixed) grids[i][j].force += windowForce * (sin(r1) * sin(r2)*0.5 + 1.0);
        }
    }

    //
    UpdateSpringForces();

    // 空気抵抗を計算をするために先に速度だけを計算する
    for(int i = 0; i <= d; ++i) {
        for(int j = 0; j <= d; ++j) {
            grids[i][j].velocity = grids[i][j].force / grids[i][j].mass;
        }
    }

    // 空気抵抗は最後に計算する
    // 空気抵抗
    const float damping = 0.01f;
    for(int i = 0; i <= d; ++i) { 
        for(int j = 0; j <= d; ++j) { 
            grids[i][j].force -= damping * grids[i][j].velocity;
        }
    }

    // 最後に加速度、速度、位置を更新する
    for(int i = 0; i <= d; ++i) {
        for(int j = 0; j <= d; ++j) {
            grids[i][j].accelaration = grids[i][j].force / grids[i][j].mass;
            grids[i][j].velocity += grids[i][j].accelaration * dt;
            grids[i][j].position += grids[i][j].velocity * dt;
        }
    }
}

void GridSurface::SetAllGridStringType(StringType stringType) {
    vector<ClothConstraint>::iterator ite = this->constraints.begin();
    for(ite; ite != this->constraints.end(); ++ite) {
        ite->stringType = stringType;
    }
}


// ============ Protected Methods ============ 

// ============= Initialize Methods ==========

void GridSurface::InitializeGrids() {
    // x方向
    float x0, x1, y0, y1;
    // x0, x1, y0, y1がそれぞれ何を表しているのか考える
    x0 = -x; x1 = -x;
    y0 = -y; y1 = y;

    for(int i = 0; i <= d; ++i){
        for(int j = 0; j <= d; ++j) {
            // x0 = x0 + deltaX;
            // y0 = y0 + deltaY;
            if(!grids[j][i].isFixed) {
                grids[j][i].position.x = x0 + deltaX*i;
                grids[j][i].position.y = y0 + deltaY*j;
                // TODO: ここは、もっと３次元的な位置で初期化できるようにする必要がある
                grids[j][i].position.z = this->h;
                grids[i][j].velocity = Asura::vector3d(0.0f, 0.0f, 0.0f);
                grids[i][j].force = Asura::vector3d(0.0f, 0.0f, 0.0f);
            }
        }
    }
}

void GridSurface::InitializeClothConstraints(float rest) {
    // stringTypeによって、どんな布にするのか決定する
    SetAllGridStringType(stringType);
    // TODO: 最終的には、分けるがとりあえずすべての実装をここにする
    // それぞれの接続によって加える力が違う
    // Strech > Shearing > Bendingの順になるように制御する
    // const float strech_rest = 
    // const float shearing_rest = 
    // const float bending_rest = 
    //　接続の種類に対して、バネ定数をかえる　
    const float streach_Ks = 0.07f;
    const float shearing_Ks = 0.02f;
    const float bending_Ks = 0.01;


    // Strech: 横
    for(int h = 0; h <= d; ++h) {
        for(int w = 0; w < d; ++w) {
            ClothConstraint constraint = ClothConstraint(&grids[h][w], &grids[h][w+1], rest, streach_Ks);
            constraints.push_back(constraint);
        }
    }

    // Strech: 縦
    for(int h = 0; h < d; ++h) {
        for(int w = 0; w <= d; ++w) {
            ClothConstraint constraint = ClothConstraint(&grids[h][w], &grids[h+1][w], rest, streach_Ks);
            constraints.push_back(constraint);
        }
    }

    // Shearing: 斜めと接続する
    // // 右肩下がりを接続する
    for(int h = 0; h+1 <= d; ++h) {
        for(int w = 0; w+1 <= d; ++w) {
            ClothConstraint constraint = ClothConstraint(&grids[h][w], &grids[h+1][w+1], rest*pow(2,1/2), shearing_Ks);
            constraints.push_back(constraint);
        }
    }

    // // 右肩上がりを接続する
    for(int h = 1; h <= d; ++h) {
        for(int w = 0; w+1 <= d; ++w) {
            ClothConstraint constraint = ClothConstraint(&grids[h][w], &grids[h-1][w+1], rest*pow(2,1/2), shearing_Ks);
            constraints.push_back(constraint);
        }
    }

    // Bending: 縮む力 注目点の+2の４近傍と接続する
    // 横を１つ飛ばしで接続する
    for(int h = 0; h+2 <= d; ++h) {
        for(int w = 0; w < d; ++w) {
            ClothConstraint constraint = ClothConstraint(&grids[h][w], &grids[h+2][w], rest*2, bending_Ks);
            constraints.push_back(constraint);
        }
    }

    // 盾を１つ飛ばしで接続する
    for(int h = 0; h < d; ++h) {
        for(int w = 0; w+2 <= d; ++w) {
            ClothConstraint constraint = ClothConstraint(&grids[h][w], &grids[h][w+2], rest*2, bending_Ks);
            constraints.push_back(constraint);
        }
    }


    // Shear: 斜め

    // initialize strech
    // 平面座標系において、縦横に隣り合う点はStreachである

    // initialize shear
    // 平面座標系において、斜めに隣り合う点はshearである

    // initialize bending
    // 平面座標系において、点を１つ飛ばして縦横に隣り合う点はbendingである

}


void GridSurface::EularMethod() {

}

void GridSurface::TestUpdate() {
    // X方向に点が伸びるように実装してみる
    float deltaX = this->deltaX/30;
    for(int i=0; i<=d; ++i) {
        for(int j=0; j<=d; ++j) {
            grids[i][j].position.x += deltaX;
        }
    }
}

void GridSurface::UpdateGravityForce() {
    // 各頂点を外力によって位置を更新する
    for(int i = 0; i <= d; ++i) {
        for(int j = 0; j <= d; ++j) {
            if(!this->grids[i][j].isFixed) {
                this->grids[i][j].force += Asura::vector3d(0.0f, -GRAVITY * this->grids[i][j].mass, 0.0f);
            }
        }
    }
}

void GridSurface::UpdateInternalForces() {
    // TODO: 布の質点同士の関係による弾性力更新など
}

// TODO: 物体との衝突判定を実装するが他のオブジェクトにも汎用的に使えるようにしたい
void GridSurface::UpdateCollision() { 

}

// 縦横の４近傍の弾性力を計算してプロパティを更新する
void GridSurface::UpdateStreach() {
}

// 
void GridSurface::UpdateShear() { 

}

void GridSurface::UpdateBending() { 

}

// 布の物理特性によって質点のプロパティを更新する
void GridSurface::UpdateSpringForces() {

    // 一度各点の力を０に初期化する必要がある
        // TODO: このfor文での参照は危険かも
    // Springを参照して全ての質点の力を更新する
    vector<ClothConstraint>::iterator ite = constraints.begin();
    for(ite; ite != constraints.end(); ++ite) {
        // バネを取得する
        // i番目のバネの自然長と
        // 現在の長さの差分を求める
        Asura::vector3d pointSub = ite->grid1->position - ite->grid2->position;
        float lenSub = pointSub.Length() - ite->rest;
        // 力の向きを考慮して、バネ力を求める
        pointSub.Normalize();
        Asura::vector3d force = -1 * ite->Ks * lenSub * pointSub;
        // 両端の質点に対して、力ベクトルを求める
        // TODO: gridはポインタで表現されているので、自動的に値が更新される
        if(!ite->grid1->isFixed) {
            ite->grid1->force += force;
            // ite->grid1->accelaration = ite->grid1->force / ite->grid1->mass;
            // ite->grid1->velocity += ite->grid1->accelaration * dt;
            // ite->grid1->position += ite->grid1->velocity * dt;
        }

        if(!ite->grid2->isFixed) {
            ite->grid2->force += -1 * force;
            // ite->grid2->accelaration = ite->grid2->force / ite->grid2->mass;
            // ite->grid2->velocity += ite->grid2->accelaration * dt;
            // ite->grid2->position += ite->grid2->velocity * dt;
        }
    }

    // TODO: 最終的には、３つの力を合成することで実装したい
    GridSurface::UpdateStreach();
    GridSurface::UpdateShear();
    GridSurface::UpdateBending();
}