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

	// �p�Y���p�摜
	int boxHandle[7] = { 0, 0, 0, 0, 0, 0, 0 };
};

extern ResourceMng rm;