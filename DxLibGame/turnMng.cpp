#include<DxLib.h>
#include"turnMng.h"
#include"CardGene.h"
#include "KeyMng.h"
#include "koko.h"

TurnMng::TurnMng(){
	
}

void TurnMng::Update(){	

	// デバック用のpow表示
	DrawFormatString(500, 30, GetColor(255, 255, 255), "POW %d", pow);
	
	switch (phaseNo)
	{
	case start:
		// スタートフェイズ処理
		
		// 0があるならその次の数字を0に入れる
		HandZeroGo();

		// ハンドを数える
		nowHands = HowManyHands();
		
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
		pow = 0;
		// ドローフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "DrowPhase");
		
		// カードを五枚になるように引く
		for (nowHands; nowHands < maxHand; )
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
		gKoko.level++;
		
		phaseNo++;
		//NextPhase();
		break;
		
	case main:
		// メインフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "MainPhase");


		// ここすくりぷと
		gKoko.PlayerMove();
		if (Key.keyState[KEY_INPUT_P] == 1)
		{
			if (gKoko.SetCheck())
			{
				gKoko.ArrayAdd(gKoko.pieceData[gKoko.pieceNum], gKoko.field, gKoko.posX, gKoko.posY);
				gKoko.Debug("せいこう");
			}
			else
			{
				gKoko.Debug("おけないよーん");
			}
		}
		// ここまで
		// カード
		if (Key.keyState[KEY_INPUT_UP] == 1)
		{
			if (setHand < maxHand-1)
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
		for (int i=0;i<nowHands;i++)
		{
			DrawFormatString(0 + i * 100, 300, GetColor(255, 255, 255), "攻撃力 %d", hands[i]);
			DrawFormatString(0 + i * 100, 350, GetColor(255, 255, 255), "番号 %d", i);
		}

		DrawFormatString(50, 400, GetColor(255, 255, 255), "nowHands %d", nowHands);
		
		// カードの選択　ここにパズル動かすすくりぷとをいれる
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

// 次のターンに進む
void TurnMng::NextPhase() {
	if (Key.keyState[KEY_INPUT_RETURN] == 1)phaseNo++;
}

// 手札の数を数えるメソッド
int TurnMng::HowManyHands() {
	int manyHands = 0;
	for (int i = 0; i < maxHand; ++i)
	{
		if (hands[i] > 0)
		{
			manyHands++;
		}
	}
	return  manyHands;
}

// 数字を前に詰める
void TurnMng::CloseToTheFront(int line) {
	hands[line - 1] = hands[line];
	hands[line] = 0;
}

void TurnMng::HandZeroGo(){
	for (int i = 0; i < maxHand - 1; ++i)
	{
		if (hands[i] == 0)
		{
			CloseToTheFront(i + 1);
		}
	}
}