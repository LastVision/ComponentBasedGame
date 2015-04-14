#pragma once

#include "Vector.h"

namespace Intersection
{
	class LineSegment3D
	{
	public:
		LineSegment3D();
		~LineSegment3D();

		CU::Vector3<float> myStartPos;
		CU::Vector3<float> myEndPos;
	};

	LineSegment3D::LineSegment3D(){}

	LineSegment3D::~LineSegment3D(){}
}



