#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Init(float aProjectionHeight, float aProjectionWidth, CU::Vector2<float> aPosition)
{
	myProjection.myMatrix[0] = 2.f / aProjectionWidth;
	myProjection.myMatrix[4] = 2.f / aProjectionHeight;
	myOrientation.SetTranslation(aPosition.x, aPosition.y, 1);

	myProjectionHeight = aProjectionHeight;
	myProjectionWidth = aProjectionWidth;

	myRectangle.x = myOrientation.GetTranslation().x;
	myRectangle.y = myOrientation.GetTranslation().y;
	myRectangle.width = myProjectionWidth;
	myRectangle.height = myProjectionHeight;
}

void Camera::Move(float aX, float aY)
{
	CU::Matrix33<float> translation;
	translation.SetTranslation(aX, aY, 1);
	myOrientation = translation * myOrientation;

	myRectangle.x = myOrientation.GetTranslation().x;
	myRectangle.y = myOrientation.GetTranslation().y;
}

CU::Matrix33<float> Camera::GetInverse() const
{
	return Inverse(myOrientation);
}

const CU::Matrix33<float> Camera::GetProjection() const
{
	return myProjection;
}

float Camera::GetScreenWidth() const
{
	return myProjectionWidth;
}
float Camera::GetScreenHeight() const
{
	return myProjectionHeight;
}

CU::Vector2<float> Camera::GetPosition() const
{
	return CU::Vector2<float>(myOrientation.GetTranslation().x, myOrientation.GetTranslation().y);
}

const Rect& Camera::GetCameraRect() const
{
	return myRectangle;
}

void Camera::ClampCamera(const CU::Vector2<float> &aMaxPos)
{
	CU::Vector2<float> cameraPos(myRectangle.x, myRectangle.y);

	if (aMaxPos.x < myProjectionWidth || aMaxPos.y < myProjectionHeight)
	{
		if (aMaxPos.x <= myProjectionWidth)
		{
			float widthDifference = myProjectionWidth - aMaxPos.x;

			cameraPos.x = myProjectionWidth / 2.f - widthDifference / 2.f;
		}
			


		if (aMaxPos.y <= myProjectionHeight)
		{
			float heightDifference = myProjectionHeight - aMaxPos.y;

			cameraPos.y = myProjectionHeight / 2.f - heightDifference/2.f;
		}
	}
	else
	{
		if (cameraPos.x <= myRectangle.width / 2.f)
			cameraPos.x = myRectangle.width / 2.f;
		if (cameraPos.x + myRectangle.width / 2.f >= aMaxPos.x)
			cameraPos.x = aMaxPos.x - myRectangle.width / 2.f;

		if (cameraPos.y <= myRectangle.height / 2.f)
			cameraPos.y = myRectangle.height / 2.f;
		if (cameraPos.y + myRectangle.height / 2.f >= aMaxPos.y)
			cameraPos.y = aMaxPos.y - myRectangle.height / 2.f;
	}

	

	myOrientation.SetTranslation(cameraPos.x, cameraPos.y, 1.f);
}

void Camera::SetPosition(const CU::Vector2<float> &aPosition)
{
	myOrientation.SetTranslation(aPosition.x, aPosition.y, 1.f);

	myRectangle.x = myOrientation.GetTranslation().x;
	myRectangle.y = myOrientation.GetTranslation().y;
}