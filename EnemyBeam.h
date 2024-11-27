#pragma once
#include "struct.h"

class Beam {
public://メンバ変数
	//画像
	Images images_;
	//ビームの数
	int beamNumber_;
	//描画(危険信号)
	Quad dangerSignal_[3];
	//描画(ビーム)
	Quad beam_[3];
	//危険信号のフラグ
	bool dangerSignalFlag_[3];
	//ビームのフラグ
	bool beamFlag_[3];
	//ビームの速度
	float beamSpeed_;
	//敵のposXランダムな値
	float beamRandNumberX_[3];
	//危険信号からビームに変わる為のタイマー
	int transitionTimeSet_;
	int transitionTimer_;
	//ビーム中のタイマー
	int duringBeamTimeSet_;
	int duringBeamTimer_;
public://コンストラクタとデストラクタ
	//コンストラクタ
	Beam();
	//デストラクタ
	~Beam();
public://メンバ関数
	//基本的な動き
	void Move();
	//描画
	void Draw();
};
