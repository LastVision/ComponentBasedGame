#include "Renderer.h"
#include "DL_Debug.h"

#include "hge.h"
#include "hgefont.h"
#include "hgesprite.h"
#include "hgeColor.h"

//****** STATIC ******



void Renderer::Create(HGE *aHGEHandle, Syncronizer *aSyncronizer)
{
	DL_ASSERT_EX(ourInstance == nullptr, "Tried to [Create] a [Renderer] after we allready created one");

	ourInstance = new Renderer();
	ourInstance->Init(aHGEHandle, aSyncronizer);
}
bool Renderer::Destroy()
{
	delete ourInstance;
	ourInstance = nullptr;

	return true;
}

Renderer* Renderer::GetInstance()
{
	DL_ASSERT_EX(ourInstance != nullptr, "Tried to [GetInstance] a [Renderer] that wasnt created");

	return ourInstance;
}

//****** PUBLIC ******
void Renderer::AddRenderCommand(const RenderCommand &aRenderCommand)
{
	CU::GrowingArray<RenderCommand, int> &buffer = myBuffers[myActiveBuffer ^ 1];
	buffer.Add(aRenderCommand);
}

void Renderer::RenderCircle(const CU::Vector2<float> aCenterPoint, const float aRadius, const int aNumPointsOnCircle, const hgeColor& aColor)
{
	float step = 2 * M_PI / aNumPointsOnCircle;

	float theta = 0;

	CU::Vector2<float> currPoint;
	CU::Vector2<float> prevPoint;

	bool firstPoint = true;

	while (theta < 360.f)
	{
		currPoint.x = aCenterPoint.x + aRadius * cos(theta);
		currPoint.y = aCenterPoint.y + aRadius * sin(theta);

		if (firstPoint == true)
		{
			firstPoint = false;
			prevPoint = currPoint;
		}
		

		LineStruct newLine;
		newLine.FirstPoint = prevPoint;
		newLine.SecondPoint = currPoint;
		newLine.Color = aColor;

		myLineBuffers[myActiveBuffer ^ 1].Add(newLine);

		prevPoint = currPoint;

		theta += step;
	}
}

void Renderer::RenderLine(const CU::Vector2<float>& aFirstPoint, const CU::Vector2<float>& aSecondPoint, const hgeColor& aColor)
{
	LineStruct newLine;
	newLine.FirstPoint = aFirstPoint;
	newLine.SecondPoint = aSecondPoint;
	newLine.Color = aColor;
	myLineBuffers[myActiveBuffer ^ 1].Add(newLine);
}

void Renderer::Render()
{
	while (mySyncronizer->GetShutDownStatus() == false)
	{
		FinalRender();

		mySyncronizer->WaitForUpdate();
		SwapBuffers();
		mySyncronizer->SetRenderReady();
	}
}



//****** PRIVATE ******

Renderer* Renderer::ourInstance = nullptr;

Renderer::Renderer()
{

}


Renderer::~Renderer()
{
}

void Renderer::Init(HGE *aHGE, Syncronizer *aSyncronizer)
{
	myHgeHandle = aHGE;
	mySyncronizer = aSyncronizer;

	myBuffers.Reserve(2);
	myBuffers[0].Init(100);
	myBuffers[1].Init(100);

	myLineBuffers.Reserve(2);
	myLineBuffers[0].Init(100);
	myLineBuffers[1].Init(100);

	myActiveBuffer = 0;
}

void Renderer::SwapBuffers()
{
	myBuffers[myActiveBuffer].RemoveAll();
	myLineBuffers[myActiveBuffer].RemoveAll();
	myActiveBuffer ^= 1;
}

void Renderer::FinalRender()
{
	myHgeHandle->Gfx_BeginScene();
	myHgeHandle->Gfx_Clear(0);


	for (int i = 0; i < myBuffers[myActiveBuffer].Size(); i++)
	{
		RenderCommand &currCommand = myBuffers[myActiveBuffer][i];

		RenderWithoutCamera(currCommand);
	}

	for (int i = 0; i < myLineBuffers[myActiveBuffer].Size(); i++)
	{
		CU::Vector2<float> firstPoint = myLineBuffers[myActiveBuffer][i].FirstPoint;
		CU::Vector2<float> secondPoint = myLineBuffers[myActiveBuffer][i].SecondPoint;

		myHgeHandle->Gfx_RenderLine(firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y);
	}

	myHgeHandle->Gfx_EndScene();
}

void Renderer::RenderWithoutCamera(const RenderCommand& aCommand)
{
	if (aCommand.GetData().myFontMode == false)
	{
		if (aCommand.GetData().mySize.x != 0.f || aCommand.GetData().mySize.y != 0.f)
		{
			CU::Vector2<float> drawMin = aCommand.GetData().myPosition;
			CU::Vector2<float> drawMax(drawMin);
			drawMax.x += aCommand.GetData().mySize.x;
			drawMax.y += aCommand.GetData().mySize.y;

			aCommand.GetData().mySprite->SetColor(aCommand.GetData().myColor.GetHWColor());
			aCommand.GetData().mySprite->RenderStretch(drawMin.x, drawMin.y, drawMax.x, drawMax.y);
		}
		else
		{
			CU::Vector2<float> drawPos = aCommand.GetData().myPosition;

			aCommand.GetData().mySprite->SetColor(aCommand.GetData().myColor.GetHWColor());
			aCommand.GetData().mySprite->RenderEx(
				drawPos.x,
				drawPos.y,
				aCommand.GetData().myRotation,
				aCommand.GetData().myXScale,
				aCommand.GetData().myYScale);
		}

	}
	else
	{
		CU::Vector2<float> drawPos = aCommand.GetData().myPosition;

		aCommand.GetData().myFont->SetColor(aCommand.GetData().myColor.GetHWColor());

		aCommand.GetData().myFont->Render(
			drawPos.x,
			drawPos.y,
			aCommand.GetData().myAlignMode,
			aCommand.GetData().myText.c_str());
	}
}