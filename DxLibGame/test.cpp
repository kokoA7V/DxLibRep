#include <DxLib.h>
#include <stdio.h>
#include "KeyMng.h"
#include "koko.h"

//
//ここで変数を用意
//



// スプライトハンドル
int spriteHandle;
int spriteHandle2;

// サウンドハンドル
int soundHandle;

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

// 表示用配列初期化
void ArrayZero()
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
void ArraySub()
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
void ArrayDisp()
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



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    ChangeWindowMode(TRUE);//非全画面にセット
    SetGraphMode(640, 480, 32);//画面サイズ指定
    SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
    if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了

    //ここで画像・音を読み込み
    {
        gKoko.Init();

        spriteHandle = LoadGraph("Sprite/test.PNG");
        spriteHandle2 = LoadGraph("Sprite/test2.PNG");

        soundHandle = LoadSoundMem("Sound/Twinfield - Kabedon.mp3");
    }

    while (ProcessMessage() == 0)
    {
        ClearDrawScreen();//裏画面消す
        SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

        //ここに毎フレーム呼ぶ処理を書く
        {
            gKeyMng.KeyUpdate();//キー入力状態を更新する

            DrawFormatString(200, 100, GetColor(255, 255, 255), "Z KEY %d", gKeyMng.keyState[KEY_INPUT_Z]);
            DrawFormatString(200, 120, GetColor(255, 255, 255), "X KEY %d", gKeyMng.keyState[KEY_INPUT_X]);

            DrawGraph(0, 0, spriteHandle, 0);//描画
            DrawGraph(0, 64, spriteHandle2, 0);//描画

            // 音楽再生
            if (gKeyMng.keyState[KEY_INPUT_Z] == 1)
            {
                PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
            }

            // 音楽停止
            if (gKeyMng.keyState[KEY_INPUT_X] == 1)
            {
                StopSoundMem(soundHandle);
            }

            // ここからパズル盤面プログラム
            {
                // 表示用配列初期化
                ArrayZero();

                // キー入力
                if (gKeyMng.keyState[KEY_INPUT_D] == 1)
                {
                    posX += 1;
                }

                if (gKeyMng.keyState[KEY_INPUT_A] == 1)
                {
                    posX -= 1;
                }

                if (gKeyMng.keyState[KEY_INPUT_W] == 1)
                {
                    posY -= 1;
                }

                if (gKeyMng.keyState[KEY_INPUT_S] == 1)
                {
                    posY += 1;
                }

                // 現在位置に1を配置
                if (gKeyMng.keyState[KEY_INPUT_P] == 1)
                {
                    field[posY][posX] = 1;
                }

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


                // 配列代入
                ArraySub();

                // 現在位置座標を+2
                dispField[posY][posX] += 2;

                // 配列描画
                ArrayDisp();

                gKoko.Update();

                // スコア表示
                DrawFormatString(100, 50, GetColor(255, 255, 255), "score : %d", score);
            }
        }

        ScreenFlip();//裏画面を表画面にコピー
    }

    DxLib_End();
    return 0;
}

