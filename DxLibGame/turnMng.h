#pragma once
#include"DxLib.h"
#include<List>
#include<string>

class TurnMng {
private:
public:
	///* �ő�̎�D�̐�
 //   int maxHand = 5;
	//
	// ��D�̖���
	//int nowHandsPl1 = 0;
	//int nowHandsPl2 = 0;
	//
	// �g�����Ƃ��Ă�J�[�h
	//int setHandPl1 = 0;
	//int setHandPl2 = 0;
	//
	// ��D
	//int handsPl1[5] = {0,0,0,0,0};
	//int handsPl2[5] = {0,0,0,0,0};*/
	
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
	
	//// ��D�𐔂���
	//int HowManyHands();
	//
	//// ����O�ɋl�߂�
	//void CloseToTheFront(int line);
	//
	//// ��D������0������Ȃ�O�ɋl�߂郁�\�b�h���N������
	//void HandZeroGo();
	//
	////  ��D��\��������
	//void DispHandsPl1(int posX);
	//void DispHandsPl2(int posX);
	//
	//// ��D��I������
	//void SelectHandPl1();
	//void SelectHandPl2();

	void Init();
};