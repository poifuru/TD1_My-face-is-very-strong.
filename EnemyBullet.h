#pragma once
#include "Object.h"

class Bullet :public Object {
public://�����o�ϐ�
	//�����x
	Vector2 acceleration_;
	//���x
	Vector2 velocity_;
	//���ˊp�x
	float angle_;
	//�e��
	int ammo_;
	//�����Ă��邩
	bool isShotFlag_;

	//�R���X�g���N�^
	Bullet();
	//�f�X�g���N�^
	~Bullet();
public://�����o�֐�
	//��{�I�ȓ���
	void Move();
	//�`��
	void Draw();
};
