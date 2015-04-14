#pragma once

#include "Vector.h"

template <typename T>
class Line
{
public:
	Line();
	Line(CU::Vector2<T> aFirstPoint, CU::Vector2<T> aSecondPoint);
	~Line();

	void InitWith2Points(CU::Vector2<T> aFirstPoint, CU::Vector2<T> aSecondPoint);
	void InitWithPointAndDirection(CU::Vector2<T> aPoint, CU::Vector2<T> aDirection);

	bool Inside(CU::Vector2<T> aPosition);

	CU::Vector2<T> GetNormal() const;
	CU::Vector2<T> GetPoint() const;

	CU::Vector3<T> myXYZ;

private:
	CU::Vector2<T> myNormal;
	CU::Vector2<T> myPoint;
};

template <typename T>
Line<T>::Line()
{

}

template <typename T>
Line<T>::Line(CU::Vector2<T> aFirstPoint, CU::Vector2<T> aSecondPoint)
{
	InitWith2Points(aFirstPoint, aSecondPoint);
}

template <typename T>
Line<T>::~Line()
{

}

template <typename T>
void Line<T>::InitWith2Points(CU::Vector2<T> aFirstPoint, CU::Vector2<T> aSecondPoint)
{
	myPoint = aFirstPoint;

	myNormal = aSecondPoint - aFirstPoint;
	CU::Normalize(myNormal);

	T oldX = myNormal.x;

	myNormal.x = -myNormal.y;
	myNormal.y = oldX;

	Vector2<T> line = aSecondPoint - aFirstPoint;
	Vector2<T> norm = Vector2<T>(-line.y, line.x);
	CU::Normalize(norm);

	myXYZ.x = norm.x;
	myXYZ.y = norm.y;
	myXYZ.z = CU::Dot(aFirstPoint, norm);

}

template <typename T>
void Line<T>::InitWithPointAndDirection(CU::Vector2<T> aPoint, CU::Vector2<T> aDirection)
{
	myPoint = aPoint;

	myNormal = aDirection;
	CU::Normalize(myNormal);

	T oldX = myNormal.x;

	myNormal.x = -myNormal.y;
	myNormal.y = oldX;

	Normalize(aDirection);
	myXYZ.x = -aDirection.y;
	myXYZ.y = aDirection.x;
	myXYZ.z = Dot(aPoint, Vector2<T>(myXYZ.x, myXYZ.y));
}

template <typename T>
bool Line<T>::Inside(CU::Vector2<T> aPosition)
{
	T distance = CU::Dot(myNormal, (aPosition - myPoint));

	if (distance < 0)
		return true;
	
	return false;
}

template <typename T>
CU::Vector2<T> Line<T>::GetNormal() const
{
	return myNormal;
}

template <typename T>
CU::Vector2<T> Line<T>::GetPoint() const
{
	return myPoint;
}
