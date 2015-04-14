#pragma once

#include "Vector.h"

namespace RigidBodySystem
{
	class ICollider;

	class ColliderFactory
	{
	public:
		ColliderFactory();
		~ColliderFactory();

		ICollider* CreateRectangleCollider(const CU::Vector2<float>& aTopLeft, const CU::Vector2<float>& aSize);
		ICollider* CreateRectangleCollider(const CU::Vector4<float>& aRect);
		ICollider* CreateCircleCollider(const CU::Vector2<float>& aCenterPosition, const float aRadius);
		ICollider* CreateCircleCollider(const CU::Vector3<float>& aCircle);
	};
};