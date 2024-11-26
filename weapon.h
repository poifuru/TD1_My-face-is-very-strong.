#pragma once
#include "Struct.h"
#include "Object.h"
#include "Enemy.h"
#include "Player.h"

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
	Vector2 bulletSpeed_[kBulletNum];
	int isShot_[kBulletNum];
	Vector2 bulletVec_[kBulletNum];
	Vector2 vectorToTarget_[kBulletNum]; //弾発射時の座標と敵の座標を結ぶベクトル
	int readyToFire_;
	int shotCoolTime_;

	//コンストラクタ
	Weapon();

	//メンバ関数
	void Update(Enemy enemy/*, const char* keys*/);
	void Draw();
};

