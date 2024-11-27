#include "Weapon.h"
#include <Novice.h>
#include <math.h>

Weapon::Weapon() {
	sword_.pos = { 300.0f, 868.0f };
	sword_.radius = { 32.0f, 32.0f };
	sword_.leftTop = {};
	sword_.leftBottom = {};
	sword_.rightBottom = {};
	sword_.rightTop = {};
	sword_.drawLeftTop = {};
	sword_.drawLeftBottom = {};
	sword_.drawRightBottom = {};
	sword_.drawRightTop = {};
	sword_.imagePos = {};
	sword_.imageWidth = 32;
	sword_.imageHeight = 32;
	sword_.image = images_.white1x1;
	sword_.color = RED;
	attack_ = 0;
	attackingTimer_ = 0;

	gun_.pos = { 300.0f, 868.0f };
	gun_.radius = { 32.0f, 32.0f };
	gun_.leftTop = {};
	gun_.leftBottom = {};
	gun_.rightBottom = {};
	gun_.rightTop = {};
	gun_.drawLeftTop = {};
	gun_.drawLeftBottom = {};
	gun_.drawRightBottom = {};
	gun_.drawRightTop = {};
	gun_.imagePos = {};
	gun_.imageWidth = 32;
	gun_.imageHeight = 32;
	gun_.image = images_.white1x1;
	gun_.color = BLUE;

	for (int i = 0; i < kBulletNum; i++) {
		bullet_[i].pos = { 300.0f, 868.0f };
		bulletSpeed_[i] = { 50.0f, 50.0f };
		bullet_[i].radius = { 10.0f, 10.0f };
		bullet_[i].leftTop = {};
		bullet_[i].leftBottom = {};
		bullet_[i].rightBottom = {};
		bullet_[i].rightTop = {};
		bullet_[i].drawLeftTop = {};
		bullet_[i].drawLeftBottom = {};
		bullet_[i].drawRightBottom = {};
		bullet_[i].drawRightTop = {};
		bullet_[i].imagePos = { 0, 0 };
		bullet_[i].imageWidth = 32;
		bullet_[i].imageHeight = 32;
		bullet_[i].image = images_.white1x1;
		bullet_[i].color = GREEN;
		isShot_[i] = false;
		bulletVec_[i] = {};
		vectorToTarget_[i] = {};
	}

	for (int i = 0; i < kMaxAttack; i++) {
		startPos[i] = {};
		endPos[i] = {};
		easeT[i] = {};
		isPush[i] = {};
		isEase[i] = {};
	}

	weaponMode_ = 0; //0が剣　1が銃
	wheelScroll_ = 60;
	readyToFire_ = true;
	shotCoolTime_ = 6;
}

