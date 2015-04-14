#pragma once

#include "..\HGE_BasicProject\XMLReader.h"
#include "ComponentFactory.h"

namespace RigidBodySystem
{
	class PhysicsWorld;
}
namespace RBS = RigidBodySystem;

namespace ComponentSystem
{
	class GameObject;
	class IComponent;

	class GameObjectFactory
	{
	public:
		
		GameObjectFactory(RBS::PhysicsWorld& aPhysicsWorld, InputWrapper& aInput, CU::GrowingArray<GameObject*, int> &aGameObjects);
		~GameObjectFactory();

		void SetGameObjectTags(const std::string& aTagsFile);

		GameObject* BuildGameObject(const std::string& aGameObjectPath);
		GameObject* CopyGameObject(const GameObject& aGameObject);

	private:
		void operator=(const GameObjectFactory& aFactory);

		XMLReader myXMLReader;
		RBS::PhysicsWorld* myPhysicsWorld;
		ComponentFactory myComponentFactory;
		std::unordered_map<std::string, int> myTags;
		CU::GrowingArray<GameObject*, int>& myGameObjects;

		void BuildTags(GameObject* aObject, XMLElement aTagsElement);
		void BuildSpriteComponent(GameObject* aObject, XMLElement aSpriteElement);
		void BuildPhysicsComponent(GameObject* aObject, XMLElement aPhysicsElement);
		void BuildInputComponent(GameObject* aObject, XMLElement aInputElement);
		void BuildPositionComponent(GameObject* aObject, XMLElement aPositionElement);
		void BuildRigidBodyComponent(GameObject* aObject, XMLElement aRigidBodyElement);
		void BuildEnemyRigidBodyComponent(GameObject* aObject, XMLElement aEnemyRigidBodyElement);
		void BuildEnemyAIComponent(GameObject* aObject, XMLElement aEnemyAIElement);
		void BuildTargetingComponent(GameObject* aObject, XMLElement aTargetingElement);
		void BuildHealthComponent(GameObject* aObject, XMLElement aHealthElement);

	};
};
