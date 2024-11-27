﻿#pragma once
#include "Object.h"

class Bom : public Object{
public://メンバ変数
	//画像
	Images images_;
	//速度
	Vector2 velocity_;
	//加速度
	Vector2 acceleration_;
	//ボムフラグ
	bool bomFlag_;
public://コンストラクタとデストラクタ
	//コンストラクタ
	Bom();
	//デストラクタ
	~Bom();
public://メンバ関数
	//基本的な動き
	void Move();
	//描画
	void Draw();
};