#pragma once

#include "GrowingArray.h"
#include "Vector.h"

namespace CommonUtilities
{
	template <typename T>
	class Matrix44
	{
	public:
		Matrix44();
		Matrix44(const Matrix44<T> &aMatrix);
		~Matrix44();

		Matrix44<T>& operator=(const Matrix44<T> &aRightMatrix);

		static Matrix44<T> CreateRotateAroundX(T aAngleInRadians);
		static Matrix44<T> CreateRotateAroundY(T aAngleInRadians);
		static Matrix44<T> CreateRotateAroundZ(T aAngleInRadians);

		void SetTranslation(T aX, T aY, T aZ, T aW);
		void SetTranslation(CU::Vector4<T> aTranslation);
		CU::Vector4<T> GetTranslation() const;

		CU::GrowingArray<T, int> myMatrix;
	};

	template <typename T>
	Matrix44<T>::Matrix44()
	{
		myMatrix.Reserve(16);
		for (int i = 0; i < 16; i++)
			myMatrix[i] = 0;

		myMatrix[0] = 1;
		myMatrix[5] = 1;
		myMatrix[10] = 1;
		myMatrix[15] = 1;
	}

	template <typename T>
	Matrix44<T>::Matrix44(const Matrix44<T> &aMatrix)
	{
		myMatrix.Reserve(16);
		for (int i = 0; i < 16; i++)
		{
			myMatrix[i] = aMatrix.myMatrix[i];
		}
	}

	template <typename T>
	Matrix44<T>::~Matrix44()
	{

	}

	template <typename T>
	Matrix44<T>& Matrix44<T>::operator=(const Matrix44<T> &aRightMatrix)
	{
		myMatrix.Reserve(16);
		for (int i = 0; i < 16; i++)
		{
			myMatrix[i] = aRightMatrix.myMatrix[i];
		}

		return *this;
	}


	template<typename T>
	Matrix44<T> Matrix44<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		Matrix44<T> newMatrix;

		newMatrix.myMatrix[5] = cos(aAngleInRadians);
		newMatrix.myMatrix[6] = sin(aAngleInRadians);

		newMatrix.myMatrix[9] = -sin(aAngleInRadians);
		newMatrix.myMatrix[10] = cos(aAngleInRadians);

		return newMatrix;
	}

	template<typename T>
	Matrix44<T> Matrix44<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		Matrix44<T> newMatrix;

		newMatrix.myMatrix[0] = cos(aAngleInRadians);
		newMatrix.myMatrix[2] = -sin(aAngleInRadians);

		newMatrix.myMatrix[8] = sin(aAngleInRadians);
		newMatrix.myMatrix[10] = cos(aAngleInRadians);

		return newMatrix;
	}

	template<typename T>
	Matrix44<T> Matrix44<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		Matrix44<T> newMatrix;

		newMatrix.myMatrix[0] = cos(aAngleInRadians);
		newMatrix.myMatrix[1] = sin(aAngleInRadians);

		newMatrix.myMatrix[4] = -sin(aAngleInRadians);
		newMatrix.myMatrix[5] = cos(aAngleInRadians);

		return newMatrix;
	}

	template <typename T>
	void Matrix44<T>::SetTranslation(T aX, T aY, T aZ, T aW)
	{
		myMatrix[12] = aX;
		myMatrix[13] = aY;
		myMatrix[14] = aZ;
		myMatrix[15] = aW;
	}

	template <typename T>
	void Matrix44<T>::SetTranslation(CU::Vector4<T> aTranslation)
	{
		myMatrix[12] = aTranslation.x;
		myMatrix[13] = aTranslation.y;
		myMatrix[14] = aTranslation.z;
		myMatrix[15] = aTranslation.w;
	}

	template <typename T>
	CU::Vector4<T> Matrix44<T>::GetTranslation() const
	{
		return CU::Vector4<T>(myMatrix[12], myMatrix[13], myMatrix[14], myMatrix[15]);
	}
}