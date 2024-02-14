
#include "koko.h"
#include "KeyMng.h"

koko gKoko;

koko::koko() { }

void koko::Debug(string str)
{
    debug += str + "\n";
}

void koko::Init()
{
    level = 0;

    pieceNum = 0;

    PlayerPosReset();

    Debug("デバッグ文↓");
}

void koko::Update()
{
    PlayerMove();

    // ピース変更
    if (Key.keyState[KEY_INPUT_0] == 1)
    {
        pieceNum = 0;
        PlayerPosReset();
        Debug("ピース0に変更");
    }
    if (Key.keyState[KEY_INPUT_1] == 1)
    {
        pieceNum = 1;
        PlayerPosReset();
        Debug("ピース1に変更");
    }
    if (Key.keyState[KEY_INPUT_2] == 1)
    {
        pieceNum = 2;
        PlayerPosReset();
        Debug("ピース2に変更");
    }

    // レベルアップ
    if (Key.keyState[KEY_INPUT_L] == 1)
    {
        level++;
        Debug("レベルアップ！");
    }

    // 表示用配列初期化
    ArrayZero(dispField);

    // 表示用配列にコピー
    ArrayCopy(field, dispField);

    // Playerピースを表示
    ArrayCopy(pieceData[pieceNum], plPiece);
    ArrayMul(plPiece, 2);
    ArrayAdd(plPiece, dispField, posX, posY);

    // バー表示
    Bar(level);

    // 現在位置にピースを配置
    if (Key.keyState[KEY_INPUT_P] == 1)
    {
        if (SetCheck())
        {
            ArrayAdd(pieceData[pieceNum], field, posX, posY);
            Debug("せいこう");
        }
        else
        {
            Debug("おけないよーん");
        }
    }

    // 横一列並んだら消す
    HorizonCheck();

    // 配列描画
    ArrayDisp(dispField);

    // スコア描画
    DrawFormatString(100, 50, GetColor(255, 255, 255), "score : %d", score);
    DrawFormatString(300, 0, GetColor(255, 255, 255), "%s", debug.c_str());
}

// 配列初期化
void koko::ArrayZero(int array[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            array[i][j] = 0;
        }
    }
}

// 配列描画
void koko::ArrayDisp(int array[5][5])
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
                array[i][j]
            );
        }
    }
}

// 配列をコピー
void koko::ArrayCopy(int fromArray[5][5], int toArray[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            toArray[i][j] = fromArray[i][j];
        }
    }
}

// 配列加算
void koko::ArrayAdd(int fromArray[5][5], int toArray[5][5], int offsetX, int offsetY)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j >= offsetX && i >= offsetY)
            {
                toArray[i][j] += fromArray[i - offsetY][j - offsetX];
            }
        }
    }
}

void koko::ArrayMul(int array[5][5], int value)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            array[i][j] *= value;
        }
    }
}

bool koko::SetCheck()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (dispField[i][j] == 3 || dispField[i][j] == 6)
            {
                return false;
            }
        }
    }
    return true;
}

void koko::Bar(int level)
{
    for (int i = 0; i < 5 - level; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            dispField[i][j] += 4;
        }
    }
}

void koko::HorizonCheck()
{
    int horizon = 0;
    bool line[4];
    for (int i = 0; i < 4; i++)
    {
        line[i] = false;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            horizon += field[i][j];
        }

        if (horizon == 5)
        {
            for (int j = 0; j < 5; j++)
            {
                field[i][j] = 0;
            }
            if (i != 0)
            {
                line[i - 1] = true;
            }
            score += 1;
            Debug("ワンポインツ！");
        }
        horizon = 0;
    }

    for (int i = 0; i < 4; i++)
    {
        if (line[i])
        {
            for (int j = i; j >= 0; j--)
            {
                LineDown(j);
            }
        }
    }
}

void koko::LineDown(int line)
{
    for (int i = 0; i < 5; i++)
    {
        field[line + 1][i] = field[line][i];
        field[line][i] = 0;
    }
}

void koko::PlayerMove()
{
    // キー入力
    if (Key.keyState[KEY_INPUT_D] == 1 && posX <= (4 - pieceSize[pieceNum][0]))
    {
        posX += 1;
    }

    if (Key.keyState[KEY_INPUT_S] == 1 && posY <= (4 - pieceSize[pieceNum][1]))
    {
        posY += 1;
    }

    if (Key.keyState[KEY_INPUT_A] == 1 && posX >= 1)
    {
        posX -= 1;
    }

    if (Key.keyState[KEY_INPUT_W] == 1 && posY >= 1)
    {
        posY -= 1;
    }

    // ピースが画面外にはみ出したら修正
    if (posX + pieceSize[pieceNum][0] >= 6)
    {
        posX = 5 - pieceSize[pieceNum][0];
        Debug("おい、Xはみ出したぞ");
    }
    if (posY + pieceSize[pieceNum][1] >= 6)
    {
        posY = 5 - pieceSize[pieceNum][1];
        Debug("おい、Yはみ出したぞ");
    }
}

void koko::PlayerPosReset()
{
    posX = 0;
    posY = 5 - pieceSize[pieceNum][1];
}