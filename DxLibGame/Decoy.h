#pragma once
#include"Dxlib.h"
#include"Player.h"
#include"Card.h"

class Decoy :public Card{
private:
public:
	int plusPow;
	int CardEffect(Player pow);

};