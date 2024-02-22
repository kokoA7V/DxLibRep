
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

    boxHandle[0] = LoadGraph("Sprite/box0.PNG");
    boxHandle[1] = LoadGraph("Sprite/box1.PNG");
    boxHandle[2] = LoadGraph("Sprite/box2.PNG");
    boxHandle[3] = LoadGraph("Sprite/box3.PNG");
    boxHandle[4] = LoadGraph("Sprite/box4.PNG");
    boxHandle[5] = LoadGraph("Sprite/box5.PNG");
    boxHandle[6] = LoadGraph("Sprite/box6.PNG");

    pieceNum = 0;

    PiecePosReset();

    Debug("デバッグ文↓");
}

void koko::Update()
{
    PieceMove();

    // ピース変更
    if (Key.keyState[KEY_INPUT_0] == 1)
    {
        pieceNum = 0;
        PiecePosReset();
        Debug("ピース0に変更");
    }
    if (Key.keyState[KEY_INPUT_1] == 1)
    {
        pieceNum = 1;
        PiecePosReset();
        Debug("ピース1に変更");
    }
    if (Key.keyState[KEY_INPUT_2] == 1)
    {
        pieceNum = 2;
        PiecePosReset();
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
    LevelLine(level);

    // 現在位置にピースを配置　起動したらセットするように変えたbyより
    //PieceSet();
    if (Key.keyState[KEY_INPUT_P] == 1)
    {
       // PieceSet();
    }

    // 横一列並んだら消す
    HorizonCheck();

    // 配列描画
    ArrayDemoDisp(dispField, 100, 50);

    ArrayDisp(dispField, 100, 150);

    // スコア描画
    DrawFormatString(100, 25, GetColor(255, 255, 255), "score : %d", score);
    DrawFormatString(300, 0, GetColor(255, 255, 255), "%s", debug.c_str());
}

// 配列初期化
void koko::ArrayZero(int array[fieldSizeY][fieldSizeX])
{
    for (int y = 0; y < fieldSizeX; y++)
    {
        for (int x = 0; x < fieldSizeY; x++)
        {
            array[y][x] = 0;
        }
    }
}

// 配列仮描画
void koko::ArrayDemoDisp(int array[fieldSizeY][fieldSizeX], int posX, int posY)
{
    int space = 15;

    for (int y = 0; y < fieldSizeX; y++)
    {
        for (int x = 0; x < fieldSizeY; x++)
        {
            DrawFormatString
            (
                posX + (x * space),
                posY + (y * space),
                GetColor(255, 255, 255),
                "%d",
                array[y][x]
            );
        }
    }
}

// イラスト配列描画
void koko::ArrayDisp(int array[fieldSizeY][fieldSizeX], int posX, int posY)
{
    int space = 64;

    for (int y = 0; y < fieldSizeX; y++)
    {
        for (int x = 0; x < fieldSizeY; x++)
        {
            if (!SetCheck() && array[y][x] == 2)
            {
                DrawGraph
                (
                    posX + (x * space),
                    posY + (y * space),
                    boxHandle[5],
                    0
                );
            }
            else
            {
                DrawGraph
                (
                    posX + (x * space),
                    posY + (y * space),
                    boxHandle[array[y][x]],
                    0
                );
            }
        }
    }
}

// 配列をコピー
void koko::ArrayCopy(int fromArray[fieldSizeY][fieldSizeX], int toArray[5][5])
{
    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            toArray[y][x] = fromArray[y][x];
        }
    }
}

// 配列加算
void koko::ArrayAdd(int fromArray[fieldSizeY][fieldSizeX], int toArray[fieldSizeY][fieldSizeX], int offsetX, int offsetY)
{
    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            if (x >= offsetX && y >= offsetY)
            {
                toArray[y][x] += fromArray[y - offsetY][x - offsetX];
            }
        }
    }
}

// 配列かけ算
void koko::ArrayMul(int array[fieldSizeY][fieldSizeX], int value)
{
    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            array[y][x] *= value;
        }
    }
}

// プレイヤーピースが設置済みピースに被ってないか確認
// trueで置いてもよい、falseは被ってる
bool koko::SetCheck()
{
    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            if (dispField[y][x] == 3 || dispField[y][x] == 6)
            {
                return false;
            }
        }
    }
    return true;
}

// fieldにピースを配置
bool koko::PieceSet()
{
    // 現在位置にピースを配置
    if (SetCheck())
    {
        ArrayAdd(pieceData[pieceNum], field, posX, posY);
        Debug("せいこう");
        return true;
    }
    else
    {
        Debug("おけないよーん");
        return false;
    }
    return false;
}

// 引数は0~5
// 下から順に使えるようになる
void koko::LevelLine(int level)
{
    for (int y = 0; y < fieldSizeY - level; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            dispField[y][x] += 4;
        }
    }
}

// 横一列並んだ時の処理
void koko::HorizonCheck()
{
    int horizon = 0;
    bool line[4];
    for (int i = 0; i < 4; i++)
    {
        line[i] = false;
    }

    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            horizon += field[y][x];
        }

        if (horizon == 5)
        {
            for (int x = 0; x < fieldSizeX; x++)
            {
                field[y][x] = 0;
            }
            if (y != 0)
            {
                line[y - 1] = true;
            }

            // 横一列消えたときの処理
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

// 引数は0~3（4を入れるとフィールド範囲外になる）
// 指定列を一個下へ移動、指定列を０に
void koko::LineDown(int line)
{
    for (int x = 0; x < fieldSizeX; x++)
    {
        field[line + 1][x] = field[line][x];
        field[line][x] = 0;
    }
}

// ピースサイズ出力
// YorX = 0 : out Y
// YorX = 1 : out X
int koko::PieceSize(int num, int YorX)
{
    int sizeY = 0;
    int sizeX = 0;

    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            if (pieceData[num][y][x] >= 1)
            {
                if (x > sizeX)
                {
                    sizeX = x;
                }

                if (y > sizeY)
                {
                    sizeY = y;
                }
            }
        }
    }

    sizeY++;
    sizeX++;

    if (YorX == 0) { return sizeY; }
    if (YorX == 1) { return sizeX; }
}

// ピース移動
void koko::PieceMove()
{
    // キー入力
    if (Key.keyState[KEY_INPUT_D] == 1 && posX <= ((fieldSizeX - 1) - PieceSize(pieceNum, 1)))
    {
        posX += 1;
    }

    if (Key.keyState[KEY_INPUT_S] == 1 && posY <= ((fieldSizeY - 1) - PieceSize(pieceNum, 0)))
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
    if (posX + PieceSize(pieceNum, 1) >= fieldSizeX + 1)
    {
        posX = fieldSizeX - PieceSize(pieceNum, 1);
        Debug("おい、Xはみ出したぞ");
    }
    if (posY + PieceSize(pieceNum, 0) >= fieldSizeY + 1)
    {
        posY = fieldSizeY - PieceSize(pieceNum, 0);
        Debug("おい、Yはみ出したぞ");
    }
}

// ピースを左下へ移動
void koko::PiecePosReset()
{
    posX = 0;
    posY = fieldSizeY - PieceSize(pieceNum, 0);
}