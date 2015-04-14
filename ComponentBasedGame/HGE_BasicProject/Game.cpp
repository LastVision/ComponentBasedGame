#include "Game.h"
#include "DL_Debug.h"
#include "Rendering\ResourceManager.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "PositionComponent.h"

#define GRID_SIZE 8
#define TILE_SIZE 32

Game::Game() : myComponentFactory(myInputWrapper), myGameObjectFactory(myPhysicsWorld, myInputWrapper, myGameObjects)
{
	myGameIsRunning = true;
	myIsDebuging = false;
}


Game::~Game()
{
}

void Game::Init(int aScreenWidth, int aScreenHeight)
{
	myScreenWidth = aScreenWidth;
	myScreenHeight = aScreenHeight;

	myHGEHandle = hgeCreate(HGE_VERSION);

	myHGEHandle->System_SetState(HGE_WINDOWED, true);
	myHGEHandle->System_SetState(HGE_USESOUND, false);
	myHGEHandle->System_SetState(HGE_TITLE, "HGE_BasicProject");
	myHGEHandle->System_SetState(HGE_SCREENWIDTH, myScreenWidth);
	myHGEHandle->System_SetState(HGE_SCREENHEIGHT, myScreenHeight);
	myHGEHandle->System_SetState(HGE_SHOWSPLASH, false);

	if (myHGEHandle->System_Initiate())
	{
		myInputWrapper.Init(GetActiveWindow());
		DL_Debug::Debug::Create();
		CU::ResourceManager::Create(myHGEHandle);
		Renderer::Create(myHGEHandle, &mySyncronizer);

		myPhysicsWorld.SetCollisionTags("../Data/Settings/Tags.xml");
		myGameObjectFactory.SetGameObjectTags("../Data/Settings/Tags.xml");
		

		myPlayer = *myGameObjectFactory.BuildGameObject("../Data/GameObjects/Player.xml");	
		myEnemy = *myGameObjectFactory.BuildGameObject("../Data/GameObjects/Enemy.xml");
		myBlockedTile = *myGameObjectFactory.BuildGameObject("../Data/GameObjects/BlockedTile.xml");
		myOpenTile = *myGameObjectFactory.BuildGameObject("../Data/GameObjects/OpenTile.xml");
		myPushableTile = *myGameObjectFactory.BuildGameObject("../Data/GameObjects/PushableTile.xml");


		myMapHeight = 0;
		myMapWidth = 0;
		myTileSize = 0;
		//BuildMapFromXML("../Data/Maps/TestMap.tmx");
		BuildMapFromXML("../Data/Maps/PuzzelMap.tmx");


		

		//myGameObjects.Init(64);
		//ConstructTileArray();	
		//myGameObjects.Add(&myPlayer);
		//myGameObjects.Add(&myEnemy);


		//myPlayer.DeactivateGameObject();
		//myEnemy.DeactivateGameObject();
		myBlockedTile.DeactivateGameObject();
		myOpenTile.DeactivateGameObject();
		myPushableTile.DeactivateGameObject();

		myRenderThread = new std::thread([&]{Renderer::GetInstance()->Render(); });
		myHGEHandle->System_Start();
	}
}

void Game::Run()
{
	while (mySyncronizer.GetShutDownStatus() == false)
	{
		MSG myMSG;
		if (PeekMessage(&myMSG, NULL, 0, 0, PM_REMOVE))
		{
			if (myMSG.message == WM_QUIT)
			{
				myGameIsRunning = false;
				return;
			}
			DispatchMessage(&myMSG);
		}

		Update();

		mySyncronizer.SetUpdateReady();

		if (myInputWrapper.IsKeyClicked(DIK_ESCAPE))
		{
			mySyncronizer.ShutDownThreads();
		}

		mySyncronizer.WaitForRender();
	}
}

void Game::Update()
{
	UpdateSubSystems();

	float deltaTime = myTimerManager.MasterFrameTime().GetSeconds();


	if (myInputWrapper.IsKeyClicked(DIK_1))
	{
		myEnemy.ActivateGameObject();
	}
	else if (myInputWrapper.IsKeyClicked(DIK_2))
	{
		myEnemy.DeactivateGameObject();
	}


	for (int i = 0; i < myGameObjects.Size(); ++i)
	{
		myGameObjects[i]->Update(deltaTime);
	}
	//myPhysicsWorld.DoCollisionChecks();
	

	if (myIsDebuging == true)
	{
		myPhysicsWorld.RenderColliders();
	}
}

void Game::UpdateSubSystems()
{
	myInputWrapper.Update();
	myTimerManager.Update();

	if (myInputWrapper.IsKeyClicked(DIK_F12))
		myIsDebuging = !myIsDebuging;
}

