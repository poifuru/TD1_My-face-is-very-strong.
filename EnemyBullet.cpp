#include <Novice.h>
#include "EnemyBullet.h"

//�R���X�g���N�^
Bullet::Bullet() {
	//DrawQuad�Ŏ�Ɏg��
	quad_.pos = {};
	quad_.radius = {};
	quad_.radius = { 10.0f,10.0f };
	quad_.leftTop = {};
	quad_.leftBottom = {};
	quad_.rightBottom = {};
	quad_.rightTop = {};
	quad_.imagePos = {};
	quad_.imageWidth = {};
	quad_.imageHeight = {};
	quad_.image = {};
	quad_.color = {};
	//�����x
	acceleration_ = {};
	//���x
	velocity_ = {};
	//���ˊp�x
	angle_ = {};
	//�e��
	ammo_ = 48;
	//�����Ă��邩
	isShotFlag_ = false;
}

//�f�X�g���N�^
Bullet::~Bullet() {

}

//�G�̒e�̊�{�I�ȓ���
void Bullet::Move() {

}

//�e�̕`��
void Bullet::Draw() {

}
