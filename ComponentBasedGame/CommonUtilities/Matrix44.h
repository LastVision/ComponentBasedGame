#pragma once

#include "Matrix44Decl.h"
#include "Vector.h"
#include <math.h>

namespace CommonUtilities
{
	//***********************************
	//*** Matrix VS Matrix Operations ***
	//***      Compound + Normal      ***
	//***********************************

	template<typename T>
	Matrix44<T> operator+(const Matrix44<T>& aLeftMatrix, const Matrix44<T>& aRightMatrix)
	{
		Matrix44<T> result(aLeftMatrix);
		result += aRightMatrix;
		return result;
	};

	template <typename T>
	Matrix44<T> operator+=(Matrix44<T>& aLeftMatrix, const Matrix44<T>& aRightMatrix)
	{
		for (int i = 0; i < 16; i++)
			aLeftMatrix.myMatrix[i] += aRightMatrix.myMatrix[i];

		return aLeftMatrix;
	};

	template<typename T>
	Matrix44<T> operator-(const Matrix44<T>& aLeftMatrix, const Matrix44<T>& aRightMatrix)
	{
		Matrix44<T> result(aLeftMatrix);
		result -= aRightMatrix;
		return result;
	};

	template <typename T>
	Matrix44<T> operator-=(Matrix44<T>& aLeftMatrix, const Matrix44<T>& aRightMatrix)
	{
		for (int i = 0; i < 16; i++)
			aLeftMatrix.myMatrix[i] -= aRightMatrix.myMatrix[i];

		return aLeftMatrix;
	};

	template <typename T>
	Matrix44<T> operator*(Matrix44<T>& aLeftMatrix, const Matrix44<T>& aRightMatrix)
	{
		return aLeftMatrix *= aRightMatrix;
	};

	template <typename T>
	Matrix44<T> operator*=(Matrix44<T>& aLeftMatrix, const Matrix44<T>& aRightMatrix)
	{
		CU::Vector4<T> firstCol(aRightMatrix.myMatrix[0], aRightMatrix.myMatrix[4], aRightMatrix.myMatrix[8], aRightMatrix.myMatrix[12]);
		CU::Vector4<T> secondCol(aRightMatrix.myMatrix[1], aRightMatrix.myMatrix[5], aRightMatrix.myMatrix[9], aRightMatrix.myMatrix[13]);
		CU::Vector4<T> thirdCol(aRightMatrix.myMatrix[2], aRightMatrix.myMatrix[6], aRightMatrix.myMatrix[10], aRightMatrix.myMatrix[14]);
		CU::Vector4<T> fourthCol(aRightMatrix.myMatrix[3], aRightMatrix.myMatrix[7], aRightMatrix.myMatrix[11], aRightMatrix.myMatrix[15]);

		CU::Vector4<T> firstRow(aLeftMatrix.myMatrix[0], aLeftMatrix.myMatrix[1], aLeftMatrix.myMatrix[2], aLeftMatrix.myMatrix[3]);
		CU::Vector4<T> secondRow(aLeftMatrix.myMatrix[4], aLeftMatrix.myMatrix[5], aLeftMatrix.myMatrix[6], aLeftMatrix.myMatrix[7]);
		CU::Vector4<T> thirdRow(aLeftMatrix.myMatrix[8], aLeftMatrix.myMatrix[9], aLeftMatrix.myMatrix[10], aLeftMatrix.myMatrix[11]);
		CU::Vector4<T> fourthRow(aLeftMatrix.myMatrix[12], aLeftMatrix.myMatrix[13], aLeftMatrix.myMatrix[14], aLeftMatrix.myMatrix[15]);

		aLeftMatrix.myMatrix[0] = CU::Dot(firstRow, firstCol);
		aLeftMatrix.myMatrix[1] = CU::Dot(firstRow, secondCol);
		aLeftMatrix.myMatrix[2] = CU::Dot(firstRow, thirdCol);
		aLeftMatrix.myMatrix[3] = CU::Dot(firstRow, fourthCol);

		aLeftMatrix.myMatrix[4] = CU::Dot(secondRow, firstCol);
		aLeftMatrix.myMatrix[5] = CU::Dot(secondRow, secondCol);
		aLeftMatrix.myMatrix[6] = CU::Dot(secondRow, thirdCol);
		aLeftMatrix.myMatrix[7] = CU::Dot(secondRow, fourthCol);

		aLeftMatrix.myMatrix[8] = CU::Dot(thirdRow, firstCol);
		aLeftMatrix.myMatrix[9] = CU::Dot(thirdRow, secondCol);
		aLeftMatrix.myMatrix[10] = CU::Dot(thirdRow, thirdCol);
		aLeftMatrix.myMatrix[11] = CU::Dot(thirdRow, fourthCol);

		aLeftMatrix.myMatrix[12] = CU::Dot(fourthRow, firstCol);
		aLeftMatrix.myMatrix[13] = CU::Dot(fourthRow, secondCol);
		aLeftMatrix.myMatrix[14] = CU::Dot(fourthRow, thirdCol);
		aLeftMatrix.myMatrix[15] = CU::Dot(fourthRow, fourthCol);

		return aLeftMatrix;
	};




