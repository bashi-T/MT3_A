#pragma once
#include<algorithm>
#include "vector.h"

bool IsCollision(const Segment&segment,const Plane&plane)
{
	float dot = Dot(Subtract(segment.diff, segment.origin), plane.normal);
	if (dot != 0.0f)
	{
		float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

		if (t >= 0.0f && t <= 1.0f)
		{
			return true;
		}
		else {
			return false;
		}
	}
	else
	{
		return false;
	}

}

bool isCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x) && (aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y) && (aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z) && (aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	else {
		return false;
	}

}

bool isCollision(const AABB& aabb, const Sphere& sphere)
{
	Vector3 closestPoint{
		std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
		std::clamp(sphere.center.y,aabb.min.y,aabb.max.y),
		std::clamp(sphere.center.z,aabb.min.z,aabb.max.z)
	};
	float distance = Length(Subtract(closestPoint,sphere.center));
	if (distance <= sphere.radius) {
		return true;
	}
	else {
		return false;
	}
}

bool isCollision(const AABB& aabb, const Segment& segment)
{
	float TXmin = (aabb.min.x - segment.origin.x) / Subtract(segment.diff, segment.origin).x;
	float TXmax = (aabb.max.x - segment.origin.x) / Subtract(segment.diff, segment.origin).x;
	float TYmin = (aabb.min.y - segment.origin.y) / Subtract(segment.diff, segment.origin).y;
	float TYmax = (aabb.max.y - segment.origin.y) / Subtract(segment.diff, segment.origin).y;
	float TZmin = (aabb.min.z - segment.origin.z) / Subtract(segment.diff, segment.origin).z;
	float TZmax = (aabb.max.z - segment.origin.z) / Subtract(segment.diff, segment.origin).z;

	float tNearX = min(TXmin, TXmax);
	float tFarX = max(TXmin, TXmax);
	float tNearY = min(TYmin, TYmax);
	float tFarY = max(TYmin, TYmax);
	float tNearZ = min(TZmin, TZmax);
	float tFarZ = max(TZmin, TZmax);

	float tmin = max(max(tNearX, tNearY), tNearZ);
	float tmax = min(min(tFarX, tFarY), tFarZ);

	if (tmin <= tmax) {
		return true;
	}
	else {
		return false;
	}
}