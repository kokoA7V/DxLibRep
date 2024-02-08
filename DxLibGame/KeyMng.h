#pragma once
#include "DxLib.h"

class KeyMng
{
private:
public:
	//キー取得用の配列
	char buf[256] = { 0 };
	int keyState[256] = { 0 };

	KeyMng();

	void KeyUpdate();

};

extern KeyMng gKeyMng;