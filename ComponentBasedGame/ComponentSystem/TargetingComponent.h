#pragma once
#include "IComponent.h"
#include "GrowingArray.h"

namespace ComponentSystem
{
	class TargetingComponent : public IComponent
	{
	public:
		TargetingComponent(GameObject &aOwner, CU::GrowingArray<GameObject*, int> &aGameObjects, const float aRange, const int aTargetingTags);
		~TargetingComponent();

		virtual void Update(const float aDelta) override;

		inline const float GetRange() const;
		inline const int GetTargetingTags() const;

	private:
		void operator=(const TargetingComponent& aComponent);

		CU::GrowingArray<GameObject*, int>& myTargets;
		GameObject* myCurrentTarget;
		float myRange;
		int myTargetingTags;
	};

	inline const float TargetingComponent::GetRange() const
	{
		return myRange;
	}

	inline const int TargetingComponent::GetTargetingTags() const
	{
		return myTargetingTags;
	}
};
