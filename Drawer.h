#pragma once
#include "vector.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfwidth = 20.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfwidth * 2.0f) / float(kSubdivision);


	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex)
	{
		Vector3 positionStartGrid =
		{-kGridHalfwidth + kGridEvery * xIndex, 0, kGridHalfwidth * 2};
		Matrix4x4 gridStartPoint = MakeTranslateMatrix(positionStartGrid);
		positionStartGrid =
		{
		    gridStartPoint.m[3][0],
			gridStartPoint.m[3][1],
			gridStartPoint.m[3][2]
		};

		Vector3 positionEndGrid =
		{-kGridHalfwidth + kGridEvery * xIndex, 0, 0};
		Matrix4x4 gridEndPoint = MakeTranslateMatrix(positionEndGrid);
		positionEndGrid =//world
		{
			gridEndPoint.m[3][0],
			gridEndPoint.m[3][1],
			gridEndPoint.m[3][2]
		};


		Matrix4x4 startViewMatrix = Inverse(gridStartPoint);//MT2_08_00_07,MT3_00_02_10
		Matrix4x4 matStartViewProjection = Multiply(startViewMatrix, viewProjectionMatrix);//MT3_01_00_10
		Matrix4x4 matStartViewProjectionViewport = Multiply(matStartViewProjection, viewportMatrix); // MT3_01_00_25
		positionStartGrid = Transform(positionStartGrid, matStartViewProjectionViewport);//MT3_01_00_23

		Matrix4x4 endViewMatrix = Inverse(gridEndPoint);
		Matrix4x4 matEndViewProjection = Multiply(endViewMatrix, viewProjectionMatrix);
		Matrix4x4 matEndViewProjectionViewport = Multiply(matEndViewProjection, viewportMatrix);
		positionEndGrid = Transform(positionEndGrid, matEndViewProjectionViewport);

		Novice::DrawLine(int(positionStartGrid.x), int(positionStartGrid.y),
		    int(positionEndGrid.x), int(positionEndGrid.y), 0xff0000ff);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex)
	{
		Vector3 positionStartGrid =
		{-kGridHalfwidth, 0, kGridHalfwidth * 2 - kGridEvery * zIndex};
		Matrix4x4 gridStartPoint =
		    MakeAffineMatrix({0, 0, 0}, {0, 0, 0}, positionStartGrid);
		positionStartGrid =
		{
		    gridStartPoint.m[3][0],
			gridStartPoint.m[3][1],
			gridStartPoint.m[3][2]
		};

		Vector3 positionEndGrid =
		{kGridHalfwidth, 0, kGridHalfwidth * 2 - kGridEvery * zIndex};
		Matrix4x4 gridEndPoint =
		    MakeAffineMatrix({0, 0, 0}, {0, 0, 0}, positionEndGrid);
		positionEndGrid =
		{
			gridEndPoint.m[3][0],
			gridEndPoint.m[3][1],
			gridEndPoint.m[3][2]
		};


		Matrix4x4 viewStartMatrix = Inverse(gridStartPoint);
		Matrix4x4 matStartViewProjectionViewport = Multiply(viewStartMatrix, viewProjectionMatrix);
		matStartViewProjectionViewport = Multiply(matStartViewProjectionViewport, viewportMatrix);
		positionStartGrid = Transform(positionStartGrid, matStartViewProjectionViewport);

		Matrix4x4 viewEndMatrix = Inverse(gridEndPoint);
		Matrix4x4 matEndViewProjectionViewport = Multiply(viewEndMatrix, viewProjectionMatrix);
		matEndViewProjectionViewport = Multiply(matEndViewProjectionViewport, viewportMatrix);
		positionEndGrid = Transform(positionEndGrid, matEndViewProjectionViewport);

		Novice::DrawLine(int(positionStartGrid.x), int(positionStartGrid.y),
		     int(positionEndGrid.x), int(positionEndGrid.y), 0xff0000ff);
	}
}

float pi;

struct Sphere {
	Vector3 center;
	float radius;
}sphere;

//void DrawSphere(const Sphere&sphere,
//	const Matrix4x4&viewProjectionMatrix,
//	const Matrix4x4&viewportMatrix,
//    uint32_t color)
//{
//	const uint32_t kSubdivision = 18;
//	const float kLonevery = 2.0f / kSubdivision * M_PI;
//	const float kLatevery = 2.0f / kSubdivision * M_PI;
//
//	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex)
//	{
//		float lat = -pi / 2.0f + kLatevery * latIndex;
//
//		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex)
//		{
//			float lon = lonIndex * kLonevery;
//			Vector3 a, b, c;
//
//
//
//			//Novice::DrawLine();
//			//Novice::DrawLine();
//		}
//	}
//}