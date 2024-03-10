#pragma once

#include "DxLib.h"

class ResourceMng
{
private:
public:

	ResourceMng();
	void Init();

	// 背景
	int backGround;

	// スタート画面ボタン
	int sellectButton[2];

	// 0:under
	// 1:fw
	// 2:sp
	// 3:time
	int stats[4];

	// パズル用画像
	int boxHandle[7] = { 0, 0, 0, 0, 0, 0, 0 };
};

extern ResourceMng rm;