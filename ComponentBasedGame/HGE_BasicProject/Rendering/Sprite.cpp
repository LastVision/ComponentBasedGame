#include "Sprite.h"


Sprite::Sprite()
{
	myHGESprite = nullptr;
	myScale = { 1.f, 1.f };
}

Sprite::~Sprite()
{
}

void Sprite::Render(const CU::Vector2<float>& aPosition)
{
	if (myHGESprite != nullptr)
	{
		myRenderCommand.SetPosition(CU::Vector2<float>(aPosition.myX + GetHotspotX(), aPosition.myY + GetHotspotY()));

		Renderer::GetInstance()->AddRenderCommand(myRenderCommand);
	}
}

void Sprite::Render(const float aScale)
{
	if (myHGESprite != nullptr)
	{
		myRenderCommand.SetPosition(myPosition);
		myRenderCommand.SetXScale(aScale);
		myRenderCommand.SetYScale(aScale);

		Renderer::GetInstance()->AddRenderCommand(myRenderCommand);
	}
}