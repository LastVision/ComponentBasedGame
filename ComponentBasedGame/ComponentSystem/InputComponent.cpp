#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "DL_Debug.h"
#include "GameObject.h"

namespace ComponentSystem
{
	InputComponent::InputComponent(GameObject& aOwner, InputWrapper* aInput, const char aUpKey, const char aDownKey, const char aLeftKey, const char aRightKey) : IComponent(aOwner),
		myInput(aInput), myUpKey(aUpKey), myDownKey(aDownKey), myLeftKey(aLeftKey), myRightKey(aRightKey)
	{
		myPriority = 10;
	}


	InputComponent::~InputComponent()
	{
	}

	void InputComponent::Update(const float)
	{
		PhysicsComponent* ownerPhysComp = static_cast<PhysicsComponent*>(myOwner->GetComponent(eComponentType::PHYSICS_COMPONENT));
		DL_ASSERT_EX(ownerPhysComp != nullptr, "[InputComponent]: Owner did not have an PhysicsComponent, that does not work!");


		const CU::Vector2<float>& acceleration = ownerPhysComp->GetAcceleration();
		if (myInput->IsKeyDown(myUpKey) == true)
		{
			ownerPhysComp->AddVelocity({ 0.f, -acceleration.y });
		}
		if (myInput->IsKeyDown(myDownKey) == true)
		{
			ownerPhysComp->AddVelocity({ 0.f, acceleration.y });
		}
		if (myInput->IsKeyDown(myLeftKey) == true)
		{
			ownerPhysComp->AddVelocity({ -acceleration.x, 0.f });
		}
		if (myInput->IsKeyDown(myRightKey) == true)
		{
			ownerPhysComp->AddVelocity({ acceleration.x, 0.f });
		}
	}
}
