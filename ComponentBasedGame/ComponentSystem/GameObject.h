#pragma once

#include <DynamicContainer.h>
#include <OpaqueDictionary.h>
#include <unordered_map>

#include "IComponent.h"

class IComponent;

enum class eComponentType
{
	INPUT_COMPONENT,
	PHYSICS_COMPONENT,
	POSITION_COMPONENT,
	RIGID_BODY_COMPONENT,
	ENEMY_RIGID_BODY_COMPONENT,
	SPRITE_COMPONENT,
	ENEMY_AI_COMPONENT,
	TARGETING_COMPONENT,
	HEALTH_COMPONENT
};

namespace ComponentSystem
{
	class GameObject
	{
	public:
		friend class GameObjectFactory;

		GameObject();
		~GameObject();

		void AddComponent(IComponent* aComponent, eComponentType aComponentType);

		virtual void Update(const float aDeltaTime);

		inline IComponent* GetComponent(const eComponentType aComponentType) const;
		inline void ActivateComponent(const eComponentType aComponentType);
		inline void DeactivateComponent(const eComponentType aComponentType);
		inline void ActivateGameObject();
		inline void DeactivateGameObject();
		inline void SetTags(const int aTags);
		inline int GetTags() const;

	protected:
		CU::DynamicContainer<IComponent*> myComponents;
		std::unordered_map<eComponentType, IComponent*> myComponentsMap;
		int myTags;

	};

	inline IComponent* GameObject::GetComponent(const eComponentType aComponentType) const
	{
		auto it = myComponentsMap.find(aComponentType);

		if (it != myComponentsMap.end() && it->second->GetIsActive() == true)
		{
			return it->second;
		}

		return nullptr;
	}

	inline void GameObject::ActivateComponent(const eComponentType aComponentType)
	{
		auto it = myComponentsMap.find(aComponentType);

		if (it != myComponentsMap.end())
		{
			it->second->SetActiveStatus(true);
			return;
		}

		DL_DEBUG("[GameObject]: Tried to ActivateComponent ID: %i, but that Component was not found on the GameObject.", static_cast<int>(aComponentType));
		DL_ASSERT("[GameObject]: Tried to ActivateComponent a Component that wasnt found in the GameObject.");
	}

	inline void GameObject::DeactivateComponent(const eComponentType aComponentType)
	{
		auto it = myComponentsMap.find(aComponentType);

		if (it != myComponentsMap.end())
		{
			it->second->SetActiveStatus(false);
			return;
		}

		DL_DEBUG("[GameObject]: Tried to DeactivateComponent ID: %i, but that Component was not found on the GameObject.", static_cast<int>(aComponentType));
		DL_ASSERT("[GameObject]: Tried to DeactivateComponent a Component that wasnt found in the GameObject.");
	}

	inline void GameObject::ActivateGameObject()
	{
		for (int i = 0; i < myComponents.Size(); ++i)
			myComponents[i]->SetActiveStatus(true);
	}

	inline void GameObject::DeactivateGameObject()
	{
		for (int i = 0; i < myComponents.Size(); ++i)
			myComponents[i]->SetActiveStatus(false);
	}

	inline void GameObject::SetTags(const int aTags)
	{
		myTags = aTags;
	}

	inline int GameObject::GetTags() const
	{
		return myTags;
	}
}

