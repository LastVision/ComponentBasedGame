#include "EnemyAIComponent.h"
#include "PhysicsComponent.h"
#include "GameObject.h"

namespace ComponentSystem
{
	EnemyAIComponent::EnemyAIComponent(GameObject& aOwner) : IComponent(aOwner)
	{
		myPriority = 10;
		myDirection = eDirection::NONE;
	}


	EnemyAIComponent::~EnemyAIComponent()
	{
	}

	void EnemyAIComponent::Update(const float)
	{
		PhysicsComponent* ownerPhysComp = static_cast<PhysicsComponent*>(myOwner->GetComponent(eComponentType::PHYSICS_COMPONENT));
		if (ownerPhysComp == nullptr) return;

		CU::Vector2<float> velocity = ownerPhysComp->GetVelocity();

		if (myDirection == eDirection::NONE)
		{
			myDirection = eDirection::RIGHT;
			velocity.x = 200;
			ownerPhysComp->SetVelocity(velocity);
		}
	}

	void EnemyAIComponent::HandleCollision()
	{
		PhysicsComponent* ownerPhysComp = static_cast<PhysicsComponent*>(myOwner->GetComponent(eComponentType::PHYSICS_COMPONENT));
		if (ownerPhysComp == nullptr) return;

		CU::Vector2<float> velocity = ownerPhysComp->GetVelocity();


		//Should get speedvalues from some kind of EnemyController component....

		if (myDirection == eDirection::LEFT)
		{
			velocity.x = 0;
			velocity.y = 200;
			myDirection = eDirection::DOWN;
		}
		else if (myDirection == eDirection::RIGHT)
		{
			velocity.x = 0;
			velocity.y = -200;
			myDirection = eDirection::UP;
		}
		else if (myDirection == eDirection::UP)
		{
			velocity.x = -200;
			velocity.y = 0;
			myDirection = eDirection::LEFT;
		}
		else if (myDirection == eDirection::DOWN)
		{
			velocity.x = 200;
			velocity.y = 0;
			myDirection = eDirection::RIGHT;
		}

		ownerPhysComp->SetVelocity(velocity);
	}
};
