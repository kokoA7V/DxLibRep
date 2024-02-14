#include<DxLib.h>
#include"turnMng.h"
#include"CardGene.h"
#include "KeyMng.h"
#include "koko.h"

TurnMng::TurnMng(){

}


void TurnMng::Update(){
	DrawFormatString(500, 30, GetColor(255, 255, 255), "POW %d", pow);
	switch (phaseNo)
	{
	case start:
		// スタートフェイズ処理
		howManyHands();
		DrawFormatString(400, 10, GetColor(255, 255, 255), "StartPhase : nowHands%d", nowHands);
		NextPhase();
		break;
		
	case attack:
		// バトルフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "AttackPhase");
		// 自分の持ってるカードの合計攻撃力分相手にダメージを与える	
		DrawFormatString(200, 0, GetColor(255, 255, 255), "%d",pow,"ダメージを与えた！！");
		NextPhase();
		break;
		
	case drow:
		// ドローフェイズ処理
		pow = 0;
		DrawFormatString(400, 10, GetColor(255, 255, 255), "DrowPhase");
		// カードを五枚になるように引く

		for (nowHands; nowHands <= maxHand; )
		{
			if (hands[nowHands] <= 0)
			{
				int hand = DeckGene.hand_card();
				hands[nowHands] = hand;		
			}
			else
			{
				nowHands++;
			}
		}
		
		NextPhase();
		break;
		
	case levelUp:
		// レベルアップフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "LevelUpPhase");
		// パズルのレーン増える
		NextPhase();
		break;
		
	case main:
		// メインフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "MainPhase");
		// カード選択
		if (Key.keyState[KEY_INPUT_UP] == 1)
		{
			if (setHand < maxHand)
			{
				setHand++;
			}
		}
		if (Key.keyState[KEY_INPUT_DOWN] == 1)
		{
			if (setHand > 0)
			{
				setHand--;
			}
		}

		DrawFormatString(200, 300, GetColor(255, 255, 255), "攻撃力 %d", hands[setHand]);
		DrawFormatString(200, 350, GetColor(255, 255, 255), "今持ってるカードの番号 %d", setHand);
		DrawFormatString(200, 400, GetColor(255, 255, 255), "nowHands %d", nowHands);

		// カードのプレイ
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			pow += hands[setHand];
			hands[setHand] = 0;
		}
		
		NextPhase();
		break;
		
	case trush:
		// トラッシュフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "TrushPhase");
		//手札を捨てる
		NextPhase();
		break;
	case end:
		DrawFormatString(400, 10, GetColor(255, 255, 255), "EndPhase");
		// ターンエンド処理
		phaseNo = 0;
		break;
	}
}

void TurnMng::NextPhase() {
	if (Key.keyState[KEY_INPUT_RETURN] == 1)phaseNo++;
}

int  TurnMng::howManyHands() {
	setHand = 0;
	nowHands = 0;
	for (int i = 0; i <= maxHand; ++i)
	{
		if (hands[i] < 0)
		{
			nowHands++;
		}
	}
	return nowHands;
}