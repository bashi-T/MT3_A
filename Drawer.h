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
		{-kGridHalfwidth + kGridEvery * xIndex, 0, kGridHalfwidth};
		Matrix4x4 gridStartPoint = MakeAffineMatrix(
			{ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
		Vector3 positionEndGrid =
		{-kGridHalfwidth + kGridEvery * xIndex, 0, -kGridHalfwidth };
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
		{-kGridHalfwidth, 0, kGridHalfwidth - kGridEvery * zIndex};

		Vector3 positionEndGrid =
		{kGridHalfwidth, 0, kGridHalfwidth - kGridEvery * zIndex};

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

void DrawPlane(Plane&plane,const Matrix4x4&viewProjectionMatrix,const Matrix4x4&viewportMatrix,uint32_t color)
{
	Vector3 center = Multiply(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] =
	{
		-perpendiculars[0].x,
		-perpendiculars[0].y,
		-perpendiculars[0].z
	};
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3]=
	{
		-perpendiculars[2].x,
		-perpendiculars[2].y,
		-perpendiculars[2].z
	};

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index)
	{
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine(int(points[1].x), int(points[1].y),
		int(points[2].x), int(points[2].y), color);

	Novice::DrawLine(int(points[3].x), int(points[3].y),
		int(points[0].x), int(points[0].y), color);

	Novice::DrawLine(int(points[0].x), int(points[0].y),
		int(points[2].x), int(points[2].y), color);

	Novice::DrawLine(int(points[1].x), int(points[1].y),
		int(points[3].x), int(points[3].y), color);
}

void DrawTriangle(const Triangle& triangle,
	const Matrix4x4& viewProjectionMatrix,
	const Matrix4x4& viewportMatrix,
	uint32_t color)
{
	Vector3 positionTriangle[3] =
	{
        triangle.vertices[0],
        triangle.vertices[1],
        triangle.vertices[2]
	};

	Matrix4x4 triangleVertex = MakeAffineMatrix(
		{ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });

	Matrix4x4 matv1WorldViewProjection = Multiply(triangleVertex, viewProjectionMatrix);
	positionTriangle[0] = Transform(positionTriangle[0], matv1WorldViewProjection);
	positionTriangle[0] = Transform(positionTriangle[0], viewportMatrix);

	Matrix4x4 matv2WorldViewProjection = Multiply(triangleVertex, viewProjectionMatrix);
	positionTriangle[1] = Transform(positionTriangle[1], matv2WorldViewProjection);
	positionTriangle[1] = Transform(positionTriangle[1], viewportMatrix);

	Matrix4x4 matv3WorldViewProjection = Multiply(triangleVertex, viewProjectionMatrix);
	positionTriangle[2] = Transform(positionTriangle[2], matv3WorldViewProjection);
	positionTriangle[2] = Transform(positionTriangle[2], viewportMatrix);

	Novice::DrawTriangle(
		int(positionTriangle[0].x), int(positionTriangle[0].y),
		int(positionTriangle[1].x), int(positionTriangle[1].y),
		int(positionTriangle[2].x), int(positionTriangle[2].y),
		color, kFillModeWireFrame);

}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 positionAABB[8] =
	{
		{aabb.min.x,aabb.min.y,aabb.min.z},
		{aabb.min.x,aabb.min.y,aabb.max.z},
		{aabb.max.x,aabb.min.y,aabb.max.z},
		{aabb.max.x,aabb.min.y,aabb.min.z},

		{aabb.min.x,aabb.max.y,aabb.min.z},
		{aabb.min.x,aabb.max.y,aabb.max.z},
		{aabb.max.x,aabb.max.y,aabb.max.z},
		{aabb.max.x,aabb.max.y,aabb.min.z},
	};

	Matrix4x4 AABBVertex = MakeAffineMatrix(
		{ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });

	Matrix4x4 matv1WorldViewProjection = Multiply(AABBVertex, viewProjectionMatrix);
	positionAABB[0] = Transform(positionAABB[0], matv1WorldViewProjection);
	positionAABB[0] = Transform(positionAABB[0], viewportMatrix);

	Matrix4x4 matv2WorldViewProjection = Multiply(AABBVertex, viewProjectionMatrix);
	positionAABB[1] = Transform(positionAABB[1], matv2WorldViewProjection);
	positionAABB[1] = Transform(positionAABB[1], viewportMatrix);
	
	Matrix4x4 matv3WorldViewProjection = Multiply(AABBVertex, viewProjectionMatrix);
	positionAABB[2] = Transform(positionAABB[2], matv3WorldViewProjection);
	positionAABB[2] = Transform(positionAABB[2], viewportMatrix);

	Matrix4x4 matv4WorldViewProjection = Multiply(AABBVertex, viewProjectionMatrix);
	positionAABB[3] = Transform(positionAABB[3], matv4WorldViewProjection);
	positionAABB[3] = Transform(positionAABB[3], viewportMatrix);
	
	Matrix4x4 matv5WorldViewProjection = Multiply(AABBVertex, viewProjectionMatrix);
	positionAABB[4] = Transform(positionAABB[4], matv5WorldViewProjection);
	positionAABB[4] = Transform(positionAABB[4], viewportMatrix);

	Matrix4x4 matv6WorldViewProjection = Multiply(AABBVertex, viewProjectionMatrix);
	positionAABB[5] = Transform(positionAABB[5], matv6WorldViewProjection);
	positionAABB[5] = Transform(positionAABB[5], viewportMatrix);
	
	Matrix4x4 matv7WorldViewProjection = Multiply(AABBVertex, viewProjectionMatrix);
	positionAABB[6] = Transform(positionAABB[6], matv7WorldViewProjection);
	positionAABB[6] = Transform(positionAABB[6], viewportMatrix);

	Matrix4x4 matv8WorldViewProjection = Multiply(AABBVertex, viewProjectionMatrix);
	positionAABB[7] = Transform(positionAABB[7], matv8WorldViewProjection);
	positionAABB[7] = Transform(positionAABB[7], viewportMatrix);

	Novice::DrawLine(int(positionAABB[0].x), int(positionAABB[0].y),
		int(positionAABB[1].x), int(positionAABB[1].y), color);
	Novice::DrawLine(int(positionAABB[1].x), int(positionAABB[1].y),
		int(positionAABB[2].x), int(positionAABB[2].y), color);
	Novice::DrawLine(int(positionAABB[2].x), int(positionAABB[2].y),
		int(positionAABB[3].x), int(positionAABB[3].y), color);
	Novice::DrawLine(int(positionAABB[3].x), int(positionAABB[3].y),
		int(positionAABB[0].x), int(positionAABB[0].y), color);

	Novice::DrawLine(int(positionAABB[4].x), int(positionAABB[4].y),
		int(positionAABB[5].x), int(positionAABB[5].y), color);
	Novice::DrawLine(int(positionAABB[5].x), int(positionAABB[5].y),
		int(positionAABB[6].x), int(positionAABB[6].y), color);
	Novice::DrawLine(int(positionAABB[6].x), int(positionAABB[6].y),
		int(positionAABB[7].x), int(positionAABB[7].y), color);
	Novice::DrawLine(int(positionAABB[7].x), int(positionAABB[7].y),
		int(positionAABB[4].x), int(positionAABB[4].y), color);

	Novice::DrawLine(int(positionAABB[0].x), int(positionAABB[0].y),
		int(positionAABB[4].x), int(positionAABB[4].y), color);
	Novice::DrawLine(int(positionAABB[1].x), int(positionAABB[1].y),
		int(positionAABB[5].x), int(positionAABB[5].y), color);
	Novice::DrawLine(int(positionAABB[2].x), int(positionAABB[2].y),
		int(positionAABB[6].x), int(positionAABB[6].y), color);
	Novice::DrawLine(int(positionAABB[3].x), int(positionAABB[3].y),
		int(positionAABB[7].x), int(positionAABB[7].y), color);

}