	//***********************************
	//*** Vetor/Matrix Multiplication ***
	//***********************************

	template <typename T>
	CU::Vector4<T> operator*(const CU::Vector4<T>& aVector, const Matrix44<T>& aMatrix)
	{
		CU::Vector4<T> firstCol(aMatrix.myMatrix[0], aMatrix.myMatrix[4], aMatrix.myMatrix[8], aMatrix.myMatrix[12]);
		CU::Vector4<T> secondCol(aMatrix.myMatrix[1], aMatrix.myMatrix[5], aMatrix.myMatrix[9], aMatrix.myMatrix[13]);
		CU::Vector4<T> thirdCol(aMatrix.myMatrix[2], aMatrix.myMatrix[6], aMatrix.myMatrix[10], aMatrix.myMatrix[14]);
		CU::Vector4<T> fourthCol(aMatrix.myMatrix[3], aMatrix.myMatrix[7], aMatrix.myMatrix[11], aMatrix.myMatrix[15]);

		CU::Vector4<T> resultVector;

		resultVector.x = CU::Dot(aVector, firstCol);
		resultVector.y = CU::Dot(aVector, secondCol);
		resultVector.z = CU::Dot(aVector, thirdCol);
		resultVector.w = CU::Dot(aVector, fourthCol);

		return resultVector;
	};



	//***************
	//*** Compare ***
	//***************

	template <typename T>
	bool operator==(const Matrix44<T>& aLeftMatrix, const Matrix44<T> &aRightMatrix)
	{
		for (int i = 0; i < 16; i++)
		{
			if (aLeftMatrix.myMatrix[i] != aRightMatrix.myMatrix[i])
				return false;
		}

		return true;
	};



	//*****************
	//*** Transpose ***
	//*****************

	template <typename T>
	Matrix44<T> Transpose(const Matrix44<T> &aMatrixToTranspose)
	{
		Matrix44<T> tempMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				tempMatrix.myMatrix[j + (i * 4)] = aMatrixToTranspose.myMatrix[i + (j * 4)];
			}
		}

		return tempMatrix;
	}

	//*****************
	//**** Inverse ****
	//*****************

	template <typename T>
	Matrix44<T> Inverse(const Matrix44<T> &aMatrixToInverse)
	{
		CU::Vector4<T> translation;
		translation = aMatrixToInverse.GetTranslation();
		translation.x *= -1;
		translation.y *= -1;
		translation.z *= -1;
		translation.w = 1;

		Matrix44<T> matrix(aMatrixToInverse);

		matrix.SetTranslation(0.f, 0.f, 0.f, 1.f);
		matrix = Transpose(matrix);

		translation = translation * matrix;

		matrix.SetTranslation(translation.x, translation.y, translation.z, translation.w);

		return matrix;
	}

	//****************************
	//**** ProjectionMatrixLH ****
	//****************************

	template <typename T>
	Matrix44<T> CreateProjectionMatrixLH(T aNearZ, T aFarZ, T aAspectRatio, T aFovAngle)
	{
		Matrix44<T> temp;
		T SinFov;
		T CosFov;
		T Height;
		T Width;

		SinFov = sin(0.5f * aFovAngle);
		CosFov = cos(0.5f * aFovAngle);

		Height = CosFov / SinFov;
		Width = Height / aAspectRatio;

		T scaling = aFarZ / (aFarZ - aNearZ);

		temp.myMatrix[0] = Width;
		temp.myMatrix[1] = 0.0f;
		temp.myMatrix[2] = 0.0f;
		temp.myMatrix[3] = 0.0f;

		temp.myMatrix[4] = 0.0f;
		temp.myMatrix[5] = Height;
		temp.myMatrix[6] = 0.0f;
		temp.myMatrix[7] = 0.0f;

		temp.myMatrix[8] = 0.0f;
		temp.myMatrix[9] = 0.0f;
		temp.myMatrix[10] = scaling;
		temp.myMatrix[11] = 1.f;

		temp.myMatrix[12] = 0.0f;
		temp.myMatrix[13] = 0.0f;
		temp.myMatrix[14] = -scaling * aNearZ;
		temp.myMatrix[15] = 0.0f;

		return temp;
	}
}

