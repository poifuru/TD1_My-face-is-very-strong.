#include <Novice.h>
#include <corecrt_math_defines.h>
#include <math.h>
#include "Player.h"
#include "Enemy.h"
#include "enum.h"
#include <time.h>

//コンストラクタ
Enemy::Enemy() {
	//[基本]=======================================
	//DrawQuadで主に使う
	quad_.pos = { 980.0f,540.0f };
	quad_.radius = { 50.0f,50.0f };
	quad_.leftTop = {};
	quad_.leftBottom = {};
	quad_.rightBottom = {};
	quad_.rightTop = {};
	quad_.imagePos = {0,0};
	quad_.imageWidth = {105};
	quad_.imageHeight = {105};
	quad_.image = images_.bossStupidFace;
	quad_.color = {};
	//プレイヤーとの距離
	length_ = 0.0f;
	//敵の速度
	velocity_ = { 5.0f,0.0f };
	//敵の加速度
	acceleration_ = {};
	//敵の状態
	situation_ = moving;
	//Movingの速度
	movingVelocity_ = {};
	//==============================================

	//[status]======================================
	//HP
	hp_ = 10000;
	//攻撃力
	fallingAttackPower_ = 200;//落下攻撃
	rushAttackPower_ = 100;//突進攻撃
	allDerectionShotPower_ = 20;//全方向弾
	allDerectionPower_ = 50;//全方向弾時の突進
	//==============================================

	//[fallingAttack]===============================
	//落下し始めるポイント
	fallingStartPoint_ = 0.0f;
	//落下し終わったのかを確認するフラグ
	fellFlag_ = false;
	//落下後に上昇する速度
	risingVelocity_ = 1.0f;
	//==============================================
	
	//[rushAttack]==================================
	//突進攻撃後の戻る場所
	rushStartPoint_ = {};
	//突進前の時間
	timeSetBeforeTheRush_ = 1 * 60;//時間設定(n秒x60fps)
	timerBeforeTheRush_ = timeSetBeforeTheRush_;//タイマー
	//突進攻撃回数
	rushAttackNumber_ = {};
	//テレポートのフラグ
	teleportFlag_ = false;
	//==============================================
	
	//[allDerectionShot]============================
	//弾
	bullet_ = {};
	//波の幅
	amplitude_ = 400.0f;
	//波の速度
	waveSpeed_ = {};
	//撃った数
	shotNumber_ = 0;
	//全部の弾がfalseになったら
	allShotFalseFlag_ = false;
	//==============================================
	
	//[beam]========================================
	//ビーム
	beam_ = {};
	//ビーム前の場所の記録
	beamStartPoint_ = {};
	//ビーム中のボスの速度
	duringBeamSpeed_ = { 5.0f,10.0f };
	//==============================================

	//[shake]=======================================
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
	//==============================================

	//AI
	attackCoolTimeSet_ = 5 * 60;//行動パターンのタイマー(秒数 x fps)
	attackCoolTimer_ = attackCoolTimeSet_;//タイマー部分
	attackNumber_ = 0;//確率
}

//デストラクタ
Enemy::~Enemy() {

}

