#include <Novice.h>
#include <corecrt_math_defines.h>
#include "EnemyBullet.h"
#include <math.h>

//コンストラクタ
Bullet::Bullet() {
	//発射角度
	angle_ = {};
	//弾数
	ammo_ = 16;
	for (int i = 0; i < ammo_; i++) {
		//DrawQuadで主に使う
		quad_[i].pos = {};
		quad_[i].radius = {};
		quad_[i].radius = { 10.0f,10.0f };
		quad_[i].leftTop = {};
		quad_[i].leftBottom = {};
		quad_[i].rightBottom = {};
		quad_[i].rightTop = {};
		quad_[i].imagePos = {};
		quad_[i].imageWidth = {};
		quad_[i].imageHeight = {};
		quad_[i].image = images_.white1x1;
		quad_[i].color = {};
		//加速度
		acceleration_[i] = { 0.1f,0.1f };
		//速度
		velocity_[i] = {};
		//撃っているか
		isShotFlag_[i] = false;
	}
}

//デストラクタ
Bullet::~Bullet() {

}

//敵の弾の基本的な動き
void Bullet::Move() {
	for (int i = 0; i < ammo_; i++) {
		if (isShotFlag_) {
			//角度をつける
			angle_ = i * (2 * float(M_PI) / ammo_);

			//加速させる
			if (velocity_[i].x <= 2.0f) {//x座標
				velocity_[i].x += acceleration_[i].x;
			} else {
				velocity_[i].x = 10.0f;
			}

			if (velocity_[i].y <= 2.0f) {//y座標
				velocity_[i].y += acceleration_[i].y;
			} else {
				velocity_[i].y = 10.0f;
			}

			//全方向に弾を飛ばす
			quad_[i].pos.x += velocity_[i].x * cosf(angle_);
			quad_[i].pos.y += velocity_[i].y * sinf(angle_);

			//画面外に出たら
			if (quad_[i].pos.x <= 0.0f - quad_[i].radius.x || quad_[i].pos.x >= 1920.0f + quad_[i].radius.x || quad_[i].pos.y <= 0.0f - quad_[i].radius.y || quad_[i].pos.y >= 1080.0f + quad_[i].radius.y) {
				isShotFlag_[i] = false;
				velocity_[i].x = 0.0f;
				velocity_[i].y = 0.0f;
			}
		}

		//矩形4点の更新
		quad_[i].leftTop = { quad_[i].pos.x - quad_[i].radius.x,quad_[i].pos.y - quad_[i].radius.y };
		quad_[i].rightTop = { quad_[i].pos.x + quad_[i].radius.x,quad_[i].pos.y - quad_[i].radius.y };
		quad_[i].leftBottom = { quad_[i].pos.x - quad_[i].radius.x,quad_[i].pos.y + quad_[i].radius.y };
		quad_[i].rightBottom = { quad_[i].pos.x + quad_[i].radius.x,quad_[i].pos.y + quad_[i].radius.y };

		//Novice::ScreenPrintf(1500, 20 * i, "Flag[%d] = %d", i, isShotFlag_[i]);
	}
}

//弾の描画
void Bullet::Draw() {
	for (int i = 0; i < ammo_; i++) {
		if (isShotFlag_[i]) {
			Novice::DrawQuad(
				int(quad_[i].leftTop.x), int(quad_[i].leftTop.y),
				int(quad_[i].rightTop.x), int(quad_[i].rightTop.y),
				int(quad_[i].leftBottom.x), int(quad_[i].leftBottom.y),
				int(quad_[i].rightBottom.x), int(quad_[i].rightBottom.y),
				quad_[i].imagePos.x, quad_[i].imagePos.y,
				quad_[i].imageWidth, quad_[i].imageHeight,
				quad_[i].image, WHITE
			);
		}
	}
}
