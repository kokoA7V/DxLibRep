#pragma once
#include "DxLib.h"
#include <string>
using namespace std;

class koko
{
private:
public:
    
    string debug;

	// �J�[�\���ʒu���W
	int posX = 0, posY = 0;

	// �X�R�A
	int score = 0;

    int level = 0;

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

    int pieceNum = 0;

    int plPiece[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    int pieceData[3][5][5] =
    {
        {
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        },

        {
        {1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        },

        {
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
        }
    };

    int pieceSize[3][2]
    {
        {1, 1},
        {2, 2},
        {4, 1}
    };

	koko();

    void Debug(string str);

	void Init();
	void Update();

	void ArrayZero(int array[5][5]);
    void ArrayDisp(int array[5][5]);
	void ArrayCopy(int fromArray[5][5], int toArray[5][5]);
    void ArrayAdd(int fromArray[5][5], int toArray[5][5], int offsetX, int offsetY);
    void ArrayMul(int array[5][5], int value);

    bool SetCheck();
    void Bar(int level);
	void HorizonCheck();
    void LineDown(int line);

    void PlayerMove();
    void PlayerPosReset();
};

extern koko gKoko;