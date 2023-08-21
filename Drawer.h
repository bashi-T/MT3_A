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
		Matrix4x4 gridStartPoint = MakeAffineMatrix(
			{ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
		Vector3 positionEndGrid =
		{-kGridHalfwidth + kGridEvery * xIndex, 0, 0};
		Matrix4x4 gridEndPoint = MakeAffineMatrix(
			{ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, {0.0f,0.0f,0.0f});

		Matrix4x4 matStartWorldViewProjection = Multiply(gridStartPoint, viewProjectionMatrix);
		positionStartGrid = Transform(positionStartGrid, matStartWorldViewProjection);
		positionStartGrid = Transform(positionStartGrid, viewportMatrix);

		Matrix4x4 matEndWorldViewProjection = Multiply(gridEndPoint, viewProjectionMatrix);
		positionEndGrid = Transform(positionEndGrid, matStartWorldViewProjection);
		positionEndGrid = Transform(positionEndGrid, viewportMatrix);

		Novice::DrawLine(int(positionStartGrid.x), int(positionStartGrid.y),
		    int(positionEndGrid.x), int(positionEndGrid.y), 0xaaaaaaff);
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex)
	{
		Vector3 positionStartGrid =
		{-kGridHalfwidth, 0, kGridHalfwidth * 2 - kGridEvery * zIndex};

		Vector3 positionEndGrid =
		{kGridHalfwidth, 0, kGridHalfwidth * 2 - kGridEvery * zIndex};

		positionStartGrid = Transform(Transform(positionStartGrid, viewProjectionMatrix), viewportMatrix);

		positionEndGrid = Transform(Transform(positionEndGrid, viewProjectionMatrix), viewportMatrix);

		Novice::DrawLine(int(positionStartGrid.x), int(positionStartGrid.y),
		     int(positionEndGrid.x), int(positionEndGrid.y), 0xaaaaaaff);
	}
}

float pi = 3.141592f;
//float theta = 0.1f * M_PI;
struct Sphere {
	Vector3 center{ 1.0f,1.0f,1.0f };
	float radius =1.0f;
};

void DrawSphere(const Sphere&sphere_,
	const Matrix4x4&viewProjectionMatrix,
	const Matrix4x4&viewportMatrix,
    uint32_t color)
{
	const uint32_t kSubdivision = 20;
	const float kLonevery = 2.0f/kSubdivision *pi;
	const float kLatevery = 2.0f/kSubdivision *pi;

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex)
	{
		float lat = -pi / 2.0f + kLatevery * latIndex;//theta
		float latB = pi / kSubdivision;
		
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex)
		{
			float lon = lonIndex * kLonevery;//phi
			float lonC = 2 * pi / kSubdivision;

			Vector3 a =
			{
				sphere_.center.x + sphere_.radius * cos(lat) * cos(lon),
				sphere_.center.y + sphere_.radius * sin(lat),
				sphere_.center.z + sphere_.radius * cos(lat) * sin(lon)
			};

			Vector3 b =
			{
				sphere_.center.x + sphere_.radius * cos(lat+latB) * cos(lon),
				sphere_.center.y + sphere_.radius * sin(lat+latB),
				sphere_.center.z + sphere_.radius * cos(lat+latB) * sin(lon)
			};
			Vector3 c =
			{
				sphere_.center.x + sphere_.radius * cos(lat) * cos(lon + lonC),
				sphere_.center.y + sphere_.radius * sin(lat),
				sphere_.center.z + sphere_.radius * cos(lat) * sin(lon+lonC)
			};

			a = Transform(Transform(a, viewProjectionMatrix), viewportMatrix);

			b = Transform(Transform(b, viewProjectionMatrix), viewportMatrix);

			c = Transform(Transform(c, viewProjectionMatrix), viewportMatrix);
		
			Novice::DrawLine(int(a.x), int(a.y), int(b.x), int(b.y), color);
			Novice::DrawLine(int(a.x), int(a.y), int(c.x), int(c.y), color);
		}
	}
}