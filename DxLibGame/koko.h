#pragma once
#include "DxLib.h"

class koko
{
private:
public:
	// �J�[�\���ʒu���W
	int posX = 0, posY = 0;

	// �X�R�A
	int score = 0;

    // �Ֆʔz��
    int field[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    // �\���p�z��
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