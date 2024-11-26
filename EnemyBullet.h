#pragma once
#include "struct.h"

class Bullet {
public://メンバ変数
	//画像
	Images images_;
	//quad
	Quad quad_[16];
	//加速度
	Vector2 acceleration_[16];
	//速度
	Vector2 velocity_[16];
	//発射角度
	float angle_;
	//弾数
	int ammo_;
	//撃っているか
	bool isShotFlag_[16];

	//コンストラクタ
	Bullet();
  
	//デストラクタ
	~Bullet();

public://メンバ関数
	//基本的な動き
	void Move();
	//描画
	void Draw();
};
