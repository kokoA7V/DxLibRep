#include"CardGene.h"

CardGene DeckGene;
CardGene::CardGene() {

	card_num = 52;

	deck = new int[card_num]; //メモリ確保
	p_deck = &deck[0]; //先頭ポインタの設定
	//配列の初期化
	for (int i = 0; i < card_num; i++) {
		deck[i] = -1;
	}

	std::random_device rnd;	//乱数生成器

	//挿入するカードを順に変える
	for (int i = 0; i < card_num; i++) {
		//挿入位置にカードを挿入するまでループ
		while (true) {
			int place = rnd() % (card_num); //挿入位置の決定
			if (deck[place] == -1) {
				//カードの格納
				deck[place] = i % 52;
				break; //ループを抜ける
			}
		}
	}
}
// カードを取り出す
int CardGene::hand_card() {
	int hand = p_deck[0]; //排出するカードの数値を確定
	//配列処理
	p_deck++; //先頭ポインタをずらす
	card_num--; //カード枚数を減らす
	return hand; //排出するカードの数値を渡す
}