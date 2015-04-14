#pragma once

#include "Vector.h"

namespace RigidBodySystem
{
	class RectangleCollider;
	class CircleCollider;
	class RigidBody;

	class ICollider
	{
	public:
		ICollider();
		~ICollider();

		virtual void UpdatePositions(const CU::Vector2<float>& aPosition) = 0;
		virtual void Render() = 0;

		virtual bool CheckCollision(const ICollider* aCollider) const = 0;
		virtual bool CheckRigidBodyCollision(const RigidBody* aCollider) const = 0;
		virtual bool CheckRectangleCollision(const RectangleCollider* aRectangle) const = 0;
		virtual bool CheckCircleCollision(const CircleCollider* aCircle) const = 0;

		virtual inline const CU::Vector2<float> GetCenterPosition() const = 0;
		virtual inline const CU::Vector2<float> GetSize() const = 0;
	};
};
