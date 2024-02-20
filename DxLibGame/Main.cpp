#include <DxLib.h>
#include <stdio.h>
#include "KeyMng.h"
#include "koko.h"
#include "turnMng.h"

//
//�����ŕϐ���p��
//

// ���݃V�[��
// 0:�Ȃ�
// 1:���܁[�f�o�b�O�p
// 2:�����f�o�b�O�p
// 3:�����f�o�b�O�p
int sceneNum = 0;

// �X�v���C�g�n���h��
int spriteHandle;
int spriteHandle2;

int testBox[7];

// �T�E���h�n���h��
int soundHandle;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    TurnMng turnMng;

    ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
    SetGraphMode(640, 480, 32);//��ʃT�C�Y�w��
    SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
    if (DxLib_Init() == 1) { return -1; }//�������Ɏ��s���ɃG���[��f�����ďI��

    //�����ŉ摜�E����ǂݍ���
    {
        gKoko.Init();

        sceneNum = 4;

        spriteHandle = LoadGraph("Sprite/test.PNG");
        spriteHandle2 = LoadGraph("Sprite/test2.PNG");

        soundHandle = LoadSoundMem("Sound/Twinfield - Kabedon.mp3");        
    }

    while (ProcessMessage() == 0)
    {
        ClearDrawScreen();//����ʏ���
        SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

        Key.Update();//�L�[���͏�Ԃ��X�V����

        //�����ɖ��t���[���Ăԏ���������
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

            DrawGraph(0, 0, spriteHandle, 0);//�`��
            DrawGraph(0, 64, spriteHandle2, 0);//�`��

            // ���y�Đ�
            if (Key.keyState[KEY_INPUT_Z] == 1)
            {
                PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
            }

            // ���y��~
            if (Key.keyState[KEY_INPUT_X] == 1)
            {
                StopSoundMem(soundHandle);
            }

            // ��������p�Y���Ֆʃv���O����
            gKoko.Update();

        break;
        // �����f�o�b�O�V�[��
        case 3:
            turnMng.Update();
            gKoko.Update();
            break;
        case 4:
            // �^�C�g�����
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
        ScreenFlip();//����ʂ�\��ʂɃR�s�[
    }

    DxLib_End();
    return 0;
}

