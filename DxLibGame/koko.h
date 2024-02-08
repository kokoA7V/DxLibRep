#pragma once
#include "DxLib.h"

class koko
{
private:
public:
	// カーソル位置座標
	int posX = 0, posY = 0;

	// スコア
	int score = 0;

    // 盤面配列
    int field[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    // 表示用配列
    int dispField[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    int part[2][5][5] =
    {
        {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        },

        {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        }
    };

    int partSize[2][2]
    {
        {2, 1},
        {0, 0}
    };

	koko();

	void Init();
	void Update();

	void ArrayZero();
	void ArraySub();
	void ArrayDisp();
	void HorizonCheck();
};

extern koko gKoko;