#include <DxLib.h>
#include "turnMng.h"
#include "CardGene.h"
#include "KeyMng.h"
#include "koko.h"

TurnMng::TurnMng(){}

void TurnMng::Update(){	

	// デバック用のpow表示
	DrawFormatString(0, 0, GetColor(255, 255, 255), "DEBUG:POW %d", pow);
	
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
		DrawFormatString(400, 10, GetColor(255, 255, 255), "MainPhase\nスペースで切り替え\n");
		if (mode == pazzle)
		{
			DrawFormatString(400, 70, GetColor(255, 255, 255), "パズルモード");
		}
		else
		{
			DrawFormatString(400, 70, GetColor(255, 255, 255), "カード選択モード");
		}
		
		// 手札表示
		DispHands();

		DrawFormatString(50, 400, GetColor(255, 255, 255), "nowHands %d", nowHands);

		// kokoアップデートをココへ移動 by koko
		gKoko.Update(0, 0);
		
		// パズルモードと手札選択モード切り替え
		switch (mode)
		{
		case cardSelect:
						

			// カード選択
			SelectHand();

			// カードの選択へモードチェンジ
			if (Key.keyState[KEY_INPUT_SPACE] == 1)
			{
				gKoko.isPlayer = true;
				mode++;
			}
			break;
		case pazzle:
			
			
			// gKoko.Update();
			if (Key.keyState[KEY_INPUT_LSHIFT] == 1)
			{
				if (gKoko.SetCheck())
				{
					gKoko.PieceSet();
					gKoko.isPlayer = false;
					pow += hands[setHand];
					hands[setHand] = 0;
					HowManyHands();
					mode = 0;
				}
				else
				{
					DrawFormatString(400, 200, GetColor(255, 255, 255), "オケナイ！");
				}
				
			}
			if (Key.keyState[KEY_INPUT_SPACE] == 1)
			{
				gKoko.isPlayer = false;
				mode = 0;
			}
			break;
		}
		
		NextPhase();
		break;
		
	case trush:
		// トラッシュフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "TrushPhase");
		//手札を捨てる

		// カード選択
		SelectHand();

		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			hands[setHand] = 0;
			HowManyHands();
		}

		// 手札表示
		DispHands();
		
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

// 0があったら数字を前に詰めるスクリプトを起動
void TurnMng::HandZeroGo(){
	for (int i = 0; i < maxHand - 1; ++i)
	{
		if (hands[i] == 0)
		{
			CloseToTheFront(i + 1);
		}
	}
}

// 手札を表示させる
void TurnMng::DispHands() {
	DrawFormatString(400, 400, GetColor(255, 255, 255), "setHands %d", hands[setHand]);

	for (int i = 0; i < nowHands; i++)
	{
		// 選択してるなら文字を赤色に
		if (setHand == i)
		{
			DrawFormatString(i * 100 + 50, 300, GetColor(255, 0, 0), "攻撃力 %d", hands[i]);
			DrawFormatString(i * 100 + 50, 350, GetColor(255, 0, 0), "番号 %d", i);
		}
		else
		{
			DrawFormatString(i * 100 + 50, 300, GetColor(255, 255, 255), "攻撃力 %d", hands[i]);
			DrawFormatString(i * 100 + 50, 350, GetColor(255, 255, 255), "番号 %d", i);
		}
	}
}

// カード選択
void TurnMng::SelectHand() {
	if (Key.keyState[KEY_INPUT_D] == 1)
	{
		if (setHand < maxHand - 1)
		{
			setHand++;
		}
		else
		{
			setHand = 0;
		}
	}

	if (Key.keyState[KEY_INPUT_A] == 1)
	{
		if (setHand > 0)
		{
			setHand--;
		}
		else
		{
			setHand = 4;
		}
	}
}