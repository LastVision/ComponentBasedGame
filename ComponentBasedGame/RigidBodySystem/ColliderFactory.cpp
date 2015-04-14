#include "ColliderFactory.h"
#include "RectangleCollider.h"
#include "CircleCollider.h"

namespace RigidBodySystem
{
	ColliderFactory::ColliderFactory()
	{
	}


	ColliderFactory::~ColliderFactory()
	{
	}

	ICollider* ColliderFactory::CreateRectangleCollider(const CU::Vector2<float>& aTopLeft, const CU::Vector2<float>& aSize)
	{
		return  new RectangleCollider(aTopLeft, aSize);
	}
	ICollider* ColliderFactory::CreateRectangleCollider(const CU::Vector4<float>& aRect)
	{
		return new RectangleCollider(aRect);
	}

	ICollider* ColliderFactory::CreateCircleCollider(const CU::Vector2<float>& aCenterPosition, const float aRadius)
	{
		return new CircleCollider(aCenterPosition, aRadius);
	}
	ICollider* ColliderFactory::CreateCircleCollider(const CU::Vector3<float>& aCircle)
	{
		return new CircleCollider(aCircle);
	}
};
