#include "ComponentFactory.h"

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
	ComponentFactory::ComponentFactory(InputWrapper& aInput) : myInput(&aInput)
	{
	}


	ComponentFactory::~ComponentFactory()
	{
	}

	void ComponentFactory::CreateInputComponent(GameObject& aOwner, const char aUpKey, const char aDownKey, const char aLeftKey, const char aRightKey)
	{
		aOwner.AddComponent(new InputComponent(aOwner, myInput, myInput->ConvertCharToKey(aUpKey), myInput->ConvertCharToKey(aDownKey), myInput->ConvertCharToKey(aLeftKey), myInput->ConvertCharToKey(aRightKey)), eComponentType::INPUT_COMPONENT);
	}

	void ComponentFactory::CreatePhysicsComponent(GameObject& aOwner, const CU::Vector2<float>& aAcceleration, const CU::Vector2<float>& aTopSpeed, const float aFriction)
	{
		aOwner.AddComponent(new PhysicsComponent(aOwner, aAcceleration, aTopSpeed, aFriction), eComponentType::PHYSICS_COMPONENT);
	}

	void ComponentFactory::CreatePositionComponent(GameObject& aOwner, const CU::Vector2<float>& aStartPosition)
	{
		aOwner.AddComponent(new PositionComponent(aOwner, aStartPosition), eComponentType::POSITION_COMPONENT);
	}

	void ComponentFactory::CreateSpriteComponent(GameObject& aOwner, const std::string& aSpritePath, const int aRenderPriority)
	{
		aOwner.AddComponent(new SpriteComponent(aOwner, aSpritePath, aRenderPriority), eComponentType::SPRITE_COMPONENT);
	}

	void ComponentFactory::CreateRigidBodyComponent(GameObject& aOwner, RBS::RigidBody& aRigidBody, const bool aStatic, const bool aPushable)
	{
		RigidBodyComponent* component = new RigidBodyComponent(aOwner, aRigidBody, aStatic, aPushable);
		aRigidBody.SetOwner(component);
		aOwner.AddComponent(component, eComponentType::RIGID_BODY_COMPONENT);
	}

	void ComponentFactory::CreateEnemyRigidBodyComponent(GameObject& aOwner, RBS::RigidBody& aRigidBody, const bool aStatic, const bool aPushable)
	{
		EnemyRigidBodyComponent* component = new EnemyRigidBodyComponent(aOwner, aRigidBody, aStatic, aPushable);
		aRigidBody.SetOwner(component);
		aOwner.AddComponent(component, eComponentType::ENEMY_RIGID_BODY_COMPONENT);
	}

	void ComponentFactory::CreateEnemyAIComponent(GameObject& aOwner)
	{
		aOwner.AddComponent(new EnemyAIComponent(aOwner), eComponentType::ENEMY_AI_COMPONENT);
	}

	void ComponentFactory::CreateTargetingComponent(GameObject& aOwner, CU::GrowingArray<GameObject*, int>& aTargets, const float aRange, const int aTargetingTags)
	{
		aOwner.AddComponent(new TargetingComponent(aOwner, aTargets, aRange, aTargetingTags), eComponentType::TARGETING_COMPONENT);
	}

	void ComponentFactory::CreateHealthComponent(GameObject& aOwner, const float aMaxHealth, const float aHealthPerSecond, const float aTickPerSecond)
	{
		aOwner.AddComponent(new HealthComponent(aOwner, aMaxHealth, aHealthPerSecond, aTickPerSecond), eComponentType::HEALTH_COMPONENT);
	}
}
