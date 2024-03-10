#include"Player.h"
#include "KeyMng.h"
#include "CardGene.h"

// �ǋL by koko
#include "ResourceMng.h"

void Player::Update() {

}

void Player::HPDisp(int posX) {

	////
	// �\���ύX by koko
	for (int i = 0; i < nowHp; i++)
	{
		DrawGraph(posX, 500 - i * 20, rm.stats[1], 0);
	}
	// ���R�[�h
	//for ( int i=0; i < nowHp; i++)
	//{
	//	DrawFormatString(500 + posX, 450 - i * 20, GetColor(255, 255, 255), "��");
	//}
	////
}

// ��D�̐��𐔂��郁�\�b�h
int Player::HowManyHands() {
	int manyHands = 0;
	for (int i = 0; i < maxHand; ++i)
	{
		if (hands[i] > 0)
		{
			manyHands++;
		}
	}
	return  manyHands;
}

// ������O�ɋl�߂�
void Player::CloseToTheFront(int line) {
	hands[line - 1] = hands[line];
	hands[line] = 0;
}

// 0���������琔����O�ɋl�߂�X�N���v�g���N��
void Player::HandZeroGo() {
	for (int i = 0; i < maxHand - 1; ++i)
	{
		if (hands[i] == 0)
		{
			CloseToTheFront(i + 1);
		}
	}
}

// ��D��\��������
void Player::DispHands(int posX) {
	DrawFormatString(400, 400, GetColor(255, 255, 255), "setHands %d", hands[setHand]);

	for (int i = 0; i < nowHands; i++)
	{
		// �I�����Ă�Ȃ當����ԐF��
		if (setHand == i)
		{
			DrawFormatString(i * 100 + 50 + posX, 500, GetColor(255, 0, 0), "�U���� %d", hands[i]);
			DrawFormatString(i * 100 + 50 + posX, 550, GetColor(255, 0, 0), "�ԍ� %d", i);
		}
		else
		{
			DrawFormatString(i * 100 + 50 + posX, 500, GetColor(255, 255, 255), "�U���� %d", hands[i]);
			DrawFormatString(i * 100 + 50 + posX, 550, GetColor(255, 255, 255), "�ԍ� %d", i);
		}
	}
}

void Player::SelectHandPl1() {
	if (Key.keyState[KEY_INPUT_D] == 1)
	{
		if (setHand < maxHand - 1)
		{
			setHand++;
		}
		else
		{
			setHand = 0;
		}
	}

	if (Key.keyState[KEY_INPUT_A] == 1)
	{
		if (setHand > 0)
		{
			setHand--;
		}
		else
		{
			setHand = 4;
		}
	}
}

void Player::SelectHandPl2() {
	if (Key.keyState[KEY_INPUT_RIGHT] == 1)
	{
		if (setHand < maxHand - 1)
		{
			setHand++;
		}
		else
		{
			setHand = 0;
		}
	}

	if (Key.keyState[KEY_INPUT_LEFT] == 1)
	{
		if (setHand > 0)
		{
			setHand--;
		}
		else
		{
			setHand = 4;
		}
	}
}

void Player::Draw() {
	for (nowHands; nowHands < maxHand; )
	{
		if (hands[nowHands] <= 0)
		{
			int hand = DeckGene.hand_card();
			hands[nowHands] = hand;
		}
		else
		{
			nowHands++;
		}

	}
}