#include "Utilities.h"
#include <math.h>

namespace CommonUtilities
{
	float GetDistanceBetweenPoints(const CU::Vector2<float> aFirstPoint, CU::Vector2<float> aSecondPoint)
	{
		CU::Vector2<float> heading = aSecondPoint - aFirstPoint;

		return CU::Length(heading);
	}

	CU::Vector2<float> GetClosestPointInRectangle(float aRectLeft, float aRectTop, float aRectWidth, float aRectHeight, const CU::Vector2<float>& aOriginPosition)
	{
		/*
			
			http://stackoverflow.com/questions/20453545/how-to-find-the-nearest-point-in-the-perimeter-of-a-rectangle-to-a-given-point

		*/

		float aRectRight = aRectLeft + aRectWidth;
		float aRectBottom = aRectTop + aRectHeight;

		float x = aOriginPosition.x;
		float y = aOriginPosition.y;

		x = fmax(aRectLeft, fmin(aRectRight, x));
		y = fmax(aRectTop, fmin(aRectBottom, y));

		float dLeft = abs(x - aRectLeft);
		float dRight = abs(x - aRectRight);
		float dTop = abs(y - aRectTop);
		float dBottom = abs(y - aRectBottom);

		float m = Min(dLeft, dRight, dTop, dBottom);

		if (m == dTop) return CU::Vector2<float>(x, aRectTop);
		if (m == dBottom) return CU::Vector2<float>(x, aRectBottom);
		if (m == dLeft) return CU::Vector2<float>(aRectLeft, y);

		return CU::Vector2<float>(aRectRight, y);
	}

	float Min(float aNum1, float aNum2, float aNum3, float aNum4)
	{
		if (aNum1 < aNum2 && aNum1 < aNum3 && aNum1 < aNum4) return aNum1;
		if (aNum2 < aNum1 && aNum2 < aNum3 && aNum2 < aNum4) return aNum2;
		if (aNum3 < aNum1 && aNum3 < aNum2 && aNum3 < aNum4) return aNum3;
		if (aNum4 < aNum1 && aNum4 < aNum2 && aNum4 < aNum3) return aNum4;

		return 0.f;
	}

	int GetAngleBetweenVectors(CU::Vector2<float> aFirst, CU::Vector2<float> aSecond)
	{
		float firstAtan = atan2(aFirst.y, aFirst.x);
		float secondAtan = atan2(aSecond.y, aSecond.x);

		float angle = firstAtan - secondAtan;

		if (angle < 0)
			angle += 2 * 3.14159265359f;

		return int(angle * 180 / 3.14159265359f + 0.5f);
	}

}