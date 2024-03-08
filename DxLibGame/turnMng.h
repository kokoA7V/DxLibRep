#pragma once
#include"DxLib.h"
#include<List>
#include<string>

class TurnMng {
private:
public:
	///* 最大の手札の数
 //   int maxHand = 5;
	//
	// 手札の枚数
	//int nowHandsPl1 = 0;
	//int nowHandsPl2 = 0;
	//
	// 使おうとしてるカード
	//int setHandPl1 = 0;
	//int setHandPl2 = 0;
	//
	// 手札
	//int handsPl1[5] = {0,0,0,0,0};
	//int handsPl2[5] = {0,0,0,0,0};*/
	
	// 与えるダメージ(仮)
	int pow = 0;

	// フェイズ
	enum Phase{
		start,
		attack,
		drow,
		levelUp,
		main,
		trush,
		end,
		phaseTotalNum,
	};
	int phaseNo = 0;

	enum Mode {
		cardSelect,
		pazzle,
	};
	int mode = 0;
	
	// コンストラクタ
	TurnMng();
	
	// アップデート
	void Update();
	
	// 次のターンへ
	void NextPhase();
	
	//// 手札を数える
	//int HowManyHands();
	//
	//// 数を前に詰める
	//void CloseToTheFront(int line);
	//
	//// 手札を見て0があるなら前に詰めるメソッドを起動する
	//void HandZeroGo();
	//
	////  手札を表示させる
	//void DispHandsPl1(int posX);
	//void DispHandsPl2(int posX);
	//
	//// 手札を選択する
	//void SelectHandPl1();
	//void SelectHandPl2();

	void Init();
};