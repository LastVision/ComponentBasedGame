#pragma once
#include "IComponent.h"

enum class eDirection
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE
};

namespace ComponentSystem
{
	class EnemyAIComponent : public IComponent
	{
	public:
		EnemyAIComponent(GameObject& aOwner);
		~EnemyAIComponent();

		void Update(const float aDelta) override;
		void HandleCollision();

	private:
		eDirection myDirection;
	};
};

