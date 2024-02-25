#include"Player.h"


void Player::Update() {

}

void Player::HPDisp(int posX) {
	for ( int i=0; i < nowHp; i++)
	{
		DrawFormatString(500 + posX, 450 - i * 20, GetColor(255, 255, 255), "¡");
	}
}