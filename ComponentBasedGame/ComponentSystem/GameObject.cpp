#include "GameObject.h"
#include "DL_Debug.h"

namespace ComponentSystem
{
	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::AddComponent(IComponent* aComponent, eComponentType aComponentType)
	{
		myComponentsMap[aComponentType] = aComponent;

		for (int i = 0; i < myComponents.Size(); ++i)
		{
			if (aComponent->GetPriority() < myComponents[i]->GetPriority())
			{
				myComponents.Insert(i, aComponent);
				return;
			}
		}

		myComponents.Add(aComponent);
	}

	void GameObject::Update(const float aDeltaTime)
	{
		for (int i = 0; i < myComponents.Size(); ++i)
		{
			if (myComponents[i]->GetIsActive() == false) continue;

			myComponents[i]->Update(aDeltaTime);
		}
	}


}
