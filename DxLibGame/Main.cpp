#include <DxLib.h>
#include <stdio.h>
#include "KeyMng.h"
#include "koko.h"
#include "turnMng.h"

//
//ここで変数を用意
//

// 現在シーン
// 0:シーン選択
// 1:よりまーデバッグ用
// 2:ここデバッグ用
// 3:統合デバッグ用
int sceneNum = 0;

// スプライトハンドル
int spriteHandle;
int spriteHandle2;

int testBox[7];

int setBottum = 0;

// サウンドハンドル
int soundHandle;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    TurnMng turnMng;

    ChangeWindowMode(TRUE);//非全画面にセット
    SetGraphMode(1280, 720, 32);//画面サイズ指定
    SetOutApplicationLogValidFlag(FALSE);//Log.txtを生成しないように設定
    if (DxLib_Init() == 1) { return -1; }//初期化に失敗時にエラーを吐かせて終了

    //ここで画像・音を読み込み
    {
        gKoko.Init();
        turnMng.Init();
        sceneNum = 0;
        setBottum = 0;

        // spriteHandle = LoadGraph("Sprite/test.PNG");
        // spriteHandle2 = LoadGraph("Sprite/test2.PNG");

        // soundHandle = LoadSoundMem("Sound/Twinfield - Kabedon.mp3");        
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
             // シーン選択
            DrawFormatString(200, 100, GetColor(255, 255, 255), "1 KEY よりしーん");
            DrawFormatString(200, 130, GetColor(255, 255, 255), "2 KEY たけるしーん");
            DrawFormatString(200, 160, GetColor(255, 255, 255), "3 KEY とうごうしーん");
            DrawFormatString(200, 190, GetColor(255, 255, 255), "4 KEY たいとるしーん");

            if (Key.keyState[KEY_INPUT_1] == 1)sceneNum = 1;
            if (Key.keyState[KEY_INPUT_2] == 1)sceneNum = 2;
            if (Key.keyState[KEY_INPUT_3] == 1)sceneNum = 3;
            if (Key.keyState[KEY_INPUT_4] == 1)sceneNum = 4;
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
            gKoko.TestUpdate();

        break;
        // 統合デバッグシーン
        case 3:
            turnMng.Update();
            gKoko.TestUpdate();
            break;
        case 4:
            // タイトル画面
            SetFontSize(75);
            DrawFormatString(40, 100, GetColor(255, 255, 255), "CrackBlock.exe");
            SetFontSize(30);
            if (Key.keyState[KEY_INPUT_S] == 1)
            {
                if (setBottum < 2)
                {
                    setBottum++;
                }
                else
                {
                    setBottum = 0;
                }
            }

            if (Key.keyState[KEY_INPUT_W] == 1)
            {
                if (setBottum > 0)
                {
                    setBottum--;
                }
                else
                {
                    setBottum = 2;
                }
            }
            switch (setBottum)
            {
            case 0:
                // スタートセレクト状態
                DrawFormatString(40, 300, GetColor(255, 0, 0), "START 　　　　げーむはじめるよ");
                DrawFormatString(40, 330, GetColor(255, 255, 255), "OPTION");
                DrawFormatString(40, 360, GetColor(255, 255, 255), "EXIT");
                if (Key.keyState[KEY_INPUT_RETURN] == 1)
                {
                    sceneNum = 5;
                }
                break;
            case 1:
                // オプションセレクト状態
                DrawFormatString(40, 300, GetColor(255, 255, 255), "START");
                DrawFormatString(40, 330, GetColor(255, 0, 0), "OPTION　　　　おぷしょんひらくよ");
                DrawFormatString(40, 360, GetColor(255, 255, 255), "EXIT");
                if (Key.keyState[KEY_INPUT_RETURN] == 1)
                {
                    sceneNum = 8;
                }
                break;
            case 2:
                // イグジット選択状態
                DrawFormatString(40, 300, GetColor(255, 255, 255), "START");
                DrawFormatString(40, 330, GetColor(255, 255, 255), "OPTION");
                DrawFormatString(40, 360, GetColor(255, 0, 0), "EXIT  　　　　げーむをとじるよ");
                if (Key.keyState[KEY_INPUT_RETURN] == 1)
                {
                    DxLib_End();
                }
                break;
            }
            break;
        case 5:
            // いろいろセレクト画面
            SetFontSize(40);
            DrawFormatString(30, 100, GetColor(255, 255, 255), "今はまだ何もないセレクト画面\nENTERで次の画面へ");
            if (Key.keyState[KEY_INPUT_RETURN] == 1)
            {
                sceneNum++;
            }
            break;
        case 6:
            // バトルシーン
            SetFontSize(16);
            turnMng.Update();
            break;
        case 7:
            SetFontSize(40);
            DrawFormatString(30, 100, GetColor(255, 255, 255), "今はまだ何もない\nリザルト画面何か押すとタイトルへ");
            if (CheckHitKeyAll())
            {
                sceneNum = 4;
            }
            // 結果表示
            break;
        case 8:
            SetFontSize(40);
            DrawFormatString(30, 100, GetColor(255, 255, 255), "今はまだ何もないオプション画面\nESCでタイトルへ");
            // 音量設定
            // 対面操作可否(よくわからん)
            // ｸﾚｼﾞｯﾄ
            if (Key.keyState[KEY_INPUT_ESCAPE] == 1)
            {
                sceneNum = 4;
            }
            break;
        }
        ScreenFlip();//裏画面を表画面にコピー
    }

    DxLib_End();
    return 0;
}