void Weapon::Update(Enemy* enemy/*, const char* keys*/) {
	//プレイヤーの近くに武器をだすよ
	sword_.leftTop = { sword_.pos.x - (sword_.radius.x / 2), sword_.pos.y - sword_.radius.y };
	sword_.rightTop = { sword_.pos.x + (sword_.radius.x / 2), sword_.pos.y - sword_.radius.y };
	sword_.leftBottom = { sword_.pos.x - (sword_.radius.x / 2), sword_.pos.y + sword_.radius.y };
	sword_.rightBottom = { sword_.pos.x + (sword_.radius.x / 2), sword_.pos.y + sword_.radius.y };

	gun_.leftTop = { gun_.pos.x + (gun_.radius.x * 2), gun_.pos.y - (gun_.radius.y / 2) };
	gun_.rightTop = { gun_.pos.x + (gun_.radius.x * 4), gun_.pos.y - (gun_.radius.y / 2) };
	gun_.leftBottom = { gun_.pos.x + (gun_.radius.x * 2), gun_.pos.y + (gun_.radius.y / 2) };
	gun_.rightBottom = { gun_.pos.x + (gun_.radius.x * 4), gun_.pos.y + (gun_.radius.y / 2) };

	for (int i = 0; i < kBulletNum; i++) {
		bullet_[i].leftTop = { bullet_[i].pos.x - bullet_[i].radius.x, bullet_[i].pos.y - bullet_[i].radius.y };
		bullet_[i].rightTop = { bullet_[i].pos.x + bullet_[i].radius.x, bullet_[i].pos.y - bullet_[i].radius.y };
		bullet_[i].leftBottom = { bullet_[i].pos.x - bullet_[i].radius.x, bullet_[i].pos.y + bullet_[i].radius.y };
		bullet_[i].rightBottom = { bullet_[i].pos.x + bullet_[i].radius.x, bullet_[i].pos.y + bullet_[i].radius.y };
	}

	//==============攻撃！=================
	//武器の切り替え
	wheelScroll_ += Novice::GetWheel();
	if (wheelScroll_ == 60) {
		weaponMode_ = 0;
	}
	if (wheelScroll_ > 60) {
		wheelScroll_ = 60;
	}
	if (wheelScroll_ == -60) {
		weaponMode_ = 1;
	}
	if (wheelScroll_ < -60) {
		wheelScroll_ = -60;
	}

	//剣モードの処理
	if (weaponMode_ == 0) {
		//連続攻撃の状態(受付時間を過ぎたら自動的に1段目の攻撃からになる)
		if (attack_ == 0 && Novice::IsTriggerMouse(0)) {
			attack_ = 1;
			attackingTimer_ = 60;
		}
		else if (attack_ == 1 && Novice::IsTriggerMouse(0) && attackingTimer_ <= 30) {
			attack_ = 2;
			attackingTimer_ = 60;
		}
		else if (attack_ == 2 && Novice::IsTriggerMouse(0) && attackingTimer_ <= 30) {
			attack_ = 3;
			attackingTimer_ = 60;
		}
		if (attack_ >= 1 && attackingTimer_ == 0) {
			attack_ = 0;
		}

		//attack_が0の時にイージングに使う変数の初期化
		if (attack_ == 0) {
			startPos[0] = { sword_.pos.x - (sword_.radius.x * 3), sword_.pos.y - (sword_.radius.y * 3) };
			endPos[0] = { sword_.pos.x, sword_.pos.y };
			easeT[0] = {};
			isPush[0] = {};
			isEase[0] = {};
			startPos[1] = {};
			endPos[1] = {};
			easeT[1] = {};
			isPush[1] = {};
			isEase[1] = {};
			startPos[2] = {};
			endPos[2] = {};
			easeT[2] = {};
			isPush[2] = {};
			isEase[2] = {};
		}

		//連続攻撃一個一個の処理
		if (attack_ == 1) {
			attackingTimer_--;

			//イージングでうごかす1
			isPush[0] = 1;
			isEase[0] = 1;
			

			if (isPush[0] == 1) {
				if (isEase[0] == 1) {
					easeT[0] += 1.0f / 60.0f;
				}
				if (easeT[0] > 1.0f) {
					easeT[0] = 1.0f;
				}
				if (easeT[0] == 1.0f) {
					isEase[0] = 0;
					isPush[0] = 0;
				}
			}
			lerp(startPos[0], endPos[0], sword_.pos, easeInBack(easeT[0]));

			//sword_.pos.x = startPos[0].x * (1 - float(t[0])) + (endPos[0].x * float(t[0]));
		}
		else if (attack_ == 2) {
			attackingTimer_--;

			//イージングでうごかす2

		}
		else if (attack_ == 3) {
			attackingTimer_--;

			//イージングでうごかす3

		}

	}

	//銃モードの処理
	else if (weaponMode_ == 1) {
		for (int i = 0; i < kBulletNum; i++) {
			//!isShotの時に敵に向かうベクトルを作っておく
			if (!isShot_[i]) {
				vectorToTarget_[i] = { enemy->quad_.pos.x - bullet_[i].pos.x , enemy->quad_.pos.y - bullet_[i].pos.y };

				//正規化
				float length = sqrtf(vectorToTarget_[i].x * vectorToTarget_[i].x + vectorToTarget_[i].y * vectorToTarget_[i].y);

				if (length != 0.0f) {
					bulletVec_[i].x = vectorToTarget_[i].x / length;
					bulletVec_[i].y = vectorToTarget_[i].y / length;
				}
			}

			//連射弾
			if (readyToFire_ == 1)
			{
				if (!isShot_[i])
				{
					readyToFire_ = 0;
					isShot_[i] = 1;
					break;
				}
			}
		}
	}

	//クールタイムの処理
	if (readyToFire_ == 0)
	{
		shotCoolTime_--;
		if (shotCoolTime_ <= 0)
		{
			shotCoolTime_ = 6;
			readyToFire_ = 1;
		}
	}

	for (int i = 0; i < kBulletNum; i++) {
		//弾の移動処理
		if (isShot_[i]) {
			bullet_[i].pos.x += bulletVec_[i].x * bulletSpeed_[i].x;
			bullet_[i].pos.y += bulletVec_[i].y * bulletSpeed_[i].y;
		}

		//弾が画面外に出た時にfalseにする処理
		if (bullet_[i].pos.x + bullet_[i].radius.x >= 1920 ||
			bullet_[i].pos.x - bullet_[i].radius.x <= 0 ||
			bullet_[i].pos.y + bullet_[i].radius.y >= 1080 ||
			bullet_[i].pos.y - bullet_[i].radius.y <= 0) {
			isShot_[i] = 0;
		}
	}

	//描画用に座標を更新
	sword_.drawLeftTop = { sword_.leftTop };
	sword_.drawRightTop = { sword_.rightTop };
	sword_.drawLeftBottom = { sword_.leftBottom };
	sword_.drawRightBottom = { sword_.rightBottom };

	gun_.drawLeftTop = { gun_.leftTop };
	gun_.drawRightTop = { gun_.rightTop };
	gun_.drawLeftBottom = { gun_.leftBottom };
	gun_.drawRightBottom = { gun_.rightBottom };

	for (int i = 0; i < kBulletNum; i++) {
		bullet_[i].drawLeftTop = { bullet_[i].leftTop };
		bullet_[i].drawRightTop = { bullet_[i].rightTop };
		bullet_[i].drawLeftBottom = { bullet_[i].leftBottom };
		bullet_[i].drawRightBottom = { bullet_[i].rightBottom };
	}
}

