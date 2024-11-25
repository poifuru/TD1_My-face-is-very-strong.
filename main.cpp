//<>ヘッダーファイル
#include <Novice.h>

//""ヘッダーファイル
#include "struct.h"
#include "player.h"
#include "Enemy.h"
#include "Ultimate.h"

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
		/// ↓更新処理ここから
		///

		//プレイヤーの更新
		player->Update(keys, preKeys);

		//ULTの更新
		ULTUpdate(keys, preKeys);

		//敵の更新
		enemy->Move(keys, preKeys);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//地面
		Novice::DrawLine(0, 900, 1920, 900, BLACK);
			
		//プレイヤーの描画
		player->Draw();
		
		//敵の描画
		enemy->Draw();


		//カットインの描画
		DrawCutIn();

		///
		/// ↑描画処理ここまで
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
