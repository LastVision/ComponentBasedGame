#pragma once

#include "Vector.h"
#include <string>
#include "GrowingArray.h"

class InputWrapper;

namespace RigidBodySystem
{
	class RigidBody;
};
namespace RBS = RigidBodySystem;

namespace ComponentSystem
{
	class GameObject;

	class ComponentFactory
	{
	public:
		ComponentFactory(InputWrapper& aInput);
		~ComponentFactory();

		void CreateInputComponent(GameObject& aOwner, const char aUpKey, const char aDownKey, const char aLeftKey, const char aRightKey);
		void CreatePhysicsComponent(GameObject& aOwner, const CU::Vector2<float>& aAcceleration, const CU::Vector2<float>& aTopSpeed, const float aFriction);
		void CreatePositionComponent(GameObject& aOwner, const CU::Vector2<float>& aStartPosition);
		void CreateSpriteComponent(GameObject& aOwner, const std::string& aSpritePath, const int aRenderPriority = 100);
		void CreateRigidBodyComponent(GameObject& aOwner, RBS::RigidBody& aRigidBody, const bool aStatic, const bool aPushable);
		void CreateEnemyRigidBodyComponent(GameObject& aOwner, RBS::RigidBody& aRigidBody, const bool aStatic, const bool aPushable);
		void CreateEnemyAIComponent(GameObject& aOwner);
		void CreateTargetingComponent(GameObject& aOwner, CU::GrowingArray<GameObject*, int> &aTargets, const float aRange, const int aTargetingTags);
		void CreateHealthComponent(GameObject& aOwner, const float aMaxHealth, const float aHealthPerSecond, const float aTickPerSecond);

	private:
		InputWrapper* myInput;
	};
}
