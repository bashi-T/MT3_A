#pragma once
#include<algorithm>
#include "vector.h"

//bool IsCollision(const Segment&segment,const Plane&plane)
//{
//	float dot = Dot(plane.normal, line.diff);
//	if (dot == 0.0f)
//	{
//		return false;
//	}
//
//	float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;
//
//}

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