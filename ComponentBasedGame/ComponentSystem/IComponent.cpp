#include "IComponent.h"

namespace ComponentSystem
{
	IComponent::IComponent(GameObject& aOwner) : myOwner(&aOwner)
	{
		myIsActive = true;
	}


	IComponent::~IComponent()
	{
	}
}
