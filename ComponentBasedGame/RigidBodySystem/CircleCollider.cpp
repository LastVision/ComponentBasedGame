#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "RigidBody.h"
#include "Utilities.h"

#include "..\HGE_BasicProject\Rendering\Renderer.h"

namespace RigidBodySystem
{
	CircleCollider::CircleCollider()
	{
	}

	CircleCollider::CircleCollider(const CU::Vector3<float>& aCircle)
	{
		myCircle = aCircle;
		myOffset.x = myCircle.x;
		myOffset.y = myCircle.y;
	}

	CircleCollider::CircleCollider(const CU::Vector2<float>& aCenter, float aRadius)
	{
		myCircle.x = aCenter.x;
		myCircle.y = aCenter.y;
		myCircle.z = aRadius;

		myOffset = aCenter;
	}

	CircleCollider::~CircleCollider()
	{
	}

	void CircleCollider::UpdatePositions(const CU::Vector2<float>& aPosition)
	{
		myCircle.x = aPosition.x + myCircle.z + myOffset.x;
		myCircle.y = aPosition.y + myCircle.z + myOffset.y;
	}

	void CircleCollider::Render()
	{
		Renderer::GetInstance()->RenderCircle({ myCircle.x, myCircle.y }, myCircle.z, 8);
	}


	bool CircleCollider::CheckCollision(const ICollider* aCollider) const
	{
		return aCollider->CheckCircleCollision(this);
	}

	bool CircleCollider::CheckRigidBodyCollision(const RigidBody* aRigidBody) const
	{
		for (int i = 0; i < aRigidBody->GetColliders().Size(); ++i)
		{
			if (aRigidBody->GetColliders()[i]->CheckCircleCollision(this) == true)
				return true;
		}

		return false;
	}

	bool CircleCollider::CheckRectangleCollision(const RectangleCollider* aRectangle) const
	{
		/*

		http://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection

		*/

		float closestX = CU::Clamp(myCircle.x, aRectangle->GetLeft(), aRectangle->GetRight());
		float closestY = CU::Clamp(myCircle.y, aRectangle->GetTop(), aRectangle->GetBottom());

		float distanceX = myCircle.x - closestX;
		float distanceY = myCircle.y - closestY;

		float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

		return distanceSquared < (myCircle.z * myCircle.z);
	}

	bool CircleCollider::CheckCircleCollision(const CircleCollider* aCircle) const
	{
		float distance = CU::Length(CU::Vector2<float>(myCircle.x - aCircle->myCircle.x, myCircle.y - aCircle->myCircle.y));

		return (distance < aCircle->myCircle.z + myCircle.z);
	}
};