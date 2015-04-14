#pragma once

#include "Sphere.h"
#include "AABB.h"
#include "LineSegment3D.h"
#include "LineSegment2D.h"
#include "Fov90Frustrum.h"
#include "planevolume.h"
#include "line.h"


namespace Intersection
{
	bool PointInsideSphere(const Sphere &aSphere, CU::Vector3<float> aPoint)
	{
		float distance = CU::Length2(aPoint - aSphere.myCenterPosition);

		return (distance < aSphere.myRadiusSquared);
	}

	bool PointInsideAABB(const AABB &aAABB, CU::Vector3<float> aPoint)
	{
		if (aPoint.x < aAABB.myMinPos.x || aPoint.x > aAABB.myMaxPos.x)
			return false;

		if (aPoint.y < aAABB.myMinPos.y || aPoint.y > aAABB.myMaxPos.y)
			return false;

		if (aPoint.z < aAABB.myMinPos.z || aPoint.z > aAABB.myMaxPos.z)
			return false;

		return true;
	}

	bool LineVsAABB(const LineSegment3D &aLine, const AABB &aAABB, CU::Vector3<float> &aIntersectionPoint)
	{
		CU::Vector3<float> v1(aAABB.myCenterPos - aLine.myStartPos);
		CU::Vector3<float> dir1 = GetNormalized(aLine.myEndPos - aLine.myStartPos);
		float d1 = CU::Dot(dir1, v1);
		CU::Vector3<float> closestPoint1 = aLine.myStartPos + dir1 * d1;

		CU::Vector3<float> v2(aAABB.myCenterPos - aLine.myEndPos);
		CU::Vector3<float> dir2 = GetNormalized(aLine.myStartPos - aLine.myEndPos);
		float d2 = CU::Dot(dir2, v2);
		CU::Vector3<float> closestPoint2 = aLine.myEndPos + dir2 * d2;

		if (d1 < 0)
		{
			if (Intersection::PointInsideAABB(aAABB, aLine.myStartPos) == false)
			{
				return false;
			}
		}

		if (d2 < 0)
		{
			if (Intersection::PointInsideAABB(aAABB, aLine.myEndPos) == false)
			{
				return false;
			}
		}


		if (PointInsideAABB(aAABB, closestPoint1) == true)
		{
			aIntersectionPoint = closestPoint1;

			if (PointInsideAABB(aAABB, closestPoint2) == true)
			{
				aIntersectionPoint = closestPoint2;
				return true;
			}
		}

		return false;
	}

	bool LineVsSphere(const LineSegment3D &aLine, const Sphere &aSphere, CU::Vector3<float> &aIntersectionPoint)
	{
		CU::Vector3<float> dir = aLine.myEndPos - aLine.myStartPos;
		CU::Normalize(dir);
		CU::Vector3<float> v = aSphere.myCenterPosition - aLine.myStartPos;
		float D = CU::Dot(v, dir);

		if (D < 0)
			return false;

		CU::Vector3<float> closestPoint = aLine.myStartPos + dir * D;
		CU::Vector3<float> toClosest = aSphere.myCenterPosition - closestPoint;

		if ((CU::Length2(toClosest) < aSphere.myRadiusSquared) == false)
			return false;

		if (closestPoint.x > aLine.myEndPos.x && closestPoint.y > aLine.myEndPos.y && closestPoint.z > aLine.myEndPos.z)
			return false;

		aIntersectionPoint = closestPoint;
		return true;
	}

