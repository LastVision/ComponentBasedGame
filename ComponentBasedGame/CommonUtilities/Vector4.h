#pragma once

#include <assert.h>
#include <math.h>
#include "Vector4decl.h"

namespace CommonUtilities
{
	//********************************
	//*** Normal Vector Operations ***
	//********************************

	template<typename TYPE>
	Vector4<TYPE> operator+(const Vector4<TYPE>& aLeftVec, const Vector4<TYPE>& aRightVec)
	{
		return Vector4<TYPE>(aLeftVec.x + aRightVec.x, aLeftVec.y + aRightVec.y, aLeftVec.z + aRightVec.z, aLeftVec.w + aRightVec.w);
	};

	template<typename TYPE>
	Vector4<TYPE> operator-(const Vector4<TYPE>& aLeftVec, const Vector4<TYPE>& aRightVec)
	{
		return Vector4<TYPE>(aLeftVec.x - aRightVec.x, aLeftVec.y - aRightVec.y, aLeftVec.z - aRightVec.z, aLeftVec.w - aRightVec.w);
	};

	template<typename TYPE>
	Vector4<TYPE> operator*(const Vector4<TYPE>& aLeftVec, const Vector4<TYPE>& aRightVec)
	{
		return Vector4<TYPE>(aLeftVec.x * aRightVec.x, aLeftVec.y * aRightVec.y, aLeftVec.z * aRightVec.z, aLeftVec.w * aRightVec.w);
	};

	template<typename TYPE>
	Vector4<TYPE> operator/(const Vector4<TYPE>& aLeftVec, const Vector4<TYPE>& aRightVec)
	{
		assert(aRightVec.x != 0 && aRightVec.y != 0 && aRightVec.z != 0 && aRightVec.w != 0 && "[Vector4] tried to divide by 0");
		return Vector4<TYPE>(aLeftVec.x / aRightVec.x, aLeftVec.y / aRightVec.y, aLeftVec.z / aRightVec.z, aLeftVec.w / aRightVec.w);
	};

	//**********************************
	//*** Compound Vector Operations ***
	//**********************************

	template<typename TYPE>
	Vector4<TYPE>& operator+=(Vector4<TYPE>& aLeftVec, const Vector4<TYPE>& aRightVec)
	{
		aLeftVec.x += aRightVec.x;
		aLeftVec.y += aRightVec.y;
		aLeftVec.z += aRightVec.z;
		aLeftVec.w += aRightVec.w;
		return aLeftVec;
	};

	template<typename TYPE>
	Vector4<TYPE>& operator-= (Vector4<TYPE>& aLeftVec, const Vector4<TYPE>& aRightVec)
	{
		aLeftVec.x -= aRightVec.x;
		aLeftVec.y -= aRightVec.y;
		aLeftVec.z -= aRightVec.z;
		aLeftVec.w -= aRightVec.w;
		return aLeftVec;
	};

	template<typename TYPE>
	Vector4<TYPE>& operator*=(Vector4<TYPE>& aLeftVec, const Vector4<TYPE>& aRightVec)
	{
		aLeftVec.x *= aRightVec.x;
		aLeftVec.y *= aRightVec.y;
		aLeftVec.z *= aRightVec.z;
		aLeftVec.w *= aRightVec.w;
		return aLeftVec;
	};

	template<typename TYPE>
	Vector4<TYPE>& operator/=(Vector4<TYPE>& aLeftVec, const Vector4<TYPE>& aRightVec)
	{
		assert(aRightVec.x != 0 && aRightVec.y != 0 && aRightVec.z != 0 && aRightVec.w != 0 && "[Vector4] tried to divide by 0");
		aLeftVec.x /= aRightVec.x;
		aLeftVec.y /= aRightVec.y;
		aLeftVec.z /= aRightVec.z;
		aLeftVec.w /= aRightVec.w;
		return aLeftVec;
	};

	//********************************
	//*** Normal Scalar Operations ***
	//********************************

	template<typename TYPE>
	Vector4<TYPE> operator+(const Vector4<TYPE>& aLeftVec, const TYPE aScalar)
	{
		return Vector4<TYPE>(aLeftVec.x + aScalar, aLeftVec.y + aScalar, aLeftVec.z + aScalar, aLeftVec.w + aScalar);
	};


