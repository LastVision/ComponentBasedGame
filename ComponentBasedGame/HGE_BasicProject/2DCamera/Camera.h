#pragma once

#include "Matrix.h"


struct Rect
{
	float x;
	float y;
	float width;
	float height;
};

class Camera
{
public:
	Camera();
	~Camera();
	void Init(float aProjectionHeight, float aProjectionWidth, CU::Vector2<float> aPosition);
	void Move(float aX, float aY);

	
	CU::Matrix33<float> GetInverse() const;
	const CU::Matrix33<float> GetProjection() const;

	float GetScreenWidth() const;
	float GetScreenHeight() const;
	CU::Vector2<float> GetPosition() const;
	const Rect& GetCameraRect() const;

	void ClampCamera(const CU::Vector2<float> &aMaxPos);
	void SetPosition(const CU::Vector2<float> &aPosition);

private:
	CU::Matrix33<float> myOrientation;
	CU::Matrix33<float> myProjection;

	float myProjectionHeight;
	float myProjectionWidth;
	Rect myRectangle;
};
