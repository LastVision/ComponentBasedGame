#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "HealthComponent.h"

namespace ComponentSystem
{
	RigidBodyComponent::RigidBodyComponent(GameObject& aOwner, RBS::RigidBody& aRigidBody, bool aStatic, bool aPushable)
		: IComponent(aOwner), myRigidBody(&aRigidBody), myIsStatic(aStatic), myIsPushable(aPushable)
	{
		myPriority = 80;
	}

	RigidBodyComponent::~RigidBodyComponent()
	{
	}

	void RigidBodyComponent::Update(const float aDelta)
	{
		if (myIsStatic == true) return;

		PositionComponent* ownerPositionComp = static_cast<PositionComponent*>(myOwner->GetComponent(eComponentType::POSITION_COMPONENT));
		DL_ASSERT_EX(ownerPositionComp != nullptr, "[RigidBodyComponent]: Owner did not have an Position_Component, the GameObject must have an position to be able to use a RigidBody!");

		//Save our original position so that we know where to return to if we cant move in either x or y axis
		CU::Vector2<float> originalPos = ownerPositionComp->GetPosition();


		//If we have an velocity we want to check x and y seperately
		PhysicsComponent* ownerPhysics = static_cast<PhysicsComponent*>(myOwner->GetComponent(eComponentType::PHYSICS_COMPONENT));
		if (ownerPhysics != nullptr)
		{
			CU::Vector2<float> velocity = ownerPhysics->GetVelocity();
			CU::Vector2<float> xAxisCheckPosition(originalPos.x + (velocity.x * aDelta), originalPos.y);
			CU::Vector2<float> yAxisCheckPosition(originalPos.x, originalPos.y + (velocity.y * aDelta));

			myRigidBody->UpdatePositions(xAxisCheckPosition);
			RBS::RigidBody* otherRigidBody = myRigidBody->CheckCollisionVSWorld();

			//We found a collision in the x axis
			if (otherRigidBody != nullptr)
			{
				if (otherRigidBody->GetOwner()->GetIsPushable() == true)
				{
					PhysicsComponent* otherPhysic = static_cast<PhysicsComponent*>(otherRigidBody->GetOwner()->myOwner->GetComponent(eComponentType::PHYSICS_COMPONENT));
					DL_ASSERT_EX(otherPhysic != nullptr, "[RigidBodyComponent]: Found a Pushable RigidBodyComponent without a PhysicsComponent, that wont work!");
					otherPhysic->AddVelocity({ velocity.x, 0.f });
				}

				velocity.x = 0.f;
			}
			else
			{
				originalPos.x = xAxisCheckPosition.x;
			}


			myRigidBody->UpdatePositions(yAxisCheckPosition);
			otherRigidBody = myRigidBody->CheckCollisionVSWorld();

			//We found a collision in the y axis
			if (otherRigidBody != nullptr)
			{
				if (otherRigidBody->GetOwner()->GetIsPushable() == true)
				{
					PhysicsComponent* otherPhysic = static_cast<PhysicsComponent*>(otherRigidBody->GetOwner()->myOwner->GetComponent(eComponentType::PHYSICS_COMPONENT));
					DL_ASSERT_EX(otherPhysic != nullptr, "[RigidBodyComponent]: Found a Pushable RigidBodyComponent without a PhysicsComponent, that wont work!");
					otherPhysic->AddVelocity({ 0.f, velocity.y });
				}

				velocity.y = 0.f;
			}
			else
			{
				originalPos.y = yAxisCheckPosition.y;
			}

			ownerPhysics->SetVelocity(velocity);	
			
		}


		myRigidBody->UpdatePositions(originalPos);
		
	}
};
