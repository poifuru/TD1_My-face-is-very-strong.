#pragma once
#include "struct.h"
#include "enum.h"
#include "Object.h"
#include "weapon.h"

class Player : public Object{
public:
	//�����o�ϐ�
	int stickX_;
	int stickY_;
	Vector2 velocity_;
	int color_;

	/*�p���B*/
	int isParry_;
	int parryFlame_;

	/*�W�����v*/
	int isJump_;

	/*����*/
	int attack_;
	int attackingTimer_;
	Weapon* weapon_;

	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();

	//�����o�֐�
	void Update(const char keys[], const char preKeys[]);
	void Draw();
};