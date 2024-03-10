#pragma once
#include"DxLib.h"
#include<List>
#include<string>
#include"CardList.h"

class TurnMng {
private:
public:

	int phaseDispX = 570;
	int phaseDispY = 300;

	/*string phaseText[14];*/

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

	void PhaseDisp();
};