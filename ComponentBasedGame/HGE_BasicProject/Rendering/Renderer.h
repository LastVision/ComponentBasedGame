#pragma once

#include "GrowingArray.h"
#include "RenderCommand.h"
#include <bitset>
#include <atomic>
#include "..\HGE_BasicProject\Threading\Syncronizer.h"
#include "..\..\HGE\include\hgecolor.h"


class HGE;

class Renderer
{
public:
	static void Create(HGE *aHGEHandle, Syncronizer *aSyncronizer);
	static bool Destroy();
	static Renderer* GetInstance();

	void AddRenderCommand(const RenderCommand &aRenderCommand);
	void AddRenderCommandFront(const RenderCommand &aRenderCommand);
	void AddRenderCommandBack(const RenderCommand &aRenderCommand);

	void RenderCircle(const CU::Vector2<float> aCenterPoint, const float aRadius, const int aNumPointsOnCircle, const hgeColor& aColor = hgeColor(1.f, 1.f, 1.f, 1.f));
	void RenderLine(const CU::Vector2<float>& aFirstPoint, const CU::Vector2<float>& aSecondPoint, const hgeColor& aColor = hgeColor(1.f, 1.f, 1.f, 1.f));

	void Render();
	
private:

	struct LineStruct
	{
		CU::Vector2<float> FirstPoint;
		CU::Vector2<float> SecondPoint;
		hgeColor Color;
	};

	Renderer();
	~Renderer();
	static Renderer* ourInstance;
	void Init(HGE *aHGE, Syncronizer *aSyncronizer);
	void SwapBuffers();

	HGE *myHgeHandle;
	Syncronizer *mySyncronizer;

	CU::GrowingArray<CU::GrowingArray<RenderCommand, int>, int> myBuffers;
	CU::GrowingArray<CU::GrowingArray<LineStruct, int>, int> myLineBuffers;
	int myActiveBuffer;

	void FinalRender();
	void RenderWithoutCamera(const RenderCommand& aCommand);
};


