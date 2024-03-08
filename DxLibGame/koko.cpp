
#include "koko.h"
#include "KeyMng.h"
#include "ResourceMng.h"

koko gKoko;
ResourceMng rm;

koko::koko() { }

void koko::Debug(string str)
{
    debug += str + "\n";
}

void koko::Init()
{

    level = 0;

    pieceNum = 0;

    PiecePosReset();

    isPlayer = false;

    Debug("�f�o�b�O����");
}

void koko::Update(int posX, int posY)
{
    // �\���p�z�񏉊���
    ArrayZero(dispField);

    // �Ֆʂ��R�s�[
    ArrayCopy(field, dispField);

    // �o�[���R�s�[
    LevelLine(level);

    if (isPlayer)
    {
        PlayerUpdate();
    }

    // �������񂾂����
    HorizonCheck();

    // �z��`��
    ArrayDisp(dispField, posX, posY);
}

void koko::PlayerUpdate()
{
    // �s�[�X�ړ�
    PieceMove();

    // �s�[�X�\��
    ArrayCopy(pieceData[pieceNum], plPiece);
    ArrayMul(plPiece, 2);
    ArrayAdd(plPiece, dispField, posX, posY);

}

void koko::TestUpdate()
{
    PieceMove();

    if (Key.keyState[KEY_INPUT_0] == 1)
    {
        if (isPlayer) { isPlayer = false; }
        else { isPlayer = true; }
    }

    // �s�[�X�ύX
    if (Key.keyState[KEY_INPUT_0] == 1)
    {
        pieceNum = 0;
        PiecePosReset();
        Debug("�s�[�X0�ɕύX");
    }
    if (Key.keyState[KEY_INPUT_1] == 1)
    {
        pieceNum = 1;
        PiecePosReset();
        Debug("�s�[�X1�ɕύX");
    }
    if (Key.keyState[KEY_INPUT_2] == 1)
    {
        pieceNum = 2;
        PiecePosReset();
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

    // �Ֆʂ��R�s�[
    ArrayCopy(field, dispField);

    // �o�[���R�s�[
    LevelLine(level);

    // Player�s�[�X���R�s�[
    ArrayCopy(pieceData[pieceNum], plPiece);
    ArrayMul(plPiece, 2);
    ArrayAdd(plPiece, dispField, posX, posY);


    // ���݈ʒu�Ƀs�[�X��z�u�@�N��������Z�b�g����悤�ɕς���by���
    //PieceSet();
    if (Key.keyState[KEY_INPUT_P] == 1)
    {
       PieceSet();
    }

    // �������񂾂����
    HorizonCheck();

    // ���z��`��
    // ArrayDemoDisp(dispField, 100, 50);

    // �z��`��
    ArrayDisp(dispField, 100, 150);

    // �X�R�A�`��
    DrawFormatString(100, 25, GetColor(255, 255, 255), "score : %d", score);
    DrawFormatString(300, 0, GetColor(255, 255, 255), "%s", debug.c_str());
}

// �z�񏉊���
void koko::ArrayZero(int array[fieldSizeY][fieldSizeX])
{
    for (int y = 0; y < fieldSizeX; y++)
    {
        for (int x = 0; x < fieldSizeY; x++)
        {
            array[y][x] = 0;
        }
    }
}

// �z�񉼕`��
void koko::ArrayDemoDisp(int array[fieldSizeY][fieldSizeX], int posX, int posY)
{
    int space = 15;

    for (int y = 0; y < fieldSizeX; y++)
    {
        for (int x = 0; x < fieldSizeY; x++)
        {
            DrawFormatString
            (
                posX + (x * space),
                posY + (y * space),
                GetColor(255, 255, 255),
                "%d",
                array[y][x]
            );
        }
    }
}

// �C���X�g�z��`��
void koko::ArrayDisp(int array[fieldSizeY][fieldSizeX], int posX, int posY)
{
    int space = 64;

    for (int y = 0; y < fieldSizeX; y++)
    {
        for (int x = 0; x < fieldSizeY; x++)
        {
            if (!SetCheck() && array[y][x] == 2)
            {
                DrawGraph
                (
                    posX + (x * space),
                    posY + (y * space),
                    rm.boxHandle[5],
                    0
                );
            }
            else
            {
                DrawGraph
                (
                    posX + (x * space),
                    posY + (y * space),
                    rm.boxHandle[array[y][x]],
                    0
                );
            }
        }
    }
}

// �z����R�s�[
void koko::ArrayCopy(int fromArray[fieldSizeY][fieldSizeX], int toArray[fieldSizeY][fieldSizeY])
{
    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            toArray[y][x] = fromArray[y][x];
        }
    }
}

