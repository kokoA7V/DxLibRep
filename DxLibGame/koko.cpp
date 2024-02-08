
#include "koko.h"
#include "KeyMng.h"

koko gKoko;

koko::koko()
{
}

void koko::Init()
{
}

void koko::Update()
{
    // 表示用配列初期化
    ArrayZero();

    // キー入力
    if (Key.keyState[KEY_INPUT_D] == 1)
    {
        posX += 1;
    }

    if (Key.keyState[KEY_INPUT_A] == 1)
    {
        posX -= 1;
    }

    if (Key.keyState[KEY_INPUT_W] == 1)
    {
        posY -= 1;
    }

    if (Key.keyState[KEY_INPUT_S] == 1)
    {
        posY += 1;
    }

    // 現在位置に1を配置
    if (Key.keyState[KEY_INPUT_P] == 1)
    {
        field[posY][posX] = 1;
    }

    // 横一列並んだら消す
    HorizonCheck();

    // 配列代入
    ArraySub();

    // 現在位置座標を+2
    dispField[posY][posX] += 2;

    // 配列描画
    ArrayDisp();

    // スコア表示
    DrawFormatString(100, 50, GetColor(255, 255, 255), "score : %d", score);
}

// 表示用配列初期化
void koko::ArrayZero()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            dispField[i][j] = 0;
        }
    }
}

// 表示用配列に盤面配列を代入
void koko::ArraySub()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            dispField[i][j] = field[i][j];
        }
    }
}

// 表示用配列描画
void koko::ArrayDisp()
{
    int space = 15;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            DrawFormatString
            (
                100 + (j * space),
                100 + (i * space),
                GetColor(255, 255, 255),
                "%d",
                dispField[i][j]
            );
        }
    }
}

void koko::HorizonCheck()
{
    int horizon = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            horizon += field[i][j];
        }

        if (horizon >= 5)
        {
            for (int j = 0; j < 5; j++)
            {
                field[i][j] = 0;
            }
            score += 1;
        }

        horizon = 0;
    }
}