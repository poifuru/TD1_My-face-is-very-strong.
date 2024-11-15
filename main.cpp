//ソースファイル
#include <Novice.h>

//ヘッダーファイル
#include "struct.h"
#include "player.h"

const char kWindowTitle[] = "LC1A_25_マスヤ_ゴウ_タイトル";

//コメントエリア
/**/

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1920, 1080);
	//Novice::SetWindowMode(kFullscreen);

	//キー入力を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Player* player = new Player();

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

		player->Update(keys);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		player->Draw();
		Novice::ScreenPrintf(20, 20, "velocity.x:%5.1f", player->velocity_.x);
		Novice::ScreenPrintf(20, 40, "velocity.y:%5.1f", player->velocity_.y);
		Novice::ScreenPrintf(20, 60, "press keys A:%d", keys[DIK_A]);
		Novice::ScreenPrintf(20, 80, "press keys D:%d", keys[DIK_D]);


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
