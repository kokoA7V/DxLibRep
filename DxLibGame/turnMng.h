#pragma once
#include"DxLib.h"
#include<List>
#include<string>

class TurnMng {
private:
	const int maxHand = 4;
public:
	// ��D�̖���
	int nowHands = 0;
	// �g�����Ƃ��Ă�J�[�h
	int setHand = 0;
	// ��D
	int hands[5] = {0,0,0,0,0};
	// �^����_���[�W
	int pow = 0;

	// �t�F�C�Y
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