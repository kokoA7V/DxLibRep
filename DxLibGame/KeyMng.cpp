
#include "KeyMng.h"

KeyMng Key;

KeyMng::KeyMng()
{

}

//�L�[���͏�Ԃ��X�V����֐�
void KeyMng::Update()
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