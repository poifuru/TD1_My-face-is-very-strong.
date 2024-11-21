﻿#include "ULT.h"

//=======================================
//
// cutIn - 画像サイズ
// 1920 * 840
//
//=======================================

//カットインサイズ変更
const float cutInWidth = 1920.0f;
const float cutInHeight = 840.0f;

const float margin = (1080.0f - cutInHeight) / 2;

//=======================================
// 初期化
//=======================================

//変更するのであればここ
//ULTのチャージを1貯めるのに必要な時間
const int chargeTime = 30;

int isULT = false;
int isULTReady = false;
int Ultimate = 0;
int ULTTimer = chargeTime;
int isCutInEase = false;
int isCutInPush = false;

Vector2 cutInPos = {
	-1 * cutInWidth - 5,margin
};

Vector2 cutInStart[2] = {
	{-1 * cutInWidth - 5,margin},
	{0.0f,margin}
};

Vector2 cutInEnd[2] = {
	{0.0f,margin},
	{cutInWidth,margin}
};

float easeT[2] = {
	0.0f,
	0.0f
};


//=======================================
// イージング
//=======================================

float easeInExpo(float x)
{
	x = static_cast<float>(0 ? 0 : pow(2, 10 * x - 10));

	return x;
}

void lerp(Vector2 start, Vector2 end, Vector2& pos, float t) {
	pos.x = (1.0f - t) * start.x + t * end.x;
	pos.y = (1.0f - t) * start.y + t * end.y;
}


//=======================================
// カットイン用関数
//=======================================

void startCutIn()
{
	
	int is2ndEase = false;
	int is2ndPush = false;

	if (isCutInPush) {
		if (isCutInEase) {
			easeT[0] += 0.03f;
		}

		if (easeT[0] > 1.0f) {
			easeT[0] = 1.0f;
		}
		if (easeT[0] == 1.0f) {
			isCutInEase = false;
			isCutInPush = false;
			is2ndEase = true;
			is2ndPush = true;
		}
	}

	if (is2ndPush) {
		if (is2ndEase) {
			easeT[1] += 0.02f;
		}

		if (easeT[1] > 1.0f) {
			easeT[1] = 1.0f;
		}
		if (easeT[1] == 1.0f) {
			is2ndEase = false;
			is2ndPush = false;
			isULT = false;
			easeT[0] = 0.0f;
			easeT[1] = 0.0f;
		}
	}

	if (easeT[0] <= 0.99f) {
		lerp(cutInStart[0], cutInEnd[0], cutInPos, easeInExpo(easeT[0]));
	}
	if (easeT[0] == 1.0f) {
		lerp(cutInStart[1], cutInEnd[1], cutInPos, easeInExpo(easeT[1]));
	}
}


//=======================================
// ULT管理
//=======================================

void ULTUpdate(char* keys, char* preKeys)
{
	ULTTimer--;

	if (ULTTimer <= 0) {
		if (Ultimate < 100) {
			Ultimate++;
		}
		ULTTimer = chargeTime;
	}

	if (Ultimate >= 100) {
		isULTReady = true;
	} else {
		isULTReady = false;
	}

	if (isULTReady) {
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			isULT = true;
			Ultimate = 0;
		}
	}

	if (isULT) {
		isCutInEase = true;
		isCutInPush = true;
		startCutIn();
	}


	//デバック用
	if (keys[DIK_1]) {
		Ultimate = 0;
	}

	if (keys[DIK_2]) {
		Ultimate = 50;
	}

	if (keys[DIK_3]) {
		Ultimate = 100;
	}

	Novice::ScreenPrintf(1300, 80, "Ultimate : %d", Ultimate);

}

//=======================================
// 描画関数
//=======================================

void DrawCutIn()
{

	Novice::DrawBox(static_cast<int>(cutInPos.x),
		static_cast<int>(cutInPos.y),
		static_cast<int>(cutInWidth),
		static_cast<int>(cutInHeight), 0.0f, BLUE, kFillModeSolid);

	Novice::DrawEllipse(1500, 80, 50, 50, 0.0f, BLUE, kFillModeWireFrame);

	Novice::ScreenPrintf(32, 32, "CutInPos : %f", cutInPos.x);
}