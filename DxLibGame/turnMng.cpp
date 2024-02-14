#include<DxLib.h>
#include"turnMng.h"
#include"CardGene.h"
#include "KeyMng.h"

TurnMng::TurnMng(){

}

void TurnMng::Update(){
	DrawFormatString(500, 30, GetColor(255, 255, 255), "POW %d", pow);
	switch (phaseNo)
	{		

	case start:
		// �X�^�[�g�t�F�C�Y����
		setHand = 0;
		DrawFormatString(400, 10, GetColor(255, 255, 255), "StartPhase");
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
		// �h���[�t�F�C�Y����
		pow = 0;
		DrawFormatString(400, 10, GetColor(255, 255, 255), "DrowPhase");
		// �J�[�h���ܖ��ɂȂ�悤�Ɉ���
		for (nowHands; nowHands <= maxHand; )
		{
			if (hands[setHand] > 0)
			{
				int hand = DeckGene.hand_card();
				hands[nowHands] = hand;
				nowHands++; 			
			}
			else
			{
				setHand++;
			}
		}
		
		NextPhase();
		break;
		
	case levelUp:
		// ���x���A�b�v�t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "LevelUpPhase");
		// �p�Y���̃��[��������
		NextPhase();
		break;
		
	case main:
		// ���C���t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "MainPhase");
		// �J�[�h�I��
		if (Key.keyState[KEY_INPUT_UP] == 1)
		{
			if (setHand < maxHand)
			{
				setHand++;
			}
		}
		if (Key.keyState[KEY_INPUT_DOWN] == 1)
		{
			if (setHand > 0)
			{
				setHand--;
			}
		}

		DrawFormatString(200, 300, GetColor(255, 255, 255), "CardNum %d", hands[setHand]);
		DrawFormatString(400, 300, GetColor(255, 255, 255), "nowHand %d", setHand);

		// �J�[�h�̃v���C
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			pow += hands[setHand];
			hands[setHand] = 0;
			nowHands--;
		}
		
		NextPhase();
		break;
		
	case trush:
		// �g���b�V���t�F�C�Y����
		DrawFormatString(400, 10, GetColor(255, 255, 255), "TrushPhase");
		//��D���̂Ă�
		NextPhase();
		break;
	case end:
		DrawFormatString(400, 10, GetColor(255, 255, 255), "EndPhase");
		// �^�[���G���h����
		phaseNo = 0;
		break;
	}
}

void TurnMng::NextPhase() {
	if (Key.keyState[KEY_INPUT_RETURN] == 1)phaseNo++;
}