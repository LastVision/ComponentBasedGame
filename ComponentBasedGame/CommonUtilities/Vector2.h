#pragma once
#include <assert.h>
#include <math.h>
#include "Vector2decl.h"


namespace CommonUtilities
{
	//******************************
	//******** Comparing ***********
	//******************************
	template<typename TYPE>
	bool operator==(const Vector2<TYPE>& aLeftVec, const Vector2<TYPE>& aRightVec)
	{
		return (aLeftVec.x == aRightVec.x && aLeftVec.y == aRightVec.y);
	};


	//********************************
	//******** Unary Minus ***********
	//********************************
	template<typename TYPE>
	Vector2<TYPE> operator-(const Vector2<TYPE>& aVector)
	{
		return Vector2<TYPE>(-aVector.x, -aVector.y);
	};

	//********************************
	//*** Normal Vector Operations ***
	//********************************

	template<typename TYPE>
	Vector2<TYPE> operator+(const Vector2<TYPE>& aLeftVec, const Vector2<TYPE>& aRightVec)
	{
		return Vector2<TYPE>(aLeftVec.x + aRightVec.x, aLeftVec.y + aRightVec.y);
	};

	template<typename TYPE>
	Vector2<TYPE> operator-(const Vector2<TYPE>& aLeftVec, const Vector2<TYPE>& aRightVec)
	{
		return Vector2<TYPE>(aLeftVec.x - aRightVec.x, aLeftVec.y - aRightVec.y);
	};

	template<typename TYPE>
	Vector2<TYPE> operator*(const Vector2<TYPE>& aLeftVec, const Vector2<TYPE>& aRightVec)
	{
		return Vector2<TYPE>(aLeftVec.x * aRightVec.x, aLeftVec.y * aRightVec.y);
	};

	template<typename TYPE>
	Vector2<TYPE> operator/(const Vector2<TYPE>& aLeftVec, const Vector2<TYPE>& aRightVec)
	{
		assert(aRightVec.x != 0 && aRightVec.y != 0 && "[Vector2] tried to divide by 0");
		return Vector2<TYPE>(aLeftVec.x / aRightVec.x, aLeftVec.y / aRightVec.y);
	};

	//**********************************
	//*** Compound Vector Operations ***
	//**********************************

	template<typename TYPE>
	Vector2<TYPE>& operator+=(Vector2<TYPE>& aLeftVec, const Vector2<TYPE>& aRightVec)
	{
		aLeftVec.x += aRightVec.x;
		aLeftVec.y += aRightVec.y;
		return aLeftVec;
	};

	template<typename TYPE>
	Vector2<TYPE>& operator-= (Vector2<TYPE>& aLeftVec, const Vector2<TYPE>& aRightVec)
	{
		aLeftVec.x -= aRightVec.x;
		aLeftVec.y -= aRightVec.y;
		return aLeftVec;
	};

	template<typename TYPE>
	Vector2<TYPE>& operator*=(Vector2<TYPE>& aLeftVec, const Vector2<TYPE>& aRightVec)
	{
		aLeftVec.x *= aRightVec.x;
		aLeftVec.y *= aRightVec.y;
		return aLeftVec;
	};

	template<typename TYPE>
	Vector2<TYPE>& operator/=(Vector2<TYPE>& aLeftVec, const Vector2<TYPE>& aRightVec)
	{
		assert(aRightVec.x != 0 && aRightVec.y != 0 && "[Vector2] tried to divide by 0");
		aLeftVec.x /= aRightVec.x;
		aLeftVec.y /= aRightVec.y;
		return aLeftVec;
	};

	//********************************
	//*** Normal Scalar Operations ***
	//********************************

	template<typename TYPE>
	Vector2<TYPE> operator+(const Vector2<TYPE>& aLeftVec, const TYPE aScalar)
	{
		return Vector2<TYPE>(aLeftVec.x + aScalar, aLeftVec.y + aScalar);
	};


	template<typename TYPE>
	Vector2<TYPE> operator-(const Vector2<TYPE>& aLeftVec, const TYPE aScalar)
	{
		return Vector2<TYPE>(aLeftVec.x - aScalar, aLeftVec.y - aScalar);
	};

	template<typename TYPE>
	Vector2<TYPE> operator*(const Vector2<TYPE>& aLeftVec, const TYPE aScalar)
	{
		return Vector2<TYPE>(aLeftVec.x * aScalar, aLeftVec.y * aScalar);
	};


	template<typename TYPE>
	Vector2<TYPE> operator/(const Vector2<TYPE>& aLeftVec, const TYPE aScalar)
	{
		assert(aScalar != 0 && "[Vector2] tried to divide by 0");
		return Vector2<TYPE>(aLeftVec.x / aScalar, aLeftVec.y / aScalar);
	};


	//**********************************
	//*** Compound Scalar Operations ***
	//**********************************

	template<typename TYPE>
	Vector2<TYPE> operator+=(Vector2<TYPE>& aLeftVec, const TYPE aScalar)
	{
		aLeftVec.x += aScalar;
		aLeftVec.y += aScalar;
		return aLeftVec;
	};


	template<typename TYPE>
	Vector2<TYPE> operator-=(Vector2<TYPE>& aLeftVec, const TYPE aScalar)
	{
		aLeftVec.x -= aScalar;
		aLeftVec.y -= aScalar;
		return aLeftVec;
	};


	template<typename TYPE>
	Vector2<TYPE> operator*=(Vector2<TYPE>& aLeftVec, const TYPE aScalar)
	{
		aLeftVec.x *= aScalar;
		aLeftVec.y *= aScalar;
		return aLeftVec;
	};


	template<typename TYPE>
	Vector2<TYPE> operator/=(Vector2<TYPE>& aLeftVec, const TYPE aScalar)
	{
		assert(aScalar != 0 && "[Vector2] tried to divide by 0");
		aLeftVec.x /= aScalar;
		aLeftVec.y /= aScalar;
		return aLeftVec;
	};

	//*********************************
	//*** Vector Special Operations ***
	//*********************************

	template<typename TYPE>
	TYPE Length(const Vector2<TYPE>& aVec)
	{
		return static_cast<TYPE>(sqrt((aVec.x * aVec.x) + (aVec.y * aVec.y)));
	};

	template<typename TYPE>
	TYPE Length2(const Vector2<TYPE>& aVec)
	{
		return static_cast<TYPE>((aVec.x * aVec.x) + (aVec.y * aVec.y));
	}

	template<typename TYPE>
	void Normalize(Vector2<TYPE>& aVec)
	{
		assert(Length(aVec) != 0 && "Tried to Normalize a 0-Vector");
		aVec /= Length(aVec);
	}

	template<typename TYPE>
	Vector2<TYPE> GetNormalized(const Vector2<TYPE>& aVec)
	{
		assert(Length(aVec) != 0 && "Tried to Normalize a 0-Vector");
		return aVec / Length(aVec);
	}

	template<typename TYPE>
	TYPE Dot(const Vector2<TYPE>& aLeftVec, const Vector2<TYPE>& aRightVec)
	{
		return ((aLeftVec.x * aRightVec.x) + (aLeftVec.y * aRightVec.y));
	}

};
namespace CU = CommonUtilities;