#include "GridSurface.h"
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "Constants.h"
#include "AsuraVector.h"
#include "../Tools/ReadCSV.h"
using namespace std;

int counter = 0;

// TODO: ここは後で、別のファイルに切り離した方が良いかもしれない
// FIXME: 別ファイルでどのファイルからもアクセスできる状態にする
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

unsigned char line_bitmap[imageHeight][imageWidth]=
{
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff},
	{0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff}
};

/*
void makeImage(void)
{
	int i,j;
	for (i = 0; i < imageHeight; i++) {
   		for (j = 0; j < imageWidth; j++) {
			image[i][j][0] = (unsigned char) line_bitmap[i][j];
        	image[i][j][1] = (unsigned char) line_bitmap[i][j];
			image[i][j][2] = (unsigned char) line_bitmap[i][j];
        	image[i][j][3] = (unsigned char) 255 - line_bitmap[i][j];
     	}
	}
}
*/
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

void GridSurface::InitTexture(void) {
    string file_path = this->filePath;
    printf("filepath: %s", file_path.c_str());
    if(this->filePath.size() == 0) { printf("SetTexture関数でtextureのファイルパスを指定してください"); exit(1);}
    vector<vector<unsigned char> > lennaData = ReadCSVData(file_path);
    makeImage(lennaData);
    // アライメントを設定する
    // 最適にメモリアクセスができるようにするために、メモリのアライメントを設定する
    glBindTexture(GL_TEXTURE_2D, this->texNum);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, imageWidth, imageHeight,
                0, GL_RGBA, GL_UNSIGNED_BYTE, image);
}

GridSurface::GridSurface(float originX, float originY, float originH, int divideNum, float width, float height, float rest, StringType stringType = StringType::none) {
    // TODO: 以下の初期化に必要なパラメータ群の意味が少し曖昧なので、ちゃんと定義したい
    this->x = originX;
    this->y = originY;
    this->h = originH;
    this->d = divideNum;
    this->stringType = stringType; // ここで布全体のstringTypeが決定される
    // TODO: あとで全ての点から計算する
    this->rest = rest;
    // Gridの点の位置座標の間隔
    this->deltaX = width / divideNum;
    this->deltaY = height /divideNum;  
    this->grids = vector<vector<Grid> >(divideNum+1, vector<Grid>(divideNum+1));
    this->preGrids = vector<vector<Grid> >(divideNum+1, vector<Grid>(divideNum+1));
    this->nextGrids = vector<vector<Grid> >(divideNum+1, vector<Grid>(divideNum+1));
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
                        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
                        // glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
                        glEnable(GL_TEXTURE_2D);
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                        glBindTexture(GL_TEXTURE_2D,this->texNum);
                        glBegin(GL_QUADS);
                        int d = this->d;
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
                        // glBegin(GL_QUADS);
                        //     glTexCoord3f(
                        //         (grids[i][j].position.x - grids[0][0].position.x) / (grids[d][d].position.x - grids[0][0].position.x), 
                        //         (grids[i][j].position.y - grids[0][0].position.y) / (grids[d][d].position.y - grids[0][0].position.y),
                        //         (grids[i][j].position.z - grids[0][0].position.z) / (grids[d][d].position.z - grids[0][0].position.z) 
                        //     ); 
                        //     glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                        //     glTexCoord3f(
                        //         (grids[i+1][j].position.x - grids[0][0].position.x) / (grids[d][d].position.x - grids[0][0].position.x), 
                        //         (grids[i+1][j].position.y - grids[0][0].position.y) / (grids[d][d].position.y - grids[0][0].position.y),
                        //         (grids[i+1][j].position.z - grids[0][0].position.z) / (grids[d][d].position.z - grids[0][0].position.z) 
                        //     ); 
                        //     glVertex3f(grids[i+1][j].position.x , grids[i+1][j].position.y, grids[i+1][j].position.z);
                        //     glTexCoord3f(
                        //         (grids[i+1][j+1].position.x - grids[0][0].position.x) / (grids[d][d].position.x - grids[0][0].position.x), 
                        //         (grids[i+1][j+1].position.y - grids[0][0].position.y) / (grids[d][d].position.y - grids[0][0].position.y),
                        //         (grids[i+1][j+1].position.z - grids[0][0].position.z) / (grids[d][d].position.z - grids[0][0].position.z) 
                        //     ); 
                        //     glVertex3f(grids[i+1][j+1].position.x , grids[i+1][j+1].position.y, grids[i+1][j+1].position.z);
                        //     glTexCoord3f(
                        //         (grids[i][j+1].position.x - grids[0][0].position.x) / (grids[d][d].position.x - grids[0][0].position.x), 
                        //         (grids[i][j+1].position.y - grids[0][0].position.y) / (grids[d][d].position.y - grids[0][0].position.y),
                        //         (grids[i][j+1].position.z - grids[0][0].position.z) / (grids[d][d].position.z - grids[0][0].position.z) 
                        //     ); 
                        //     glVertex3f(grids[i][j+1].position.x , grids[i][j+1].position.y, grids[i][j+1].position.z);
                        // glEnd();
                    }
                }
            break;

            case 6: // Grid Surfafe with Texture 
                for(int i = 0; i < d; ++i) {
                    for(int j = 0; j < d; ++j) {
                        glEnable(GL_POLYGON_SMOOTH);
                        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
                        glEnable(GL_BLEND);
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                        // jが偶数なら透明にする
                        if(j % 2 == 0) {
                            // TODO: 全体の色にできるように設定されるようにする
                            if(this->isColor) {
                                glColor4f(this->red, this->green, this->blue, this->alpha);
                            }else {
                                glColor4f(0.2,0.2,0.2, 1.0); 
                            }
                        }else {
                            if(this->isColor) {
                                glColor4f(1.0, 1.0, 1.0, 1.0);
                            }else {
                                glColor4f(0.2,0.2,0.2, 0.0); 
                            }
                        }
                        glBegin(GL_QUADS);
                        int d = 6;
                            glVertex3f(grids[i][j].position.x , grids[i][j].position.y, grids[i][j].position.z);
                            glVertex3f(grids[i+1][j].position.x , grids[i+1][j].position.y, grids[i+1][j].position.z);
                            glVertex3f(grids[i+1][j+1].position.x , grids[i+1][j+1].position.y, grids[i+1][j+1].position.z);
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
    // UpdateGravityForce();
    // 風
    float r1 = counter / 70.0;
    float r2 = counter / 25.0;
    // Asura::vector3d windowForce(0.0001f, 0.0001f, 0.0005f);
    // Asura::vector3d windowForce(0.0001f, 0.000001f, 0.00003f);
    // for(int i = 0; i <= d; ++i) {
    //     for(int j = 0; j <=d; ++j) {
    //         if(!grids[i][j].isFixed) grids[i][j].force += windowForce * (sin(r1) * sin(r2)*0.5 + 1.0);
    //     }
    // }
    counter++;
    //
    UpdateSpringForces();

    // 空気抵抗を計算をするために先に速度だけを計算する
    for(int i = 0; i <= d; ++i) {
        for(int j = 0; j <= d; ++j) {
            grids[i][j].velocity = grids[i][j].force / grids[i][j].mass;
        }
    }

    // TestUpdate();

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
            // nextGrids[i][j].position = 2*grids[i][j].position - preGrids[i][j].position + grids[i][j].accelaration * dt * dt;
        }
    }
