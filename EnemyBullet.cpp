#include <Novice.h>
#include "EnemyBullet.h"

//コンストラクタ
Bullet::Bullet() {
	//DrawQuadで主に使う
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
	//加速度
	acceleration_ = {};
	//速度
	velocity_ = {};
	//発射角度
	angle_ = {};
	//弾数
	ammo_ = 48;
	//撃っているか
	isShotFlag_ = false;
}

//デストラクタ
Bullet::~Bullet() {

}

//敵の弾の基本的な動き
void Bullet::Move() {

}

//弾の描画
void Bullet::Draw() {

}
