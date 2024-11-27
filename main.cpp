//<>ヘッダーファイル
#include <Novice.h>

//""ヘッダーファイル
#include "struct.h"
#include "player.h"
#include "Enemy.h"
#include "Ultimate.h"
#include "CollisionCheck.h"
#include "debug.h"

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

	//scene
	int scene = title;
	//画像
	Images image;
	//背景
	int backGround_image = image.backGround;
	//game背景
	int gameBackGround_image = image.gameBackGround;
	//背景のカバー
	int gameBackGroundCover_image = image.gameBackGroundCover;

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
				//初期化
				//playerの座標
				player->quad_.pos.x = 300.0f;
				player->quad_.pos.y = 868.0f;
				//playerのHP
				player->HP_ = 1000;
				//enemyの座標
				enemy->quad_.pos.x = 980.0f;
				enemy->quad_.pos.y = 540.0f;
				//enemyのHP
				enemy->hp_ = 10000;

				//Lets game
				scene = game;
			}
			///===========================
			/// ↑↑↑ 更新処理 ↑↑↑
			///===========================
			///===========================
			/// ↓↓↓ 描画処理 ↓↓↓
			///===========================
			//背景
				Novice::DrawQuad(0, 0, 1920, 0, 0, 1080, 1920, 1080, 0, 0, 1920, 1080, backGround_image, WHITE);
			///===========================
			/// ↑↑↑ 描画処理 ↑↑↑
			///===========================
			break;
		case game:
			///===========================
			/// ↓↓↓ 更新処理 ↓↓↓
			///===========================
			//プレイヤーの更新
			player->Update(keys, preKeys, enemy);

			//ULTの更新
			ULTUpdate(keys, preKeys);

			//敵とプレイヤーの当たり判定
			collisionCheck(player, enemy);

			//敵の更新
			enemy->Move(keys, preKeys);

			//gameClearへ
			if (enemy->hp_ <= 0) {
				scene = gameClear;
			}
			//gameOverへ
			if (player->HP_ <= 0) {
				scene = gameOver;
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

			//カットインの描画
			DrawCutIn();

			//Barの描画
			DrawBar();

			//地面
			//Novice::DrawBox(0, 900, 1920, 180, 0.0f, WHITE, kFillModeSolid);
			Novice::DrawQuad(0, 900, 1920, 900, 0, 1080, 1920, 1080, 0, 0, 1920, 180, gameBackGroundCover_image, WHITE);

			//プレイヤーの描画
			player->Draw();

			//デバッグ用
			//debugprint(player, enemy);
			///===========================
			/// ↑↑↑ 描画処理 ↑↑↑
			///===========================
			break;
		case gameClear:
			///===========================
			/// ↓↓↓ 更新処理 ↓↓↓
			///===========================
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = title;
			}
			///===========================
			/// ↑↑↑ 更新処理 ↑↑↑
			///===========================
			///===========================
			/// ↓↓↓ 描画処理 ↓↓↓
			///===========================

			///===========================
			/// ↑↑↑ 描画処理 ↑↑↑
			///===========================
			break;
		case gameOver:
			///===========================
			/// ↓↓↓ 更新処理 ↓↓↓
			///===========================
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = title;
			}
			///===========================
			/// ↑↑↑ 更新処理 ↑↑↑
			///===========================
			///===========================
			/// ↓↓↓ 描画処理 ↓↓↓
			///===========================

			///===========================
			/// ↑↑↑ 描画処理 ↑↑↑
			///===========================
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
