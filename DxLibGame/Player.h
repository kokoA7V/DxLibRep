#pragma once
#include"DxLib.h"

class Player {
private :
public :

	int pow = 0;

	int maxHp = 20;
	int nowHp = 20;

	// 最大の手札の数
	int maxHand = 5;

	// 手札の枚数
	int nowHands = 0;

	// 使おうとしてるカード
	int setHand = 0;

	// 手札
	int hands[5] = { 0,0,0,0,0 };

	void Update();
	void HPDisp(int posX);

	// 手札を数える
	int HowManyHands();

	// 数を前に詰める
	void CloseToTheFront(int line);

	// 手札を見て0があるなら前に詰めるメソッドを起動する
	void HandZeroGo();

	//  手札を表示させる
	void DispHands(int posX);

	// 手札を選択する
	void SelectHandPl1();
	void SelectHandPl2();

	void Draw();
};