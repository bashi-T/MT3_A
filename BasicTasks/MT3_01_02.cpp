#include "Drawer.h"
#include<imgui.h>

const char kWindowTitle[] = "MT3_01_02";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};
	Vector3 cameraTranslate{0.0f, 1.9f, -16.49f};

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
		

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		ImGui::End();

		Matrix4x4 CameraMatWorld = MakeAffineMatrix(
			{1.0f, 1.0f, 1.0f}, cameraRotate, cameraTranslate);

		Matrix4x4 viewMatrix = Inverse(CameraMatWorld);

		Matrix4x4 ProjectionMatrix = MakePerspectiveFovMatrix(
			0.45f,
			float(kWindowWidth) / float(kWindowHeight),
			0.1f,
			100.0f);

		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, ProjectionMatrix);
		    
		Matrix4x4 viewportMatrix = MakeViewportMatrix(
			0.0f,
			0.0f,
			float(kWindowWidth),
			float(kWindowHeight),
			0,
			1);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix,0x000000ff);

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
