#include <DxLib.h>
#include "TurnMng.h"
#include "CardGene.h"
#include "KeyMng.h"
#include "koko.h"
#include "Player.h"

TurnMng::TurnMng(){}

Player player;
Player player2;
koko kokoPl1;
koko kokoPl2;

void TurnMng::Init() {
	kokoPl1.Init();
	kokoPl2.Init();
}
void TurnMng::Update(){	
	
	// デバック用のpow表示
	DrawFormatString(0, 0, GetColor(255, 255, 255), "DEBUG:POW %d", pow);	

	// パズル表示
	kokoPl1.Update(100, 80);
	kokoPl2.Update(800, 80);

	// 手札表示
	player.DispHands(0);
	player2.DispHands(700);

	player.HPDisp(0);
	player2.HPDisp(200);
	switch (phaseNo)
	{
	case start:
		// スタートフェイズ処理

		// 0があるならその次の数字を0に入れる
		player.HandZeroGo();
		player2.HandZeroGo();

		// ハンドを数える
		player.nowHands = player.HowManyHands();
		player2.nowHands = player2.HowManyHands();
		
		DrawFormatString(400, 10, GetColor(255, 255, 255), "StartPhase : nowHands%d",player.nowHands);
		DrawFormatString(800, 10, GetColor(255, 255, 255), "nowHP%d", player2.nowHp);
		NextPhase();
		break;
		
	case attack:
		// バトルフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "AttackPhase");
		
		// 自分の持ってるカードの合計攻撃力分相手にダメージを与える	
		if (battingfirst)
		{
			DrawFormatString(200, 0, GetColor(255, 255, 255), "%d", pow, "ダメージを与えた！！");
		}
		
		
		NextPhase();
		break;
		
	case drow:
		// ドローフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "DrowPhase");
		
		// カードを五枚になるように引く
		if (battingfirst) player.Draw();
		else player2.Draw();	
		
		NextPhase();
		break;
		
	case levelUp:
		// レベルアップフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "LevelUpPhase");
		
		// パズルのレーン増える
		if (battingfirst)kokoPl1.level++;
		else kokoPl2.level++;
		
		
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
		if (battingfirst)CardPlayPl1();
		else CardPlayPl2();
		
		NextPhase();
		break;
		
	case trush:
		// トラッシュフェイズ処理
		DrawFormatString(400, 10, GetColor(255, 255, 255), "TrushPhase");
		//手札を捨てる

		// カード選択
		player.SelectHandPl1();

		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			player.hands[player.setHand] = 0;
			player.nowHands = player.HowManyHands();
		}
		
		NextPhase();
		break;
	case end:
		DrawFormatString(400, 10, GetColor(255, 255, 255), "EndPhase");
		// ターンエンド処理
		if (battingfirst)
		{
			battingfirst = false;
		}
		else
		{
			battingfirst = true;
		}
		phaseNo = 0;
		break;
	}
}

// 次のターンに進む
void TurnMng::NextPhase() {
	if (Key.keyState[KEY_INPUT_RETURN] == 1) {
		phaseNo++;
		kokoPl1.isPlayer = false;
		kokoPl2.isPlayer = false;
		mode = 0;
	}
}

void TurnMng::CardPlayPl1() 
{
	DrawFormatString(50, 400, GetColor(255, 255, 255), "nowHands %d", player.nowHands);

	// パズルモードと手札選択モード切り替え
	switch (mode)
	{
	case cardSelect:

		// カード選択
		player.SelectHandPl1();

		// カードの選択へモードチェンジ
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			kokoPl1.isPlayer = true;
			mode++;
		}
		break;
	case pazzle:

		if (Key.keyState[KEY_INPUT_LSHIFT] == 1)
		{
			if (kokoPl1.SetCheck())
			{
				kokoPl1.PieceSet();
				kokoPl1.isPlayer = false;
				pow += player.hands[player.setHand];
				player.hands[player.setHand] = 0;
				player.HowManyHands();
				mode = 0;
			}
			else
			{
				DrawFormatString(400, 200, GetColor(255, 255, 255), "オケナイ！");
			}

		}
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			kokoPl1.isPlayer = false;
			mode = 0;
		}
		break;
	}
}

void TurnMng::CardPlayPl2()
{
	DrawFormatString(50, 400, GetColor(255, 255, 255), "nowHands %d", player2.nowHands);

	// パズルモードと手札選択モード切り替え
	switch (mode)
	{
	case cardSelect:

		// カード選択
		player2.SelectHandPl2();

		// カードの選択へモードチェンジ
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			kokoPl2.isPlayer = true;
			mode++;
		}
		break;
	case pazzle:

		if (Key.keyState[KEY_INPUT_RSHIFT] == 1)
		{
			if (kokoPl2.SetCheck())
			{
				kokoPl2.PieceSet();
				kokoPl2.isPlayer = false;
				pow += player2.hands[player2.setHand];
				player2.hands[player2.setHand] = 0;
				player2.HowManyHands();
				mode = 0;
			}
			else
			{
				DrawFormatString(400, 200, GetColor(255, 255, 255), "オケナイ！");
			}

		}
		if (Key.keyState[KEY_INPUT_SPACE] == 1)
		{
			kokoPl2.isPlayer = false;
			mode = 0;
		}
		break;
	}
}