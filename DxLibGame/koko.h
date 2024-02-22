#pragma once
#include "DxLib.h"
#include "Piece.h"
#include <string>
using namespace std;

class koko
{
private:
public:
    
    // デバッグ用string変数
    string debug;

    static const int fieldSizeY = 5;
    static const int fieldSizeX = 5;

	// カーソル位置座標
	int posX = 0, posY = 0;

    // プレイヤーオンオフ
    bool isPlayer = false;

	// スコア
	int score = 0;

    // レベル
    int level = 0;

    // 選択中のピース
    int pieceNum = 0;

    int boxHandle[7] = {0, 0, 0, 0, 0, 0, 0};

    // 盤面配列
    int field[fieldSizeY][fieldSizeX] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    // 表示用配列
    int dispField[fieldSizeY][fieldSizeX] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    int plPiece[fieldSizeY][fieldSizeX] =
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    int pieceData[3][fieldSizeY][fieldSizeX] =
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

	koko();

    void Debug(string str);

	void Init();
    void Update(int posX, int posY);
    void PlayerUpdate();
	void TestUpdate();

	void ArrayZero(int array[fieldSizeY][fieldSizeX]);
    void ArrayDemoDisp(int array[fieldSizeY][fieldSizeX], int posX, int posY);
    void ArrayDisp(int array[fieldSizeY][fieldSizeX], int posX, int posY);
	void ArrayCopy(int fromArray[fieldSizeY][fieldSizeX], int toArray[fieldSizeY][fieldSizeX]);
    void ArrayAdd(int fromArray[fieldSizeY][fieldSizeX], int toArray[fieldSizeY][fieldSizeX], int offsetX, int offsetY);
    void ArrayMul(int array[fieldSizeY][fieldSizeX], int value);

    bool SetCheck();
    void PieceSet();
    void LevelLine(int level);
	void HorizonCheck();
    void LineDown(int line);

    int PieceSize(int num, int YorX);
    void PieceMove();
    void PiecePosReset();
};

extern koko gKoko;