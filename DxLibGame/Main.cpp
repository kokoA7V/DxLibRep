#include <DxLib.h>
#include <stdio.h>
#include "KeyMng.h"
#include "koko.h"
#include "turnMng.h"

//
//�����ŕϐ���p��
//

// ���݃V�[��
// 0:�V�[���I��
// 1:���܁[�f�o�b�O�p
// 2:�����f�o�b�O�p
// 3:�����f�o�b�O�p
int sceneNum = 0;

// �X�v���C�g�n���h��
int spriteHandle;
int spriteHandle2;

int testBox[7];

int setBottum = 0;

// �T�E���h�n���h��
int soundHandle;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    TurnMng turnMng;

    ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
    SetGraphMode(1280, 720, 32);//��ʃT�C�Y�w��
    SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
    if (DxLib_Init() == 1) { return -1; }//�������Ɏ��s���ɃG���[��f�����ďI��

    //�����ŉ摜�E����ǂݍ���
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
        ClearDrawScreen();//����ʏ���
        SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

        Key.Update();//�L�[���͏�Ԃ��X�V����

        //�����ɖ��t���[���Ăԏ���������
        switch (sceneNum)
        {
        case 0:
             // �V�[���I��
            DrawFormatString(200, 100, GetColor(255, 255, 255), "1 KEY ��肵�[��");
            DrawFormatString(200, 130, GetColor(255, 255, 255), "2 KEY �����邵�[��");
            DrawFormatString(200, 160, GetColor(255, 255, 255), "3 KEY �Ƃ��������[��");
            DrawFormatString(200, 190, GetColor(255, 255, 255), "4 KEY �����Ƃ邵�[��");

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
            gKoko.TestUpdate();

        break;
        // �����f�o�b�O�V�[��
        case 3:
            turnMng.Update();
            gKoko.TestUpdate();
            break;
        case 4:
            // �^�C�g�����
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
                // �X�^�[�g�Z���N�g���
                DrawFormatString(40, 300, GetColor(255, 0, 0), "START �@�@�@�@���[�ނ͂��߂��");
                DrawFormatString(40, 330, GetColor(255, 255, 255), "OPTION");
                DrawFormatString(40, 360, GetColor(255, 255, 255), "EXIT");
                if (Key.keyState[KEY_INPUT_RETURN] == 1)
                {
                    sceneNum = 5;
                }
                break;
            case 1:
                // �I�v�V�����Z���N�g���
                DrawFormatString(40, 300, GetColor(255, 255, 255), "START");
                DrawFormatString(40, 330, GetColor(255, 0, 0), "OPTION�@�@�@�@���Ղ����Ђ炭��");
                DrawFormatString(40, 360, GetColor(255, 255, 255), "EXIT");
                if (Key.keyState[KEY_INPUT_RETURN] == 1)
                {
                    sceneNum = 8;
                }
                break;
            case 2:
                // �C�O�W�b�g�I�����
                DrawFormatString(40, 300, GetColor(255, 255, 255), "START");
                DrawFormatString(40, 330, GetColor(255, 255, 255), "OPTION");
                DrawFormatString(40, 360, GetColor(255, 0, 0), "EXIT  �@�@�@�@���[�ނ��Ƃ����");
                if (Key.keyState[KEY_INPUT_RETURN] == 1)
                {
                    DxLib_End();
                }
                break;
            }
            break;
        case 5:
            // ���낢��Z���N�g���
            SetFontSize(40);
            DrawFormatString(30, 100, GetColor(255, 255, 255), "���͂܂������Ȃ��Z���N�g���\nENTER�Ŏ��̉�ʂ�");
            if (Key.keyState[KEY_INPUT_RETURN] == 1)
            {
                sceneNum++;
            }
            break;
        case 6:
            // �o�g���V�[��
            SetFontSize(16);
            turnMng.Update();
            break;
        case 7:
            SetFontSize(40);
            DrawFormatString(30, 100, GetColor(255, 255, 255), "���͂܂������Ȃ�\n���U���g��ʉ��������ƃ^�C�g����");
            if (CheckHitKeyAll())
            {
                sceneNum = 4;
            }
            // ���ʕ\��
            break;
        case 8:
            SetFontSize(40);
            DrawFormatString(30, 100, GetColor(255, 255, 255), "���͂܂������Ȃ��I�v�V�������\nESC�Ń^�C�g����");
            // ���ʐݒ�
            // �Ζʑ����(�悭�킩���)
            // �ڼޯ�
            if (Key.keyState[KEY_INPUT_ESCAPE] == 1)
            {
                sceneNum = 4;
            }
            break;
        }
        ScreenFlip();//����ʂ�\��ʂɃR�s�[
    }

    DxLib_End();
    return 0;
}

