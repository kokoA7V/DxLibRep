#pragma once
#include "DxLib.h"

class KeyMng
{
private:
public:
	//�L�[�擾�p�̔z��
	char buf[256] = { 0 };
	int keyState[256] = { 0 };

	KeyMng();

	void KeyUpdate();

};

extern KeyMng gKeyMng;