#pragma once

#include "Vector.h"
#include "planevolume.h"
#include "GrowingArray.h"

namespace Intersection
{
	class Fov90Frustrum
	{
	public:
		Fov90Frustrum();
		Fov90Frustrum(float aNear, float aFar);
		~Fov90Frustrum();

		float myNear;
		float myFar;

		CU::GrowingArray<Plane<float>, int> myPlanes;
	};

	Fov90Frustrum::Fov90Frustrum()
	{
		myPlanes.Init(6);
	}

	Fov90Frustrum::Fov90Frustrum(float aNear, float aFar)
	{
		myNear = aNear;
		myFar = aFar;

		float rotate45 = sqrt(2.f) / 2.f;

		Plane<float> near(CU::Vector3<float>(0, 0, aNear), CU::Vector3<float>(0, 0, -1));
		Plane<float> far(CU::Vector3<float>(0, 0, aFar), CU::Vector3<float>(0, 0, 1));

		Plane<float> right(CU::Vector3<float>(0, 0, 0), CU::Vector3<float>(rotate45, 0, -rotate45));
		Plane<float> left(CU::Vector3<float>(0, 0, 0), CU::Vector3<float>(-rotate45, 0, -rotate45));
		Plane<float> up(CU::Vector3<float>(0, 0, 0), CU::Vector3<float>(0, rotate45, -rotate45));
		Plane<float> down(CU::Vector3<float>(0, 0, 0), CU::Vector3<float>(0, -rotate45, -rotate45));

		myPlanes.Init(6);
		myPlanes.Add(near);
		myPlanes.Add(far);
		myPlanes.Add(left);
		myPlanes.Add(right);
		myPlanes.Add(up);
		myPlanes.Add(down);
	}

	Fov90Frustrum::~Fov90Frustrum()
	{
	}

}


