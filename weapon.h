#pragma once
#include "struct.h"
#include "Object.h"

class Weapon : public Object {
public:
	//�����o�ϐ�
	Quad bullet_;
	Quad sword_;
	int wheelScroll_;

	//�R���X�g���N�^
	Weapon();
};

