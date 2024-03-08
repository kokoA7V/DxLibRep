#pragma once
#include"DxLib.h"
#include<List>
#include<string>

class TurnMng {
private:
public:
	int pow = 0;

	bool battingfirst = true;
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

	enum Mode {
		cardSelect,
		pazzle,
	};
	int mode = 0;
	
	// コンストラクタ
	TurnMng();
	
	// アップデート
	void Update();
	
	// 次のターンへ
	void NextPhase();;

	void Init();

	void CardPlayPl1();
	void CardPlayPl2();
};