#pragma once
#include <hge.h>

#include "InputWrapper.h"
#include "TimerManager.h"

#include "Threading\Syncronizer.h"
#include <thread>
#include "XMLReader.h"


#include "Rendering\Renderer.h"
#include "Rendering\Sprite.h"

#include <DynamicContainer.h>
#include <GameObject.h>
#include <ComponentFactory.h>
#include <GameObjectFactory.h>

#include <ColliderFactory.h>
#include <PhysicsWorld.h>


enum class eTileTypes
{
	BLOCKED = 1,
	ENEMY = 2,
	OPEN = 3,
	PLAYER = 4,
	PUSHABLE = 5
};


class Game
{
public:
	Game();
	~Game();

	void Init(int aScreenWidth, int aScreenHeight);

	void Run();

private:
	void Update();
	void UpdateSubSystems();
	bool myGameIsRunning;
	bool myIsDebuging;

	HGE *myHGEHandle;
	InputWrapper myInputWrapper;
	TimerManager myTimerManager;
	Syncronizer mySyncronizer;
	std::thread *myRenderThread;

	int myScreenHeight;
	int myScreenWidth;

	CS::ComponentFactory myComponentFactory;
	CS::GameObjectFactory myGameObjectFactory;

	CS::GameObject myPlayer;
	CS::GameObject myEnemy;
	CS::GameObject myBlockedTile;
	CS::GameObject myOpenTile;
	CS::GameObject myPushableTile;

	CU::GrowingArray<CS::GameObject*, int> myGameObjects;
	void ConstructTileArray();
	void BuildMapFromXML(const std::string& aMapPath);
	void AddGameObjectSortedForRender(CS::GameObject* aGameObject);
	int myMapWidth;
	int myMapHeight;
	int myTileSize;

	RBS::ColliderFactory myColliderFactory;
	RBS::PhysicsWorld myPhysicsWorld;
};

