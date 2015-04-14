#include "EnemyRigidBodyComponent.h"
#include "EnemyAIComponent.h"
#include "GameObject.h"

namespace ComponentSystem
{
	EnemyRigidBodyComponent::EnemyRigidBodyComponent(GameObject& aOwner, RBS::RigidBody& aRigidBody, bool aStatic, bool aPushable)
		: RigidBodyComponent(aOwner, aRigidBody, aStatic, aPushable)
	{
	}


	EnemyRigidBodyComponent::~EnemyRigidBodyComponent()
	{
	}

	void EnemyRigidBodyComponent::Update(const float aDeltaTime)
	{
		RigidBodyComponent::Update(aDeltaTime);


		if (myIsStatic == true) return;

		EnemyAIComponent* ownerAI = static_cast<EnemyAIComponent*>(myOwner->GetComponent(eComponentType::ENEMY_AI_COMPONENT));

		if (ownerAI != nullptr)
		{
			ownerAI->HandleCollision();
		}
	}
};
