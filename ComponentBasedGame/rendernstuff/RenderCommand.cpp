#include "RenderCommand.h"

#include <hgefont.h>
#include <hgesprite.h>


RenderCommand::RenderCommand()
{
}


RenderCommand::~RenderCommand()
{
}


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

DataStruct RenderCommand::GetData() const
{
	return myData;
}

void RenderCommand::SetGUIMode(const bool aBool)
{
	myData.myGUIMode = aBool;
}