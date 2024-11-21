#include <Novice.h>
#include "Player.h"
#include "Enemy.h"

//攻撃手段
enum situation_ {
	moving,
	fallingAttack,
	rushAttack,
	AllderectionShot
};
//突進攻撃回数
enum rushAttackNumber {
	firstAttack,
	secondAttack,
	thirdAttack,
	remove
};

//コンストラクタ
Enemy::Enemy() {
	//DrawQuadで主に使う
	quad_.pos = { 980.0f,540.0f };
	quad_.radius = { 50.0f,50.0f };
	quad_.leftTop = {};
	quad_.leftBottom = {};
	quad_.rightBottom = {};
	quad_.rightTop = {};
	quad_.imagePos = {};
	quad_.imageWidth = {};
	quad_.imageHeight = {};
	quad_.image = {};
	quad_.color = {};
	//プレイヤーとの距離
	length_ = 0.0f;
	//敵の速度
	velocity_ = { 5.0f,0.0f };
	//敵の加速度
	acceleration_ = {};
	//敵の状態
	situation_ = moving;
	//落下し始めるポイント
	fallingStartPoint_ = 0.0f;
	//落下し終わったのかを確認するフラグ
	fellFlag_ = false;
	//落下後に上昇する速度
	risingVelocity_ = 1.0f;
	//突進攻撃後の戻る場所
	rushStartPoint_ = {};
	//突進前の時間
	timeSetBeforeTheRush_ = 1 * 60;//時間設定(n秒x60fps)
	timerBeforeTheRush_ = timeSetBeforeTheRush_;//タイマー
	//突進攻撃回数
	rushAttackNumber_ = {};
	//テレポートのフラグ
	teleportFlag_ = false;
	//ランダム
	randNumber_ = {};//ランダムな値xとy
	kRandMax_ = 21.0f;//ランダムな値のMAX値(固定)
	randMax_ = kRandMax_;//ランダムな値のMAX値(変動)
	randMaxHalf_ = (randMax_ - 1.0f) / 2.0f;//ランダムな値のマイナス分(変動)
	//シェイクのタイマー
	shakeFlag_ = false;//シェイクのフラグ
	shakeTimeSecond_ = 3;//シェイクの秒数設定
	shakeTimeSet_ = shakeTimeSecond_ * 60;//シェイクの時間設定
	shakeTimer_ = shakeTimeSet_;//シェイクの時間
	isShaked_ = false;//シェイクしましたよフラグ
	//Movingの速度
	movingVelocity_ = {};
}

//デストラクタ
Enemy::~Enemy() {

}

