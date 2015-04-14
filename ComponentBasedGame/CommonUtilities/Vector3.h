#pragma once

#include <assert.h>
#include <math.h>
#include "Vector3decl.h"

namespace CommonUtilities
{
	//********************************
	//*** Normal Vector Operations ***
	//********************************

	template<typename TYPE>
	Vector3<TYPE> operator+(const Vector3<TYPE>& aLeftVec, const Vector3<TYPE>& aRightVec)
	{
		return Vector3<TYPE>(aLeftVec.x + aRightVec.x, aLeftVec.y + aRightVec.y, aLeftVec.z + aRightVec.z);
	};

	template<typename TYPE>
	Vector3<TYPE> operator-(const Vector3<TYPE>& aLeftVec, const Vector3<TYPE>& aRightVec)
	{
		return Vector3<TYPE>(aLeftVec.x - aRightVec.x, aLeftVec.y - aRightVec.y, aLeftVec.z - aRightVec.z);
	};

	template<typename TYPE>
	Vector3<TYPE> operator*(const Vector3<TYPE>& aLeftVec, const Vector3<TYPE>& aRightVec)
	{
		return Vector3<TYPE>(aLeftVec.x * aRightVec.x, aLeftVec.y * aRightVec.y, aLeftVec.z * aRightVec.z);
	};

	template<typename TYPE>
	Vector3<TYPE> operator/(const Vector3<TYPE>& aLeftVec, const Vector3<TYPE>& aRightVec)
	{
		assert(aRightVec.x != 0 && aRightVec.y != 0 && aRightVec.z != 0 && "[Vector3] tried to divide by 0");
		return Vector3<TYPE>(aLeftVec.x / aRightVec.x, aLeftVec.y / aRightVec.y, aLeftVec.z / aRightVec.z);
	};

	//**********************************
	//*** Compound Vector Operations ***
	//**********************************

	template<typename TYPE>
	Vector3<TYPE>& operator+=(Vector3<TYPE>& aLeftVec, const Vector3<TYPE>& aRightVec)
	{
		aLeftVec.x += aRightVec.x;
		aLeftVec.y += aRightVec.y;
		aLeftVec.z += aRightVec.z;
		return aLeftVec;
	};

	template<typename TYPE>
	Vector3<TYPE>& operator-= (Vector3<TYPE>& aLeftVec, const Vector3<TYPE>& aRightVec)
	{
		aLeftVec.x -= aRightVec.x;
		aLeftVec.y -= aRightVec.y;
		aLeftVec.z -= aRightVec.z;
		return aLeftVec;
	};

	template<typename TYPE>
	Vector3<TYPE>& operator*=(Vector3<TYPE>& aLeftVec, const Vector3<TYPE>& aRightVec)
	{
		aLeftVec.x *= aRightVec.x;
		aLeftVec.y *= aRightVec.y;
		aLeftVec.z *= aRightVec.z;
		return aLeftVec;
	};

	template<typename TYPE>
	Vector3<TYPE>& operator/=(Vector3<TYPE>& aLeftVec, const Vector3<TYPE>& aRightVec)
	{
		assert(aRightVec.x != 0 && aRightVec.y != 0 && aRightVec.z != 0 && "[Vector3] tried to divide by 0");
		aLeftVec.x /= aRightVec.x;
		aLeftVec.y /= aRightVec.y;
		aLeftVec.z /= aRightVec.z;
		return aLeftVec;
	};

	//********************************
	//*** Normal Scalar Operations ***
	//********************************

	template<typename TYPE>
	Vector3<TYPE> operator+(const Vector3<TYPE>& aLeftVec, const TYPE aScalar)
	{
		return Vector3<TYPE>(aLeftVec.x + aScalar, aLeftVec.y + aScalar, aLeftVec.z + aScalar);
	};


	template<typename TYPE>
	Vector3<TYPE> operator-(const Vector3<TYPE>& aLeftVec, const TYPE aScalar)
	{
		return Vector3<TYPE>(aLeftVec.x - aScalar, aLeftVec.y - aScalar, aLeftVec.z - aScalar);
	};

