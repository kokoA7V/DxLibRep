#pragma once
#include"DxLib.h"

class Player {
private :
public :

	int pow = 0;

	int maxHp = 20;
	int nowHp = 20;

	// �ő�̎�D�̐�
	int maxHand = 5;

	// ��D�̖���
	int nowHands = 0;

	// �g�����Ƃ��Ă�J�[�h
	int setHand = 0;

	// ��D
	int hands[5] = { 0,0,0,0,0 };

	void Update();
	void HPDisp(int posX);

	// ��D�𐔂���
	int HowManyHands();

	// ����O�ɋl�߂�
	void CloseToTheFront(int line);

	// ��D������0������Ȃ�O�ɋl�߂郁�\�b�h���N������
	void HandZeroGo();

	//  ��D��\��������
	void DispHands(int posX);

	// ��D��I������
	void SelectHandPl1();
	void SelectHandPl2();

	void Draw();
};