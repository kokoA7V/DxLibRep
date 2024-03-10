#include <DxLib.h>
#include "TurnMng.h"
#include "CardGene.h"
#include "KeyMng.h"
#include "koko.h"
#include "Player.h"
#include "CardList.h"
#include "Decoy.h"

// �ǋL by koko
#include "ResourceMng.h"

TurnMng::TurnMng(){}

Player player;
Player player2;
koko kokoPl1;
koko kokoPl2;

Decoy decoy;

CardList gCardList;

void TurnMng::Init() {
	kokoPl1.Init();
	kokoPl2.Init();
	
	//phaseText[0]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "StartPhase");
	//phaseText[1]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > StartPhase < ");
	//phaseText[2]= DrawFormatString(phaseDispX, 40, GetColor(255, 255, 255), "AttackPhase");
	//phaseText[3]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > AttackPhase < ");
	//phaseText[4]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "DrowPhase");
	//phaseText[5]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > DrowPhase < ");
	//phaseText[6]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "LevelUpPhase");
	//phaseText[7]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > LevelUpPhase < ");
	//phaseText[8]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "MainPhase");
	//phaseText[9]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > MainPhase < ");
	//phaseText[10]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "TrushPhase");
	//phaseText[11]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > TrushPhase < ");
	//phaseText[12]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "EndPhase");
	//phaseText[13]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > EndPhase < ");
}
void TurnMng::Update(){	
	
	// �t�F�C�Y�\��
	PhaseDisp();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d",player.pow);


	
	if (Key.keyState[KEY_INPUT_SPACE] == 1)
	{
		player.pow = decoy.CardEffect(player);
	}
	if (Key.keyState[KEY_INPUT_E] == 1)
	{
		gCardList.fieldCardList.clear();
	}

	for (int i = 0; i < gCardList.fieldCardList.size(); i++)
	{
		DrawFormatString(500 , 450 - i * 20, GetColor(255, 255, 255), "��");
	}

	// �f�o�b�N�p��pow�\��
	/*DrawFormatString(0, 0, GetColor(255, 255, 255), "DEBUG:POW %d", pow);*/	

	// �p�Y���\��
	////
	// �ʒu�ύX by koko
	kokoPl1.Update(130, 250);
	kokoPl2.Update(830, 250);
	// ���ʒu
	//kokoPl1.Update(100, 80);
	//kokoPl2.Update(800, 80);
	////

	// ������HP�g�\�L�ǉ� by koko
	DrawGraph(20, 120, rm.stats[0], 0);
	DrawGraph(1180, 120, rm.stats[0], 0);

	// ��D�\��
	player.DispHands(0);
	player2.DispHands(700);

	////
	// �\�L�ύX by koko
	player.HPDisp(60);
	player2.HPDisp(1220);
	// �ύX�O
	//player.HPDisp(0);
	//player2.HPDisp(200);
	////

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

		NextPhase();
		break;
		
	case attack:
		// �o�g���t�F�C�Y����
		
		// �����̎����Ă�J�[�h�̍��v�U���͕�����Ƀ_���[�W��^����	
		if (battingfirst)
		{
			DrawFormatString(200, 0, GetColor(255, 255, 255), "%d", pow, "�_���[�W��^�����I�I");
		}		
		
		NextPhase();
		break;
		
	case drow:
		// �h���[�t�F�C�Y����
		
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

void TurnMng::PhaseDisp() {
	switch (phaseNo)
	{
	case start:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), " > StartPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case attack:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), " > AttackPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case drow:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), " > DrowPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case levelUp:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), " > LevelUpPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case main:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), " > MainPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case trush:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), " > TrushPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case end:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), " > EndPhase < ");
		break;
	}
}