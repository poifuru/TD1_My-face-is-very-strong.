#pragma once
#include "Object.h"
#include "EnemyBullet.h"

class Enemy : public Object {
public://メンバ変数

	//画像
	Images images_;
	//速度
	Vector2 velocity_;
	//加速度
	Vector2 acceleration_;
	//長さ
	float length_;
	//状態
	int situation_;
	//落下攻撃後の戻る場所
	float fallingStartPoint_;
	//落下フラグ
	bool fellFlag_;
	//上がる速度
	float risingVelocity_;
	//突進攻撃後の戻る場所
	Vector2 rushStartPoint_;
	//突進前の時間
	int timeSetBeforeTheRush_;
	int timerBeforeTheRush_;
	//突撃攻撃回数
	int rushAttackNumber_;
	//テレポートのフラグ
	bool teleportFlag_;
	//ランダム
	Vector2 randNumber_;//ランダムな値xとy
	float kRandMax_;//ランダムな値のMAX値(固定)
	float randMax_;//ランダムな値のMAX値(変動)
	float randMaxHalf_;//ランダムな値のマイナス分(変動)
	//シェイクのタイマー
	bool shakeFlag_;//シェイクのフラグ
	int shakeTimeSecond_;//シェイクの秒数設定
	int shakeTimeSet_;//シェイクの時間設定
	int shakeTimer_;//シェイクの時間
	bool isShaked_;//シェイクしましたよフラグ
	//Movingの速度
	Vector2 movingVelocity_;
	//弾
	Bullet bullet_ = {};
	//波の幅
	float amplitude_;
	//波の速度
	float waveSpeed_;
	//撃った数
	int shotNumber_;
	//全部の弾がfalseになったら
	bool allShotFalseFlag_;
	//HP
	int hp_;
	//攻撃力
	int fallingAttackPower_;//落下攻撃
	int rushAttackPower_;//突進攻撃
	int allDerectionShotPower_;//全方向弾
	int allDerectionPower_;//全方向弾時の突進

	//コンストラクタの宣言
	Enemy();
	//デストラクタの宣言
	~Enemy();
public://メンバ関数
	//基本的な動き
	void Move(const char keys[], const char preKeys[]);
	//描画する
	void Draw();
};
