#include <algorithm> //To get acces to std::transform, used to make an string all uppercase

#include "PhysicsWorld.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"
#include "EnemyRigidBodyComponent.h"
#include "EnemyAIComponent.h"
#include "TargetingComponent.h"
#include "HealthComponent.h"

namespace ComponentSystem
{
	GameObjectFactory::GameObjectFactory(RBS::PhysicsWorld& aPhysicsWorld, InputWrapper& aInput, CU::GrowingArray<GameObject*, int> &aGameObjects)
		: myPhysicsWorld(&aPhysicsWorld), myComponentFactory(aInput), myGameObjects(aGameObjects)
	{
	}


	GameObjectFactory::~GameObjectFactory()
	{
	}

	void GameObjectFactory::SetGameObjectTags(const std::string& aTagsFile)
	{
		myXMLReader.OpenDocument(aTagsFile);


		XMLElement tagElem = myXMLReader.FindFirstChild();

		int tag = 1;
		while (tagElem != nullptr)
		{
			std::string collisionName = myXMLReader.GetElementName(tagElem);
			myTags[collisionName] = tag;


			tag += tag;
			tagElem = myXMLReader.FindNextElement(tagElem);
		}

		myXMLReader.CloseDocument();
	}

	GameObject* GameObjectFactory::BuildGameObject(const std::string& aGameObjectPath)
	{
		GameObject* object = new GameObject();

		myXMLReader.OpenDocument(aGameObjectPath);

		XMLElement componentElement = myXMLReader.FindFirstChild();

		while (componentElement != nullptr)
		{
			std::string name = myXMLReader.GetElementName(componentElement);
			std::transform(name.begin(), name.end(), name.begin(), ::toupper);

			if (name == "TAGS")
			{
				BuildTags(object, componentElement);
			}
			else if (name == "SPRITECOMPONENT")
			{
				BuildSpriteComponent(object, componentElement);
			}
			else if (name == "PHYSICSCOMPONENT")
			{
				BuildPhysicsComponent(object, componentElement);
			}
			else if (name == "INPUTCOMPONENT")
			{
				BuildInputComponent(object, componentElement);
			}
			else if (name == "POSITIONCOMPONENT")
			{
				BuildPositionComponent(object, componentElement);
			}
			else if (name == "RIGIDBODYCOMPONENT")
			{
				BuildRigidBodyComponent(object, componentElement);
			}
			else if (name == "ENEMYRIGIDBODYCOMPONENT")
			{
				BuildEnemyRigidBodyComponent(object, componentElement);
			}
			else if (name == "ENEMYAICOMPONENT")
			{
				BuildEnemyAIComponent(object, componentElement);
			}
			else if (name == "TARGETINGCOMPONENT")
			{
				BuildTargetingComponent(object, componentElement);
			}
			else if (name == "HEALTHCOMPONENT")
			{
				BuildHealthComponent(object, componentElement);
			}
			else
			{
				std::transform(name.begin(), name.end(), name.begin(), ::tolower);
				DL_DEBUG("[GameObjectFactory]: Tried to build an unknown component: %s. Check your spelling! (Caps/NonCaps does not matter)", name.c_str());
				DL_ASSERT("[GameObjectFactory]: Treid to build an unkown component.");
			}


			//Get the next component
			componentElement = myXMLReader.FindNextElement(componentElement);
		}

		myXMLReader.CloseDocument();
		return object;
	}

