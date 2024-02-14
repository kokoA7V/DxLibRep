#pragma once
#include"DxLib.h"
#include<List>
#include<string>

class TurnMng {
private:
	const int maxHand = 4;
public:
	// 手札の枚数
	int nowHands = 0;
	// 使おうとしてるカード
	int setHand = 0;
	// 手札
	int hands[5] = {0,0,0,0,0};
	// 与えるダメージ
	int pow = 0;

	// フェイズ
	enum Phase{
		start,
		attack,
		drow,
		levelUp,
		main,
		trush,
		end,
		phaseTotalNum,
	};
	int phaseNo = 0;
	TurnMng();
	void Update();
	void NextPhase();
	int howManyHands();
};