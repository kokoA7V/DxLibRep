#pragma once
#include "DxLib.h"


class Card {
private :
	enum CardStayle {
		unit,
		effect,
	};
public:
	int plusPow ;
	CardStayle cardStyle;
	void CardEffect();
};