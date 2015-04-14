#pragma once

#include "Vector.h"

namespace Intersection
{
	class LineSegment2D
	{
	public:
		LineSegment2D();
		~LineSegment2D();

		CU::Vector2<float> myStartPos;
		CU::Vector2<float> myEndPos;
	};

	LineSegment2D::LineSegment2D(){}

	LineSegment2D::~LineSegment2D(){}
}


