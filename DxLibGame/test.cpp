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
            Key.Update();//キー入力状態を更新する

            DrawFormatString(200, 100, GetColor(255, 255, 255), "Z KEY %d", Key.keyState[KEY_INPUT_Z]);
            DrawFormatString(200, 120, GetColor(255, 255, 255), "X KEY %d", Key.keyState[KEY_INPUT_X]);

            DrawGraph(0, 0, spriteHandle, 0);//描画
            DrawGraph(0, 64, spriteHandle2, 0);//描画

            // 音楽再生
            if (Key.keyState[KEY_INPUT_Z] == 1)
            {
                PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
            }

            // 音楽停止
            if (Key.keyState[KEY_INPUT_X] == 1)
            {
                StopSoundMem(soundHandle);
            }

            // ここからパズル盤面プログラム
            {
                gKoko.Update();
            }
        }

        ScreenFlip();//裏画面を表画面にコピー
    }

    DxLib_End();
    return 0;
}

