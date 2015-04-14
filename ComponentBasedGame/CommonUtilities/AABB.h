#pragma once

#include "Vector.h"

namespace Intersection
{
	class AABB
	{
	public:
		AABB();
		~AABB();

		CU::Vector3<float> myCenterPos;
		CU::Vector3<float> myExtents;
		CU::Vector3<float> myMinPos;
		CU::Vector3<float> myMaxPos;
	};

	AABB::AABB(){}

	AABB::~AABB(){}
}



