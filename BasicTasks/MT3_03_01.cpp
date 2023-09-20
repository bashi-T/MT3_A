#include "Drawer.h"
#include "Collision.h"
#include<imgui.h>

const char kWindowTitle[] = "MT3_03_01";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};
	Vector3 cameraTranslate{0.0f, 7.0f, -30.0f};
	uint32_t color1 = RED;
	uint32_t color2 = GREEN;
	uint32_t color3 = BLUE;

	Vector3 translates[3]{
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f}
	};
	Vector3 rotates[3]{
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f}
	};
	float scale1 = 1.0f;
	float scale2 = 1.0f;
	float scale3 = 1.0f;

	Vector3 scales[3]{
		{scale1,scale1,scale1},
		{scale2,scale2,scale2},
		{scale3,scale3,scale3}
	};

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
		
		Matrix4x4 CameraMatWorld = MakeAffineMatrix(
			{ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);

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

		Matrix4x4 sholderMatWorld = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Vector3 sholder = { sholderMatWorld.m[3][0], sholderMatWorld.m[3][1], sholderMatWorld.m[3][2] };
		Matrix4x4 elbowMatworld = Multiply(MakeAffineMatrix(scales[1], rotates[1], translates[1]), sholderMatWorld);
		Vector3 elbow = { elbowMatworld.m[3][0], elbowMatworld.m[3][1], elbowMatworld.m[3][2] };
		Matrix4x4 handMatworld = Multiply(MakeAffineMatrix(scales[2], rotates[2], translates[2]), elbowMatworld);
		Vector3 hand = { handMatworld.m[3][0], handMatworld.m[3][1], handMatworld.m[3][2] };

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("translates[0]", &translates[0].x, 0.01f);
		ImGui::DragFloat3("translates[1]", &translates[1].x, 0.01f);
		ImGui::DragFloat3("translates[2]", &translates[2].x, 0.01f);
		ImGui::DragFloat3("rotates[0]", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("rotates[1]", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("rotates[2]", &rotates[2].x, 0.01f);
		ImGui::DragFloat("scale1", &scale1, 0.01f);
		ImGui::DragFloat("scale2", &scale2, 0.01f);
		ImGui::DragFloat("scale3", &scale3, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawSphere({ sholder,scale1 }, viewProjectionMatrix, viewportMatrix, color1);
		DrawSphere({ elbow,scale2 }, viewProjectionMatrix, viewportMatrix, color2);
		DrawSphere({ hand,scale3 }, viewProjectionMatrix, viewportMatrix, color3);

		Vector3 Ws = Transform(sholder, viewProjectionMatrix);
		Ws = Transform(Ws, viewportMatrix);

		Vector3 We = Transform(elbow, viewProjectionMatrix);
		We = Transform(We, viewportMatrix);

		Vector3 Wh = Transform(hand, viewProjectionMatrix);
		Wh = Transform(Wh, viewportMatrix);

		Novice::DrawLine(int(Ws.x), int(Ws.y), int(We.x), int(We.y), WHITE);
		Novice::DrawLine(int(We.x), int(We.y), int(Wh.x), int(Wh.y), WHITE);

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
