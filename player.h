#pragma once
#include "Struct.h"
#include "Enum.h"
#include "Object.h"
#include "Weapon.h"
#include "Parry.h"
#include "Enemy.h"

class Weapon;//前方宣言

class Player : public Object {
public:
	//画像
	Images images_;

	//メンバ変数
	int stickX_;
	int stickY_;
	Vector2 velocity_;
	Direction direction_;
	int HP_;
	int isMove_;
	int ghPos_;
	int playerTime_;
	int playerTimer_;
	int invincible_;//無敵時間に使うよ
	int invincibleTimer_;

	/*ジャンプ*/
	int isJump_;

	/*パリィ*/
	Parry* parry_;

	/*武器*/
	Weapon* weapon_;

	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//メンバ関数
	void Update(const char keys[], const char preKeys[], Enemy* enemy);
	void Draw();
};