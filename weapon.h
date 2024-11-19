#pragma once
#include "struct.h"
#include "Object.h"

class Weapon : public Object {
public:
	//メンバ変数
	Quad bullet_;
	Quad sword_;

	//コンストラクタ
	Weapon();
};

