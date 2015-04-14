#include "RectangleCollider.h"
#include "CircleCollider.h"
#include "RigidBody.h"
#include "Utilities.h"

#include "..\HGE_BasicProject\Rendering\Renderer.h"


#define TOP_LEFT { myRect.x, myRect.y }
#define TOP_RIGHT { myRect.x + myRect.z, myRect.y }
#define BOTTOM_RIGHT { myRect.x + myRect.z, myRect.y + myRect.w }
#define BOTTOM_LEFT { myRect.x, myRect.y + myRect.w}

namespace RigidBodySystem
{
	RectangleCollider::RectangleCollider()
	{
	}

	RectangleCollider::RectangleCollider(const CU::Vector2<float>& aTopLeft, const CU::Vector2<float>& aSize)
	{
		myOffset = aTopLeft;
		myRect.x = aTopLeft.x;
		myRect.y = aTopLeft.y;
		myRect.z = aSize.x;
		myRect.w = aSize.x;
	}

	RectangleCollider::RectangleCollider(const CU::Vector4<float>& aRect)
	{
		myRect = aRect;
	}


	RectangleCollider::~RectangleCollider()
	{
	}

	void RectangleCollider::UpdatePositions(const CU::Vector2<float>& aPosition)
	{
		myRect.x = aPosition.x + myOffset.x;
		myRect.y = aPosition.y + myOffset.x;
	}

	void RectangleCollider::Render()
	{
		Renderer::GetInstance()->RenderLine(TOP_LEFT, TOP_RIGHT);
		Renderer::GetInstance()->RenderLine(TOP_RIGHT, BOTTOM_RIGHT);
		Renderer::GetInstance()->RenderLine(BOTTOM_RIGHT, BOTTOM_LEFT);
		Renderer::GetInstance()->RenderLine(BOTTOM_LEFT, TOP_LEFT);
	}

	bool RectangleCollider::CheckCollision(const ICollider* aCollider) const
	{
		return aCollider->CheckRectangleCollision(this);
	}

	bool RectangleCollider::CheckRigidBodyCollision(const RigidBody* aRigidBody) const
	{
		for (int i = 0; i < aRigidBody->GetColliders().Size(); ++i)
		{
			if (aRigidBody->GetColliders()[i]->CheckRectangleCollision(this) == true)
				return true;
		}

		return false;
	}

	bool RectangleCollider::CheckRectangleCollision(const RectangleCollider* aRectangle) const
	{
		/*

		http://studiofreya.com/3d-math-and-physics/simple-aabb-vs-aabb-collision-detection/

		*/

		CU::Vector2<float> myCenter(myRect.x + myRect.z / 2.f, myRect.y + myRect.w / 2.f);
		CU::Vector2<float> otherCenter(aRectangle->myRect.x + aRectangle->myRect.z / 2.f, aRectangle->myRect.y + aRectangle->myRect.w / 2.f);

		if (abs(myCenter.x - otherCenter.x) > (myRect.z / 2.f + aRectangle->myRect.z / 2.f)) return false;
		if (abs(myCenter.y - otherCenter.y) > (myRect.w / 2.f + aRectangle->myRect.w / 2.f)) return false;

		return true;
	}

	bool RectangleCollider::CheckCircleCollision(const CircleCollider* aCircle) const
	{
		float closestX = CU::Clamp(aCircle->GetCenterPosition().x, GetLeft(), GetRight());
		float closestY = CU::Clamp(aCircle->GetCenterPosition().y, GetTop(), GetBottom());

		float distanceX = aCircle->GetCenterPosition().x - closestX;
		float distanceY = aCircle->GetCenterPosition().y - closestY;

		float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

		return distanceSquared < (aCircle->GetRadius() * aCircle->GetRadius());
	}
};
