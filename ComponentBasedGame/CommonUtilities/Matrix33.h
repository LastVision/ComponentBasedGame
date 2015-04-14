#pragma once

#include "Matrix33Decl.h"
#include <math.h>

namespace CommonUtilities
{

	//***********************************
	//*** Matrix VS Matrix Operations ***
	//***      Compound + Normal      ***
	//***********************************

	template<typename T>
	Matrix33<T> operator+(const Matrix33<T>& aLeftMatrix, const Matrix33<T>& aRightMatrix)
	{
		Matrix33<T> result(aLeftMatrix);
		result += aRightMatrix;
		return result;
	};

	template <typename T>
	Matrix33<T> operator+=(Matrix33<T>& aLeftMatrix, const Matrix33<T>& aRightMatrix)
	{
		for (int i = 0; i < 9; i++)
			aLeftMatrix.myMatrix[i] += aRightMatrix.myMatrix[i];

		return aLeftMatrix;
	}

	template<typename T>
	Matrix33<T> operator-(const Matrix33<T>& aLeftMatrix, const Matrix33<T>& aRightMatrix)
	{
		Matrix33<T> result(aLeftMatrix);
		result -= aRightMatrix;
		return result;
	};

	template <typename T>
	Matrix33<T> operator-=(Matrix33<T>& aLeftMatrix, const Matrix33<T>& aRightMatrix)
	{
		for (int i = 0; i < 9; i++)
			aLeftMatrix.myMatrix[i] -= aRightMatrix.myMatrix[i];

		return aLeftMatrix;
	}

	template <typename T>
	Matrix33<T> operator*(const Matrix33<T>& aLeftMatrix, const Matrix33<T>& aRightMatrix)
	{
		Matrix33<T> result(aLeftMatrix);
		result *= aRightMatrix;
		return result;
	};

	template <typename T>
	Matrix33<T> operator*=(Matrix33<T>& aLeftMatrix, const Matrix33<T>& aRightMatrix)
	{
		CU::Vector3<T> firstCol(aRightMatrix.myMatrix[0], aRightMatrix.myMatrix[3], aRightMatrix.myMatrix[6]);
		CU::Vector3<T> secondCol(aRightMatrix.myMatrix[1], aRightMatrix.myMatrix[4], aRightMatrix.myMatrix[7]);
		CU::Vector3<T> thirdCol(aRightMatrix.myMatrix[2], aRightMatrix.myMatrix[5], aRightMatrix.myMatrix[8]);

		CU::Vector3<T> firstRow(aLeftMatrix.myMatrix[0], aLeftMatrix.myMatrix[1], aLeftMatrix.myMatrix[2]);
		CU::Vector3<T> secondRow(aLeftMatrix.myMatrix[3], aLeftMatrix.myMatrix[4], aLeftMatrix.myMatrix[5]);
		CU::Vector3<T> thirdRow(aLeftMatrix.myMatrix[6], aLeftMatrix.myMatrix[7], aLeftMatrix.myMatrix[8]);

		aLeftMatrix.myMatrix[0] = CU::Dot(firstRow, firstCol);
		aLeftMatrix.myMatrix[1] = CU::Dot(firstRow, secondCol);
		aLeftMatrix.myMatrix[2] = CU::Dot(firstRow, thirdCol);

		aLeftMatrix.myMatrix[3] = CU::Dot(secondRow, firstCol);
		aLeftMatrix.myMatrix[4] = CU::Dot(secondRow, secondCol);
		aLeftMatrix.myMatrix[5] = CU::Dot(secondRow, thirdCol);

		aLeftMatrix.myMatrix[6] = CU::Dot(thirdRow, firstCol);
		aLeftMatrix.myMatrix[7] = CU::Dot(thirdRow, secondCol);
		aLeftMatrix.myMatrix[8] = CU::Dot(thirdRow, thirdCol);

		return aLeftMatrix;
	};


	//***********************************
	//*** Vetor/Matrix Multiplication ***
	//***********************************


	template <typename T>
	CU::Vector3<T> operator*(const CU::Vector3<T>& aVector, const Matrix33<T>& aMatrix)
	{
		CU::Vector3<T> firstCol(aMatrix.myMatrix[0], aMatrix.myMatrix[3], aMatrix.myMatrix[6]);
		CU::Vector3<T> secondCol(aMatrix.myMatrix[1], aMatrix.myMatrix[4], aMatrix.myMatrix[7]);
		CU::Vector3<T> thirdCol(aMatrix.myMatrix[2], aMatrix.myMatrix[5], aMatrix.myMatrix[8]);

		CU::Vector3<T> resultVector;

		resultVector.x = CU::Dot(aVector, firstCol);
		resultVector.y = CU::Dot(aVector, secondCol);
		resultVector.z = CU::Dot(aVector, thirdCol);

		return resultVector;
	};

	template <typename T>
	CU::Vector2<T> operator*(const CU::Vector2<T>& aVector, const Matrix33<T>& aMatrix)
	{
		CU::Vector3<T> vec3(aVector.x, aVector.y, 1);

		vec3 = vec3 * aMatrix;

		return CU::Vector2<T>(vec3.x, vec3.y);
	}

	//***************
	//*** Compare ***
	//***************


	template <typename T>
	bool operator==(const Matrix33<T>& aLeftMatrix, const Matrix33<T> &aRightMatrix)
	{
		for (int i = 0; i < 9; i++)
		{
			if (aLeftMatrix.myMatrix[i] != aRightMatrix.myMatrix[i])
				return false;
		}

		return true;
	}


	//*****************
	//*** Transpose ***
	//*****************

	template <typename T>
	Matrix33<T> Transpose(const Matrix33<T> &aMatrixToTranspose)
	{
		Matrix33<T> tempMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				tempMatrix.myMatrix[j + (i * 3)] = aMatrixToTranspose.myMatrix[i + (j * 3)];
			}
		}

		return tempMatrix;
	}

	//*****************
	//**** Inverse ****
	//*****************

	template <typename T>
	Matrix33<T> Inverse(const Matrix33<T> &aMatrixToInverse)
	{
		CU::Vector3<T> translation;
		translation = aMatrixToInverse.GetTranslation();
		translation.x *= -1;
		translation.y *= -1;
		translation.z = 1;

		Matrix33<T> matrix(aMatrixToInverse);

		matrix.SetTranslation(0.f, 0.f, 1.f);
		matrix = Transpose(matrix);

		translation = translation * matrix;

		matrix.SetTranslation(translation.x, translation.y, translation.z);

		return matrix;
	}
}