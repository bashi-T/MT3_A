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
		Matrix4x4 gridStartPoint = MakeAffineMatrix(
			{ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });

		Vector3 positionEndGrid =
		{kGridHalfwidth, 0, kGridHalfwidth * 2 - kGridEvery * zIndex};
		Matrix4x4 gridEndPoint = MakeAffineMatrix(
			{ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });

		Matrix4x4 matStartWorldViewProjection = Multiply(gridStartPoint, viewProjectionMatrix);
		positionStartGrid = Transform(positionStartGrid, matStartWorldViewProjection);
		positionStartGrid = Transform(positionStartGrid, viewportMatrix);

		Matrix4x4 matEndWorldViewProjection = Multiply(gridEndPoint, viewProjectionMatrix);
		positionEndGrid = Transform(positionEndGrid, matEndWorldViewProjection);
		positionEndGrid = Transform(positionEndGrid, viewportMatrix);

		Novice::DrawLine(int(positionStartGrid.x), int(positionStartGrid.y),
		     int(positionEndGrid.x), int(positionEndGrid.y), 0xaaaaaaff);
	}
}

float pi = 3.141592f;
//float theta = 0.1f * M_PI;
struct Sphere {
	Vector3 center{ 1.0f,1.0f,1.0f };
	float radius =1.0f;
}sphere;

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

			Matrix4x4 PointA = MakeAffineMatrix(
				{ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
			Vector3 b =
			{
				sphere_.center.x + sphere_.radius * cos(lat+latB) * cos(lon),
				sphere_.center.y + sphere_.radius * sin(lat+latB),
				sphere_.center.z + sphere_.radius * cos(lat+latB) * sin(lon)
			};
			Matrix4x4 PointB = MakeAffineMatrix(
				{ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
			Vector3 c =
			{
				sphere_.center.x + sphere_.radius * cos(lat) * cos(lon + lonC),
				sphere_.center.y + sphere_.radius * sin(lat),
				sphere_.center.z + sphere_.radius * cos(lat) * sin(lon+lonC)
			};
			Matrix4x4 PointC = MakeAffineMatrix(
				{ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });

			Matrix4x4 matAWorldViewProjection = Multiply(PointA, viewProjectionMatrix);
			a = Transform(a, matAWorldViewProjection);
			a = Transform(a, viewportMatrix);

			Matrix4x4 matBWorldViewProjection = Multiply(PointB, viewProjectionMatrix);
			b = Transform(b, matBWorldViewProjection);
			b = Transform(b, viewportMatrix);

			Matrix4x4 matCWorldViewProjection = Multiply(PointC, viewProjectionMatrix);
			c = Transform(c, matCWorldViewProjection);
			c = Transform(c, viewportMatrix);
		
			Novice::DrawLine(int(a.x), int(a.y), int(b.x), int(b.y), color);
			Novice::DrawLine(int(a.x), int(a.y), int(c.x), int(c.y), color);
		}
	}
}