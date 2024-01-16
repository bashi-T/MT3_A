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

		Quaternion rotation0 = MakerotateAxisQuaternion(Normalize(Vector3{ 0.71f,0.71f,0.0f }), 0.3f);
		Quaternion rotation1 = MakerotateAxisQuaternion(Normalize(Vector3{ 0.71f,0.0f,0.71f }), 3.141592f);

		Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
		Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
		Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
		Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
		Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::ScreenPrintf(0, 00, "%.02f, %.02f, %.02f, %.02f :interpolate0, Slep(q0, q1, 0.0f)", interpolate0.x, interpolate0.y, interpolate0.z, interpolate0.w);
		Novice::ScreenPrintf(0, 20, "%.02f, %.02f, %.02f, %.02f :interpolate1, Slep(q0, q1, 0.3f)", interpolate1.x, interpolate1.y, interpolate1.z, interpolate1.w);
		Novice::ScreenPrintf(0, 40, "%.02f, %.02f, %.02f, %.02f :interpolate2, Slep(q0, q1, 0.5f)", interpolate2.x, interpolate2.y, interpolate2.z, interpolate2.w);
		Novice::ScreenPrintf(0, 60, "%.02f, %.02f, %.02f, %.02f :interpolate3, Slep(q0, q1, 0.7f)", interpolate3.x, interpolate3.y, interpolate3.z, interpolate3.w);
		Novice::ScreenPrintf(0, 80, "%.02f, %.02f, %.02f, %.02f :interpolate4, Slep(q0, q1, 1.0f)", interpolate4.x, interpolate4.y, interpolate4.z, interpolate4.w);
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
