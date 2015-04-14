#pragma once
#include "IComponent.h"
#include "Vector.h"

namespace ComponentSystem
{
	class PhysicsComponent : public IComponent
	{
	public:
		PhysicsComponent(GameObject& aOwner, const CU::Vector2<float>& aAcceleration, const CU::Vector2<float>& aTopSpeed, const float aFriction);
		~PhysicsComponent();

		void Update(const float aDeltaTime) override;

		inline void SetVelocity(const CU::Vector2<float>& aVelocity);
		inline const CU::Vector2<float>& GetVelocity() const;
		inline void AddVelocity(const CU::Vector2<float>& aAmount);

		inline const CU::Vector2<float>& GetAcceleration() const;
		inline const CU::Vector2<float>& GetTopSpeet() const;
		inline float GetFriction() const;

	private:
		CU::Vector2<float> myVelocity;
		CU::Vector2<float> myAcceleration;
		CU::Vector2<float> myTopSpeed;
		float myFriction;
	};

	inline void PhysicsComponent::SetVelocity(const CU::Vector2<float>& aVelocity)
	{
		myVelocity = aVelocity;
	}

	inline const CU::Vector2<float>& PhysicsComponent::GetVelocity() const
	{
		return myVelocity;
	}

	inline void PhysicsComponent::AddVelocity(const CU::Vector2<float>& aAmount)
	{
		myVelocity += aAmount;
	}

	inline const CU::Vector2<float>& PhysicsComponent::GetAcceleration() const
	{
		return myAcceleration;
	}

	inline const CU::Vector2<float>& PhysicsComponent::GetTopSpeet() const
	{
		return myTopSpeed;
	}

	inline float PhysicsComponent::GetFriction() const
	{
		return myFriction;
	}
}

