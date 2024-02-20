#include <DxLib.h>
#include <stdio.h>
#include "KeyMng.h"
#include "koko.h"
#include "turnMng.h"

//
//ここで変数を用意
//

// 現在シーン
// 0:なし
// 1:よりまーデバッグ用
// 2:ここデバッグ用
// 3:統合デバッグ用
int sceneNum = 0;

// スプライトハンドル
int spriteHandle;
int spriteHandle2;

int testBox[7];

// サウンドハンドル
int soundHandle;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    TurnMng turnMng;

    ChangeWindowMode(TRUE);//非全画面にセット
    SetGraphMode(640, 480, 32);//画面サイズ指定
    SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
    if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了

    //ここで画像・音を読み込み
    {
        gKoko.Init();

        sceneNum = 4;

        spriteHandle = LoadGraph("Sprite/test.PNG");
        spriteHandle2 = LoadGraph("Sprite/test2.PNG");

        soundHandle = LoadSoundMem("Sound/Twinfield - Kabedon.mp3");        
    }

    while (ProcessMessage() == 0)
    {
        ClearDrawScreen();//裏画面消す
        SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に

        Key.Update();//キー入力状態を更新する

        //ここに毎フレーム呼ぶ処理を書く
        switch (sceneNum)
        {
        case 0:
            break;

        case 1:
            turnMng.Update();
            break;

        case 2:
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
            gKoko.Update();

        break;
        // 統合デバッグシーン
        case 3:
            turnMng.Update();
            gKoko.Update();
            break;
        case 4:
            // タイトル画面
            SetFontSize(75);
            DrawFormatString(40, 100, GetColor(255, 255, 255), "CrackBlock.exe");
            SetFontSize(30);
            DrawFormatString(270, 250, GetColor(255, 255, 255), "START");
            if (CheckHitKeyAll())
            {
                sceneNum = 5;
            }
            break;
        case 5:

            break;
        }
        ScreenFlip();//裏画面を表画面にコピー
    }

    DxLib_End();
    return 0;
}