void Weapon::Draw() {
	if (weaponMode_ == 0) {
		Novice::DrawQuad(
			int(sword_.drawLeftTop.x), int(sword_.drawLeftTop.y),
			int(sword_.drawRightTop.x), int(sword_.drawRightTop.y),
			int(sword_.drawLeftBottom.x), int(sword_.drawLeftBottom.y),
			int(sword_.drawRightBottom.x), int(sword_.drawRightBottom.y),
			sword_.imagePos.x, sword_.imagePos.y, sword_.imageWidth, sword_.imageHeight,
			sword_.image, sword_.color
		);
	}
	else if (weaponMode_ == 1) {
		Novice::DrawQuad(
			int(gun_.drawLeftTop.x), int(gun_.drawLeftTop.y),
			int(gun_.drawRightTop.x), int(gun_.drawRightTop.y),
			int(gun_.drawLeftBottom.x), int(gun_.drawLeftBottom.y),
			int(gun_.drawRightBottom.x), int(gun_.drawRightBottom.y),
			gun_.imagePos.x, gun_.imagePos.y, gun_.imageWidth, gun_.imageHeight,
			gun_.image, gun_.color
		);
	}

	for (int i = 0; i < kBulletNum; i++) {
		if (isShot_[i]) {
			Novice::DrawQuad(
				int(bullet_[i].drawLeftTop.x), int(bullet_[i].drawLeftTop.y),
				int(bullet_[i].drawRightTop.x), int(bullet_[i].drawRightTop.y),
				int(bullet_[i].drawLeftBottom.x), int(bullet_[i].drawLeftBottom.y),
				int(bullet_[i].drawRightBottom.x), int(bullet_[i].drawRightBottom.y),
				bullet_[i].imagePos.x, bullet_[i].imagePos.y, bullet_[i].imageWidth, bullet_[i].imageHeight,
				bullet_[i].image, bullet_[i].color
			);
		}
	}

}
