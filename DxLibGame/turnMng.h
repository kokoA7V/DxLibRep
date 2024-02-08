#pragma once
#include"DxLib.h"

class turnMng {
private:
public:
	// フェイズ
	enum Phase{
		start,
		attack,
		draw,
		levelUp,
		main,
		trush,
		end,
		phaseTotalNum,
	};
	int phaseNo = 0;
	void Update(Phase);
};

