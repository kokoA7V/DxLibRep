#pragma once
#include <random> //��������
#include "DxLib.h"
#include"iostream"

//�J�[�h�r�o�N���X
// �Q�l�T�C�g�@
// https://tora-k.com/2020/04/06/cardclass/
class CardGene {
private:
	int MinDeck = 1;
	int card_num; //�J�[�h����
	int* deck; //�i�[�z��
	int* p_deck; //�z��擪�|�C���^
public:
	//�R���X�g���N�^�F�����̓f�b�L��
	CardGene();
	//�f�X�g���N�^
	//�J�[�h�̔r�o
	int hand_card();
};
extern CardGene DeckGene;