	bool LineVsLine(const LineSegment2D &aFirstLine, const LineSegment2D &aSecLine, CU::Vector2<float> aIntersectionPoint)
	{
		Line<float> lineOne(aFirstLine.myEndPos, aFirstLine.myStartPos);
		Line<float> lineTwo(aSecLine.myEndPos, aSecLine.myStartPos);


		float nX = lineTwo.myXYZ.y * lineOne.myXYZ.z - lineOne.myXYZ.y * lineTwo.myXYZ.z;
		float dX = lineOne.myXYZ.x * lineTwo.myXYZ.y - lineTwo.myXYZ.x * lineOne.myXYZ.y;

		float nY = lineOne.myXYZ.x * lineTwo.myXYZ.z - lineTwo.myXYZ.x * lineOne.myXYZ.z;
		float dY = lineOne.myXYZ.x * lineTwo.myXYZ.y - lineTwo.myXYZ.x * lineOne.myXYZ.y;

		if (dY == 0 && dY == 0)
		{
			if (lineOne.myXYZ.z != lineTwo.myXYZ.z)
				return false;

			CU::Vector2<float> dir1 = aFirstLine.myEndPos - aFirstLine.myStartPos;
			CU::Vector2<float> dir2 = aSecLine.myEndPos - aSecLine.myStartPos;

			float lenghtDir1 = CU::Length(dir1);
			dir1 /= lenghtDir1;

			float lenghtDir2 = CU::Length(dir2);
			dir2 /= lenghtDir2;

			if (CU::Dot(dir1, aSecLine.myEndPos - aFirstLine.myStartPos) < lenghtDir1
			 && CU::Dot(dir1, aSecLine.myEndPos - aFirstLine.myStartPos) > 0)
			{
				aIntersectionPoint = aSecLine.myEndPos;
				return true;
			}

			if (CU::Dot(dir1, aSecLine.myStartPos - aFirstLine.myStartPos) < lenghtDir1
			 && CU::Dot(dir1, aSecLine.myStartPos - aFirstLine.myStartPos) > 0)
			{
				aIntersectionPoint = aSecLine.myStartPos;
				return true;
			}

			if (CU::Dot(dir2, aFirstLine.myEndPos - aSecLine.myStartPos) < lenghtDir2
			 && CU::Dot(dir2, aFirstLine.myEndPos - aSecLine.myStartPos) > 0)
			{
				aIntersectionPoint = aFirstLine.myEndPos;
				return true;
			}

			if (CU::Dot(dir2, aFirstLine.myStartPos - aSecLine.myStartPos) < lenghtDir2
			 && CU::Dot(dir2, aFirstLine.myStartPos - aSecLine.myStartPos) > 0)
			{
				aIntersectionPoint = aFirstLine.myStartPos;
				return true;
			}

			return false;
		}

		aIntersectionPoint = CU::Vector2<float>(nX / dX, nY / dY);

		CU::Vector2<float> v1(aFirstLine.myEndPos - aFirstLine.myStartPos);
		CU::Vector2<float> intersect1(aIntersectionPoint - aFirstLine.myStartPos);

		if (CU::Dot(v1, intersect1) < 0 || CU::Length2(intersect1) > CU::Length2(v1))
			return false;

		CU::Vector2<float> v2(aSecLine.myEndPos - aSecLine.myStartPos);
		CU::Vector2<float> intersect2(aIntersectionPoint - aSecLine.myStartPos);

		if (CU::Dot(v2, intersect2) < 0 || CU::Length2(intersect2) > CU::Length2(v2))
			return false;

		return true;
	}

	bool SwepthSphereVsSphere(const LineSegment3D &aLine, int aLineRadius, const Sphere &aSphere)
	{
		CU::Vector3<float> dir = aLine.myEndPos - aLine.myStartPos;
		CU::Normalize(dir);


		CU::Vector3<float> v = aSphere.myCenterPosition - aLine.myStartPos;
		float d = CU::Dot(v, dir);

		if (d < 0 )
			return false;

		CU::Vector3<float> closestPoint = aLine.myStartPos + dir * d;
		CU::Vector3<float> toClosest = aSphere.myCenterPosition - closestPoint;

		if ((CU::Length2(toClosest) < (aSphere.myRadiusSquared + (aLineRadius * aLineRadius))) == false)
			return false;

		if (closestPoint.x > aLine.myEndPos.x && closestPoint.y > aLine.myEndPos.y && closestPoint.z > aLine.myEndPos.z &&
			closestPoint.x < aLine.myStartPos.x && closestPoint.y < aLine.myStartPos.y && closestPoint.z < aLine.myStartPos.z)
			return false;

		return true;
	}

	bool SwepthSphereVsAABB(const LineSegment3D &aLine, int aLineRadius, const AABB &aAABB)
	{
		AABB tempBox = aAABB;
		tempBox.myMinPos.x -= aLineRadius;
		tempBox.myMinPos.y -= aLineRadius;
		tempBox.myMinPos.z -= aLineRadius;

		tempBox.myMaxPos.x += aLineRadius;
		tempBox.myMaxPos.y += aLineRadius;
		tempBox.myMaxPos.z += aLineRadius;

		return LineVsAABB(aLine, tempBox, CU::Vector3<float>(0, 0, 0));
	}

	bool SphereVsPlane(const Sphere &aSphere, const Plane<float> &aPlane)
	{
		float d = CU::Dot(aSphere.myCenterPosition, aPlane.GetNormal()) - CU::Dot(aPlane.GetPoint(), aPlane.GetNormal());

		return (d < aSphere.myRadius);
	}

	bool SphereVsFrustrum(const Sphere &aSphere, const Fov90Frustrum &aFrustrum)
	{
		for (int i = 0; i < aFrustrum.myPlanes.Size(); ++i)
		{
			if (SphereVsPlane(aSphere, aFrustrum.myPlanes[i]) == false)
				return false;
		}

		return true;
	}
}