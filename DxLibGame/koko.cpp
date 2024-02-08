
#include "koko.h"
#include "KeyMng.h"

koko gKoko;

koko::koko()
{
}

void koko::Init()
{
}

void koko::Update()
{
    // �\���p�z�񏉊���
    ArrayZero();

    // �L�[����
    if (Key.keyState[KEY_INPUT_D] == 1)
    {
        posX += 1;
    }

    if (Key.keyState[KEY_INPUT_A] == 1)
    {
        posX -= 1;
    }

    if (Key.keyState[KEY_INPUT_W] == 1)
    {
        posY -= 1;
    }

    if (Key.keyState[KEY_INPUT_S] == 1)
    {
        posY += 1;
    }

    // ���݈ʒu��1��z�u
    if (Key.keyState[KEY_INPUT_P] == 1)
    {
        field[posY][posX] = 1;
    }

    // �������񂾂����
    HorizonCheck();

    // �z����
    ArraySub();

    // ���݈ʒu���W��+2
    dispField[posY][posX] += 2;

    // �z��`��
    ArrayDisp();

    // �X�R�A�\��
    DrawFormatString(100, 50, GetColor(255, 255, 255), "score : %d", score);
}

// �\���p�z�񏉊���
void koko::ArrayZero()
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
void koko::ArraySub()
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
void koko::ArrayDisp()
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

void koko::HorizonCheck()
{
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
}