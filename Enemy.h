#pragma once
#include "Object.h"
#include "EnemyBullet.h"
#include "EnemyBeam.h"

class Enemy : public Object {
public://メンバ変数
	//[基本]=======================================
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
	//Movingの速度
	Vector2 movingVelocity_;
	//==============================================
	
	//[fallingAttack]===============================
	//落下攻撃後の戻る場所
	float fallingStartPoint_;
	//落下フラグ
	bool fellFlag_;
	//上がる速度
	float risingVelocity_;
	//==============================================
	
	//[rushAttack]==================================
	//突進攻撃後の戻る場所
	Vector2 rushStartPoint_;
	//突進前の時間
	int timeSetBeforeTheRush_;
	int timerBeforeTheRush_;
	//突撃攻撃回数
	int rushAttackNumber_;
	//テレポートのフラグ
	bool teleportFlag_;
	//==============================================

	//[allDerectionShot]============================
	//弾
	Bullet bullet_;
	//波の幅
	float amplitude_;
	//波の速度
	float waveSpeed_;
	//撃った数
	int shotNumber_;
	//全部の弾がfalseになったら
	bool allShotFalseFlag_;
	//==============================================
	
	//[beam]========================================
	//ビーム
	Beam beam_;
	//ビーム前の場所の記録
	Vector2 beamStartPoint_;
	//ビーム中のボスの速度
	Vector2 duringBeamSpeed_;
	//==============================================

	//[shake]=======================================
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
	//==============================================
public://status
	//HP
	int hp_;
	//攻撃力
	int fallingAttackPower_;//落下攻撃
	int rushAttackPower_;//突進攻撃
	int allDerectionShotPower_;//全方向弾
	int allDerectionPower_;//全方向弾時の突進
public://AI
	//敵の攻撃のタイマー
	int attackCoolTimeSet_;
	int attackCoolTimer_;
	//敵の行動パターン
	int attackNumber_;
public://コンストラクタとデストラクタ
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
