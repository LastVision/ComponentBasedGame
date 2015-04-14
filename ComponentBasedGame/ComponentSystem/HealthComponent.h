#pragma once
#include "IComponent.h"
#include "DL_Debug.h"
#include "SpriteComponent.h"
#include "GameObject.h"

namespace ComponentSystem
{
	class HealthComponent : public IComponent
	{
	public:
		HealthComponent(GameObject& aOwner, const float aMaxHealth, const float aHealthPerSecond, const float aTickPerSecond);
		~HealthComponent();

		virtual void Update(const float aDeltaTime) override;

		inline void TakeDamage(const float aAmount);
		inline void HealDamage(const float aAmount);



		inline float GetMaxHealth() const;
		inline float GetHealthPerSecond() const;
		inline float GetTicksPerSecond() const;

	private:
		float myMaxHealth;
		float myCurrentHealth;
		float myHealthPerTick;
		float myTimePerTick;
		float myCurrentTickTime;
		bool myIsDead;
	};

	inline void HealthComponent::TakeDamage(const float aAmount)
	{
		DL_ASSERT_EX(aAmount > 0.f, "[HealthComponent]: Tried to use TakeDamage() with an negative input. Use HealDamage() to restore health instead.");

		if (myIsDead == true) return;

		myCurrentHealth -= aAmount;
		if (myCurrentHealth <= 0.f)
		{
			myCurrentHealth = 0.f;
			myIsDead = true;
		}

		SpriteComponent* ownerSprite = static_cast<SpriteComponent*>(myOwner->GetComponent(eComponentType::SPRITE_COMPONENT));
		if (ownerSprite != nullptr)
		{
			ownerSprite->StartColorBlinking(hgeColor(1.f, 0.f, 0.f, 1.f), 0.5f, 0.5f / 4.f);
		}
	}

	inline void HealthComponent::HealDamage(const float aAmount)
	{
		DL_ASSERT_EX(aAmount > 0.f, "[HealthComponent]: Tried to use HealDamage() with an negative input. Use TakeDamage() to apply damage instead.");

		if (myIsDead == true) return;

		myCurrentHealth += aAmount;
		if (myCurrentHealth >= myMaxHealth)
		{
			myCurrentHealth = myMaxHealth;
		}
	}


	inline float HealthComponent::GetMaxHealth() const
	{
		return myMaxHealth;
	}

	inline float HealthComponent::GetHealthPerSecond() const
	{
		return GetTicksPerSecond() * myHealthPerTick;
	}

	inline float HealthComponent::GetTicksPerSecond() const
	{
		return 1.f / myTimePerTick;
	}
};
