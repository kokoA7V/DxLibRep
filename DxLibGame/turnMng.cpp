#include <DxLib.h>
#include "turnMng.h"
#include "CardGene.h"
#include "KeyMng.h"
#include "koko.h"
#include "Player.h"

TurnMng::TurnMng(){}
Player player;
Player player2;
koko kokoPl1;
koko kokoPl;
void TurnMng::Update(){	
	
	// �f�o�b�N�p��pow�\��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "DEBUG:POW %d", pow);
	
	gKoko.Update(100, 80);
	gKoko.Update(800, 80);

	// ��D�\��
	DispHandsPl1(0);
	DispHandsPl2(700);

	player.HPDisp(0);
	player2.HPDisp(200);
	switch (phaseNo)
	{
	case start:
		// �X�^�[�g�t�F�C�Y����

		// 0������Ȃ炻�̎��̐�����0�ɓ����
		HandZeroGo();

		// �n���h�𐔂���
		nowHandsPl1 = HowManyHands();
		
		DrawFormatString(400, 10, GetColor(255, 255, 255), "StartPhase : nowHands%d", nowHandsPl1);
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			player2.nowHp--;
		}
		DrawFormatString(800, 10, GetColor(255, 255, 255), "nowHP%d", player2.nowHp);
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
		for (nowHandsPl1; nowHandsPl1 < maxHand; )
		{
			if (handsPl1[nowHandsPl1] <= 0)
			{
				int hand = DeckGene.hand_card();
				handsPl1[nowHandsPl1] = hand;	
			}
			else
			{
				nowHandsPl1++;
			}

		}
		for (nowHandsPl2; nowHandsPl2 < maxHand; )
		{
			if (handsPl2[nowHandsPl2] <= 0)
			{
				int hand = DeckGene.hand_card();
				handsPl2[nowHandsPl2] = hand;
			}
			else
			{
				nowHandsPl2++;
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
		


		DrawFormatString(50, 400, GetColor(255, 255, 255), "nowHands %d", nowHandsPl1);


		
		// �p�Y�����[�h�Ǝ�D�I�����[�h�؂�ւ�
		switch (mode)
		{
		case cardSelect:
						

			// �J�[�h�I��
			SelectHandPl1();

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
					pow += handsPl1[setHandPl1];
					handsPl1[setHandPl1] = 0;
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
		SelectHandPl1();

		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			handsPl1[setHandPl1] = 0;
			HowManyHands();
		}

		
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
		if (handsPl1[i] > 0)
		{
			manyHands++;
		}
	}
	return  manyHands;
}

// ������O�ɋl�߂�
void TurnMng::CloseToTheFront(int line) {
	handsPl1[line - 1] = handsPl1[line];
	handsPl1[line] = 0;
}

// 0���������琔����O�ɋl�߂�X�N���v�g���N��
void TurnMng::HandZeroGo(){
	for (int i = 0; i < maxHand - 1; ++i)
	{
		if (handsPl1[i] == 0)
		{
			CloseToTheFront(i + 1);
		}
	}
}

// ��D��\��������
void TurnMng::DispHandsPl1(int posX) {
	DrawFormatString(400, 400, GetColor(255, 255, 255), "setHands %d", handsPl1[setHandPl1]);

	for (int i = 0; i < nowHandsPl1; i++)
	{
		// �I�����Ă�Ȃ當����ԐF��
		if (setHandPl1 == i)
		{
			DrawFormatString(i * 100 + 50 + posX, 500, GetColor(255, 0, 0), "�U���� %d", handsPl1[i]);
			DrawFormatString(i * 100 + 50 + posX, 550, GetColor(255, 0, 0), "�ԍ� %d", i);
		}
		else
		{
			DrawFormatString(i * 100 + 50 + posX, 500, GetColor(255, 255, 255), "�U���� %d", handsPl1[i]);
			DrawFormatString(i * 100 + 50 + posX, 550, GetColor(255, 255, 255), "�ԍ� %d", i);
		}
	}
}

void TurnMng::DispHandsPl2(int posX) {
	DrawFormatString(400, 400, GetColor(255, 255, 255), "setHands %d", handsPl2[setHandPl2]);

	for (int i = 0; i < nowHandsPl2; i++)
	{
		// �I�����Ă�Ȃ當����ԐF��
		if (setHandPl2 == i)
		{
			DrawFormatString(i * 100 + 50 + posX, 500, GetColor(255, 0, 0), "�U���� %d", handsPl2[i]);
			DrawFormatString(i * 100 + 50 + posX, 550, GetColor(255, 0, 0), "�ԍ� %d", i);
		}
		else
		{
			DrawFormatString(i * 100 + 50 + posX, 500, GetColor(255, 255, 255), "�U���� %d", handsPl2[i]);
			DrawFormatString(i * 100 + 50 + posX, 550, GetColor(255, 255, 255), "�ԍ� %d", i);
		}
	}
}

// �J�[�h�I��
void TurnMng::SelectHandPl1() {
	if (Key.keyState[KEY_INPUT_D] == 1)
	{
		if (setHandPl1 < maxHand - 1)
		{
			setHandPl1++;
		}
		else
		{
			setHandPl1 = 0;
		}
	}

	if (Key.keyState[KEY_INPUT_A] == 1)
	{
		if (setHandPl1 > 0)
		{
			setHandPl1--;
		}
		else
		{
			setHandPl1 = 4;
		}
	}
}

void TurnMng::SelectHandPl2() {
	if (Key.keyState[KEY_INPUT_RIGHT] == 1)
	{
		if (setHandPl2 < maxHand - 1)
		{
			setHandPl2++;
		}
		else
		{
			setHandPl2 = 0;
		}
	}

	if (Key.keyState[KEY_INPUT_LEFT] == 1)
	{
		if (setHandPl2 > 0)
		{
			setHandPl2--;
		}
		else
		{
			setHandPl2 = 4;
		}
	}
}