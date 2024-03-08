#include <DxLib.h>
#include "TurnMng.h"
#include "CardGene.h"
#include "KeyMng.h"
#include "koko.h"
#include "Player.h"

TurnMng::TurnMng(){}

Player player;
Player player2;
koko kokoPl1;
koko kokoPl2;

void TurnMng::Init() {
	kokoPl1.Init();
	kokoPl2.Init();
}
void TurnMng::Update(){	
	
	// �f�o�b�N�p��pow�\��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "DEBUG:POW %d", pow);	

	// �p�Y���\��
	kokoPl1.Update(100, 80);
	kokoPl2.Update(800, 80);

	// ��D�\��
	player.DispHands(0);
	player2.DispHands(700);

	player.HPDisp(0);
	player2.HPDisp(200);
	switch (phaseNo)
	{
	case start:
		// �X�^�[�g�t�F�C�Y����

		// 0������Ȃ炻�̎��̐�����0�ɓ����
		player.HandZeroGo();
		player2.HandZeroGo();

		// �n���h�𐔂���
		player.nowHands = player.HowManyHands();
		player2.nowHands = player2.HowManyHands();
		
		DrawFormatString(400, 10, GetColor(255, 255, 255), "StartPhase : nowHands%d",player.nowHands);
		DrawFormatString(800, 10, GetColor(255, 255, 255), "nowHP%d", player2.nowHp);
		NextPhase();
		break;
		
	case attack:
		// �o�g���t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "AttackPhase");
		
		// �����̎����Ă�J�[�h�̍��v�U���͕�����Ƀ_���[�W��^����	
		if (battingfirst)
		{
			DrawFormatString(200, 0, GetColor(255, 255, 255), "%d", pow, "�_���[�W��^�����I�I");
		}
		
		
		NextPhase();
		break;
		
	case drow:
		// �h���[�t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "DrowPhase");
		
		// �J�[�h���ܖ��ɂȂ�悤�Ɉ���
		if (battingfirst) player.Draw();
		else player2.Draw();	
		
		NextPhase();
		break;
		
	case levelUp:
		// ���x���A�b�v�t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "LevelUpPhase");
		
		// �p�Y���̃��[��������
		if (battingfirst)kokoPl1.level++;
		else kokoPl2.level++;
		
		
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
		if (battingfirst)CardPlayPl1();
		else CardPlayPl2();
		
		NextPhase();
		break;
		
	case trush:
		// �g���b�V���t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "TrushPhase");
		//��D���̂Ă�

		// �J�[�h�I��
		player.SelectHandPl1();

		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			player.hands[player.setHand] = 0;
			player.nowHands = player.HowManyHands();
		}
		
		NextPhase();
		break;
	case end:
		DrawFormatString(400, 10, GetColor(255, 255, 255), "EndPhase");
		// �^�[���G���h����
		if (battingfirst)
		{
			battingfirst = false;
		}
		else
		{
			battingfirst = true;
		}
		phaseNo = 0;
		break;
	}
}

// ���̃^�[���ɐi��
void TurnMng::NextPhase() {
	if (Key.keyState[KEY_INPUT_RETURN] == 1) {
		phaseNo++;
		kokoPl1.isPlayer = false;
		kokoPl2.isPlayer = false;
		mode = 0;
	}
}

void TurnMng::CardPlayPl1() 
{
	DrawFormatString(50, 400, GetColor(255, 255, 255), "nowHands %d", player.nowHands);

	// �p�Y�����[�h�Ǝ�D�I�����[�h�؂�ւ�
	switch (mode)
	{
	case cardSelect:

		// �J�[�h�I��
		player.SelectHandPl1();

		// �J�[�h�̑I���փ��[�h�`�F���W
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			kokoPl1.isPlayer = true;
			mode++;
		}
		break;
	case pazzle:

		if (Key.keyState[KEY_INPUT_LSHIFT] == 1)
		{
			if (kokoPl1.SetCheck())
			{
				kokoPl1.PieceSet();
				kokoPl1.isPlayer = false;
				pow += player.hands[player.setHand];
				player.hands[player.setHand] = 0;
				player.HowManyHands();
				mode = 0;
			}
			else
			{
				DrawFormatString(400, 200, GetColor(255, 255, 255), "�I�P�i�C�I");
			}

		}
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			kokoPl1.isPlayer = false;
			mode = 0;
		}
		break;
	}
}

void TurnMng::CardPlayPl2()
{
	DrawFormatString(50, 400, GetColor(255, 255, 255), "nowHands %d", player2.nowHands);

	// �p�Y�����[�h�Ǝ�D�I�����[�h�؂�ւ�
	switch (mode)
	{
	case cardSelect:

		// �J�[�h�I��
		player2.SelectHandPl2();

		// �J�[�h�̑I���փ��[�h�`�F���W
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			kokoPl2.isPlayer = true;
			mode++;
		}
		break;
	case pazzle:

		if (Key.keyState[KEY_INPUT_RSHIFT] == 1)
		{
			if (kokoPl2.SetCheck())
			{
				kokoPl2.PieceSet();
				kokoPl2.isPlayer = false;
				pow += player2.hands[player2.setHand];
				player2.hands[player2.setHand] = 0;
				player2.HowManyHands();
				mode = 0;
			}
			else
			{
				DrawFormatString(400, 200, GetColor(255, 255, 255), "�I�P�i�C�I");
			}

		}
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			kokoPl2.isPlayer = false;
			mode = 0;
		}
		break;
	}
}