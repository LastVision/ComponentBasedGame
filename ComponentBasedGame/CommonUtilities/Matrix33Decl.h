#pragma once

#include "Matrix.h"

#include "GrowingArray.h"
#include "Vector.h"

namespace CommonUtilities
{
	template <typename T>
	class Matrix33
	{
	public:
		Matrix33();
		Matrix33(const Matrix33<T> &aMatrix);
		Matrix33(Matrix44<T> aMatrix);
		~Matrix33();

		Matrix33<T> operator=(const Matrix33<T> &aRightMatrix);

		static Matrix33<T> CreateRotateAroundX(T aAngleInRadians);
		static Matrix33<T> CreateRotateAroundY(T aAngleInRadians);
		static Matrix33<T> CreateRotateAroundZ(T aAngleInRadians);
		static Matrix33<T> CreateProjection(T aWidth, T aHeight);

		void Rotate2D(float aRadian);
		void SetRotation2d(float aRadian);
		void SetTranslation(T aX, T aY, T aZ);
		CU::Vector3<T> GetTranslation() const;

		CU::GrowingArray<T, int> myMatrix;
	};

	template<typename T>
	Matrix33<T>::Matrix33()
	{
		myMatrix.Reserve(9);
		myMatrix[0] = 1;
		myMatrix[1] = 0;
		myMatrix[2] = 0;

		myMatrix[3] = 0;
		myMatrix[4] = 1;
		myMatrix[5] = 0;

		myMatrix[6] = 0;
		myMatrix[7] = 0;
		myMatrix[8] = 1;
	}

	template<typename T>
	Matrix33<T>::Matrix33(const Matrix33<T> &aMatrix)
	{
		myMatrix.Reserve(9);
		for (int i = 0; i < 9; i++)
			myMatrix[i] = aMatrix.myMatrix[i];
	}

	template<typename T>
	Matrix33<T>::Matrix33(Matrix44<T> aMatrix)
	{
		myMatrix.Reserve(9);
		myMatrix[0] = aMatrix.myMatrix[0];
		myMatrix[1] = aMatrix.myMatrix[1];
		myMatrix[2] = aMatrix.myMatrix[2];

		myMatrix[3] = aMatrix.myMatrix[4];
		myMatrix[4] = aMatrix.myMatrix[5];
		myMatrix[5] = aMatrix.myMatrix[6];

		myMatrix[6] = aMatrix.myMatrix[8];
		myMatrix[7] = aMatrix.myMatrix[9];
		myMatrix[8] = aMatrix.myMatrix[10];
	}


	template<typename T>
	Matrix33<T>::~Matrix33()
	{

	}


	template <typename T>
	Matrix33<T> Matrix33<T>::operator=(const Matrix33<T> &aRightMatrix)
	{
		myMatrix.Reserve(9);

		for (int i = 0; i < 9; i++)
			myMatrix[i] = aRightMatrix.myMatrix[i];

		return *this;
	}

	template<typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		Matrix33<T> newMatrix;

		newMatrix.myMatrix[4] = cos(aAngleInRadians);
		newMatrix.myMatrix[5] = sin(aAngleInRadians);

		newMatrix.myMatrix[7] = -sin(aAngleInRadians);
		newMatrix.myMatrix[8] = cos(aAngleInRadians);

		return newMatrix;
	}

	template<typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		Matrix33<T> newMatrix;

		newMatrix.myMatrix[0] = cos(aAngleInRadians);
		newMatrix.myMatrix[2] = -sin(aAngleInRadians);

		newMatrix.myMatrix[6] = sin(aAngleInRadians);
		newMatrix.myMatrix[8] = cos(aAngleInRadians);

		return newMatrix;
	}

	template<typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		Matrix33<T> newMatrix;

		newMatrix.myMatrix[0] = cos(aAngleInRadians);
		newMatrix.myMatrix[1] = sin(aAngleInRadians);

		newMatrix.myMatrix[3] = -sin(aAngleInRadians);
		newMatrix.myMatrix[4] = cos(aAngleInRadians);

		return newMatrix;
	}

	template<typename T>
	Matrix33<T> Matrix33<T>::CreateProjection(T aWidth, T aHeight)
	{
		Matrix33<T> newMatrix;

		newMatrix.myMatrix[0] = static_cast<T>(2) / aWidth;

		newMatrix.myMatrix[4] = static_cast<T>(2) / aHeight;

		return newMatrix;
	}

	template<typename T>
	void Matrix33<T>::Rotate2D(float aRadian)
	{
		Matrix33<T> rotMatrix = Matrix33::CreateRotateAroundZ(aRadian);

		Matrix33<T> tempMatrix = *this;
		tempMatrix *= rotMatrix;

		myMatrix[0] = tempMatrix.myMatrix[0];
		myMatrix[1] = tempMatrix.myMatrix[1];
		myMatrix[3] = tempMatrix.myMatrix[3];
		myMatrix[4] = tempMatrix.myMatrix[4];
	}

	template<typename T>
	void Matrix33<T>::SetRotation2d(float aRadian)
	{
		myMatrix[0] = cos(aRadian);
		myMatrix[1] = sin(aRadian);

		myMatrix[3] = -sin(aRadian);
		myMatrix[4] = cos(aRadian);
	}

	template<typename T>
	void Matrix33<T>::SetTranslation(T aX, T aY, T aZ)
	{
		myMatrix[6] = aX;
		myMatrix[7] = aY;
		myMatrix[8] = aZ;
	}

	template<typename T>
	CU::Vector3<T> Matrix33<T>::GetTranslation() const
	{
		return CU::Vector3<T>(myMatrix[6], myMatrix[7], myMatrix[8]);
	}
}
