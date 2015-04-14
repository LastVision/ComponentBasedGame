#pragma once

#include "Renderer.h"
#include "Vector.h"
#include "hgesprite.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Render(const CU::Vector2<float>& aPosition);
	void Render(const float aScale);

	inline void SetRotation(const float& aRotation);
	inline void SetPosition(const CU::Vector2<float>& aPosition);
	inline const CU::Vector2<float>& GetPosition() const;
	inline float GetWidth() const;
	inline float GetHeight() const;
	inline float GetHotspotX() const;
	inline float GetHotspotY() const;

	inline void SetHGESprite(hgeSprite* aSprite);
	inline void SetTextureRect(const CU::Vector2<float>& aPos, const CU::Vector2<float>& aLength) const;
	inline void GetTextureRect(float& aX, float& aY, float& aW, float& aH);
	inline void SetHotspot(const CU::Vector2<float>& aHotspot);

	inline void SetColor(DWORD aColor);
	inline void SetScale(const CU::Vector2<float>& aScale);
	inline void SetScale(const float aScale);
	inline void SetXScale(const float aScale);
	inline void SetYScale(const float aScale);

private:
	hgeSprite* myHGESprite;
	CU::Vector2<float> myPosition;
	CU::Vector2<float> myScale;
	RenderCommand myRenderCommand;
};

void Sprite::SetColor(DWORD aColor)
{
	myHGESprite->SetColor(aColor);
}

void Sprite::SetRotation(const float& aRotation)
{
	myRenderCommand.SetRotation(aRotation);
}

void Sprite::SetPosition(const CU::Vector2<float>& aPosition)
{
	myPosition = aPosition;
}

const CU::Vector2<float>& Sprite::GetPosition() const
{
	return myPosition;
}


float Sprite::GetWidth() const
{
	return myHGESprite->GetWidth();
}

float Sprite::GetHeight() const
{
	return myHGESprite->GetHeight();
}

float Sprite::GetHotspotX() const
{
	float value;
	float secvalue;
	myHGESprite->GetHotSpot(&value, &secvalue);

	return value;
}

float Sprite::GetHotspotY() const
{
	float value;
	float secvalue;
	myHGESprite->GetHotSpot(&secvalue, &value);

	return value;
}

void Sprite::SetHGESprite(hgeSprite* aSprite)
{
	myHGESprite = aSprite;
	myRenderCommand.SetSprite(myHGESprite);
}

void Sprite::SetTextureRect(const CU::Vector2<float>& aPos, const CU::Vector2<float>& aLength) const
{
	myHGESprite->SetTextureRect(aPos.x, aPos.y, aLength.x, aLength.y);
}

void Sprite::GetTextureRect(float& aX, float& aY, float& aW, float& aH)
{
	myHGESprite->GetTextureRect(&aX, &aY, &aW, &aH);
}


void Sprite::SetHotspot(const CU::Vector2<float>& aHotspot)
{
	myHGESprite->SetHotSpot(aHotspot.myX, aHotspot.myY);
}

void Sprite::SetScale(const CU::Vector2<float>& aScale)
{
	myScale = aScale;

	myRenderCommand.SetXScale(myScale.x);
	myRenderCommand.SetYScale(myScale.y);
}

void Sprite::SetScale(const float aScale)
{
	myScale.x = aScale;
	myScale.y = aScale;

	myRenderCommand.SetXScale(myScale.x);
	myRenderCommand.SetYScale(myScale.y);
}

void Sprite::SetXScale(const float aScale)
{
	myScale.x = aScale;

	myRenderCommand.SetXScale(myScale.x);
}

void Sprite::SetYScale(const float aScale)
{
	myScale.y = aScale;

	myRenderCommand.SetYScale(myScale.y);
}