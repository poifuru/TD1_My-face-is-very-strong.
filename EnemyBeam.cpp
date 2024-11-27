#include <Novice.h>
#include <math.h>
#include <corecrt_math_defines.h>
#include "EnemyBeam.h"
#include <time.h>

//コンストラクタ
Beam::Beam() {
	//ビームの数
	beamNumber_ = 3;
	for (int i = 0; i < beamNumber_; i++) {
		//描画(危険信号)
		dangerSignal_[i].pos = { 0.0f,450.0f };
		dangerSignal_[i].radius = { 120.0f,450.0f };
		dangerSignal_[i].leftTop = {};
		dangerSignal_[i].leftBottom = {};
		dangerSignal_[i].rightBottom = {};
		dangerSignal_[i].rightTop = {};
		dangerSignal_[i].imagePos = { 0,0 };
		dangerSignal_[i].imageWidth = { 400 };
		dangerSignal_[i].imageHeight = { 900 };
		dangerSignal_[i].image = images_.dangerSignal;
		dangerSignal_[i].color = {};
		//描画(beam)
		beam_[i].pos = { 0.0f,-750.0f };
		beam_[i].radius = { 120.0f,750.0f };
		beam_[i].leftTop = {};
		beam_[i].leftBottom = {};
		beam_[i].rightBottom = {};
		beam_[i].rightTop = {};
		beam_[i].imagePos = { 0,0 };
		beam_[i].imageWidth = { 400 };
		beam_[i].imageHeight = { 1500 };
		beam_[i].image = images_.beam;
		beam_[i].color = {};
		//危険信号のフラグ
		dangerSignalFlag_[i] = false;
		//ビームのフラグ
		beamFlag_[i] = false;
		//敵のposXランダムな値
		beamRandNumberX_[i] = 0.0f;
		//危険信号からビームに変わる為のタイマー
		transitionTimeSet_ = 5 * 60 * beamNumber_;
		transitionTimer_ = transitionTimeSet_;
		//ビーム中のタイマー
		duringBeamTimeSet_ = 3 * 60 * beamNumber_;
		duringBeamTimer_ = duringBeamTimeSet_;
	}
	//ビームの速度
	beamSpeed_ = 50.0f;
	//音
	enemyDuringBeamSE_ = SE_.enemyDuringBeam;
	enemyDuringBeamHandle_ = -1;
}

//デストラクタ
Beam::~Beam() {

}

//敵のビームの基本的な動き
void Beam::Move() {
	for (int i = 0; i < beamNumber_; i++) {
		//posXにランダムな値を代入
		dangerSignal_[i].pos.x = beamRandNumberX_[i];
		beam_[i].pos.x = beamRandNumberX_[i];
		//危険信号からビームに変わる
		if (transitionTimer_ > 0) {
			transitionTimer_--;
		} else {
			//音
			if (beam_[i].pos.y <= 800.0f) {
				enemyDuringBeamHandle_ = Novice::PlayAudio(enemyDuringBeamSE_, false, 0.0015f);
			}
			//ビームを出す
			if (beam_[i].pos.y <= 500.0f) {
				//速度を追加
				beam_[i].pos.y += beamSpeed_;
			} else {
				//危険信号
				dangerSignalFlag_[i] = false;
				if (duringBeamTimer_ > 0) {
					duringBeamTimer_--;
				} else {
					//速度を追加
					beam_[i].pos.y += beamSpeed_;
				}
			}
		}

		//Novice::ScreenPrintf(1800, 20, "timer = %d", transitionTimer_ / 60 / beamNumber_);
		//Novice::ScreenPrintf(1000, i * 20, "flag = %d , rand = %f , pos = {%f,%f}", dangerSignalFlag_[i], beamRandNumberX_[i], dangerSignal_[i].pos.x, dangerSignal_[i].pos.y);

		//矩形4点の更新(危険信号)
		dangerSignal_[i].leftTop = { dangerSignal_[i].pos.x - dangerSignal_[i].radius.x - 160.0f,dangerSignal_[i].pos.y - dangerSignal_[i].radius.y };
		dangerSignal_[i].rightTop = { dangerSignal_[i].pos.x + dangerSignal_[i].radius.x + 160.0f,dangerSignal_[i].pos.y - dangerSignal_[i].radius.y };
		dangerSignal_[i].leftBottom = { dangerSignal_[i].pos.x - dangerSignal_[i].radius.x - 160.0f,dangerSignal_[i].pos.y + dangerSignal_[i].radius.y };
		dangerSignal_[i].rightBottom = { dangerSignal_[i].pos.x + dangerSignal_[i].radius.x + 160.0f,dangerSignal_[i].pos.y + dangerSignal_[i].radius.y };
		//矩形4点の更新(ビーム)
		beam_[i].leftTop = { beam_[i].pos.x - beam_[i].radius.x - 160.0f,beam_[i].pos.y - beam_[i].radius.y };
		beam_[i].rightTop = { beam_[i].pos.x + beam_[i].radius.x + 160.0f,beam_[i].pos.y - beam_[i].radius.y };
		beam_[i].leftBottom = { beam_[i].pos.x - beam_[i].radius.x - 160.0f,beam_[i].pos.y + beam_[i].radius.y };
		beam_[i].rightBottom = { beam_[i].pos.x + beam_[i].radius.x + 160.0f,beam_[i].pos.y + beam_[i].radius.y };
	}
}

//ビームの描画
void Beam::Draw() {
	for (int i = 0; i < beamNumber_; i++) {
		//危険信号
		if (dangerSignalFlag_[i]) {
			Novice::DrawQuad(
				int(dangerSignal_[i].leftTop.x), int(dangerSignal_[i].leftTop.y),
				int(dangerSignal_[i].rightTop.x), int(dangerSignal_[i].rightTop.y),
				int(dangerSignal_[i].leftBottom.x), int(dangerSignal_[i].leftBottom.y),
				int(dangerSignal_[i].rightBottom.x), int(dangerSignal_[i].rightBottom.y),
				dangerSignal_[i].imagePos.x, dangerSignal_[i].imagePos.y,
				dangerSignal_[i].imageWidth, dangerSignal_[i].imageHeight,
				dangerSignal_[i].image, WHITE
			);
		}
		//ビーム
		if (beamFlag_[i]) {
			Novice::DrawQuad(
				int(beam_[i].leftTop.x), int(beam_[i].leftTop.y),
				int(beam_[i].rightTop.x), int(beam_[i].rightTop.y),
				int(beam_[i].leftBottom.x), int(beam_[i].leftBottom.y),
				int(beam_[i].rightBottom.x), int(beam_[i].rightBottom.y),
				beam_[i].imagePos.x, beam_[i].imagePos.y,
				beam_[i].imageWidth, beam_[i].imageHeight,
				beam_[i].image, WHITE
			);
		}
	}
}