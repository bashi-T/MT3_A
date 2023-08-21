#include "Drawer.h"
#include<imgui.h>

const char kWindowTitle[] = "MT3_02_01";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};
	Vector3 cameraTranslate{0.0f, 3.9f, -16.49f};

	Vector3 point{ 1.5f,0.6f,0.6f };
	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };

	Sphere pointSphere1{ point,1.0f };
	Sphere pointSphere2{ segment.origin,1.0f };

	int color1 = WHITE;
	int color2 = WHITE;

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


		float distance = Length(Subtract(pointSphere2.center, pointSphere1.center));

		if (distance <= pointSphere1.radius + pointSphere2.radius)
		{
			color1 = RED;
		}
		else {
			color1 = WHITE;
		}




		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		//ImGui::DragFloat3("point", &point.x, 0.01f);
		//ImGui::DragFloat3("segment.origin", &segment.origin.x, 0.01f);
		//ImGui::DragFloat3("segment.diff", &segment.diff.x, 0.01f);
		ImGui::DragFloat3("SphereCenter1", &pointSphere1.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius1", &pointSphere1.radius, 0.01f);
		ImGui::DragFloat3("SphereCenter2", &pointSphere2.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius2", &pointSphere2.radius, 0.01f);
		//ImGui::InputFloat3("Project", &project.x, "%.3f",ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawSphere(pointSphere1, viewProjectionMatrix, viewportMatrix, color1);
		DrawSphere(pointSphere2, viewProjectionMatrix, viewportMatrix, color2);
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
