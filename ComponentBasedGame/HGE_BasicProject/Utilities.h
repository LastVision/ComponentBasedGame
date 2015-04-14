#pragma once
#include "Vector.h"

namespace CommonUtilities
{
	float GetDistanceBetweenPoints(const CU::Vector2<float> aFirstPoint, CU::Vector2<float> aSecondPoint);

	CU::Vector2<float> GetClosestPointInRectangle(float aRectLeft, float aRectTop, float aRectWidth, float aRectHeight, const CU::Vector2<float>& aOriginPosition);

	float Min(float aNum1, float aNum2, float aNum3, float aNum4);

	int GetAngleBetweenVectors(CU::Vector2<float> aFirst, CU::Vector2<float> aSecond);
}