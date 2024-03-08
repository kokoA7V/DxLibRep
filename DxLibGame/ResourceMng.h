#pragma once

#include "DxLib.h"

class ResourceMng
{
private:
public:

	ResourceMng();
	void Init();

	// ”wŒi
	int backGround;

	// ƒpƒYƒ‹—p‰æ‘œ
	int boxHandle[7] = { 0, 0, 0, 0, 0, 0, 0 };
};

extern ResourceMng rm;