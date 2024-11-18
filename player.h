#pragma once
#include "struct.h"
#include "Object.h"


class Player : public FloatObject{
public:
	//メンバ変数
	Vector2 velocity_;
	int color_;
	/*パリィ*/
	int isParry_;
	int parryFlame_;
	/*ジャンプ*/
	int isJump_;
	//int JumpSizeFlame_;

	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//メンバ関数
	void Update(const char keys[], const char preKeys[]);
	void Draw();
};