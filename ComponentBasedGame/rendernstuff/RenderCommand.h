#pragma once

#include <memory>
#include <string>
#include "Vector.h"


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
};

class RenderCommand
{
public:
	RenderCommand();
	~RenderCommand();
	
	void SetSprite(hgeSprite* aSprite);
	void SetFont(std::shared_ptr<hgeFont> aFont);
	void SetPosition(CU::Vector2<float> aPosition);
	void SetSize(CU::Vector2<float> aSize);
	void SetRotation(float aRotation);
	void SetXScale(float aScale);
	void SetYScale(float aScale);
	void SetText(const std::string &aText);
	void SetAlignMode(int aAlignMode);
	void SetGUIMode(const bool aBool);

	DataStruct GetData() const;
	
private:
	DataStruct myData;
};

