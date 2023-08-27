#include "Drawer.h"
#include<imgui.h>

const char kWindowTitle[] = "MT3_02_03";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 cameraRotate{0.26f, 0.0f, 0.0f};
	Vector3 cameraTranslate{0.0f, 7.0f, -40.0f};

	Vector3 point{ 1.5f,0.6f,0.6f };

	int color1 = WHITE;

	Plane plane{ {0.0f,1.0f,0.0f},5.0f };
	Segment segment{ {0.0f,0.0f,0.0f},{6.0f,4.0f,0.0f} };
	Triangle triangle{};
	triangle.vertices[0] = { -3.0f,0.0f,3.0f };
	triangle.vertices[1] = {  0.0f,3.0f,3.0f };
	triangle.vertices[2] = {  3.0f,0.0f,3.0f };

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

		Vector3 v01 = Subtract(triangle.vertices[1], triangle.vertices[0]);
		Vector3 v12 = Subtract(triangle.vertices[2], triangle.vertices[1]);
		Vector3 v20 = Subtract(triangle.vertices[0], triangle.vertices[2]);
		plane.normal =Normalize(Cross(v01, v12));
		plane.distance = Dot(triangle.vertices[1], plane.normal);

		float dot = Dot(Subtract(segment.diff, segment.origin), plane.normal);
		if (dot != 0.0f)
		{
			float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;
			Novice::ScreenPrintf(10, 10, "%f", t);
			if (t >= 0.0f && t <= 1.0f)
			{
				Vector3 v0p = Subtract(Multiply(t, Subtract(segment.diff, segment.origin)), triangle.vertices[0]);
				Vector3 v1p = Subtract(Multiply(t, Subtract(segment.diff, segment.origin)), triangle.vertices[1]);
				Vector3 v2p = Subtract(Multiply(t, Subtract(segment.diff, segment.origin)), triangle.vertices[2]);

				Vector3 cross01 = Cross(v01, v1p);
				Vector3 cross12 = Cross(v12, v2p);
				Vector3 cross20 = Cross(v20, v0p);

				if (Dot(cross01, plane.normal) >= 0.0f &&
					Dot(cross12, plane.normal) >= 0.0f &&
					Dot(cross20, plane.normal) >= 0.0f)
				{
					color1 = RED;
				}
				else
				{
					color1 = WHITE;
				}


				
			}
			else
			{
				color1 = WHITE;
			}


		}
		else
		{
			color1 = WHITE;
		}

		Vector3 start = Transform(Transform(segment.origin, viewProjectionMatrix), viewportMatrix);
		Vector3 end = Transform(Transform(Add(segment.origin, segment.diff), viewProjectionMatrix), viewportMatrix);


		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("segment.origin", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("segment.diff", &segment.diff.x, 0.01f);
		ImGui::DragFloat3("triangle.vertices[0]", &triangle.vertices[0].x, 0.01f);
		ImGui::DragFloat3("triangle.vertices[1]", &triangle.vertices[1].x, 0.01f);
		ImGui::DragFloat3("triangle.vertices[2]", &triangle.vertices[2].x, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		DrawGrid(viewProjectionMatrix, viewportMatrix);
		//DrawPlane(plane, viewProjectionMatrix, viewportMatrix, WHITE);
		DrawTriangle(triangle , viewProjectionMatrix, viewportMatrix, WHITE);
		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), color1);

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
