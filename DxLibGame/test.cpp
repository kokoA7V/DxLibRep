#include <DxLib.h>
#include <stdio.h>
#include "KeyMng.h"
#include "koko.h"

//
//�����ŕϐ���p��
//




// �X�v���C�g�n���h��
int spriteHandle;
int spriteHandle2;

// �T�E���h�n���h��
int soundHandle;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
    SetGraphMode(640, 480, 32);//��ʃT�C�Y�w��
    SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
    if (DxLib_Init() == 1) { return -1; }//�������Ɏ��s���ɃG���[��f�����ďI��

    //�����ŉ摜�E����ǂݍ���
    {
        gKoko.Init();

        spriteHandle = LoadGraph("Sprite/test.PNG");
        spriteHandle2 = LoadGraph("Sprite/test2.PNG");

        soundHandle = LoadSoundMem("Sound/Twinfield - Kabedon.mp3");
    }

    while (ProcessMessage() == 0)
    {
        ClearDrawScreen();//����ʏ���
        SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

        //�����ɖ��t���[���Ăԏ���������
        {
            Key.Update();//�L�[���͏�Ԃ��X�V����

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
            {
                gKoko.Update();
            }
        }

        ScreenFlip();//����ʂ�\��ʂɃR�s�[
    }

    DxLib_End();
    return 0;
}

