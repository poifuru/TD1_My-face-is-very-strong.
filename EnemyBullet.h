#pragma once
#include "Object.h"

class EnemyBullet :public Object {
public://メンバ変数
	//加速度
	Vector2 acceleration_;
	//速度
	Vector2 velocity_;
	//発射角度
	float angle_;
	//弾数
	int ammo_;
	//撃っているか
	bool isShotFlag_;

	//コンストラクタ
	EnemyBullet();
  
	//デストラクタ
	~EnemyBullet();

public://メンバ関数
	//基本的な動き
	void Move();
	//描画
	void Draw();
};
