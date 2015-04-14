#pragma once

#include "Vector.h"

namespace Intersection
{
	class Sphere
	{
	public:
		Sphere();
		~Sphere();

		CU::Vector3<float> myCenterPosition;
		int myRadius;
		int myRadiusSquared;

		
	};

	Sphere::Sphere(){}

	Sphere::~Sphere(){}
}

