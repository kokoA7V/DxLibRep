
#include "KeyMng.h"

KeyMng Key;

KeyMng::KeyMng()
{

}

//キー入力状態を更新する関数
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