#pragma once
#include "Object.h"

class Enemy : public Object {
public://メンバ変数
	//速度
	Vector2 velocity_;
	//加速度
	Vector2 acceleration_;
	//長さ
	float length_;

	//コンストラクタの宣言
	Enemy();
	//デストラクタの宣言
	~Enemy();
public://メンバ関数
	//基本的な動き
	void Move();
	//描画する
	void Draw();
};
