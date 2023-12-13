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

		Quaternion rotation = MakerotateAxisQuaternion(Normalize(Vector3{ 1.0f,0.4f,-0.2f }), 0.45f);
		Vector3 pointY = { 2.1f,-0.9f,1.3f };
		Matrix4x4 rotateMatrix = MakeRotateMatrix(rotation);
		Vector3 rotateByQuaternion = RotateVector(pointY, rotation);
		Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::ScreenPrintf(0, 0, "%.02f,%.02f,%.02f,%.02f :rotation", rotation.x, rotation.y, rotation.z, rotation.w);
		Novice::ScreenPrintf(0, 20, "rotateMatrix");
		MatrixScreenPrintf(0, 40, rotateMatrix);
		Novice::ScreenPrintf(0, 120, "%.02f,%.02f,%.02f :rotateByQuaternion", rotateByQuaternion.x, rotateByQuaternion.y, rotateByQuaternion.z);
		Novice::ScreenPrintf(0, 140, "%.02f,%.02f,%.02f :rotateByMatrix", rotateByMatrix.x, rotateByMatrix.y, rotateByMatrix.z);

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