	GameObject* GameObjectFactory::CopyGameObject(const GameObject& aGameObject)
	{
		GameObject* newObject = new GameObject();

		auto it = aGameObject.myComponentsMap.begin();

		while (it != aGameObject.myComponentsMap.end())
		{
			switch (it->first)
			{
			case eComponentType::ENEMY_AI_COMPONENT:
			{
				myComponentFactory.CreateEnemyAIComponent(*newObject);
				break;
			}
			case eComponentType::ENEMY_RIGID_BODY_COMPONENT:
			{
				EnemyRigidBodyComponent* component = static_cast<EnemyRigidBodyComponent*>(it->second);
				myComponentFactory.CreateEnemyRigidBodyComponent(*newObject, *myPhysicsWorld->CopyRigidBody(component->GetRigidBody()), component->GetIsStatic(), component->GetIsPushable());
				break;
			}
			case eComponentType::INPUT_COMPONENT:
			{
				InputComponent* component = static_cast<InputComponent*>(it->second);
				myComponentFactory.CreateInputComponent(*newObject, component->GetUpKey(), component->GetDownKey(), component->GetLeftKey(), component->GetRightKey());
				break;
			}
			case eComponentType::PHYSICS_COMPONENT:
			{
				PhysicsComponent* component = static_cast<PhysicsComponent*>(it->second);
				myComponentFactory.CreatePhysicsComponent(*newObject, component->GetAcceleration(), component->GetTopSpeet(), component->GetFriction());
				break;
			}
			case eComponentType::POSITION_COMPONENT:
			{
				PositionComponent* component = static_cast<PositionComponent*>(it->second);
				myComponentFactory.CreatePositionComponent(*newObject, component->GetPosition());
				break;
			}
			case eComponentType::RIGID_BODY_COMPONENT:
			{
				RigidBodyComponent* component = static_cast<RigidBodyComponent*>(it->second);
				myComponentFactory.CreateRigidBodyComponent(*newObject, *myPhysicsWorld->CopyRigidBody(component->GetRigidBody()), component->GetIsStatic(), component->GetIsPushable());
				break;
			}
			case eComponentType::SPRITE_COMPONENT:
			{
				SpriteComponent* component = static_cast<SpriteComponent*>(it->second);
				myComponentFactory.CreateSpriteComponent(*newObject, component->GetSpritePath(), component->GetRenderPriority());
				break;
			}
			case eComponentType::TARGETING_COMPONENT:
			{
				TargetingComponent* component = static_cast<TargetingComponent*>(it->second);
				myComponentFactory.CreateTargetingComponent(*newObject, myGameObjects, component->GetRange(), component->GetTargetingTags());
				break;
			}
			case eComponentType::HEALTH_COMPONENT:
			{
				HealthComponent* component = static_cast<HealthComponent*>(it->second);
				myComponentFactory.CreateHealthComponent(*newObject, component->GetMaxHealth(), component->GetHealthPerSecond(), component->GetTicksPerSecond());
				break;
			}
			default:
				break;
			}

			it++;
		}

		newObject->myTags = aGameObject.myTags;

		return newObject;
	}


	//***********************
	//  Component Builders
	//***********************
	void GameObjectFactory::BuildTags(GameObject* aObject, XMLElement aTagsElement)
	{
		int tag = 0;

		XMLElement tagElem = myXMLReader.FindFirstChild(aTagsElement);

		while (tagElem != nullptr)
		{
			std::string tagName = myXMLReader.GetElementName(tagElem);
			auto it = myTags.find(tagName);

			if (it != myTags.end())
			{
				tag = tag | it->second;
			}

			tagElem = myXMLReader.FindNextElement(tagElem);
		}

		aObject->SetTags(tag);
	}

	void GameObjectFactory::BuildSpriteComponent(GameObject* aObject, XMLElement aSpriteElement)
	{
		std::string filePath;
		myXMLReader.ForceReadAttribute(myXMLReader.FindFirstChild(aSpriteElement, "Sprite"), "FilePath", filePath);

		XMLElement priorityElement = myXMLReader.FindFirstChild(aSpriteElement, "RenderPriority");
		if (priorityElement != nullptr)
		{
			int prio = 0;
			myXMLReader.ForceReadAttribute(priorityElement, "Value", &prio);

			myComponentFactory.CreateSpriteComponent(*aObject, filePath, prio);
		}
		else
		{
			myComponentFactory.CreateSpriteComponent(*aObject, filePath);
		}

	}

	void GameObjectFactory::BuildPhysicsComponent(GameObject* aObject, XMLElement aPhysicsElement)
	{
		CU::Vector2<float> acceleration(0.5, 0.5f);
		CU::Vector2<float> topSpeed(200.f, 200.f);
		float friction = 0.95f;

		XMLElement accelerationElement = myXMLReader.FindFirstChild(aPhysicsElement, "Acceleration");
		if (accelerationElement != nullptr)
		{
			myXMLReader.ForceReadAttribute(accelerationElement, "X", &acceleration.x);
			myXMLReader.ForceReadAttribute(accelerationElement, "Y", &acceleration.y);
		}

		XMLElement maxSpeedElement = myXMLReader.FindFirstChild(aPhysicsElement, "MaxSpeed");
		if (maxSpeedElement != nullptr)
		{
			myXMLReader.ForceReadAttribute(maxSpeedElement, "X", &topSpeed.x);
			myXMLReader.ForceReadAttribute(maxSpeedElement, "Y", &topSpeed.y);
		}

		XMLElement frictionElement = myXMLReader.FindFirstChild(aPhysicsElement, "Friction");
		if (frictionElement != nullptr)
		{
			myXMLReader.ForceReadAttribute(frictionElement, "Value", &friction);
		}

		myComponentFactory.CreatePhysicsComponent(*aObject, acceleration, topSpeed, friction);
	}

