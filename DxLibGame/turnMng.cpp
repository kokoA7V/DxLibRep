#include <DxLib.h>
#include "TurnMng.h"
#include "CardGene.h"
#include "KeyMng.h"
#include "koko.h"
#include "Player.h"
#include "CardList.h"
#include "Decoy.h"

// 追記 by koko
#include "ResourceMng.h"

TurnMng::TurnMng(){}

Player player;
Player player2;
koko kokoPl1;
koko kokoPl2;

Decoy decoy;

CardList gCardList;

void TurnMng::Init() {
	kokoPl1.Init();
	kokoPl2.Init();
	
	//phaseText[0]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "StartPhase");
	//phaseText[1]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > StartPhase < ");
	//phaseText[2]= DrawFormatString(phaseDispX, 40, GetColor(255, 255, 255), "AttackPhase");
	//phaseText[3]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > AttackPhase < ");
	//phaseText[4]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "DrowPhase");
	//phaseText[5]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > DrowPhase < ");
	//phaseText[6]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "LevelUpPhase");
	//phaseText[7]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > LevelUpPhase < ");
	//phaseText[8]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "MainPhase");
	//phaseText[9]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > MainPhase < ");
	//phaseText[10]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "TrushPhase");
	//phaseText[11]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > TrushPhase < ");
	//phaseText[12]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), "EndPhase");
	//phaseText[13]= DrawFormatString(phaseDispX, 10, GetColor(255, 255, 255), " > EndPhase < ");
}
void TurnMng::Update(){	
	
	// フェイズ表示
	PhaseDisp();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d",player.pow);


	
	if (Key.keyState[KEY_INPUT_SPACE] == 1)
	{
		player.pow = decoy.CardEffect(player);
	}
	if (Key.keyState[KEY_INPUT_E] == 1)
	{
		gCardList.fieldCardList.clear();
	}

	for (int i = 0; i < gCardList.fieldCardList.size(); i++)
	{
		DrawFormatString(500 , 450 - i * 20, GetColor(255, 255, 255), "■");
	}

	// デバック用のpow表示
	/*DrawFormatString(0, 0, GetColor(255, 255, 255), "DEBUG:POW %d", pow);*/	

	// パズル表示
	////
	// 位置変更 by koko
	kokoPl1.Update(130, 250);
	kokoPl2.Update(830, 250);
	// 元位置
	//kokoPl1.Update(100, 80);
	//kokoPl2.Update(800, 80);
	////

	// お試しHP枠表記追加 by koko
	DrawGraph(20, 120, rm.stats[0], 0);
	DrawGraph(1180, 120, rm.stats[0], 0);

	// 手札表示
	player.DispHands(0);
	player2.DispHands(700);

	////
	// 表記変更 by koko
	player.HPDisp(60);
	player2.HPDisp(1220);
	// 変更前
	//player.HPDisp(0);
	//player2.HPDisp(200);
	////

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

		NextPhase();
		break;
		
	case attack:
		// バトルフェイズ処理
		
		// 自分の持ってるカードの合計攻撃力分相手にダメージを与える	
		if (battingfirst)
		{
			DrawFormatString(200, 0, GetColor(255, 255, 255), "%d", pow, "ダメージを与えた！！");
		}		
		
		NextPhase();
		break;
		
	case drow:
		// ドローフェイズ処理
		
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

void TurnMng::PhaseDisp() {
	switch (phaseNo)
	{
	case start:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), " > StartPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case attack:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), " > AttackPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case drow:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), " > DrowPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case levelUp:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), " > LevelUpPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case main:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), " > MainPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case trush:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), " > TrushPhase < ");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), "   EndPhase");
		break;
	case end:
		DrawFormatString(phaseDispX, phaseDispY , GetColor(255, 255, 255), "   StartPhase");
		DrawFormatString(phaseDispX, phaseDispY + 30, GetColor(255, 255, 255), "   AttackPhase");
		DrawFormatString(phaseDispX, phaseDispY + 60, GetColor(255, 255, 255), "   DrowPhase");
		DrawFormatString(phaseDispX, phaseDispY + 90, GetColor(255, 255, 255), "   LevelUpPhase");
		DrawFormatString(phaseDispX, phaseDispY + 120, GetColor(255, 255, 255), "   MainPhase");
		DrawFormatString(phaseDispX, phaseDispY + 150, GetColor(255, 255, 255), "   TrushPhase");
		DrawFormatString(phaseDispX, phaseDispY + 180, GetColor(255, 255, 255), " > EndPhase < ");
		break;
	}
}