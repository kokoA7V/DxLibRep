#pragma once
#include"Card.h"
#include <list>

using namespace std;
class CardList {
private:
public:
	list<Card*> fieldCardList;

	void FieldCardPush(Card* card);
};

extern CardList gCardList;