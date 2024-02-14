
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

    pieceNum = 0;

    PlayerPosReset();

    Debug("�f�o�b�O����");
}

void koko::Update()
{
    PlayerMove();

    // �s�[�X�ύX
    if (Key.keyState[KEY_INPUT_0] == 1)
    {
        pieceNum = 0;
        PlayerPosReset();
        Debug("�s�[�X0�ɕύX");
    }
    if (Key.keyState[KEY_INPUT_1] == 1)
    {
        pieceNum = 1;
        PlayerPosReset();
        Debug("�s�[�X1�ɕύX");
    }
    if (Key.keyState[KEY_INPUT_2] == 1)
    {
        pieceNum = 2;
        PlayerPosReset();
        Debug("�s�[�X2�ɕύX");
    }

    // ���x���A�b�v
    if (Key.keyState[KEY_INPUT_L] == 1)
    {
        level++;
        Debug("���x���A�b�v�I");
    }

    // �\���p�z�񏉊���
    ArrayZero(dispField);

    // �\���p�z��ɃR�s�[
    ArrayCopy(field, dispField);

    // Player�s�[�X��\��
    ArrayCopy(pieceData[pieceNum], plPiece);
    ArrayMul(plPiece, 2);
    ArrayAdd(plPiece, dispField, posX, posY);

    // �o�[�\��
    Bar(level);

    // ���݈ʒu�Ƀs�[�X��z�u
    if (Key.keyState[KEY_INPUT_P] == 1)
    {
        if (SetCheck())
        {
            ArrayAdd(pieceData[pieceNum], field, posX, posY);
            Debug("��������");
        }
        else
        {
            Debug("�����Ȃ���[��");
        }
    }

    // �������񂾂����
    HorizonCheck();

    // �z��`��
    ArrayDisp(dispField);

    // �X�R�A�`��
    DrawFormatString(100, 50, GetColor(255, 255, 255), "score : %d", score);
    DrawFormatString(300, 0, GetColor(255, 255, 255), "%s", debug.c_str());
}

// �z�񏉊���
void koko::ArrayZero(int array[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            array[i][j] = 0;
        }
    }
}

// �z��`��
void koko::ArrayDisp(int array[5][5])
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
                array[i][j]
            );
        }
    }
}

// �z����R�s�[
void koko::ArrayCopy(int fromArray[5][5], int toArray[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            toArray[i][j] = fromArray[i][j];
        }
    }
}

// �z����Z
void koko::ArrayAdd(int fromArray[5][5], int toArray[5][5], int offsetX, int offsetY)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j >= offsetX && i >= offsetY)
            {
                toArray[i][j] += fromArray[i - offsetY][j - offsetX];
            }
        }
    }
}

void koko::ArrayMul(int array[5][5], int value)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            array[i][j] *= value;
        }
    }
}

bool koko::SetCheck()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (dispField[i][j] == 3 || dispField[i][j] == 6)
            {
                return false;
            }
        }
    }
    return true;
}

void koko::Bar(int level)
{
    for (int i = 0; i < 5 - level; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            dispField[i][j] += 4;
        }
    }
}

void koko::HorizonCheck()
{
    int horizon = 0;
    bool line[4];
    for (int i = 0; i < 4; i++)
    {
        line[i] = false;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            horizon += field[i][j];
        }

        if (horizon == 5)
        {
            for (int j = 0; j < 5; j++)
            {
                field[i][j] = 0;
            }
            if (i != 0)
            {
                line[i - 1] = true;
            }
            score += 1;
            Debug("�����|�C���c�I");
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

void koko::LineDown(int line)
{
    for (int i = 0; i < 5; i++)
    {
        field[line + 1][i] = field[line][i];
        field[line][i] = 0;
    }
}

void koko::PlayerMove()
{
    // �L�[����
    if (Key.keyState[KEY_INPUT_D] == 1 && posX <= (4 - pieceSize[pieceNum][0]))
    {
        posX += 1;
    }

    if (Key.keyState[KEY_INPUT_S] == 1 && posY <= (4 - pieceSize[pieceNum][1]))
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

    // �s�[�X����ʊO�ɂ͂ݏo������C��
    if (posX + pieceSize[pieceNum][0] >= 6)
    {
        posX = 5 - pieceSize[pieceNum][0];
        Debug("�����AX�͂ݏo������");
    }
    if (posY + pieceSize[pieceNum][1] >= 6)
    {
        posY = 5 - pieceSize[pieceNum][1];
        Debug("�����AY�͂ݏo������");
    }
}

void koko::PlayerPosReset()
{
    posX = 0;
    posY = 5 - pieceSize[pieceNum][1];
}