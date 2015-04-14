#pragma once
#include "IComponent.h"

#include "RigidBody.h"

namespace ComponentSystem
{
	class RigidBodyComponent : public IComponent
	{
	public:
		RigidBodyComponent(GameObject& aOwner, RBS::RigidBody& aRigidBody, bool aStatic, bool aPushable);
		~RigidBodyComponent();

		virtual void Update(const float aDeltaTime);
		virtual inline void UpdatePositions(const CU::Vector2<float>& aNewPosition);

		inline RBS::RigidBody* GetRigidBody();

		virtual inline void SetActiveStatus(const bool aStatus) override;
		inline const bool GetIsStatic() const;
		inline const bool GetIsPushable() const;

	protected:
		RBS::RigidBody* myRigidBody;
		bool myIsStatic;
		bool myIsPushable;
	};

	inline RBS::RigidBody* RigidBodyComponent::GetRigidBody()
	{
		return myRigidBody;
	}

	void RigidBodyComponent::SetActiveStatus(const bool aStatus)
	{
		IComponent::SetActiveStatus(aStatus);
		myRigidBody->SetActiveStatus(aStatus);
	}

	inline const bool RigidBodyComponent::GetIsStatic() const
	{
		return myIsStatic;
	}

	inline const bool RigidBodyComponent::GetIsPushable() const
	{
		return myIsPushable;
	}

	inline void RigidBodyComponent::UpdatePositions(const CU::Vector2<float>& aNewPosition)
	{
		myRigidBody->UpdatePositions(aNewPosition);
	}
}
