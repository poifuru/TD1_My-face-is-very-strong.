//<>ヘッダーファイル
#include <Novice.h>

//""ヘッダーファイル
#include "struct.h"
#include "player.h"
#include "Enemy.h"
#include "Ultimate.h"
#include "CollisionCheck.h"
#include "debug.h"
#include "hud.h"

const char kWindowTitle[] = "LC1A_25_マスヤ_ゴウ_タイトル";

//コメントエリア
/*ファイルを訂正しました。11/21(木)*/

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1920, 1080);
	Novice::SetWindowMode(kFullscreen);

	//キー入力を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int isStop = false;

	//scene
	int scene = title;

	//画像
	Images image;
	//BGM
	BGMs BGM;
	//SE
	SEs SE;

	//カットイン
	int cutIn_image = image.playerUlt;
	//ULT
	int ULTGo_image = image.ULTGo;
	int notULT_image = image.notULT;

	//hud
	int AKey_image[2] = {
		image.AKey,
	    image.onAKey
	};
	int DKey_image[2] = {
		image.Dkey,
		image.onDKey
	};
	int QKey_image[2] = {
		image.QKey,
		image.onQKey
	};
	int SPACEKey_image[2] = {
		image.SPACEKey,
		image.onSPACEKey
	};
	int weponGuide_image = image.weponGuide;
	//int Num_image = image.num;

	//背景
	int backGround_image = image.backGround;
	//game背景
	int gameBackGround_image = image.gameBackGround;
	//背景のカバー
	int gameBackGroundCover_image = image.gameBackGroundCover;
	//title
	int title_image = image.title;
	Animation title_animation;
	title_animation.x = 0;
	title_animation.timeSet = 30;
	title_animation.timer = title_animation.timeSet;
	//gameClear
	int gameClear_image = image.gameClear;
	Animation gameClear_animation;
	gameClear_animation.x = 0;
	gameClear_animation.timeSet = 30;
	gameClear_animation.timer = gameClear_animation.timeSet;
	//gameOver
	int gameOver_image = image.gameOver;
	Animation gameOver_animation;
	gameOver_animation.x = 0;
	gameOver_animation.timeSet = 30;
	gameOver_animation.timer = gameOver_animation.timeSet;
	//BGMs
	//title
	int titleBGM = BGM.title;
	int titleHandle = -1;
	//game
	int gameBGM = BGM.game;
	int gameHandle = -1;
	//gameClear
	int gameClearBGM = BGM.gameClear;
	int gameClearHandle = -1;
	//gameOver
	int gameOverBGM = BGM.gameOver;
	int gameOverHandle = -1;
	//sistemClick
	int sistemClickSE = SE.sistemClick;
	int sistemClickHandle = -1;

	Player* player = new Player();
	Enemy* enemy = new Enemy();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓処理ここから
		///

		switch (scene) {
		case title:
			///===========================
			/// ↓↓↓ 更新処理 ↓↓↓
			///===========================
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				//sistemClick
				sistemClickHandle = Novice::PlayAudio(sistemClickSE, false, 0.1f);
				
				//初期化
				//playerの座標
				player->quad_.pos.x = 300.0f;
				player->quad_.pos.y = 868.0f;
				//playerのHP
				player->HP_ = 1000;
				player->weapon_->weaponMode_ = 0;
				//enemyの座標
				enemy->quad_.pos.x = 980.0f;
				enemy->quad_.pos.y = 540.0f;
				//enemyのHP
				enemy->hp_ = 10000;

				//Lets game
				scene = game;

				//ULTのリセット
				resetULT();
			}

			//titleの画像入れ替え
			if (title_animation.timer > 0) {
				title_animation.timer--;
			} else {
				title_animation.timer = title_animation.timeSet;
				if (title_animation.x < 1) {
					title_animation.x++;
				} else {
					title_animation.x = 0;
				}
			}

			///===========================
			/// ↑↑↑ 更新処理 ↑↑↑
			///===========================
			///===========================
			/// ↓↓↓ 描画処理 ↓↓↓
			///===========================
			//背景
			Novice::DrawQuad(0, 0, 1920, 0, 0, 1080, 1920, 1080, 0, 0, 1920, 1080, backGround_image, WHITE);
			//title
			Novice::DrawQuad(0, 0, 1920, 0, 0, 1080, 1920, 1080, title_animation.x * 1920, 0, 1920, 1080, title_image, WHITE);

			///===========================
			/// ↑↑↑ 描画処理 ↑↑↑
			///===========================
			break;
		case game:
			///===========================
			/// ↓↓↓ 更新処理 ↓↓↓
			///===========================

			//プレイヤーの停止
			isStop = Stop(isStop);

			if (!isStop) {
				//プレイヤーの更新
				player->Update(keys, preKeys, enemy);

				//敵とプレイヤーの当たり判定
				collisionCheck(player, enemy);

				//敵の更新
				enemy->Move();

			}

			//ULTの更新
			ULTUpdate(keys, preKeys, enemy);

			//playerのHPが0以下にならない
			if (player->HP_ <= 0) {
				player->HP_ = 0;
			}
			//enemyのHPが0以下にならない
			if (enemy->hp_ <= 0) {
				enemy->hp_ = 0;
			}

			//gameClearへ
			if (enemy->hp_ <= 0 && enemy->situation_ == moving) {
				scene = gameClear;
			}
			//gameOverへ
			if (player->HP_ <= 0 && enemy->situation_ == moving) {
				scene = gameOver;
				player->invincibleTimer_ = 120;
				player->invincible_ = 0;
			}

			///===========================
			/// ↑↑↑ 更新処理 ↑↑↑
			///===========================
			///===========================
			/// ↓↓↓ 描画処理 ↓↓↓
			///===========================
			//背景
			Novice::DrawQuad(0, 0, 1920, 0, 0, 1080, 1920, 1080, 0, 0, 1920, 1080, gameBackGround_image, WHITE);

			//敵の描画
			enemy->Draw();

			//Barの描画
			DrawBar(ULTGo_image, notULT_image, keys, preKeys);

			//地面
			//Novice::DrawBox(0, 900, 1920, 180, 0.0f, WHITE, kFillModeSolid);
			Novice::DrawQuad(0, 900, 1920, 900, 0, 1080, 1920, 1080, 0, 0, 1920, 180, gameBackGroundCover_image, WHITE);

			//プレイヤーの描画
			player->Draw();

			//hudの描画
			DrawHud(keys, AKey_image, DKey_image, QKey_image, SPACEKey_image , weponGuide_image/*, Num_image*/);

			//カットインの描画
			DrawCutIn(cutIn_image);

			//デバッグ用
			debugprint(player, enemy);
			///===========================
			/// ↑↑↑ 描画処理 ↑↑↑
			///===========================
			break;
		case gameClear:
			///===========================
			/// ↓↓↓ 更新処理 ↓↓↓
			///===========================
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				//sistemClick
				sistemClickHandle = Novice::PlayAudio(sistemClickSE, false, 0.1f);
				
				scene = title;
			}

			//gameClearの画像入れ替え
			if (gameClear_animation.timer > 0) {
				gameClear_animation.timer--;
			} else {
				gameClear_animation.timer = gameClear_animation.timeSet;
				if (gameClear_animation.x < 1) {
					gameClear_animation.x++;
				} else {
					gameClear_animation.x = 0;
				}
			}
			///===========================
			/// ↑↑↑ 更新処理 ↑↑↑
			///===========================
			///===========================
			/// ↓↓↓ 描画処理 ↓↓↓
			///===========================
			//背景
			Novice::DrawQuad(0, 0, 1920, 0, 0, 1080, 1920, 1080, 0, 0, 1920, 1080, backGround_image, WHITE);
			//gameClear
			Novice::DrawQuad(0, 0, 1920, 0, 0, 1080, 1920, 1080, gameClear_animation.x * 1920, 0, 1920, 1080, gameClear_image, WHITE);
			///===========================
			/// ↑↑↑ 描画処理 ↑↑↑
			///===========================
			break;
		case gameOver:
			///===========================
			/// ↓↓↓ 更新処理 ↓↓↓
			///===========================
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				//sistemClick
				sistemClickHandle = Novice::PlayAudio(sistemClickSE, false, 0.1f);
				
				scene = title;
			}

			//gameOverの画像入れ替え
			if (gameOver_animation.timer > 0) {
				gameOver_animation.timer--;
			} else {
				gameOver_animation.timer = gameOver_animation.timeSet;
				if (gameOver_animation.x < 1) {
					gameOver_animation.x++;
				} else {
					gameOver_animation.x = 0;
				}
			}
			///===========================
			/// ↑↑↑ 更新処理 ↑↑↑
			///===========================
			///===========================
			/// ↓↓↓ 描画処理 ↓↓↓
			///===========================
			//背景
			Novice::DrawQuad(0, 0, 1920, 0, 0, 1080, 1920, 1080, 0, 0, 1920, 1080, backGround_image, WHITE);
			//gameOver
			Novice::DrawQuad(0, 0, 1920, 0, 0, 1080, 1920, 1080, gameOver_animation.x * 1920, 0, 1920, 1080, gameOver_image, WHITE);
			///===========================
			/// ↑↑↑ 描画処理 ↑↑↑
			///===========================
			break;
		}

		///// BGM /////
		switch (scene) {
		case title:
			Novice::StopAudio(gameOverHandle);
			Novice::StopAudio(gameHandle);
			Novice::StopAudio(gameClearHandle);
			if (!Novice::IsPlayingAudio(titleHandle) || titleHandle == -1) {
				titleHandle = Novice::PlayAudio(titleBGM, true, 0.03f);
			}
			break;
		case game:
			Novice::StopAudio(titleHandle);
			Novice::StopAudio(gameOverHandle);
			Novice::StopAudio(gameClearHandle);
			if (!Novice::IsPlayingAudio(gameHandle) || gameHandle == -1) {
				gameHandle = Novice::PlayAudio(gameBGM, true, 0.03f);
			}
			break;
		case gameClear:
			Novice::StopAudio(titleHandle);
			Novice::StopAudio(gameOverHandle);
			Novice::StopAudio(gameHandle);
			if (!Novice::IsPlayingAudio(gameClearHandle) || gameClearHandle == -1) {
				gameClearHandle = Novice::PlayAudio(gameClearBGM, true, 0.02f);
			}
			break;
		case gameOver:
			Novice::StopAudio(titleHandle);
			Novice::StopAudio(gameHandle);
			Novice::StopAudio(gameClearHandle);
			if (!Novice::IsPlayingAudio(gameOverHandle) || gameOverHandle == -1) {
				gameOverHandle = Novice::PlayAudio(gameOverBGM, true, 0.03f);
			}
			break;
		}
		///
		/// ↑処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
