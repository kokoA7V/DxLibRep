#include"Decoy.h"
#include"CardList.h"

int Decoy::CardEffect(Player player)
{
	plusPow = 1;
	plusPow += player.pow;
	gCardList.FieldCardPush(this);
	return plusPow;
}; 