	template<typename TYPE>
	Vector3<TYPE> operator*(const Vector3<TYPE>& aLeftVec, const TYPE aScalar)
	{
		return Vector3<TYPE>(aLeftVec.x * aScalar, aLeftVec.y * aScalar, aLeftVec.z * aScalar);
	};


	template<typename TYPE>
	Vector3<TYPE> operator/(const Vector3<TYPE>& aLeftVec, const TYPE aScalar)
	{
		assert(aScalar != 0 && "[Vector3] tried to divide with 0");
		return Vector3<TYPE>(aLeftVec.x / aScalar, aLeftVec.y / aScalar, aLeftVec.z / aScalar);
	};


	//**********************************
	//*** Compound Scalar Operations ***
	//**********************************

	template<typename TYPE>
	Vector3<TYPE> operator+=(Vector3<TYPE>& aLeftVec, const TYPE aScalar)
	{
		aLeftVec.x += aScalar;
		aLeftVec.y += aScalar;
		aLeftVec.z += aScalar;
		return aLeftVec;
	};


	template<typename TYPE>
	Vector3<TYPE> operator-=(Vector3<TYPE>& aLeftVec, const TYPE aScalar)
	{
		aLeftVec.x -= aScalar;
		aLeftVec.y -= aScalar;
		aLeftVec.z -= aScalar;
		return aLeftVec;
	};


	template<typename TYPE>
	Vector3<TYPE> operator*=(Vector3<TYPE>& aLeftVec, const TYPE aScalar)
	{
		aLeftVec.x *= aScalar;
		aLeftVec.y *= aScalar;
		aLeftVec.z *= aScalar;
		return aLeftVec;
	};


	template<typename TYPE>
	Vector3<TYPE> operator/=(Vector3<TYPE>& aLeftVec, const TYPE aScalar)
	{
		assert(aScalar != 0 && "[Vector3] tried to divide with 0");
		aLeftVec.x /= aScalar;
		aLeftVec.y /= aScalar;
		aLeftVec.z /= aScalar;
		return aLeftVec;
	};

	//*********************************
	//*** Vector Special Operations ***
	//*********************************

	template<typename TYPE>
	TYPE Length(const Vector3<TYPE>& aVec)
	{
		return static_cast<TYPE>(sqrt((aVec.x * aVec.x) + (aVec.y * aVec.y) + (aVec.z * aVec.z)));
	};

	template<typename TYPE>
	TYPE Length2(const Vector3<TYPE>& aVec)
	{
		return static_cast<TYPE>((aVec.x * aVec.x) + (aVec.y * aVec.y) + (aVec.z * aVec.z));
	}

	template<typename TYPE>
	void Normalize(Vector3<TYPE>& aVec)
	{
		assert(Length(aVec) != 0 && "Tried to Normalize a 0-Vector");
		aVec /= Length(aVec);
	}

	template<typename TYPE>
	Vector3<TYPE> GetNormalized(const Vector3<TYPE>& aVec)
	{
		assert(Length(aVec) != 0 && "Tried to Normalize a 0-Vector");
		return aVec / Length(aVec);
	}

	template<typename TYPE>
	TYPE Dot(const Vector3<TYPE>& aLeftVec, const Vector3<TYPE>& aRightVec)
	{
		return ((aLeftVec.x * aRightVec.x) + (aLeftVec.y * aRightVec.y) + (aLeftVec.z * aRightVec.z));
	}

	template<typename TYPE>
	Vector3<TYPE> Cross(const Vector3<TYPE>& aLeftVec, const Vector3<TYPE>& aRightVec)
	{
		return Vector3<TYPE>(
			(aLeftVec.y * aRightVec.z) - (aLeftVec.z * aRightVec.y), //x
			(aLeftVec.z * aRightVec.x) - (aLeftVec.x * aRightVec.z), //y
			(aLeftVec.x * aRightVec.y) - (aLeftVec.y * aRightVec.x)  //z
			);
	}
}