#pragma once
#include"DxLib.h"
#include"Card.h"
#include"CardList.h"
#include"Player.h"

class AutoCrack:public Card {
private:
public:
	void CardEffect(CardList pl);
};