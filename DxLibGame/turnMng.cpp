#include <DxLib.h>
#include "turnMng.h"
#include "CardGene.h"
#include "KeyMng.h"
#include "koko.h"

TurnMng::TurnMng(){}

void TurnMng::Update(){	

	// �f�o�b�N�p��pow�\��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "DEBUG:POW %d", pow);
	
	switch (phaseNo)
	{
	case start:
		// �X�^�[�g�t�F�C�Y����

		// 0������Ȃ炻�̎��̐�����0�ɓ����
		HandZeroGo();

		// �n���h�𐔂���
		nowHands = HowManyHands();
		
		DrawFormatString(400, 10, GetColor(255, 255, 255), "StartPhase : nowHands%d", nowHands);
		
		NextPhase();
		break;
		
	case attack:
		// �o�g���t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "AttackPhase");
		
		// �����̎����Ă�J�[�h�̍��v�U���͕�����Ƀ_���[�W��^����	
		DrawFormatString(200, 0, GetColor(255, 255, 255), "%d",pow,"�_���[�W��^�����I�I");
		
		NextPhase();
		break;
		
	case drow:
		pow = 0;
		// �h���[�t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "DrowPhase");
		
		// �J�[�h���ܖ��ɂȂ�悤�Ɉ���
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
		
		NextPhase();
		break;
		
	case levelUp:
		// ���x���A�b�v�t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "LevelUpPhase");
		
		// �p�Y���̃��[��������
		gKoko.level++;
		
		phaseNo++;
		//NextPhase();
		break;
	case main:
		// ���C���t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "MainPhase\n�X�y�[�X�Ő؂�ւ�\n");
		if (mode == pazzle)
		{
			DrawFormatString(400, 70, GetColor(255, 255, 255), "�p�Y�����[�h");
		}
		else
		{
			DrawFormatString(400, 70, GetColor(255, 255, 255), "�J�[�h�I�����[�h");
		}
		
		// ��D�\��
		DispHands();

		DrawFormatString(50, 400, GetColor(255, 255, 255), "nowHands %d", nowHands);

		// koko�A�b�v�f�[�g���R�R�ֈړ� by koko
		gKoko.Update(0, 0);
		
		// �p�Y�����[�h�Ǝ�D�I�����[�h�؂�ւ�
		switch (mode)
		{
		case cardSelect:
						

			// �J�[�h�I��
			SelectHand();

			// �J�[�h�̑I���փ��[�h�`�F���W
			if (Key.keyState[KEY_INPUT_SPACE] == 1)
			{
				gKoko.isPlayer = true;
				mode++;
			}
			break;
		case pazzle:
			
			
			// gKoko.Update();
			if (Key.keyState[KEY_INPUT_LSHIFT] == 1)
			{
				if (gKoko.SetCheck())
				{
					gKoko.PieceSet();
					gKoko.isPlayer = false;
					pow += hands[setHand];
					hands[setHand] = 0;
					HowManyHands();
					mode = 0;
				}
				else
				{
					DrawFormatString(400, 200, GetColor(255, 255, 255), "�I�P�i�C�I");
				}
				
			}
			if (Key.keyState[KEY_INPUT_SPACE] == 1)
			{
				gKoko.isPlayer = false;
				mode = 0;
			}
			break;
		}
		
		NextPhase();
		break;
		
	case trush:
		// �g���b�V���t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "TrushPhase");
		//��D���̂Ă�

		// �J�[�h�I��
		SelectHand();

		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			hands[setHand] = 0;
			HowManyHands();
		}

		// ��D�\��
		DispHands();
		
		NextPhase();
		break;
	case end:
		DrawFormatString(400, 10, GetColor(255, 255, 255), "EndPhase");
		// �^�[���G���h����
		phaseNo = 0;
		break;
	}
}

// ���̃^�[���ɐi��
void TurnMng::NextPhase() {
	if (Key.keyState[KEY_INPUT_RETURN] == 1)phaseNo++;
}

// ��D�̐��𐔂��郁�\�b�h
int TurnMng::HowManyHands() {
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
void TurnMng::CloseToTheFront(int line) {
	hands[line - 1] = hands[line];
	hands[line] = 0;
}

// 0���������琔����O�ɋl�߂�X�N���v�g���N��
void TurnMng::HandZeroGo(){
	for (int i = 0; i < maxHand - 1; ++i)
	{
		if (hands[i] == 0)
		{
			CloseToTheFront(i + 1);
		}
	}
}

// ��D��\��������
void TurnMng::DispHands() {
	DrawFormatString(400, 400, GetColor(255, 255, 255), "setHands %d", hands[setHand]);

	for (int i = 0; i < nowHands; i++)
	{
		// �I�����Ă�Ȃ當����ԐF��
		if (setHand == i)
		{
			DrawFormatString(i * 100 + 50, 300, GetColor(255, 0, 0), "�U���� %d", hands[i]);
			DrawFormatString(i * 100 + 50, 350, GetColor(255, 0, 0), "�ԍ� %d", i);
		}
		else
		{
			DrawFormatString(i * 100 + 50, 300, GetColor(255, 255, 255), "�U���� %d", hands[i]);
			DrawFormatString(i * 100 + 50, 350, GetColor(255, 255, 255), "�ԍ� %d", i);
		}
	}
}

// �J�[�h�I��
void TurnMng::SelectHand() {
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