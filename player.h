#pragma once
#include "struct.h"
#include "enum.h"
#include "Object.h"
#include "weapon.h"

class Player : public Object{
public:
	//メンバ変数
	int stickX_;
	int stickY_;
	Vector2 velocity_;
	int color_;
	int direction_;

	/*パリィ*/
	int isParry_;
	int parryFlame_;

	/*ジャンプ*/
	int isJump_;

	/*武器*/
	Weapon* weapon_;

	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//メンバ関数
	void Update(const char keys[], const char preKeys[]);
	void Draw();
};