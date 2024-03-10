
#include "ResourceMng.h"

ResourceMng::ResourceMng() {};

void ResourceMng::Init()
{
    backGround = LoadGraph("Sprite/BackGround.PNG");

    sellectButton[0] = LoadGraph("Sprite/SellectButton0.PNG");
    sellectButton[1] = LoadGraph("Sprite/SellectButton1.PNG");

    stats[0] = LoadGraph("Sprite/Stats_Under.PNG");
    stats[1] = LoadGraph("Sprite/Stats_FW.PNG");
    stats[2] = LoadGraph("Sprite/Stats_SP.PNG");
    stats[3] = LoadGraph("Sprite/Stats_Time.PNG");

    // ƒpƒYƒ‹—p‰æ‘œ
    boxHandle[0] = LoadGraph("Sprite/box0.PNG");
    boxHandle[1] = LoadGraph("Sprite/box1.PNG");
    boxHandle[2] = LoadGraph("Sprite/box2.PNG");
    boxHandle[3] = LoadGraph("Sprite/box3.PNG");
    boxHandle[4] = LoadGraph("Sprite/box4.PNG");
    boxHandle[5] = LoadGraph("Sprite/box5.PNG");
    boxHandle[6] = LoadGraph("Sprite/box6.PNG");
}