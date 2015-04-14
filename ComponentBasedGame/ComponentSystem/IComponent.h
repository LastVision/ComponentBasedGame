#pragma once

namespace ComponentSystem
{
	class GameObject;
	typedef unsigned int Priority;

	class IComponent
	{
	public:
		IComponent(GameObject& aOwner);
		~IComponent();

		virtual void Update(const float aDeltaTime) = 0;

		inline const Priority GetPriority() const;
		inline const bool GetIsActive() const;
		virtual inline void SetActiveStatus(const bool aStatus);
	protected:
		Priority myPriority;
		GameObject* myOwner;
		bool myIsActive;
	};

	const Priority IComponent::GetPriority() const
	{
		return myPriority;
	}

	const bool IComponent::GetIsActive() const
	{
		return myIsActive;
	}

	void IComponent::SetActiveStatus(const bool aStatus)
	{
		myIsActive = aStatus;
	}
};
namespace CS = ComponentSystem;
