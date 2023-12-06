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

		Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
		Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
		Quaternion identity = identityQuaternion();
		Quaternion conj = Conjugate(q1);
		Quaternion inv = Inverse(q1);
		Quaternion normal = Normalize(q1);
		Quaternion mul1 = Multiply(q1, q2);
		Quaternion mul2 = Multiply(q2, q1);
		float norm = Norm(q1);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::ScreenPrintf(0, 0, "%f,%f,%f,%f :identityQuaternion",identity.x, identity.y, identity.z, identity.w);
		Novice::ScreenPrintf(0, 20, "%f,%f,%f,%f :Conjugate", conj.x, conj.y, conj.z, conj.w);
		Novice::ScreenPrintf(0, 40, "%f,%f,%f,%f :Inverse", inv.x, inv.y, inv.z, inv.w);
		Novice::ScreenPrintf(0, 60, "%f,%f,%f,%f :Normalize", normal.x, normal.y, normal.z, normal.w);
		Novice::ScreenPrintf(0, 80, "%f,%f,%f,%f :Mul1", mul1.x, mul1.y, mul1.z, mul1.w);
		Novice::ScreenPrintf(0, 100, "%f,%f,%f,%f :Mul2", mul2.x, mul2.y, mul2.z, mul2.w);
		Novice::ScreenPrintf(0, 120, "%f, :Norm",norm);

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
