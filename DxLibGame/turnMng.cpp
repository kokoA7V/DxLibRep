#include <DxLib.h>
#include "turnMng.h"
#include "CardGene.h"
#include "KeyMng.h"
#include "koko.h"
#include "Player.h"

TurnMng::TurnMng(){}
Player player;
Player player2;
koko kokoPl1;
koko kokoPl;
void TurnMng::Update(){	
	
	// デバック用のpow表示
	DrawFormatString(0, 0, GetColor(255, 255, 255), "DEBUG:POW %d", pow);
	
	gKoko.Update(100, 80);
	gKoko.Update(800, 80);

	// 手札表示
	DispHandsPl1(0);
	DispHandsPl2(700);

	player.HPDisp(0);
	player2.HPDisp(200);
	switch (phaseNo)
	{
	case start:
		// スタートフェイズ処理

		// 0があるならその次の数字を0に入れる
		HandZeroGo();

		// ハンドを数える
		nowHandsPl1 = HowManyHands();
		
		DrawFormatString(400, 10, GetColor(255, 255, 255), "StartPhase : nowHands%d", nowHandsPl1);
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			player2.nowHp--;
		}
		DrawFormatString(800, 10, GetColor(255, 255, 255), "nowHP%d", player2.nowHp);
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
		for (nowHandsPl1; nowHandsPl1 < maxHand; )
		{
			if (handsPl1[nowHandsPl1] <= 0)
			{
				int hand = DeckGene.hand_card();
				handsPl1[nowHandsPl1] = hand;	
			}
			else
			{
				nowHandsPl1++;
			}

		}
		for (nowHandsPl2; nowHandsPl2 < maxHand; )
		{
			if (handsPl2[nowHandsPl2] <= 0)
			{
				int hand = DeckGene.hand_card();
				handsPl2[nowHandsPl2] = hand;
			}
			else
			{
				nowHandsPl2++;
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
		


		DrawFormatString(50, 400, GetColor(255, 255, 255), "nowHands %d", nowHandsPl1);


		
		// パズルモードと手札選択モード切り替え
		switch (mode)
		{
		case cardSelect:
						

			// カード選択
			SelectHandPl1();

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
					pow += handsPl1[setHandPl1];
					handsPl1[setHandPl1] = 0;
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
		SelectHandPl1();

		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			handsPl1[setHandPl1] = 0;
			HowManyHands();
		}

		
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
		if (handsPl1[i] > 0)
		{
			manyHands++;
		}
	}
	return  manyHands;
}

// 数字を前に詰める
void TurnMng::CloseToTheFront(int line) {
	handsPl1[line - 1] = handsPl1[line];
	handsPl1[line] = 0;
}

// 0があったら数字を前に詰めるスクリプトを起動
void TurnMng::HandZeroGo(){
	for (int i = 0; i < maxHand - 1; ++i)
	{
		if (handsPl1[i] == 0)
		{
			CloseToTheFront(i + 1);
		}
	}
}

// 手札を表示させる
void TurnMng::DispHandsPl1(int posX) {
	DrawFormatString(400, 400, GetColor(255, 255, 255), "setHands %d", handsPl1[setHandPl1]);

	for (int i = 0; i < nowHandsPl1; i++)
	{
		// 選択してるなら文字を赤色に
		if (setHandPl1 == i)
		{
			DrawFormatString(i * 100 + 50 + posX, 500, GetColor(255, 0, 0), "攻撃力 %d", handsPl1[i]);
			DrawFormatString(i * 100 + 50 + posX, 550, GetColor(255, 0, 0), "番号 %d", i);
		}
		else
		{
			DrawFormatString(i * 100 + 50 + posX, 500, GetColor(255, 255, 255), "攻撃力 %d", handsPl1[i]);
			DrawFormatString(i * 100 + 50 + posX, 550, GetColor(255, 255, 255), "番号 %d", i);
		}
	}
}

void TurnMng::DispHandsPl2(int posX) {
	DrawFormatString(400, 400, GetColor(255, 255, 255), "setHands %d", handsPl2[setHandPl2]);

	for (int i = 0; i < nowHandsPl2; i++)
	{
		// 選択してるなら文字を赤色に
		if (setHandPl2 == i)
		{
			DrawFormatString(i * 100 + 50 + posX, 500, GetColor(255, 0, 0), "攻撃力 %d", handsPl2[i]);
			DrawFormatString(i * 100 + 50 + posX, 550, GetColor(255, 0, 0), "番号 %d", i);
		}
		else
		{
			DrawFormatString(i * 100 + 50 + posX, 500, GetColor(255, 255, 255), "攻撃力 %d", handsPl2[i]);
			DrawFormatString(i * 100 + 50 + posX, 550, GetColor(255, 255, 255), "番号 %d", i);
		}
	}
}

// カード選択
void TurnMng::SelectHandPl1() {
	if (Key.keyState[KEY_INPUT_D] == 1)
	{
		if (setHandPl1 < maxHand - 1)
		{
			setHandPl1++;
		}
		else
		{
			setHandPl1 = 0;
		}
	}

	if (Key.keyState[KEY_INPUT_A] == 1)
	{
		if (setHandPl1 > 0)
		{
			setHandPl1--;
		}
		else
		{
			setHandPl1 = 4;
		}
	}
}

void TurnMng::SelectHandPl2() {
	if (Key.keyState[KEY_INPUT_RIGHT] == 1)
	{
		if (setHandPl2 < maxHand - 1)
		{
			setHandPl2++;
		}
		else
		{
			setHandPl2 = 0;
		}
	}

	if (Key.keyState[KEY_INPUT_LEFT] == 1)
	{
		if (setHandPl2 > 0)
		{
			setHandPl2--;
		}
		else
		{
			setHandPl2 = 4;
		}
	}
}