	template<typename TYPE>
	Vector4<TYPE> operator-(const Vector4<TYPE>& aLeftVec, const TYPE aScalar)
	{
		return Vector4<TYPE>(aLeftVec.x - aScalar, aLeftVec.y - aScalar, aLeftVec.z - aScalar, aLeftVec.w - aScalar);
	};

	template<typename TYPE>
	Vector4<TYPE> operator*(const Vector4<TYPE>& aLeftVec, const TYPE aScalar)
	{
		return Vector4<TYPE>(aLeftVec.x * aScalar, aLeftVec.y * aScalar, aLeftVec.z * aScalar, aLeftVec.w * aScalar);
	};


	template<typename TYPE>
	Vector4<TYPE> operator/(const Vector4<TYPE>& aLeftVec, const TYPE aScalar)
	{
		assert(aScalar != 0 && "[Vector4] tried to divide with 0");
		return Vector4<TYPE>(aLeftVec.x / aScalar, aLeftVec.y / aScalar, aLeftVec.z / aScalar, aLeftVec.w / aScalar);
	};


	//**********************************
	//*** Compound Scalar Operations ***
	//**********************************

	template<typename TYPE>
	Vector4<TYPE> operator+=(Vector4<TYPE>& aLeftVec, const TYPE aScalar)
	{
		aLeftVec.x += aScalar;
		aLeftVec.y += aScalar;
		aLeftVec.z += aScalar;
		aLeftVec.w += aScalar;
		return aLeftVec;
	};


	template<typename TYPE>
	Vector4<TYPE> operator-=(Vector4<TYPE>& aLeftVec, const TYPE aScalar)
	{
		aLeftVec.x -= aScalar;
		aLeftVec.y -= aScalar;
		aLeftVec.z -= aScalar;
		aLeftVec.w -= aScalar;
		return aLeftVec;
	};


	template<typename TYPE>
	Vector4<TYPE> operator*=(Vector4<TYPE>& aLeftVec, const TYPE aScalar)
	{
		aLeftVec.x *= aScalar;
		aLeftVec.y *= aScalar;
		aLeftVec.z *= aScalar;
		aLeftVec.w *= aScalar;
		return aLeftVec;
	};


	template<typename TYPE>
	Vector4<TYPE> operator/=(Vector4<TYPE>& aLeftVec, const TYPE aScalar)
	{
		assert(aScalar != 0 && "[Vector4] tried to divide with 0");
		aLeftVec.x /= aScalar;
		aLeftVec.y /= aScalar;
		aLeftVec.z /= aScalar;
		aLeftVec.w /= aScalar;
		return aLeftVec;
	};

	//*********************************
	//*** Vector Special Operations ***
	//*********************************

	template<typename TYPE>
	TYPE Length(const Vector4<TYPE>& aVec)
	{
		return static_cast<TYPE>(sqrt((aVec.x * aVec.x) + (aVec.y * aVec.y) + (aVec.z * aVec.z) + (aVec.w * aVec.w)));
	};

	template<typename TYPE>
	TYPE Length2(const Vector4<TYPE>& aVec)
	{
		return static_cast<TYPE>((aVec.x * aVec.x) + (aVec.y * aVec.y) + (aVec.z * aVec.z) + (aVec.w * aVec.w));
	}

	template<typename TYPE>
	void Normalize(Vector4<TYPE>& aVec)
	{
		assert(Length(aVec) != 0 && "Tried to Normalize a 0-Vector");
		aVec /= Length(aVec);
	}

	template<typename TYPE>
	Vector4<TYPE> GetNormalized(const Vector4<TYPE>& aVec)
	{
		assert(Length(aVec) != 0 && "Tried to Normalize a 0-Vector");
		return aVec / Length(aVec);
	}

	template<typename TYPE>
	TYPE Dot(const Vector4<TYPE>& aLeftVec, const Vector4<TYPE>& aRightVec)
	{
		return ((aLeftVec.x * aRightVec.x) + (aLeftVec.y * aRightVec.y) + (aLeftVec.z * aRightVec.z) + (aLeftVec.w * aRightVec.w));
	}
}