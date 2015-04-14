#include "PositionComponent.h"
#include "GameObject.h"
#include "PhysicsComponent.h"

namespace ComponentSystem
{
	PositionComponent::PositionComponent(GameObject& aOwner, const CU::Vector2<float>& aStartPosition) : IComponent(aOwner), myPosition(aStartPosition)
	{
		myPriority = 99;
	}

	PositionComponent::~PositionComponent()
	{
	}

	void PositionComponent::Update(const float aDeltaTime)
	{
		myLastPosition = myPosition;

		PhysicsComponent* ownerPhysComp = static_cast<PhysicsComponent*>(myOwner->GetComponent(eComponentType::PHYSICS_COMPONENT));
		if (ownerPhysComp != nullptr)
		{
			myPosition += ownerPhysComp->GetVelocity() * aDeltaTime;
		}
	}
}
