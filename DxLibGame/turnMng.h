#pragma once
#include"DxLib.h"
#include<List>
#include<string>

class TurnMng {
private:
public:
	// �ő�̎�D�̐�
    int maxHand = 5;
	// ��D�̖���
	int nowHands = 0;
	// �g�����Ƃ��Ă�J�[�h
	int setHand = 0;
	// ��D
	int hands[5] = {0,0,0,0,0};
	// �^����_���[�W(��)
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

	enum Mode {
		cardSelect,
		pazzle,
	};
	int mode = 0;
	// �R���X�g���N�^
	TurnMng();
	// �A�b�v�f�[�g
	void Update();
	// ���̃^�[����
	void NextPhase();
	// ��D�𐔂���
	int HowManyHands();
	// ����O�ɋl�߂�
	void CloseToTheFront(int line);
	// ��D������0������Ȃ�O�ɋl�߂郁�\�b�h���N������
	void HandZeroGo();
};