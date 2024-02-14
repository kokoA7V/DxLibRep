#pragma once
#include <random> //乱数生成
#include "DxLib.h"
#include"iostream"

//カード排出クラス
// 参考サイト　
// https://tora-k.com/2020/04/06/cardclass/
class CardGene {
private:
	int MinDeck = 1;
	int card_num; //カード枚数
	int* deck; //格納配列
	int* p_deck; //配列先頭ポインタ
public:
	//コンストラクタ：引数はデッキ数
	CardGene();
	//デストラクタ
	//カードの排出
	int hand_card();
};
extern CardGene DeckGene;