//敵の基本的な動き
void Enemy::Move(const char keys[], const char preKeys[]) {
	//実験用(ホントはタイマーで管理)
	if(keys[DIK_E] && !preKeys[DIK_E] && situation_ == moving) {
		//元の速度の記録
		movingVelocity_.x = velocity_.x;
		//落下攻撃を始める
		situation_ = fallingAttack;
		//落下し始めるポイントを設定
		fallingStartPoint_ = quad_.pos.y;
	}
	if (keys[DIK_R] && !preKeys[DIK_R] && situation_ == moving) {
		//元の速度の記録
		movingVelocity_.x = velocity_.x;
		//突進攻撃を始める
		situation_ = rushAttack;
		//突進攻撃回数
		rushAttackNumber_ = firstAttack;
		//突進攻撃後に戻るポイントの設定
		rushStartPoint_.x = quad_.pos.x;
		rushStartPoint_.y = quad_.pos.y;
	}
	
	//[moving]======================================
	//左右移動
	if (situation_ == moving) {
		quad_.pos.x += velocity_.x;

		//両端に着いたら反射する
		if (quad_.pos.x - quad_.radius.x <= 0.0f || quad_.pos.x + quad_.radius.x >= 1920.0f) {
			velocity_.x *= -1;
		}
	}
	//==============================================

	//[fallingAttack]===============================
	if (situation_ == fallingAttack) {
		//加速度を設定
		acceleration_.y = 5.0f;
		//シェイクフラグ
		if (!isShaked_) {
			shakeFlag_ = true;
			isShaked_ = true;
		}
		if (!shakeFlag_ && isShaked_) {
			//速度に加速度を追加する
			if (!fellFlag_) {
				velocity_.y += acceleration_.y;
			} else {
				velocity_.y -= risingVelocity_;
			}
			//Enemyのposに速度を追加する
			quad_.pos.y += velocity_.y;

			//地面に着いたら
			if (quad_.pos.y + quad_.radius.y >= 900.0f) {
				quad_.pos.y = 900.0f - quad_.radius.y;
				velocity_.y = 0.0f;
				fellFlag_ = true;
			}
			//落下し始めるポイントに戻ったら
			if (quad_.pos.y <= fallingStartPoint_ && fellFlag_) {
				//初期化
				quad_.pos.y = fallingStartPoint_;
				velocity_.x = movingVelocity_.x;
				velocity_.y = 0.0f;
				fellFlag_ = false;
				isShaked_ = false;
				situation_ = moving;
			}
		}
	}
	//==============================================

	//[rushAttack]==================================
	if (situation_ == rushAttack) {
		//加速度を設定
		acceleration_.x = -1.0f;
		//シェイクフラグ
		if (!isShaked_) {
			shakeFlag_ = true;
			isShaked_ = true;
		}
		//震え終わったらテレポート
		if (!shakeFlag_ && isShaked_ && !teleportFlag_) {
			//テレポート先
			quad_.pos.x = 1850.0f;
			quad_.pos.y = 850.0f;
			teleportFlag_ = true;
		}
		if (teleportFlag_) {
			if (rushAttackNumber_ == firstAttack) {//1回目の攻撃
				//突進攻撃させる
				if (quad_.pos.x >= -100.0f) {
					velocity_.x += acceleration_.x;
				}
				//Enemyのposに速度を追加する
				quad_.pos.x += velocity_.x;

				if (quad_.pos.x <= -100.0f) {
					quad_.pos.x = -100.0f;
					quad_.pos.y = 700.0f;
					velocity_.x = 0.0f;
					rushAttackNumber_ = secondAttack;
				}
			} else if (rushAttackNumber_ == secondAttack) {//2回目の攻撃
				//突進攻撃させる
				if (quad_.pos.x >= -100.0f) {
					velocity_.x += acceleration_.x;
				}
				//Enemyのposに速度を追加する
				quad_.pos.x -= velocity_.x;

				if (quad_.pos.x >= 2020.0f) {
					quad_.pos.x = 2020.0f;
					quad_.pos.y = 850.0f;
					velocity_.x = 0.0f;
					rushAttackNumber_ = thirdAttack;
				}
			} else if (rushAttackNumber_ == thirdAttack) {//3回目の攻撃
				//突進攻撃させる
				if (quad_.pos.x >= -100.0f) {
					velocity_.x += acceleration_.x;
				}
				//Enemyのposに速度を追加する
				quad_.pos.x += velocity_.x;

				if (quad_.pos.x <= -100.0f) {
					//初期化
					quad_.pos.x = -100.0f;
					quad_.pos.y = rushStartPoint_.y;
					velocity_.x = 0.0f;
					rushAttackNumber_ = remove;
				}
			} else if (rushAttackNumber_ == remove) {//元の位置に戻る
				//突進攻撃させる
				if (quad_.pos.x >= -100.0f) {
					velocity_.x += acceleration_.x;
				}
				//Enemyのposに速度を追加する
				quad_.pos.x -= velocity_.x;

				if (quad_.pos.x >= rushStartPoint_.x) {
					//初期化
					quad_.pos.x = rushStartPoint_.x;
					quad_.pos.y = rushStartPoint_.y;
					velocity_.x = movingVelocity_.x;
					isShaked_ = false;
					teleportFlag_ = false;
					situation_ = moving;
					rushAttackNumber_ = firstAttack;
				}
			}
		}
	}
	//==============================================
	
	//シェイクフラグ
	if (shakeFlag_) {
		if (shakeTimer_ > 0 && randMax_ > 0) {
			shakeTimer_--;
			if (shakeTimer_ % 4 == 0) {
				randMax_ -= 2;
			}
			//シェイクする
			randNumber_.x = float(rand() % int(randMax_) - int(randMaxHalf_));
			randNumber_.y = float(rand() % int(randMax_) - int(randMaxHalf_));
		} else {
			shakeTimer_ = shakeTimeSet_;
			randMax_ = kRandMax_;
			shakeFlag_ = false;
		}
	}

	//矩形4点の更新
	quad_.leftTop = { quad_.pos.x - quad_.radius.x + randNumber_.x,quad_.pos.y - quad_.radius.y + randNumber_.y };
	quad_.rightTop = { quad_.pos.x + quad_.radius.x + randNumber_.x,quad_.pos.y - quad_.radius.y + randNumber_.y };
	quad_.leftBottom = { quad_.pos.x - quad_.radius.x + randNumber_.x,quad_.pos.y + quad_.radius.y + randNumber_.y };
	quad_.rightBottom = { quad_.pos.x + quad_.radius.x + randNumber_.x,quad_.pos.y + quad_.radius.y + randNumber_.y };
}

//敵を描画する関数
void Enemy::Draw() {
	Novice::DrawQuad(
		int(quad_.leftTop.x), int(quad_.leftTop.y),
		int(quad_.rightTop.x), int(quad_.rightTop.y),
		int(quad_.leftBottom.x), int(quad_.leftBottom.y),
		int(quad_.rightBottom.x), int(quad_.rightBottom.y),
		quad_.imagePos.x, quad_.imagePos.y,
		quad_.imageWidth, quad_.imageHeight,
		quad_.image.white1x1, WHITE
	);
}
