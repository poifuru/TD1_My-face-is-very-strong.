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
	//メンバ変数
	int stickX_;
	int stickY_;
	Vector2 velocity_;
	int direction_;
	int HP_;

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
	void Update(const char keys[], const char preKeys[], Enemy enemy);
	void Draw();
};