	void GameObjectFactory::BuildInputComponent(GameObject* aObject, XMLElement aInputElement)
	{
		char upKey, downKey, leftKey, rightKey;

		myXMLReader.ForceReadAttribute(myXMLReader.FindFirstChild(aInputElement, "UpKey"), "Key", &upKey);
		myXMLReader.ForceReadAttribute(myXMLReader.FindFirstChild(aInputElement, "DownKey"), "Key", &downKey);
		myXMLReader.ForceReadAttribute(myXMLReader.FindFirstChild(aInputElement, "LeftKey"), "Key", &leftKey);
		myXMLReader.ForceReadAttribute(myXMLReader.FindFirstChild(aInputElement, "RightKey"), "Key", &rightKey);

		myComponentFactory.CreateInputComponent(*aObject, int(upKey), int(downKey), int(leftKey), int(rightKey));
	}

	void GameObjectFactory::BuildPositionComponent(GameObject* aObject, XMLElement aPositionElement)
	{
		CU::Vector2<float> startPosition;
		myXMLReader.ReadAttribute(myXMLReader.FindFirstChild(aPositionElement, "StartPosition"), "X", &startPosition.x);
		myXMLReader.ReadAttribute(myXMLReader.FindFirstChild(aPositionElement, "StartPosition"), "Y", &startPosition.y);

		myComponentFactory.CreatePositionComponent(*aObject, startPosition);
	}

	void GameObjectFactory::BuildRigidBodyComponent(GameObject* aObject, XMLElement aRigidBodyElement)
	{
		int collisionGroup = 0;
		int targetCollisionGroup = 0;
		std::string groupName;


		collisionGroup = aObject->GetTags();


		//Read the CollisionGroup(s) that the RigidBody will collide with
		XMLElement targetCollisionGroupElem = myXMLReader.FindFirstChild(aRigidBodyElement, "TargetCollisionGroup");
		while (targetCollisionGroupElem != nullptr)
		{

			myXMLReader.ForceReadAttribute(targetCollisionGroupElem, "ID", groupName);
			targetCollisionGroup = targetCollisionGroup | myPhysicsWorld->GetCollisionGroupValue(groupName);

			targetCollisionGroupElem = myXMLReader.FindNextElement(targetCollisionGroupElem, "TargetCollisionGroup");
		}

		//Create the RigidBody
		RBS::RigidBody* rigidBody = myPhysicsWorld->CreateRigidBody(collisionGroup, targetCollisionGroup);

		//Read all RectangleCollider(s)
		XMLElement rectangleCollider = myXMLReader.FindFirstChild(aRigidBodyElement, "RectangleCollider");
		while (rectangleCollider != nullptr)
		{
			myPhysicsWorld->BuildRectangleCollider(rigidBody, rectangleCollider);

			rectangleCollider = myXMLReader.FindNextElement(rectangleCollider, "RectangleCollider");
		}

		//Read all CircleCollider(s)
		XMLElement circleCollider = myXMLReader.FindFirstChild(aRigidBodyElement, "CircleCollider");
		while (circleCollider != nullptr)
		{
			myPhysicsWorld->BuildCircleCollider(rigidBody, circleCollider);

			circleCollider = myXMLReader.FindNextElement(circleCollider, "CircleCollider");
		}

		bool isStatic = false;
		XMLElement staticElement = myXMLReader.FindFirstChild(aRigidBodyElement, "Static");
		myXMLReader.ReadAttribute(staticElement, "Value", &isStatic);

		bool isPushable = false;
		XMLElement pushableElement = myXMLReader.FindFirstChild(aRigidBodyElement, "IsPushable");
		if (pushableElement != nullptr)
		{
			myXMLReader.ForceReadAttribute(pushableElement, "Value", &isPushable);
		}

		myComponentFactory.CreateRigidBodyComponent(*aObject, *rigidBody, isStatic, isPushable);
	}

