#include<DxLib.h>
#include"turnMng.h"

void turnMng::Update(Phase _phaseNo){
	phaseNo = _phaseNo;
	switch (phaseNo)
	{
		// �X�^�[�g�t�F�C�Y����
	case start:
		phaseNo++;
		break;
		// �o�g���t�F�C�Y����
	case attack:
		
		break;
		// �h���[�t�F�C�Y����
	case draw:
		
		break;
		// ���x���A�b�v�t�F�C�Y����
	case levelUp:
		
		break;
		// ���C���t�F�C�Y����
	case main:
		
		break;
		// �g���b�V���t�F�C�Y����
	case trush:
		
		break;
		// �^�[���G���h����
	case end:
		
		break;
	}
}