#pragma once
#include "IComponent.h"
#include "Vector.h"

namespace ComponentSystem
{
	class PositionComponent : public IComponent
	{
	public:
		PositionComponent(GameObject& aOwner, const CU::Vector2<float>& aStartPosition);
		~PositionComponent();

		void Update(const float aUpdate) override;

		inline void SetPosition(const CU::Vector2<float>& aPosition);
		inline const CU::Vector2<float>& GetPosition() const;
		inline const CU::Vector2<float>& GetLastPosition() const;

	private:
		CU::Vector2<float> myPosition;
		CU::Vector2<float> myLastPosition;
	};

	inline void PositionComponent::SetPosition(const CU::Vector2<float>& aPosition)
	{
		myLastPosition = myPosition;
		myPosition = aPosition;
	}

	inline const CU::Vector2<float>& PositionComponent::GetPosition() const
	{
		return myPosition;
	}

	inline const CU::Vector2<float>& PositionComponent::GetLastPosition() const
	{
		return myLastPosition;
	}
}
