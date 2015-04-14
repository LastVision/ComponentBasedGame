#pragma once

#include <memory>
#include <string>
#include "Vector.h"
#include "..\..\HGE\include\hgecolor.h"


class hgeSprite;
class hgeFont;

struct DataStruct
{
	bool myFontMode;
	bool myGUIMode = false;
	hgeSprite* mySprite;
	std::shared_ptr<hgeFont> myFont;
	CU::Vector2<float> myPosition;
	CU::Vector2<float> mySize;
	float myRotation = 0.f;
	float myXScale = 1.f;
	float myYScale = 1.f;
	std::string myText;
	int myAlignMode = 2;
	hgeColor myColor = hgeColor(1.f, 1.f, 1.f, 1.f);
	int myRenderPriority = 100;
};

class RenderCommand
{
public:
	RenderCommand();
	~RenderCommand();
	
	inline void SetSprite(hgeSprite* aSprite);
	inline void SetFont(std::shared_ptr<hgeFont> aFont);
	inline void SetPosition(CU::Vector2<float> aPosition);
	inline void SetSize(CU::Vector2<float> aSize);
	inline void SetRotation(float aRotation);
	inline void SetXScale(float aScale);
	inline void SetYScale(float aScale);
	inline void SetText(const std::string &aText);
	inline void SetAlignMode(int aAlignMode);
	inline void SetGUIMode(const bool aBool);
	inline void SetColor(const hgeColor& aColor);
	inline void SetRenderPriority(const int aPriority);

	inline const DataStruct& GetData() const;
	
private:
	DataStruct myData;
};

void RenderCommand::SetSprite(hgeSprite* aSprite)
{
	myData.mySprite = aSprite;
	myData.myFontMode = false;
}
void RenderCommand::SetFont(std::shared_ptr<hgeFont> aFont)
{
	myData.myFont = aFont;
	myData.myFontMode = true;
}
void RenderCommand::SetPosition(CU::Vector2<float> aPosition)
{
	myData.myPosition = aPosition;
}
void RenderCommand::SetSize(CU::Vector2<float> aSize)
{
	myData.mySize = aSize;
}
void RenderCommand::SetRotation(float aRotation)
{
	myData.myRotation = aRotation;
}
void RenderCommand::SetXScale(float aScale)
{
	myData.myXScale = aScale;
}
void RenderCommand::SetYScale(float aScale)
{
	myData.myYScale = aScale;
}
void RenderCommand::SetText(const std::string &aText)
{
	myData.myText = aText;
}
void RenderCommand::SetAlignMode(int aAlignMode)
{
	myData.myAlignMode = aAlignMode;
}

const DataStruct& RenderCommand::GetData() const
{
	return myData;
}

void RenderCommand::SetGUIMode(const bool aBool)
{
	myData.myGUIMode = aBool;
}

void RenderCommand::SetColor(const hgeColor& aColor)
{
	myData.myColor = aColor;
}

void RenderCommand::SetRenderPriority(const int aPriority)
{
	myData.myRenderPriority = aPriority;
}
