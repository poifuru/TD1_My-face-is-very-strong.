#pragma once
#include "Struct.h"
#include "Object.h"

const int kBulletNum = 30;

class Weapon : public Object {
public:
	//メンバ変数
	Quad sword_;
	Quad gun_;

	int weaponMode_;

	/*剣モードの変数*/
	int attack_;
	int attackingTimer_;
	int wheelScroll_;

	/*銃モードの変数*/
	Quad bullet_[kBulletNum];
	int isShot_[kBulletNum];
	int readyToFire_;
	Vector2 targetPos_[kBulletNum]; //敵の座標と同期させる
	Vector2 vectorToTarget_[kBulletNum]; //弾発射時の座標と敵の座標を結ぶベクトル

	//コンストラクタ
	Weapon();

	//メンバ関数
	void Update();
	void Draw();
};

