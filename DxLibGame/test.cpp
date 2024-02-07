#include <DxLib.h>
#include <stdio.h>

//
//�����ŕϐ���p��
//

//�L�[�擾�p�̔z��
char buf[256] = { 0 };
int keyState[256] = { 0 };

//�L�[���͏�Ԃ��X�V����֐�
void KeyUpdate()
{
    GetHitKeyStateAll(buf);
    for (int i = 0; i < 256; i++)
    {
        if (buf[i] == 1) {
            keyState[i]++;
        }
        else {
            keyState[i] = 0;
        }
    }
}

// �X�v���C�g�n���h��
int spriteHandle;
int spriteHandle2;

// �T�E���h�n���h��
int soundHandle;

// �J�[�\���ʒu���W
int posX = 0, posY = 0;

// �X�R�A
int score = 0;

// �Ֆʔz��
int field[5][5] =
{
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

// �\���p�z��
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

// �\���p�z�񏉊���
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

// �\���p�z��ɔՖʔz�����
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

// �\���p�z��`��
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

    ChangeWindowMode(TRUE);//��S��ʂɃZ�b�g
    SetGraphMode(640, 480, 32);//��ʃT�C�Y�w��
    SetOutApplicationLogValidFlag(FALSE);//Log.txt�𐶐����Ȃ��悤�ɐݒ�
    if (DxLib_Init() == 1) { return -1; }//�������Ɏ��s���ɃG���[��f�����ďI��

    //�����ŉ摜�E����ǂݍ���
    {
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
            KeyUpdate();//�L�[���͏�Ԃ��X�V����

            DrawFormatString(200, 100, GetColor(255, 255, 255), "Z KEY %d", keyState[KEY_INPUT_Z]);
            DrawFormatString(200, 120, GetColor(255, 255, 255), "X KEY %d", keyState[KEY_INPUT_X]);

            DrawGraph(0, 0, spriteHandle, 0);//�`��
            DrawGraph(0, 64, spriteHandle2, 0);//�`��

            // ���y�Đ�
            if (keyState[KEY_INPUT_Z] == 1)
            {
                PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
            }

            // ���y��~
            if (keyState[KEY_INPUT_X] == 1)
            {
                StopSoundMem(soundHandle);
            }

            // ��������p�Y���Ֆʃv���O����
            {
                // �\���p�z�񏉊���
                ArrayZero();

                // �L�[����
                if (keyState[KEY_INPUT_D] == 1)
                {
                    posX += 1;
                }

                if (keyState[KEY_INPUT_A] == 1)
                {
                    posX -= 1;
                }

                if (keyState[KEY_INPUT_W] == 1)
                {
                    posY -= 1;
                }

                if (keyState[KEY_INPUT_S] == 1)
                {
                    posY += 1;
                }

                // ���݈ʒu��1��z�u
                if (keyState[KEY_INPUT_P] == 1)
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


                // �z����
                ArraySub();

                // ���݈ʒu���W��+2
                dispField[posY][posX] += 2;

                // �z��`��
                ArrayDisp();

                // �X�R�A�\��
                DrawFormatString(100, 50, GetColor(255, 255, 255), "score : %d", score);
            }
        }

        ScreenFlip();//����ʂ�\��ʂɃR�s�[
    }

    DxLib_End();
    return 0;
}

