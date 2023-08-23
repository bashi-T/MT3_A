#pragma once
#include "Drawer.h"

bool IsCollision(const Segment&segment,const Plane&plane)
{
	float dot = Dot(plane.normal, line.diff);
	if (dot == 0.0f)
	{
		return false;
	}

	float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;

}