//敵の基本的な動き
void Enemy::Move(const char keys[], const char preKeys[]) {
	//ランダム
	unsigned int currentTime = unsigned(time(nullptr));//乱数
	srand(currentTime);
	//AI
	if (situation_ == moving) {
		if (attackCoolTimer_ > 0) {
			attackCoolTimer_--;
		} else {
			attackNumber_ = rand() % 100 + 1;//確率
			
		}
	}
	
	//実験用(ホントはタイマーで管理)
	if (keys[DIK_E] && !preKeys[DIK_E] && situation_ == moving) {
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
	if (keys[DIK_T] && !preKeys[DIK_T] && situation_ == moving) {
		//元の速度の記録
		movingVelocity_.x = velocity_.x;
		//全方向弾を放ち始める
		situation_ = allDerectionShot;
	}
	if (keys[DIK_Y] && !preKeys[DIK_Y] && situation_ == moving) {
		//元の速度の記録
		movingVelocity_.x = velocity_.x;
		//ビーム後に戻るポイントの設定
		beamStartPoint_.x = quad_.pos.x;
		beamStartPoint_.y = quad_.pos.y;
		//ビームを放ち始める
		situation_ = beam;
		//ビームのposXを決める
		for (int i = 0; i < beam_.beamNumber_; i++) {
			//ランダムなposX
			beam_.beamRandNumberX_[i] = float(rand() % (1920 - 240) + 240);
		}
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
		acceleration_.x = -4.0f;
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

	//[allDerectionShot]============================
	if (situation_ == allDerectionShot) {	
		//シェイクフラグ
		if (!isShaked_) {
			shakeFlag_ = true;
			isShaked_ = true;
		}
		
		if (!shakeFlag_ && isShaked_) {
			//左右移動
			quad_.pos.x += velocity_.x;
			//両端に着いたら反射する
			if (quad_.pos.x - quad_.radius.x <= 0.0f || quad_.pos.x + quad_.radius.x >= 1920.0f) {
				velocity_.x *= -1;
			}
			//上下の波移動
			waveSpeed_ += float(M_PI) / 60.0f;//120fpsで1波
			quad_.pos.y = sinf(waveSpeed_) * amplitude_ + 450.0f;

			//弾が撃たれていなかったら発射する
			if (shotNumber_ < 100) {
				for (int i = 0; i < bullet_.ammo_; i++) {
					if (!bullet_.isShotFlag_[i]) {
						//フラグを立てる
						bullet_.isShotFlag_[i] = true;
						//
						shotNumber_++;

						//敵のposに代入
						bullet_.quad_[i].pos.x = quad_.pos.x;
						bullet_.quad_[i].pos.y = quad_.pos.y;
						break;
					}
				}
			}

			//弾の動き
			bullet_.Move();

			//タイマー
			if (shotNumber_ >= 100) {
				//すべての弾がでているかの確認
				for (bool flag : bullet_.isShotFlag_) {
					allShotFalseFlag_ = true;
					if (flag) {
						allShotFalseFlag_ = false;
						break;
					}
				}
			}

			//Novice::ScreenPrintf(1000, 0, "Number = %d", shotNumber_);

			//撃った弾数がNを超えたら
			if (allShotFalseFlag_ && quad_.pos.y >= 530.0f && quad_.pos.y <= 550.0f) {
				//初期化
				allShotFalseFlag_ = false;
				isShaked_ = false;
				quad_.pos.y = 540.0f;
				waveSpeed_ = 0.0f;
				shotNumber_ = 0;
				velocity_.x = movingVelocity_.x;
				situation_ = moving;
			}
		}
	}
	//==============================================

	//[beam]========================================
	if (situation_ == beam) {
		//シェイクフラグ
		if (!isShaked_) {
			shakeFlag_ = true;
			isShaked_ = true;
		}
		//ボス
		if (!shakeFlag_ && isShaked_) {
			if (quad_.pos.y >= -100.0f) {
				quad_.pos.y -= duringBeamSpeed_.y;
			}

			//ビーム
			for (int i = 0; i < beam_.beamNumber_; i++) {
				//危険信号のフラグ
				if (!beam_.dangerSignalFlag_[i]) {
					beam_.dangerSignalFlag_[i] = true;
				}
				//ビームのフラグ
				if (!beam_.beamFlag_[i]) {
					beam_.beamFlag_[i] = true;
				}
			}

			//ビームの動き
			beam_.Move();

			for (int i = 0; i < beam_.beamNumber_; i++) {
				if (beam_.beam_[i].pos.y >= 1080.0f + beam_.beam_[i].radius.y) {
					if (quad_.pos.y < 540.0f) {
						quad_.pos.y += duringBeamSpeed_.y;
					} else {
						//初期化
						quad_.pos.x = beamStartPoint_.x;
						quad_.pos.y = beamStartPoint_.y;
						isShaked_ = false;
						velocity_.x = movingVelocity_.x;
						beam_.beamFlag_[i] = false;//ビームフラグ
						beam_.beam_[0].pos.y = -750.0f;//ビームのY座標を初期位置に
						beam_.beam_[1].pos.y = -750.0f;//ビームのY座標を初期位置に
						beam_.beam_[2].pos.y = -750.0f;//ビームのY座標を初期位置に
						beam_.transitionTimer_ = beam_.transitionTimeSet_;//危険信号からビームに変わる為のタイマー
						beam_.duringBeamTimer_ = beam_.duringBeamTimeSet_;//ビーム中のタイマー
						situation_ = moving;//シチュエーション
					}
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
	quad_.leftTop = { quad_.pos.x - quad_.radius.x + randNumber_.x - 2.5f,quad_.pos.y - quad_.radius.y + randNumber_.y - 2.5f };
	quad_.rightTop = { quad_.pos.x + quad_.radius.x + randNumber_.x + 2.5f,quad_.pos.y - quad_.radius.y + randNumber_.y - 2.5f };
	quad_.leftBottom = { quad_.pos.x - quad_.radius.x + randNumber_.x - 2.5f,quad_.pos.y + quad_.radius.y + randNumber_.y + 2.5f};
	quad_.rightBottom = { quad_.pos.x + quad_.radius.x + randNumber_.x + 2.5f,quad_.pos.y + quad_.radius.y + randNumber_.y + 2.5f };
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
		quad_.image, WHITE
	);
	//弾
	bullet_.Draw();
	//ビーム
	beam_.Draw();
}
