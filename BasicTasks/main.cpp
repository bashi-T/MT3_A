#include "Drawer.h"
#include<imgui.h>

const char kWindowTitle[] = "MT4_01_02";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 from0 = Normalize({ 1.0f, 0.7f, 0.5f });
	Vector3 to0 = { -from0.x,-from0.y,-from0.z };
	Vector3 from1 = Normalize({ -0.6f, 0.9f, 0.2f });
	Vector3 to1 = Normalize({ 0.4f,0.7f,-0.5f });


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

		Matrix4x4 rotateMatrix0 = DirectionTodirection(Normalize({ 1.0f,0.0f,0.0f }),Normalize({ -1.0f,0.0f,0.0f }));
		Matrix4x4 rotateMatrix1 = DirectionTodirection(from0, to0);
		Matrix4x4 rotateMatrix2 = DirectionTodirection(from1, to1);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::ScreenPrintf(0, 0, "rotateMatrix0");
		MatrixScreenPrintf(0, 20, rotateMatrix0);
		Novice::ScreenPrintf(0, 100, "rotateMatrix1");
		MatrixScreenPrintf(0, 120, rotateMatrix1);
		Novice::ScreenPrintf(0, 200, "rotateMatrix2");
		MatrixScreenPrintf(0, 220, rotateMatrix2);

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