/*
    // 現在のgridsを前のgridsの保存しておく
    for(int i = 0; i <=d; ++i) {
        for(int j = 0; j <= d; ++j) {
            preGrids[i][j].accelaration = grids[i][j].accelaration;
            preGrids[j][j].position = grids[i][j].position;
        }
    }

    // 現在のgridに書き換える
    for(int i = 0; i <=d; ++i) {
        for(int j = 0; j <= d; ++j) {
            grids[i][j].accelaration = nextGrids[i][j].accelaration;
            grids[j][j].position = nextGrids[i][j].position;
        }
    }
    */
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

    for(int i = 0; i <= d; ++i){
        for(int j = 0; j <= d; ++j) {
                // xを先に動かす
                grids[i][j].position.x = this->x + deltaX*j;
                grids[i][j].position.y = this->y + deltaY*i;
                // TODO: ここは、もっと３次元的な位置で初期化できるようにする必要がある
                grids[i][j].position.z = this->h;
                grids[i][j].velocity = Asura::vector3d(0.0f, 0.0f, 0.0f);
                grids[i][j].force = Asura::vector3d(0.0f, 0.0f, 0.0f);

                preGrids[i][j].position.x = this->x + deltaX*j;
                preGrids[i][j].position.y = this->y + deltaY*i;
                // TODO: ここは、もっと３次元的な位置で初期化できるようにする必要がある
                preGrids[i][j].position.z = this->h;
                preGrids[i][j].velocity = Asura::vector3d(0.0f, 0.0f, 0.0f);
                preGrids[i][j].force = Asura::vector3d(0.0f, 0.0f, 0.0f);
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
    const float streach_Ks = 0.007f;
    const float shearing_Ks = 0.002f;
    const float bending_Ks = 0.001;


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
    // X方向に移動するようにする
    float deltaX = this->deltaX/30;
    int direction = pow(-1, int(counter / 400));
    for(int i=0; i<=d; ++i) {
        for(int j=0; j<=d; ++j) {
            grids[i][j].position.x += deltaX * direction;
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

/// 与えられた点に対して力を一定の方向に加える
/// この実装だとfoceに0が与えられているタイミングでないとダメ
void  GridSurface::PullGridSurface(Asura::vector3d force, int row, int col) {
    // TODO: 布の引っ張り方が意図した挙動になっていない
    // forceを元に位置を変更する処理がうまく噛み合っていない?
    this->grids[row][col].force += force;
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
            // TODO: 上辺が固定されていることを仮定する
            Asura::vector3d fix_force(force.x, 0.0f, force.z);
            ite->grid1->force += fix_force;

            // ite->grid1->force += force;
            // ite->grid1->accelaration = ite->grid1->force / ite->grid1->mass;
            // ite->grid1->velocity += ite->grid1->accelaration * dt;
            // ite->grid1->position += ite->grid1->velocity * dt;
        }

        if(!ite->grid2->isFixed) {
            Asura::vector3d fix_force(force.x, 0.0f, force.z);
            ite->grid2->force += -1 * fix_force;
            // ite->grid2->force += -1 * force;
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