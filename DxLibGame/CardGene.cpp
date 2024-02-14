#include"CardGene.h"

CardGene DeckGene;
CardGene::CardGene() {

	card_num = 52;

	deck = new int[card_num]; //�������m��
	p_deck = &deck[0]; //�擪�|�C���^�̐ݒ�
	//�z��̏�����
	for (int i = 0; i < card_num; i++) {
		deck[i] = -1;
	}

	std::random_device rnd;	//����������

	//�}������J�[�h�����ɕς���
	for (int i = 0; i < card_num; i++) {
		//�}���ʒu�ɃJ�[�h��}������܂Ń��[�v
		while (true) {
			int place = rnd() % (card_num); //�}���ʒu�̌���
			if (deck[place] == -1) {
				//�J�[�h�̊i�[
				deck[place] = i % 52;
				break; //���[�v�𔲂���
			}
		}
	}
}
// �J�[�h�����o��
int CardGene::hand_card() {
	int hand = p_deck[0]; //�r�o����J�[�h�̐��l���m��
	//�z�񏈗�
	p_deck++; //�擪�|�C���^�����炷
	card_num--; //�J�[�h���������炷
	return hand; //�r�o����J�[�h�̐��l��n��
}