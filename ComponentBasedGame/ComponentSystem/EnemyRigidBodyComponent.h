#pragma once
#include "RigidBodyComponent.h"

namespace ComponentSystem
{
	class EnemyRigidBodyComponent :
		public RigidBodyComponent
	{
	public:
		EnemyRigidBodyComponent(GameObject& aOwner, RBS::RigidBody& aRigidBody, bool aStatic, bool aPushable);
		~EnemyRigidBodyComponent();

		virtual void Update(const float aDeltaTime) override;
	};
};