	void GameObjectFactory::BuildEnemyRigidBodyComponent(GameObject* aObject, XMLElement aEnemyRigidBodyElement)
	{
		int collisionGroup = 0;
		int targetCollisionGroup = 0;
		std::string groupName;


		collisionGroup = aObject->GetTags();


		//Read the CollisionGroup(s) that the RigidBody will collide with
		XMLElement targetCollisionGroupElem = myXMLReader.FindFirstChild(aEnemyRigidBodyElement, "TargetCollisionGroup");
		while (targetCollisionGroupElem != nullptr)
		{

			myXMLReader.ForceReadAttribute(targetCollisionGroupElem, "ID", groupName);
			targetCollisionGroup = targetCollisionGroup | myPhysicsWorld->GetCollisionGroupValue(groupName);

			targetCollisionGroupElem = myXMLReader.FindNextElement(targetCollisionGroupElem, "TargetCollisionGroup");
		}

		//Create the RigidBody
		RBS::RigidBody* rigidBody = myPhysicsWorld->CreateRigidBody(collisionGroup, targetCollisionGroup);

		//Read all RectangleCollider(s)
		XMLElement rectangleCollider = myXMLReader.FindFirstChild(aEnemyRigidBodyElement, "RectangleCollider");
		while (rectangleCollider != nullptr)
		{
			myPhysicsWorld->BuildRectangleCollider(rigidBody, rectangleCollider);

			rectangleCollider = myXMLReader.FindNextElement(rectangleCollider, "RectangleCollider");
		}

		//Read all CircleCollider(s)
		XMLElement circleCollider = myXMLReader.FindFirstChild(aEnemyRigidBodyElement, "CircleCollider");
		while (circleCollider != nullptr)
		{
			myPhysicsWorld->BuildCircleCollider(rigidBody, circleCollider);

			circleCollider = myXMLReader.FindNextElement(circleCollider, "CircleCollider");
		}

		bool isStatic = false;
		XMLElement staticElement = myXMLReader.FindFirstChild(aEnemyRigidBodyElement, "Static");
		myXMLReader.ReadAttribute(staticElement, "Value", &isStatic);

		bool isPushable = false;
		XMLElement pushableElement = myXMLReader.FindFirstChild(aEnemyRigidBodyElement, "IsPushable");
		if (pushableElement != nullptr)
		{
			myXMLReader.ForceReadAttribute(pushableElement, "Value", &isPushable);
		}

		myComponentFactory.CreateEnemyRigidBodyComponent(*aObject, *rigidBody, isStatic, isPushable);
	}

	void GameObjectFactory::BuildEnemyAIComponent(GameObject* aObject, XMLElement)
	{
		myComponentFactory.CreateEnemyAIComponent(*aObject);
	}

	void GameObjectFactory::BuildTargetingComponent(GameObject* aObject, XMLElement aTargetingElement)
	{
		float range = 0.f;
		int targetingTags = 0;

		XMLElement rangeElem = myXMLReader.ForceFindFirstChild(aTargetingElement, "Range");
		myXMLReader.ForceReadAttribute(rangeElem, "Value", &range);

		XMLElement targetElem = myXMLReader.ForceFindFirstChild(aTargetingElement, "Target");
		while (targetElem != nullptr)
		{
			std::string targetName;
			myXMLReader.ForceReadAttribute(targetElem, "Tag", targetName);
			auto it = myTags.find(targetName);

			if (it != myTags.end())
			{
				targetingTags = targetingTags | it->second;
			}

			targetElem = myXMLReader.FindNextElement(targetElem, "Target");
		}

		myComponentFactory.CreateTargetingComponent(*aObject, myGameObjects, range, targetingTags);
	}

	void GameObjectFactory::BuildHealthComponent(GameObject* aObject, XMLElement aHealthElement)
	{
		float maxHealth = 100.f;
		float healthPerSecond = 100.f;
		float ticksPerSecond = 2.f;

		XMLElement maxHealthElement = myXMLReader.FindFirstChild(aHealthElement, "MaxHealth");
		myXMLReader.ReadAttribute(maxHealthElement, "Value", &maxHealth);

		XMLElement healthRegElement = myXMLReader.FindFirstChild(aHealthElement, "HealthRegeneration");
		if (healthRegElement != nullptr)
		{
			XMLElement healthPerSecondElement = myXMLReader.FindFirstChild(healthRegElement, "HealthPerSecond");
			myXMLReader.ReadAttribute(healthPerSecondElement, "Value", &healthPerSecond);

			XMLElement ticksPerSecondElement = myXMLReader.FindFirstChild(healthRegElement, "TicksPerSecond");
			myXMLReader.ReadAttribute(ticksPerSecondElement, "Value", &ticksPerSecond);
		}

		myComponentFactory.CreateHealthComponent(*aObject, maxHealth, healthPerSecond, ticksPerSecond);
	}
};