#include<DxLib.h>
#include"turnMng.h"

void turnMng::Update(Phase _phaseNo){
	phaseNo = _phaseNo;
	switch (phaseNo)
	{
		// スタートフェイズ処理
	case start:
		phaseNo++;
		break;
		// バトルフェイズ処理
	case attack:
		
		break;
		// ドローフェイズ処理
	case draw:
		
		break;
		// レベルアップフェイズ処理
	case levelUp:
		
		break;
		// メインフェイズ処理
	case main:
		
		break;
		// トラッシュフェイズ処理
	case trush:
		
		break;
		// ターンエンド処理
	case end:
		
		break;
	}
}