// �z����Z
void koko::ArrayAdd(int fromArray[fieldSizeY][fieldSizeX], int toArray[fieldSizeY][fieldSizeX], int offsetX, int offsetY)
{
    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            if (x >= offsetX && y >= offsetY)
            {
                toArray[y][x] += fromArray[y - offsetY][x - offsetX];
            }
        }
    }
}

// �z�񂩂��Z
void koko::ArrayMul(int array[fieldSizeY][fieldSizeX], int value)
{
    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            array[y][x] *= value;
        }
    }
}

// �v���C���[�s�[�X���ݒu�ς݃s�[�X�ɔ���ĂȂ����m�F
// true�Œu���Ă��悢�Afalse�͔���Ă�
bool koko::SetCheck()
{
    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            if (dispField[y][x] == 3 || dispField[y][x] == 6)
            {
                return false;
            }
        }
    }

    if (!isPlayer) { return false; }

    return true;
}

// field�Ƀs�[�X��z�u
void koko::PieceSet()
{
    // ���݈ʒu�Ƀs�[�X��z�u
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

// ������0~5
// �����珇�Ɏg����悤�ɂȂ�
void koko::LevelLine(int level)
{
    for (int y = 0; y < fieldSizeY - level; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            dispField[y][x] += 4;
        }
    }
}

// �������񂾎��̏���
void koko::HorizonCheck()
{
    int horizon = 0;
    bool line[4];
    for (int i = 0; i < 4; i++)
    {
        line[i] = false;
    }

    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            horizon += field[y][x];
        }

        if (horizon == 5)
        {
            for (int x = 0; x < fieldSizeX; x++)
            {
                field[y][x] = 0;
            }
            if (y != 0)
            {
                line[y - 1] = true;
            }

            // �����������Ƃ��̏���
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

// ������0~3�i4������ƃt�B�[���h�͈͊O�ɂȂ�j
// �w��������ֈړ��A�w�����O��
void koko::LineDown(int line)
{
    for (int x = 0; x < fieldSizeX; x++)
    {
        field[line + 1][x] = field[line][x];
        field[line][x] = 0;
    }
}

// �s�[�X�T�C�Y�o��
// YorX = 0 : out Y
// YorX = 1 : out X
int koko::PieceSize(int num, int YorX)
{
    int sizeY = 0;
    int sizeX = 0;

    for (int y = 0; y < fieldSizeY; y++)
    {
        for (int x = 0; x < fieldSizeX; x++)
        {
            if (pieceData[num][y][x] >= 1)
            {
                if (x > sizeX)
                {
                    sizeX = x;
                }

                if (y > sizeY)
                {
                    sizeY = y;
                }
            }
        }
    }

    sizeY++;
    sizeX++;

    if (YorX == 0) { return sizeY; }
    if (YorX == 1) { return sizeX; }
}

// �s�[�X�ړ�
void koko::PieceMove()
{
    // �L�[����
    if (Key.keyState[KEY_INPUT_D] == 1 && posX <= ((fieldSizeX - 1) - PieceSize(pieceNum, 1)))
    {
        posX += 1;
    }

    if (Key.keyState[KEY_INPUT_S] == 1 && posY <= ((fieldSizeY - 1) - PieceSize(pieceNum, 0)))
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
    if (posX + PieceSize(pieceNum, 1) >= fieldSizeX + 1)
    {
        posX = fieldSizeX - PieceSize(pieceNum, 1);
        Debug("�����AX�͂ݏo������");
    }
    if (posY + PieceSize(pieceNum, 0) >= fieldSizeY + 1)
    {
        posY = fieldSizeY - PieceSize(pieceNum, 0);
        Debug("�����AY�͂ݏo������");
    }
}

// �s�[�X�������ֈړ�
void koko::PiecePosReset()
{
    posX = 0;
    posY = fieldSizeY - PieceSize(pieceNum, 0);
}