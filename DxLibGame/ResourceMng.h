#pragma once

#include "DxLib.h"

class ResourceMng
{
private:
public:

	ResourceMng();
	void Init();

	// �w�i
	int backGround;

	// �X�^�[�g��ʃ{�^��
	int sellectButton[2];

	// 0:under
	// 1:fw
	// 2:sp
	// 3:time
	int stats[4];

	// �p�Y���p�摜
	int boxHandle[7] = { 0, 0, 0, 0, 0, 0, 0 };
};

extern ResourceMng rm;