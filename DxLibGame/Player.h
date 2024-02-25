#pragma once
#include"DxLib.h"

class Player {
private :
public :
	int maxHp = 20;
	int nowHp = 20;

	void Update();
	void HPDisp(int posX);
};