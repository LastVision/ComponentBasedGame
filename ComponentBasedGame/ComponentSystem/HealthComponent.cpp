#include "HealthComponent.h"
#include "GameObject.h"

namespace ComponentSystem
{
	HealthComponent::HealthComponent(GameObject& aOwner, const float aMaxHealth, const float aHealthPerSecond, const float aTickPerSecond) : IComponent(aOwner)
	{
		myMaxHealth = aMaxHealth;
		myCurrentHealth = myMaxHealth;
		myCurrentTickTime = 0.f;
		myTimePerTick = 1.f / aTickPerSecond;
		myHealthPerTick = aHealthPerSecond / aTickPerSecond;
		myIsDead = false;
		myPriority = 100;
	}


	HealthComponent::~HealthComponent()
	{
	}

	void HealthComponent::Update(const float aDeltaTime)
	{
		myCurrentTickTime += aDeltaTime;

		if (myCurrentTickTime >= myTimePerTick)
		{
			myCurrentTickTime = 0.f;
			myCurrentHealth += myHealthPerTick;

			if (myCurrentHealth >= myMaxHealth)
			{
				myCurrentHealth = myMaxHealth;

				if (myIsDead == true)
				{
					myIsDead = false;
					myOwner->ActivateGameObject();
				}
			}
		}

		if (myCurrentHealth <= 0.f)
		{
			myCurrentHealth = 0.f;
			myIsDead = true;
			myOwner->DeactivateGameObject();
			myIsActive = true;
		}
	}
};
