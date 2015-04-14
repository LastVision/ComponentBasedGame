#include "PhysicsComponent.h"
#include "GameObject.h"

namespace ComponentSystem
{
	PhysicsComponent::PhysicsComponent(GameObject& aOwner, const CU::Vector2<float>& aAcceleration, const CU::Vector2<float>& aTopSpeed, const float aFriction)
		: IComponent(aOwner), myAcceleration(aAcceleration), myTopSpeed(aTopSpeed), myFriction(aFriction)
	{
		myPriority = 20;
		myVelocity = { 0, 0 };
	}


	PhysicsComponent::~PhysicsComponent()
	{
	}

	void PhysicsComponent::Update(const float)
	{
		//Do more physics stuff that applies to the Velocity (Gravity, Friction etc!)

		if (abs(myVelocity.x) >= myTopSpeed.x)
		{
			if (myVelocity.x > 0)
				myVelocity.x = myTopSpeed.x;
			else
				myVelocity.x = -myTopSpeed.x;
		}
		if (abs(myVelocity.y) >= myTopSpeed.y)
		{
			if (myVelocity.y > 0)
				myVelocity.y = myTopSpeed.y;
			else
				myVelocity.y = -myTopSpeed.y;
		}

		myVelocity *= myFriction;


		if (abs(myVelocity.x) < 0.15f)
			myVelocity.x = 0.f;
		if (abs(myVelocity.y) < 0.15f)
			myVelocity.y = 0.f;
	}
}