void Game::ConstructTileArray()
{
	for (int i = 0; i < GRID_SIZE * GRID_SIZE; ++i)
	{
		int x = (i % GRID_SIZE);
		int y = (i / GRID_SIZE);

		if (x == 0 || y == 0 || x == GRID_SIZE - 1 || y == GRID_SIZE - 1 )
		{
			CS::GameObject* tile = myGameObjectFactory.CopyGameObject(myBlockedTile);
			
			CS::PositionComponent* tilePos = static_cast<CS::PositionComponent*>(tile->GetComponent(eComponentType::POSITION_COMPONENT));
			tilePos->SetPosition({ float(x) * TILE_SIZE, float(y) * TILE_SIZE });
			myGameObjects.Add(tile);
		}
		else
		{
			CS::GameObject* tile = myGameObjectFactory.CopyGameObject(myOpenTile);

			CS::PositionComponent* tilePos = static_cast<CS::PositionComponent*>(tile->GetComponent(eComponentType::POSITION_COMPONENT));
			tilePos->SetPosition({ float(x) * TILE_SIZE, float(y) * TILE_SIZE });
			myGameObjects.Add(tile);
		}
	}


	CS::GameObject* tile = myGameObjectFactory.CopyGameObject(myPushableTile);

CS::PositionComponent* tilePos = static_cast<CS::PositionComponent*>(tile->GetComponent(eComponentType::POSITION_COMPONENT));
tilePos->SetPosition({ 468, 500.f });
myGameObjects.Add(tile);

CS::GameObject* tile2 = myGameObjectFactory.CopyGameObject(myPushableTile);

tilePos = static_cast<CS::PositionComponent*>(tile2->GetComponent(eComponentType::POSITION_COMPONENT));
tilePos->SetPosition({ 500.f, 500.f });
myGameObjects.Add(tile2);

CS::GameObject* tile3 = myGameObjectFactory.CopyGameObject(myPushableTile);

tilePos = static_cast<CS::PositionComponent*>(tile3->GetComponent(eComponentType::POSITION_COMPONENT));
tilePos->SetPosition({ 532, 500.f });
myGameObjects.Add(tile3);


CS::GameObject* tile4 = myGameObjectFactory.CopyGameObject(myBlockedTile);

tilePos = static_cast<CS::PositionComponent*>(tile4->GetComponent(eComponentType::POSITION_COMPONENT));
tilePos->SetPosition({ 564, 500.f });
myGameObjects.Add(tile4);

CS::GameObject* tile5 = myGameObjectFactory.CopyGameObject(myBlockedTile);

tilePos = static_cast<CS::PositionComponent*>(tile5->GetComponent(eComponentType::POSITION_COMPONENT));
tilePos->SetPosition({ 436, 500.f });
myGameObjects.Add(tile5);
}

void Game::BuildMapFromXML(const std::string& aMapPath)
{
	XMLReader mapReader;
	mapReader.OpenDocument(aMapPath);

	XMLElement mapElement = mapReader.FindFirstChild("map");
	mapReader.ForceReadAttribute(mapElement, "width", &myMapWidth);
	mapReader.ForceReadAttribute(mapElement, "height", &myMapHeight);
	mapReader.ForceReadAttribute(mapElement, "tilewidth", &myTileSize);

	myGameObjects.Init(myMapHeight * myMapWidth * 3);

	XMLElement layerElement = mapReader.FindFirstChild(mapElement, "layer");
	while (layerElement != nullptr)
	{
		int indexCounter = 0;
		XMLElement dataElement = mapReader.FindFirstChild(layerElement, "data");
		XMLElement tileElement = mapReader.FindFirstChild(dataElement, "tile");
		while (tileElement != nullptr)
		{
			//Get the TileID from Tiled
			int tileGID = -1;
			mapReader.ForceReadAttribute(tileElement, "gid", &tileGID);

			if (tileGID == static_cast<int>(eTileTypes::ENEMY))
			{
				tileElement = mapReader.FindNextElement(tileElement, "tile");
				++indexCounter;
				continue;
			}

			//Calculate the Position based on which index currently are reading
			CU::Vector2<float> position;
			position.x = (indexCounter % myMapWidth) * myTileSize * 1.f;
			position.y = (indexCounter / myMapWidth) * myTileSize * 1.f;


			CS::GameObject* tile = nullptr;
			eTileTypes tileToCreate = static_cast<eTileTypes>(tileGID);
			switch (tileToCreate)
			{
			case eTileTypes::BLOCKED:
				tile = myGameObjectFactory.CopyGameObject(myBlockedTile);
				break;
			case eTileTypes::ENEMY:
				tile = myGameObjectFactory.CopyGameObject(myEnemy);
				break;
			case eTileTypes::PLAYER:
				tile = myGameObjectFactory.CopyGameObject(myPlayer);
				myPlayer = *tile;
				break;
			case eTileTypes::PUSHABLE:
				tile = myGameObjectFactory.CopyGameObject(myPushableTile);
				break;
			}

			if (tile != nullptr)
			{
				CS::PositionComponent* tilePos = static_cast<CS::PositionComponent*>(tile->GetComponent(eComponentType::POSITION_COMPONENT));
				tilePos->SetPosition(position);
				AddGameObjectSortedForRender(tile);
			}

			if (tileGID != static_cast<int>(eTileTypes::BLOCKED))
			{
				CS::GameObject* openTile = myGameObjectFactory.CopyGameObject(myOpenTile);
				CS::PositionComponent* openTilePos = static_cast<CS::PositionComponent*>(openTile->GetComponent(eComponentType::POSITION_COMPONENT));
				openTilePos->SetPosition(position);
				AddGameObjectSortedForRender(openTile);
			}
			

			tileElement = mapReader.FindNextElement(tileElement, "tile");
			++indexCounter;
		}


		layerElement = mapReader.FindNextElement(layerElement, "layer");
	}
}

void Game::AddGameObjectSortedForRender(CS::GameObject* aGameObject)
{
	CS::SpriteComponent* newSprite = static_cast<CS::SpriteComponent*>(aGameObject->GetComponent(eComponentType::SPRITE_COMPONENT));
	if (newSprite == nullptr)
	{
		myGameObjects.Add(aGameObject);
		return;
	}


	for (int i = 0; i < myGameObjects.Size(); ++i)
	{
		CS::SpriteComponent* sprite = static_cast<CS::SpriteComponent*>(myGameObjects[i]->GetComponent(eComponentType::SPRITE_COMPONENT));
		
		if (sprite != nullptr && newSprite->GetRenderPriority() > sprite->GetRenderPriority())
		{
			myGameObjects.Insert(i, aGameObject);
			return;
		}
	}

	myGameObjects.Add(aGameObject);
}